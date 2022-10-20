// BWUtil.h: interface for the BWUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BWUTIL_H__2A10A8CE_0625_410B_A49F_E00514C2B09A__INCLUDED_)
#define AFX_BWUTIL_H__2A10A8CE_0625_410B_A49F_E00514C2B09A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define V1161

#ifdef V1161
	#define IN_REPLAY				0x006D0F14 // Byte -- Need to use this with InGame to determine
	#define IN_GAME					0x006D11EC // Byte
	#define IN_DEBRIEFING_ROOM		0x006D63C0 // Byte, = 1 if they're currently viewing the 'scores room' after the game
	#define MAP_FILE_PATH			0x0057FD3C // string
	#define SAVED_REP_NAME			0x0051BFB8 // string, contains name used in rep saving without '.rep'
	#define GAME_TIME				0x0057F23C // Dword
	#define REP_SPEED				0x006CDFD4 // byte, 6 for fastest
	#define REP_SPEED_MULTIPLIER	0x0050E058 // byte, x2 = 2, x4 = 4, etc.
	#define REP_SPEED_TIMING		0x005124F0 // byte, stores time for each frame, 42ms for fastest
	#define REP_PAUSED				0x006D11B0 // Byte
	#define GAME_PAUSED				0x006509C4 // Byte
	#define GAME_COMPLETE_DIALOG	0x00685178 // Byte, tells whether the "Exit Replay"/"Continue Playing" dlg is up
	#define GAME_DIGITAL_VOLUME		0x006CDFE4 // Byte, 0-100 for percent volume
	#define TICK_TIME_TABLE			0x005124D8 // Table of DWords giving actual timings for speeds <= Fastest (Dwords)
	#define REP_SELECTED_PLAYER		0x005153F8 // -1 if nothing is selected, otherwise player #
	#define PLAYER_NAMES			0x0057EEEB // 36 Bytes per player, first 24 are the string
	#define BUILDINGS_CONTROLLED	0x00581F34 // DW, +4*Player
	#define POPULATION				0x00581E14 // DW, +4*Player
	#define MINERALS				0x0057F0F0 //DW, +4*Player
	#define VESPENE					0x0057F120 //DW, +4*Player
	#define MY_PLAYER_NUM			0x00512684 // Current Player's number
	#define CURSOR_X				0x006CDDC4 // DW, X coord of the mouse cursor ingame
	#define CURSOR_Y				0x006CDDC8 // DW, Y coord of the mouse cursor ingame
	#define PLAYER_COLORS			0x00581DD6 // array of player colors
	#define CUR_TEXT_FORMAT			0x006D5DDC // DW, the current font the text is in
	#define BWTF_RESET				0x00000000
	#define BWTF_ULTRALARGE			0x006CE100
	#define BWTF_LARGE				0x006CE0FC
	#define BWTF_NORMAL				0x006CE0F8
	#define BWTF_MINI				0x006CE0F4
	#define BOX_COLOR				0x006CF4AC // where to store the color when using the box drawing function
	#define TEXT_RECT_X				0x006CE108 // what x to use when checking text rect
	#define TEXT_RECT_Y				0x006CE0E0 // what y to use when checking text rect
	#define TEXT_RECT_LEFT			0x006CE0D8 // the left value returned by GetTextRect
	#define TEXT_RECT_TOP			0x006CE0DA // the top value returned by GetTextRect
	#define TEXT_RECT_RIGHT			0x006CE0DC // the right value returned by GetTextRect
	#define TEXT_RECT_BOTTOM		0x006CE0DE // the bottom value returned by GetTextRect
	#define TEXT_WIDTH				0x006CE108 // the width of the text in the current font (GetTextWidth)
	#define SEND_ACTION_PNUM		0x0051267C // the player number in the SendAction function
    #define MY_PLAYER_ID            0x00512688

	//functions
	#define BWFXN_CTEXTOUT			0x0048D1C0 // Centered TextOut
	#define BWFXN_TEXTOUT			0x0048D0C0 // TextOut
	#define BWFXN_DRAWBOX			0x004E1D20 // Box drawing function
	#define BWFXN_DRAWTEXT			0x004202B0 // Draw text at x,y
	#define BWFXN_FORMATTEXT		0x0041FB30 // Format text with specified font
	#define BWFXN_REFRESHTEXT		0x0041E0D0 // Refresh text in a portion of the screen
	#define BWFXN_GETTEXTRECT		0x004200D0 // Get the rect of the text in the current font
	#define BWFXN_GETTEXTWIDTH		0x0041F920 // Get the width of the text in the current font
	#define BWFXN_SETSPEED			0x004DEB90 // Set The Replay Speed

	#define BWFXN_PLAYSOUND			0x004BC270 // Play the specified sound
    #define BWFXN_REFGAMELAYER      0x004BD350 // refresh screen

	// Hooks

    #define HOOK_DRAW               0x0048CF6D


    #define HOOK_SEND_ACTION          0x00486D8B
    #define HOOK_REFRESH_SCREEN     0x004D98DE


	// Patches
	#define PTCH_TEXTREFRESH1		0x0047F26C
	#define PTCH_TEXTREFRESH2		0x0047F120
