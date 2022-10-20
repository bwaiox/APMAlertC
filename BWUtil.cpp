// BWUtil.cpp: implementation of the BWUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "APMAlert.h"
#include "BWUtil.h"
#include "Logger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BWUtil* BWUtil::g_util;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BWUtil::BWUtil()
{
	patchflag = false;
}

BWUtil::~BWUtil()
{
	for (std::vector<PatchedJmp*>::iterator it = m_patchedVec.begin();
		it != m_patchedVec.end(); it++)
	{
		delete[] (*it)->origMemory;
		delete[] (*it)->newMemory;
		delete *it;
	}
	for (std::vector<PatchedMem*>::iterator it2 = m_patchedMemVec.begin();
		it2 != m_patchedMemVec.end(); it2++)
		{
			delete[] (*it2)->origMemory;
			delete[] (*it2)->newMemory;
			delete *it2;
	}
}

BWUtil* BWUtil::getInst()
{
	if (!g_util)
		g_util = new BWUtil();
	return g_util;
}

void BWUtil::releaseInst()
{
	if (g_util)
	{
		delete g_util;
		g_util = NULL;
	}
}

void BWUtil::WriteMem(DWORD memOffset, DWORD dataptr, DWORD datalen)
{
	DWORD oldprot;
    //DWORD oldprot2;
	VirtualProtect((LPVOID)memOffset, datalen, PAGE_EXECUTE_READWRITE, &oldprot);
	//VirtualProtect((LPVOID)dataptr, datalen, PAGE_EXECUTE_READWRITE, &oldprot2);
	CopyMemory((LPVOID)memOffset, (LPVOID)dataptr, datalen);
	VirtualProtect((LPVOID)memOffset, datalen, oldprot, &oldprot);
	//VirtualProtect((LPVOID)dataptr, datalen, oldprot2, &oldprot2);
}

void BWUtil::CallOrJumpPatch(DWORD location, DWORD dst, byte flag)
{
	unsigned char * ddd = new unsigned char[5];
	ddd[0] = flag; // call
	*((PDWORD)&ddd[1]) = (dst - location) - 5;
	WriteMem(location, (DWORD)ddd, 5);
	delete[] ddd;
    ddd = NULL;
}

void BWUtil::AddPatch2(DWORD dAddr, DWORD dJmpTo, byte exxarg, int whenrun)
{
    int needmem = 2 + 5 + 5 + 5; // pushad popad, call myfunction, jmp orgin dst, jmp after origin function
    if (exxarg > 0) 
    {
        needmem += 1;// push ebx
    }

    PatchedJmp* p = new PatchedJmp();
    p->addr = dAddr;
    p->jmpTo = dJmpTo;
    p->origMemory = new byte[5];
    p->newMemory = new byte[needmem];
    memset(p->newMemory, 0x90, needmem); // fill with nop
    DWORD oldprot;
    VirtualProtect((LPVOID)p->newMemory, needmem, PAGE_EXECUTE_READWRITE, &oldprot);
    for (int i = 0; i < 5; i++)
    {
        // ±£´æÇ°5¸öbyte
        p->origMemory[i] = *(byte*)(dAddr + i);
        p->newMemory[i] = p->origMemory[i];
    }
    CLogger::getinstance()->log("AddPatch2 %#x -> %#x  originext%#x", p->addr, p->jmpTo, p->addr + 5);

    DWORD arrpos = 0;
    //handle redirecting jmps/calls
    if (whenrun == 1)
    {
        if (p->origMemory[0] == 0xE8 || p->origMemory[0] == 0xE9)
        {
            p->newMemory[arrpos] = p->origMemory[0];
            DWORD oldtarget = *(DWORD*)(&p->origMemory[1]);// old offset
            oldtarget += p->addr + 5; // old target
            *(DWORD*)(&p->newMemory[arrpos + 1]) = (oldtarget - (DWORD)(&p->newMemory[arrpos])) - 5;
            arrpos += 5;
        }
    }
    CLogger::getinstance()->log("AddPatch2 1 %#x -> %#x, %d", p->addr, p->jmpTo, arrpos);
    
    DWORD pushad = 0x60;
    p->newMemory[arrpos++] = pushad;
    
    // ebx
    if (exxarg > 0)
        p->newMemory[arrpos++] = exxarg;
    
    CallOrJumpPatch((DWORD)&p->newMemory[arrpos], p->jmpTo, 0xE8); // Call our hooking function    
    arrpos += 5;
    CLogger::getinstance()->log("AddPatch2 2 %#x -> %#x, %d", p->addr, p->jmpTo, arrpos);

    DWORD popad = 0x61;
    p->newMemory[arrpos++] = popad;

    if (whenrun == 2)
    {
        if (p->origMemory[0] == 0xE8 || p->origMemory[0] == 0xE9)
        {
            p->newMemory[arrpos] = p->origMemory[0];
            DWORD oldtarget = *(DWORD*)(&p->origMemory[1]);// old offset
            oldtarget += p->addr + 5; // old target
            *(DWORD*)(&p->newMemory[arrpos + 1]) = (oldtarget - (DWORD)(&p->newMemory[arrpos])) - 5;
            arrpos += 5;
        }
    }
    
    CallOrJumpPatch((DWORD)&p->newMemory[arrpos], p->addr + 5, 0xE9); // Jump back right past where we overwrite
    arrpos += 5;
    CLogger::getinstance()->log("AddPatch2 2 %#x -> %#x, %d", p->addr, p->jmpTo, arrpos);

	m_patchedVec.push_back(p);

}

