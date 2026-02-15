// The code here is so fucking mess

#pragma warning(disable : 6011)

#include <Windows.h>

#include <base_feature.h>
#include <dbg.h>

#include <ISvenModAPI.h>
#include <IMemoryUtils.h>

#include "../patterns.h"
#include "../game/utils.h"

//-----------------------------------------------------------------------------
// Patches module feature
//-----------------------------------------------------------------------------

class CPatchesModule : public CBaseFeature
{
public:
	CPatchesModule();

	virtual bool Load();
	virtual void PostLoad();

	virtual void Unload();
};

//-----------------------------------------------------------------------------
// Patches module feature impl
//-----------------------------------------------------------------------------

CPatchesModule::CPatchesModule()
{
}

bool CPatchesModule::Load()
{
	ud_t inst;

	void *pNextCmdTime = MemoryUtils()->FindPattern( SvenModAPI()->Modules()->Hardware, Patterns::Hardware::flNextCmdTime );

	if ( !pNextCmdTime )
	{
		Warning("Cannot locate flNextCmdTime\n");
		return false;
	}

	void *pTextureLoadAddress = MemoryUtils()->FindString( SvenModAPI()->Modules()->Hardware, "Texture load: %6.1fms" );

	if ( !pTextureLoadAddress )
	{
		Warning("Cannot locate \"Texture load\" string\n");
		return false;
	}

	void *pTextureLoad = MemoryUtils()->FindAddress( SvenModAPI()->Modules()->Hardware, pTextureLoadAddress );

	if ( !pTextureLoad )
	{
		Warning("Cannot locate \"Texture load\" address\n");
		return false;
	}

	// g_dbGameSpeed
	MemoryUtils()->InitDisasm(&inst, (BYTE *)pTextureLoad - 0xA, 32, 15);
	MemoryUtils()->Disassemble(&inst);

	if (inst.mnemonic == UD_Ifmul && inst.operand[0].type == UD_OP_MEM)
	{
		g_dbGameSpeed = reinterpret_cast<double *>(inst.operand[0].lval.udword);
	}
	else
	{
		Warning("Cannot locate g_dbGameSpeed\n");
		return false;
	}

	// g_flNextCmdTime
	MemoryUtils()->InitDisasm(&inst, (BYTE *)pNextCmdTime, 32, 15);
	MemoryUtils()->Disassemble(&inst);

	if (inst.mnemonic == UD_Ifstp && inst.operand[0].type == UD_OP_MEM)
	{
		g_flNextCmdTime = reinterpret_cast<float *>(inst.operand[0].lval.udword);
	}
	else
	{
		Warning("Cannot locate flNextCmdTime #2\n");
		return false;
	}
	
	// dbRealtime
	MemoryUtils()->InitDisasm(&inst, (BYTE *)g_pEngineFuncs->pNetAPI->SendRequest + 0x88, 32, 15);
	MemoryUtils()->Disassemble(&inst);

	if (inst.mnemonic == UD_Ifld && inst.operand[0].type == UD_OP_MEM)
	{
		dbRealtime = reinterpret_cast<double *>(inst.operand[0].lval.udword);
	}
	else
	{
		Warning("Cannot locate dbRealtime\n");
		return false;
	}

	int dwProtection;
	MemoryUtils()->VirtualProtect(g_dbGameSpeed, sizeof(double), PAGE_EXECUTE_READWRITE, &dwProtection);

	return true;
}

void CPatchesModule::PostLoad()
{
}

void CPatchesModule::Unload()
{
	UTIL_SetGameSpeed(1.0);
	UTIL_SendPacket(true);
}

//-----------------------------------------------------------------------------
// Create singleton
//-----------------------------------------------------------------------------

CPatchesModule g_PatchesModule;