#endif

#include <vector>

typedef struct PatchedJmp{
	DWORD addr;
	DWORD jmpTo;
	int numNops;
	byte* origMemory;
	byte* newMemory;
}PatchedJmp,* PPatchedJmp;

typedef struct PatchedMem{
	DWORD addr;
	int memLength;
	byte* origMemory;
	byte* newMemory;
}PatchedMem, * PPatchedMem;

void BWCenteredTextOut(char * text);
void BWTextOut(char * text);
void BWDrawBox(DWORD x, DWORD y, DWORD w, DWORD h, byte clr);
void BWDrawTransparentBox(unsigned int x, unsigned int y, unsigned int w, unsigned int h, byte midclr);
void BWDrawPixel(DWORD x, DWORD y, byte clr);
void BWDrawText(DWORD x, DWORD y, char * text);
void BWPlaySound(DWORD sound);
void BWRestoreTextFormat(DWORD storedFormat);
void BWFormatText(DWORD format);
void BWFormatTextR(DWORD format);
void __stdcall BWSetFontFunc(DWORD font);
void __stdcall DrawTextFunc(DWORD y);
void BWDrawFormattedText(DWORD x, DWORD y, char * text, DWORD format);
void BWRefreshText(DWORD x, DWORD y, DWORD x2, DWORD y2);
// RECT BWGetTextRect(DWORD x, DWORD y, char * str);
int BWGetTextWidth(char * text);

typedef bool(__cdecl* reffunctype)();

class BWUtil
{
public:
    bool IsInReplay() {return *(bool*)IN_REPLAY;}
    bool IsInGame() {return *(bool*)IN_GAME;}
    bool IsPaused() {return *(bool*)GAME_PAUSED || *(bool*)REP_PAUSED;}
    UINT32 GetMyPlayerID(){return *(UINT32*)MY_PLAYER_ID;};
    void RefScreen() {((reffunctype)BWFXN_REFGAMELAYER)(); }
    UINT32 GetSendActionPlayerID(){return *(UINT32*)SEND_ACTION_PNUM;};
    UINT32 GetBuildingsControlled(UINT32 playerid) {return ((UINT32*)BUILDINGS_CONTROLLED)[playerid];};
    UINT32 GetPopulation(UINT32 playerid){return ((UINT32*)POPULATION)[playerid];};
    UINT32 GetMinerals(UINT32 playerid){return ((UINT32*)MINERALS)[playerid];};
    UINT32 GetVespene(UINT32 playerid){return ((UINT32*)VESPENE)[playerid];};
    std::string GetPlayerName(UINT32 playerid){
        char buff[24];
        memset(buff, 0, 24);
        memcpy(buff, (void*)(PLAYER_NAMES + 36 * playerid), 24);
        return std::string(buff);
    };
    byte GetPlayerColor(UINT32 playerid) {
        return ((byte*)PLAYER_COLORS)[playerid];
    };
    bool IsObserver(UINT32 playerid)
    {
        UINT32 buildnum = GetBuildingsControlled(playerid);
        UINT32 popnum = GetPopulation(playerid);
        UINT32 minnum = GetMinerals(playerid);
        UINT32 vesnum = GetVespene(playerid);
        bool obsums = buildnum <= 1 && popnum <=2 && minnum <= 50 && vesnum == 0;
        bool almostdeadobs = buildnum <= 1 && popnum == 0;
        return obsums || almostdeadobs;
    };

    bool IsInObsMode(){
        UINT32 playerid = GetSendActionPlayerID();
        if (playerid == 0xffffffff)
            return IsInReplay();
        else
        {
            if (IsInReplay())
                return true;
            return IsObserver(playerid);
        }
    };
    DWORD GameTime() { return *(DWORD*)GAME_TIME;};
	static BWUtil* getInst();
	static void releaseInst();

	BWUtil();
	virtual ~BWUtil();
	void Patch();
	void UnPatch();
	void CallOrJumpPatch(DWORD location, DWORD dst, byte flag);
    void WriteMem(DWORD memOffset, DWORD dataptr, DWORD datalen);
    void AddPatch2(DWORD dAddr, DWORD dJmpTo, byte exxarg, int whenrun);
	void AddPatchMem(DWORD dAddr, byte* newMem, int memLength);
	std::vector<PatchedJmp*> m_patchedVec;
	std::vector<PatchedMem*> m_patchedMemVec;

	static BWUtil* g_util;
private:
	bool patchflag;
};







#endif // !defined(AFX_BWUTIL_H__2A10A8CE_0625_410B_A49F_E00514C2B09A__INCLUDED_)