void BWUtil::AddPatchMem(DWORD dAddr, byte* newMem, int memLength)
{
	PatchedMem* p = new PatchedMem();
	p->addr = dAddr;
	p->memLength = memLength;
	p->newMemory = new byte[memLength];
	int i;
	for (i = 0; i < memLength; i++)
		p->newMemory[i] = newMem[i];
	
	p->origMemory = new byte[memLength];
	for (i = 0; i < memLength; i++)
		p->origMemory[i] = *(byte*)(p->addr + i);
	
    m_patchedMemVec.push_back(p);
}

void BWUtil::Patch()
{
	const byte Nop = 0x90;
	int i=0;
	std::vector<PatchedJmp*>::iterator it;
	for (it = m_patchedVec.begin(); it != m_patchedVec.end(); it++)
	{
		CallOrJumpPatch((*it)->addr, (DWORD)(*it)->newMemory, 0xE9);
		for (i = 0; i < (*it)->numNops; i++)
		{
			WriteMem((*it)->addr + 5 + i, (DWORD)&Nop, 1);
		}
	}

	std::vector<PatchedMem*>::iterator it2;
	for (it2 = m_patchedMemVec.begin(); it2 != m_patchedMemVec.end(); it2++)
	{
        DWORD t = (DWORD)&(*it2)->newMemory;
        DWORD t2 = (DWORD)&(*it2)->newMemory[0];
		WriteMem((*it2)->addr, (DWORD)&(*it2)->newMemory[0], (*it2)->memLength);
	}
	patchflag = true;
    CLogger::getinstance()->log("Patched game");
}

void BWUtil::UnPatch()
{
	int i=0;
	std::vector<PatchedJmp*>::iterator it;
	for (it = m_patchedVec.begin(); it != m_patchedVec.end(); it++)
	{
		WriteMem((*it)->addr, (DWORD)(*it)->origMemory, 5 + (*it)->numNops);
	}
	
	std::vector<PatchedMem*>::iterator it2;
	for (it2 = m_patchedMemVec.begin(); it2 != m_patchedMemVec.end(); it2++)
	{
		WriteMem((*it2)->addr, (DWORD)&(*it2)->origMemory, (*it2)->memLength);
	}
	patchflag = false;
	CLogger::getinstance()->log("UnPatched game");
}


void BWCenteredTextOut(char * text)
{
    __asm {
        pushad
            mov esi, [text]
            mov eax, -1
            push 0h
            push esi
            mov esi, BWFXN_CTEXTOUT
            call esi
            popad
    }
}

void BWTextOut(char * text)
{
    __asm {
        pushad
            xor eax, eax
            mov edi, text
            mov esi, BWFXN_TEXTOUT
            call esi
            popad
    }
}

void BWDrawBox(DWORD x, DWORD y, DWORD w, DWORD h, byte clr)
{
    __asm {
        pushad
            mov cl, clr
            mov eax, BOX_COLOR
            mov byte ptr ds:[eax], cl
            push h
            push w
            push y
            push x
            mov esi, BWFXN_DRAWBOX
            call esi
            popad
    }
}

