#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/socket.h>
#include <malloc.h>
#include <math.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <locale>
#include <string>
#include <codecvt>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "ImguiPP.h"
#include "Includes/obfuscate.h"
#include "fake_dlfcn.h"
#include "plthook.h"
#include "json.hpp"
#include "StrEnc.h"
#include "Spoof.h"
#include "SDK.hpp"
#include "KittyMemory/MemoryPatch.h"
#include "Rect.h"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Macros.h"
#include "Substrate/SubstrateHook.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "foxcheats/include/ScanEngine.hpp"
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <cassert>
#include "icon.h"
#include "font.h"
#define _BYTE uint8_t
#define _WORD uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t
#define DefineHook(RET, NAME, ARGS) \
    RET(*Orig_##NAME)               \
    ARGS;                           \
    RET Hook_##NAME ARGS
    
