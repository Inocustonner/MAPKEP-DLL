#include <Windows.h>

#include <ios>					// for create console
#include <cstdio>				// for create console

#define CAVE void __declspec(naked)

int res;
HANDLE proc = GetCurrentProcess();
//DWORD base = (DWORD)GetExeModule(proc); // doesnt' work on winXP
DWORD base = 0x400000; // let's assume that it is always this num
DWORD sndFunc = base + 0x076C4;

bool CreateConsole()
{
    if (AllocConsole())
    {
        FILE* conin, * conout;
        freopen_s(&conin, "conin$", "r", stdin);
        freopen_s(&conout, "conout$", "w", stdout);
        freopen_s(&conout, "conout$", "w", stderr);

        std::ios::sync_with_stdio();

        return true;
    }
    else
    {
        return false;
    }
}

CAVE onButton()
{
  __asm
  {
    push ebp
    mov  ebp, esp

    //my insert
    pushad
    //my insert
  }
  res = MessageBoxW(NULL, 
    L"Вы уверены что хотите использовать активный джойстик?", 
    L"Подтверждение", 
    MB_YESNO | MB_ICONWARNING);

  if (res == IDYES)
  {
    res = MessageBoxW(NULL, 
      L"Вы ТОЧНО уверены хотите использовать активный джойстик?", 
      L"ТОЧНОЕ подтверждение", 
      MB_YESNO | MB_ICONWARNING);

    if (res == IDYES) {

      __asm
      {
        popad
        add esp, 0xFFFFFFF4

        mov BYTE PTR[ebp-9], cl
        mov DWORD PTR[ebp-8], edx
        mov DWORD PTR[ebp-4], eax
        push DWORD PTR[ebp-4]

        // my insert
        mov eax, sndFunc
        // my insert

        call eax
        pop ecx
      }
    }
  }
  
  __asm 
  {
    mov esp, ebp
    pop ebp
    retn 0Ch
  }
}


void *funcAddr = onButton;
void __declspec(dllexport) create_cave()
{
  int argc;
  wchar_t **argv = reinterpret_cast<wchar_t**>(CommandLineToArgvW(GetCommandLineW(), &argc));

  const wchar_t *debug_flag = L"-debugDll";
  bool debug = false;

  for (int i = 0; i < argc; ++i)
  {
    if (wcscmp(argv[i], debug_flag) == 0)
    {
      debug = true;
      break;
    }
  }

  

  BYTE jmp_addr[6] = { 0xff, 0x25 }; // jmp [funcAddr]
  *(DWORD*)(jmp_addr + 2) = (DWORD)&funcAddr;

  if (debug)
  {
    CreateConsole();
    printf("base: %x\n", base);
    printf("cave addr: %p\n", onButton);
    printf("bytes to be written: %X%X%X%X%X%X\n", 
            jmp_addr[0], 
            jmp_addr[1], 
            jmp_addr[2], 
            jmp_addr[3], 
            jmp_addr[4],
            jmp_addr[5]);
  }
  WriteProcessMemory(proc, (void*)(base + 0x0000AEC4), jmp_addr, sizeof jmp_addr, NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved)
{
  switch (ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
      create_cave();
      break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