void BWDrawTransparentBox(unsigned int x, unsigned int y, unsigned int w, unsigned int h, byte midclr)
{
    bool bDraw = true;
    for(unsigned int i = y; i < y+h; i++) {
        for(unsigned int z = x; z < x+w; z++) {
            if(bDraw)
                BWDrawBox(z,i,1,1,midclr);
            bDraw = !bDraw;
        }
        if(w % 2 == 0)
            bDraw = !bDraw;
    }
}

void BWDrawPixel(DWORD x, DWORD y, byte clr)
{
    __asm {
        pushad
            mov cl, clr
            mov eax, BOX_COLOR
            mov byte ptr ds:[eax], cl
            push 1
            push 1
            push y
            push x
            mov esi, BWFXN_DRAWBOX
            call esi
            popad
    }
}

void BWDrawText(DWORD x, DWORD y, char * text)
{
    __asm {
        pushad
            mov eax, [text]
            mov esi, x
            push y
            mov ecx, BWFXN_DRAWTEXT
            call ecx
        popad
    }
}

void BWPlaySound(DWORD sound)
{
    __asm {
        pushad
            push 0
            push 0
            push 20
            push sound
            mov eax, BWFXN_PLAYSOUND
            call eax
            popad
    }
}

void BWRestoreTextFormat(DWORD storedFormat)
{
    __asm {
        pushad
            mov ecx, storedFormat
            mov eax, BWFXN_FORMATTEXT
            call eax
            popad
    }
}


void BWFormatText(DWORD format)
{
    __asm {
        pushad
            cmp format, 0
            jnz PtrLoad
            xor ecx, ecx
            jmp FuncCall
PtrLoad:
        mov eax, dword ptr ss: [format]
            mov ecx, dword ptr ds: [eax]
FuncCall:
        mov edx, BWFXN_FORMATTEXT
            call edx
            popad
    }
}
void BWFormatTextR(DWORD format)
{
    BWFormatText(BWTF_RESET);
    BWFormatText(format);
}

void BWDrawFormattedText(DWORD x, DWORD y, char * text, DWORD format)
{
    BWFormatTextR(format);
    BWDrawText(x, y, text);
}

void BWRefreshText(DWORD x, DWORD y, DWORD x2, DWORD y2) 
{
    __asm {
        pushad
            push x2
            mov eax, x
            mov ecx, y
            mov edx, y2
            mov esi, BWFXN_REFRESHTEXT
            call esi
            popad
    }
}

/*
// NOTE: This will oddly actually draw the string, which is not what we want
function BWGetTextRect(x, y: DWORD; str: PChar): TRect; stdcall;
begin
  asm
    pushad
    push ecx
    lea ecx,[esp]
    push ecx
    mov eax, [Offsets.TextRectX]
    mov edi, x
    mov dword ptr [eax],edi
    mov eax, [Offsets.TextRectY]
    mov edi, y
    mov dword ptr [eax],edi
    mov eax,[str]
    call dword ptr [Offsets.BWFXN_GetTextRect]
    pop ecx
    popad
  end;
  Result.Left := (Integer(Word(Pointer(Offsets.TextRectLeft)^)));
  Result.Top := (Integer(Word(Pointer(Offsets.TextRectTop)^)));
  Result.Right := (Integer(Word(Pointer(Offsets.TextRectRight)^)));
  Result.Bottom := (Integer(Word(Pointer(Offsets.TextRectBottom)^)));
end;
*/
// not gonna implement this, not used ever

/*
function BWGetTextWidth(str: PChar): Integer; stdcall;
begin
  asm
    pushad
    mov ecx, [Offsets.TextWidth]
    mov dword ptr ds:[ecx],0
    mov eax, [str]
    call dword ptr [Offsets.BWFXN_GetTextWidth]
    popad
  end;
  Result := (PInteger(Offsets.TextWidth))^;
end;
*/
int BWGetTextWidth(char * text)
{
	__asm {
		pushad
		mov ecx, TEXT_WIDTH
		mov dword ptr ds:[ecx], 0
		mov eax, [text]
		mov edx, BWFXN_GETTEXTWIDTH
		call edx
		popad
	}
	
	return *(int *)(TEXT_WIDTH);
}

void __stdcall BWSetFontFunc(DWORD font)
{
    

}
void __stdcall DrawTextFunc(DWORD y)
{

}
