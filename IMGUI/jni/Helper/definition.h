

namespace Cheat {

    uintptr_t libUE4Base;
    uintptr_t GName_Offest = 0x6E069C0;
    uintptr_t GEngine_Offset = 0xBFBC508;
    uintptr_t GUObject_Offset = 0xBDB91E0;
    uintptr_t GNativeAndroidApp_Offset = 0xBB53E38;
    uintptr_t ActorArray_Offest = 0x876537c;
    uintptr_t ProcessEvent_Offset = 0x57E7DC8;
    uintptr_t ProcessEvent;
    int localPlayer_Offset = 0x8651A34;


    namespace Esp {
        bool Line = false;
        bool Skeleton = false;
        bool Health = false;
        bool Distance = false;
        bool Name = false;
        bool TeamID = false;
        bool Alert = false;
        bool OneClick = false;
        
      namespace Vehicle {      
         bool Name = false;
         bool Health = false;
         bool Fuel = false;
        
      }       
    }
    namespace BulletTrack {
        bool Enable;
        bool VisCheck;
        bool IgnoreKnock;
        bool IgnoreBot;
        bool AutoFire;
        bool AutoFireOff = false;
        float Range = 0;
        float AimSet = 0.0f;
        auto AimPrediction = 0;
        float Radius = 300.0f;
    }

    namespace Memory {
        bool HeadShot = false;
        bool HeadShotv1 = false;
        bool HeadShotv2 = false;
        bool HeadShotv3 = false;
        bool AutoFlash = false;
        bool AutoFlashOff = false;
        bool ManualFlash = false;
        bool ManualFlashOff = false;
        bool InstantHit = false;
        bool NoRecoil = false;
        bool WideView = false;
        bool XHitEffect = false;
        bool AutoParachute = false;
        bool SmallCrossHair = false;
        bool KnockSpeed = false;
        bool GodView = false;
        bool ShowDamage = false;
        bool NoTree = false;
        bool FastShoot = false;
        bool NoGrass = false;
        bool FixFlash = false;
        bool KillMessage = false;
        bool InstantHitv1 = false;
        float InstantHitSet = 1.0f;       
        float XHitEffectSize = 10.0f;
        float ControlSpeed = 0.100f;
        float SetView = 220.0f;
        float GameSpeed = 22.5f;
        float PlayerSpeed = 0.15f;
    }

}

#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))
#define DEG2RADD(x) ((float)(x) * (float)(IM_PI / 360.f))
#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)

using namespace SDK;
uintptr_t ProcessEvent;
bool BulletTrack = true;
using namespace SDK;

bool WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size),
                    (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 &&
           memcpy(addr, buffer, length) != 0;
}

template<typename T>
void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}

int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;

int Write_Float(long int addr, float value) {
    Tools::WriteAddr((void *) (addr), (void *) &value, 4);
    return 0;
}

FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName) {
    return Actor->GetBonePos(BoneName, FVector());
}


// Login && SDK Implement
bool initImGui;
bool bValid = false;
using json = nlohmann::json;
time_t rng = 0;
std::string g_Token, g_Auth;
pthread_t t;
android_app *g_App = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;

using namespace SDK;

struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isObjectInvalid(UObject *obj) {
    if (!Tools::IsPtrValid(obj)) {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate)) {
        return true;
    }

    if (obj->InternalIndex <= 0) {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0) {
        return true;
    }

    if ((uintptr_t) (obj) % sizeof(uintptr_t) != 0x0 &&
        (uintptr_t) (obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) {
        return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end;
    }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) {
            return ((uintptr_t) obj->ClassPrivate) >= region.start &&
                   ((uintptr_t) obj->ClassPrivate) <= region.end;
        })) {
        return true;
    }

    return false;
}

UWorld *GetWorld() {
    auto GEngine = *(UEngine **) (Cheat::libUE4Base + Cheat::GEngine_Offset);
    if (GEngine) {
        auto ViewPort = GEngine->GameViewport;
        if (ViewPort) {
            return ViewPort->World;
        }
    }
    return 0;
}

TNameEntryArray *GetGNames() {
    return ((TNameEntryArray *(*)()) (Cheat::libUE4Base + Cheat::GName_Offest))();
}

std::vector<AActor *> GetActors() {
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();

    struct GovnoArray {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };
    static thread_local GovnoArray Actors{};

    Actors = *(((GovnoArray *(*)(uintptr_t)) (Cheat::libUE4Base + Cheat::ActorArray_Offest))(
            reinterpret_cast<uintptr_t>(PersistentLevel)));

    if (Actors.count <= 0) {
        return {};
    }

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.count; i++) {
        auto Actor = *(uintptr_t *) (Actors.base + (i * sizeof(uintptr_t)));
        if (Actor) {
            actors.push_back(reinterpret_cast<AActor *const>(Actor));
        }
    }
    return actors;
}


template<class T>
void GetAllActors(std::vector<T *> &Actors) {
    UGameplayStatics *gGameplayStatics = (UGameplayStatics *) gGameplayStatics->StaticClass();
    auto GWorld = GetWorld();
    if (GWorld) {
        TArray<AActor *> Actors2;
        gGameplayStatics->GetAllActorsOfClass((UObject *) GWorld, T::StaticClass(), &Actors2);
        for (int i = 0; i < Actors2.Num(); i++) {
            Actors.push_back((T *) Actors2[i]);
        }
    }
}



std::string getClipboardText() {
    if (!g_App)
        return "";

    auto activity = g_App->activity;
    if (!activity)
        return "";

    auto vm = activity->vm;
    if (!vm)
        return "";

    auto object = activity->clazz;
    if (!object)
        return "";

    std::string result;

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    {
        auto ContextClass = env->FindClass("android/content/Context");
        auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService",
                                                       "(Ljava/lang/String;)Ljava/lang/Object;");
        auto str = env->NewStringUTF("clipboard");
        auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
        env->DeleteLocalRef(str);
        auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
        auto getText = env->GetMethodID(ClipboardManagerClass, "getText",
                                        "()Ljava/lang/CharSequence;");
        auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
        auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString",
                                               "()Ljava/lang/String;");
        auto text = env->CallObjectMethod(clipboardManager, getText);
        if (text) {
            str = (jstring) env->CallObjectMethod(text, toStringMethod);
            result = env->GetStringUTFChars(str, 0);
            env->DeleteLocalRef(str);
            env->DeleteLocalRef(text);
        }

        env->DeleteLocalRef(CharSequenceClass);
        env->DeleteLocalRef(ClipboardManagerClass);
        env->DeleteLocalRef(clipboardManager);
        env->DeleteLocalRef(ContextClass);
    }
    vm->DetachCurrentThread();

    return result;
}

const char *GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/
            StrEnc("`L+&0^[S+-:J^$,r9q92(as",
                   "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07",
                   23).c_str());
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/
                                                          StrEnc("E8X\\7r7ys_Q%JS+L+~",
                                                                 "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C",
                                                                 18).c_str(), /*()Landroid/content/ContentResolver;*/
                                                          StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L",
                                                                 "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77",
                                                                 35).c_str());
    jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/
            StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"",
                   "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47",
                   32).c_str());
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/
                                                       StrEnc("e<F*J5c0Y",
                                                              "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E",
                                                              9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/
                                                       StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H",
                                                              "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73",
                                                              71).c_str());

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj,
                                                     env->NewStringUTF(/*android_id*/
                                                             StrEnc("ujHO)8OfOE",
                                                                    "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21",
                                                                    10).c_str()));
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/StrEnc("m5I{GKGWBP-VOxkA",
                                                                  "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25",
                                                                  16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/
                                             StrEnc("|}[q:", "\x31\x32\x1F\x34\x76",
                                                    5).c_str(), /*Ljava/lang/String;*/
                                             StrEnc(".D:C:ETZ1O-Ib&^h.Y",
                                                    "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62",
                                                    18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/StrEnc("0iW=2^>0zTRB!B90",
                                                                  "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54",
                                                                  16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/
                                             StrEnc("@{[FP", "\x02\x29\x1A\x08\x14",
                                                    5).c_str(), /*Ljava/lang/String;*/
                                             StrEnc(".D:C:ETZ1O-Ib&^h.Y",
                                                    "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62",
                                                    18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/
            StrEnc("`L+&0^[S+-:J^$,r9q92(as",
                   "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07",
                   23).c_str());
    jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/
                                                  StrEnc("YN4DaP)!{wRGN}",
                                                         "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18",
                                                         14).c_str(), /*()Ljava/lang/String;*/
                                                  StrEnc("VnpibEspM(b]<s#[9cQD",
                                                         "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F",
                                                         20).c_str());

    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(/*java/util/UUID*/
            StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C",
                   14).c_str());

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/
                                                               StrEnc("P6LV|'0#A+zQmoat,",
                                                                      "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F",
                                                                      17).c_str(), /*([B)Ljava/util/UUID;*/
                                                               StrEnc("sW[\"Q[W3,7@H.vT0) xB",
                                                                      "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79",
                                                                      20).c_str());
    jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/StrEnc("2~5292eW",
                                                                              "\x46\x11\x66\x46\x4B\x5B\x0B\x30",
                                                                              8).c_str(), /*()Ljava/lang/String;*/
                                                StrEnc("P$BMc' #j?<:myTh_*h0",
                                                       "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B",
                                                       20).c_str());

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}

std::string RSA_Encrypt(const std::string &clear_text, const std::string &pub_key) {
    std::string result;
    BIO *key = BIO_new_mem_buf((unsigned char *) pub_key.c_str(), -1);
    RSA *rsa = RSA_new();
    rsa = PEM_read_bio_RSA_PUBKEY(key, &rsa, NULL, NULL);
    if (!rsa) {
        return "";
    }

    int key_len = RSA_size(rsa);
    int block_len = key_len - 11;

    char *sub_text = new char[key_len + 1];
    memset(sub_text, 0, key_len + 1);
    int ret = 0;
    int pos = 0;
    std::string sub_str;

    while (pos < clear_text.length()) {
        sub_str = clear_text.substr(pos, block_len);
        memset(sub_text, 0, key_len + 1);
        ret = RSA_public_encrypt(sub_str.length(), (const unsigned char *) sub_str.c_str(),
                                 (unsigned char *) sub_text, rsa, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            result.append(std::string(sub_text, ret));
        }
        pos += block_len;
    }

    BIO_free_all(key);
    RSA_free(rsa);
    delete[] sub_text;

    return result;
}

std::string RSA_Decrypt(const std::string &cipher_text, const std::string &pub_key) {
    std::string result;
    BIO *key = BIO_new_mem_buf((unsigned char *) pub_key.c_str(), -1);
    RSA *rsa = RSA_new();

    rsa = PEM_read_bio_RSA_PUBKEY(key, &rsa, NULL, NULL);
    if (!rsa) {
        return "";
    }

    int len = RSA_size(rsa);
    char *buf = new char[len + 1];
    memset(buf, 0, len + 1);

    int ret = RSA_public_decrypt(cipher_text.length(), (const unsigned char *) cipher_text.c_str(),
                                 (unsigned char *) buf, rsa, RSA_PKCS1_PADDING);
    if (ret >= 0) {
        result.append(std::string(buf, ret));
    }

    free(buf);
    BIO_free_all(key);
    RSA_free(rsa);

    return result;
}

uint8_t PUBLIC_KEY[450] = {0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0xE2, 0xE5, 0xE7, 0xE9, 0xEE, 0x80, 0xF0,
                           0xF5, 0xE2, 0xEC, 0xE9, 0xE3, 0x80, 0xEB, 0xE5, 0xF9, 0x8D, 0x8D, 0x8D,
                           0x8D, 0x8D, 0xAA, 0xED, 0xE9, 0xE9, 0xE2, 0xE9, 0xCA, 0xE1, 0xEE, 0xE2,
                           0xC7, 0xCB, 0xD1, 0xC8, 0xCB, 0xC9, 0xE7, 0x99, 0xD7, 0x90, 0xE2, 0xE1,
                           0xF1, 0xE5, 0xE6, 0xE1, 0xE1, 0xEF, 0xE3, 0xE1, 0xF1, 0x98, 0xE1, 0xED,
                           0xE9, 0xE9, 0xE2, 0xE3, 0xC7, 0xEB, 0xE3, 0xE1, 0xF1, 0xE5, 0xE1, 0x91,
                           0xD4, 0xCF, 0xEA, 0x96, 0xED, 0x95, 0xCB, 0xF4, 0xEA, 0xCD, 0xCA, 0xE2,
                           0xC9, 0xE6, 0xD0, 0xFA, 0xCE, 0xC8, 0xC3, 0xAA, 0x96, 0x90, 0xCB, 0x8B,
                           0xD8, 0xE7, 0xF7, 0xD6, 0xC6, 0xE1, 0xC4, 0xD1, 0xD7, 0xD6, 0xE5, 0xEA,
                           0xE7, 0xE2, 0xED, 0x95, 0x93, 0xDA, 0xEA, 0x94, 0xCF, 0x99, 0xF9, 0xDA,
                           0x91, 0xF0, 0xC3, 0x90, 0x94, 0xE6, 0xEA, 0x98, 0xF4, 0xF6, 0xFA, 0xE1,
                           0xE8, 0xC1, 0x95, 0x8F, 0xCB, 0x96, 0xEA, 0xC8, 0xC7, 0xD0, 0x8F, 0xC7,
                           0xF3, 0xC6, 0xC7, 0xE1, 0xF6, 0x8F, 0xF0, 0xEB, 0xC1, 0xC5, 0xD8, 0xCA,
                           0xAA, 0x96, 0x90, 0x94, 0x98, 0xD3,
                           0xEA, 0xCE, 0xC9, 0x8B, 0xF9, 0x97, 0xF8, 0xE2, 0xD2, 0xC8, 0xEE, 0xF9,
                           0x93, 0xE5, 0xD2, 0xC7, 0xF2, 0xEA, 0x96, 0xED, 0xCF, 0xC5, 0xED, 0xCB,
                           0xDA, 0xF0, 0xE9, 0xEF, 0xD4, 0xEA, 0xE7, 0xCB, 0x90, 0xC7, 0xD8, 0xEF,
                           0xF7, 0x95, 0x93, 0xC6, 0xCF, 0x8F, 0xD3, 0xC8, 0xEB, 0xC8, 0xCD, 0xF5,
                           0xC2, 0x96, 0xC7, 0xC7, 0x90, 0xD0, 0xCE, 0xD6, 0xD0, 0x92, 0xE8, 0xAA,
                           0x98, 0xE3, 0xE9, 0x97, 0xD2, 0x99, 0xFA, 0xEC, 0xEB, 0x96, 0xC7, 0xF3,
                           0xF9, 0xC4, 0xF6, 0xD0, 0xD5, 0x98, 0xD4, 0xF9, 0xCA, 0xFA, 0xEC, 0xEE,
                           0xD1, 0xE6, 0x95, 0xF3, 0xF2, 0xCB, 0xCE, 0xE1, 0xE7, 0xED, 0x92, 0x93,
                           0xC8, 0xC9, 0x8F, 0xF8, 0x8B, 0xCD, 0xF4, 0x92, 0xF8, 0x93, 0xEC, 0xEF,
                           0x93, 0xF0, 0x91, 0xC8, 0xCB, 0xC1, 0x8F, 0xC7, 0xF5, 0xCD, 0xF5, 0xEB,
                           0xC5, 0x95, 0xCF, 0xFA, 0xAA, 0x90, 0x8B, 0xEB, 0xC6, 0xF1, 0x90, 0xF4,
                           0xCA, 0x96, 0x91, 0xF7, 0xCE, 0xE6, 0x93, 0xE7, 0x92, 0xC1, 0x95, 0xF7,
                           0xF9, 0xE2, 0xD9, 0x96, 0x8F, 0xCA, 0xE7, 0xE5, 0xDA, 0xC8, 0xF1, 0xC5,
                           0xEC, 0xC7, 0x95, 0x92, 0x91, 0x90,
                           0xF4, 0x99, 0xD9, 0x91, 0xD3, 0xD8, 0xF6, 0xEC, 0xE5, 0xF6, 0xF6, 0xF6,
                           0x95, 0xD8, 0xC8, 0xCA, 0xF1, 0xE8, 0xE7, 0xE1, 0xD2, 0x95, 0xD7, 0xC6,
                           0x97, 0xF1, 0xE9, 0xAA, 0xCD, 0x96, 0xF5, 0xC7, 0xCE, 0xF7, 0xEC, 0xD9,
                           0xCD, 0x8B, 0xDA, 0xC6, 0x99, 0xE9, 0xCA, 0xC6, 0xC9, 0xCE, 0xE2, 0xC7,
                           0xF2, 0x99, 0xF0, 0xF4, 0x99, 0xC3, 0xE8, 0xFA, 0xF4, 0x93, 0xD0, 0xC4,
                           0x8B, 0x97, 0xC9, 0xE1, 0x91, 0xE4, 0xF7, 0x93, 0x92, 0xE3, 0x98, 0xC4,
                           0xD7, 0xF5, 0xEA, 0xD6, 0xE2, 0xF4, 0xF0, 0xCE, 0xD8, 0xDA, 0xEE, 0xC9,
                           0xEA, 0x96, 0xCF, 0x96, 0xE2, 0x90, 0xF3, 0xCC, 0xAA, 0xD5, 0xD7, 0xE9,
                           0xE4, 0xE1, 0xF1, 0xE1, 0xE2, 0xAA, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0xE5,
                           0xEE, 0xE4, 0x80, 0xF0, 0xF5, 0xE2, 0xEC, 0xE9, 0xE3, 0x80, 0xEB, 0xE5,
                           0xF9, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D};


struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

std::string Login(const char *user_key) {
    if (!g_App)
        return "Internal Error";

    auto activity = g_App->activity;
    if (!activity)
        return "Internal Error";

    auto vm = activity->vm;
    if (!vm)
        return "Internal Error";

    auto object = activity->clazz;
    if (!object)
        return "Internal Error";

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    std::string hwid = user_key;
    hwid += GetAndroidID(env, object);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);
    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());
    vm->DetachCurrentThread();
    std::string errMsg;

    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        std::string sss_aus = OBFUSCATE("https://www.nemesismods.site/connect");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, /*POST*/
                         StrEnc(",IL=", "\x7C\x06\x1F\x69", 4).c_str());
        curl_easy_setopt(curl, CURLOPT_URL,
                         sss_aus.c_str()); //"https://api.keyvip.tech/Dimension/public/connect");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, /*https*/
                         StrEnc("!mLBO", "\x49\x19\x38\x32\x3C", 5).c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, /*Content-Type: application/x-www-form-urlencoded*/
                                    StrEnc("@;Ls\\(KP4Qrop`b#d3094/r1cf<c<=H)AiiBG6i|Ta66s2[",
                                           "\x03\x54\x22\x07\x39\x46\x3F\x7D\x60\x28\x02\x0A\x4A\x40\x03\x53\x14\x5F\x59\x5A\x55\x5B\x1B\x5E\x0D\x49\x44\x4E\x4B\x4A\x3F\x04\x27\x06\x1B\x2F\x6A\x43\x1B\x10\x31\x0F\x55\x59\x17\x57\x3F",
                                           47).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char data[4096];
        sprintf(data, /*game=PUBG&user_key=%s&serial=%s*/StrEnc("qu2yXK,YkJyGD@ut0.u~Nb'5(:.:chK",
                                                                "\x16\x14\x5F\x1C\x65\x1B\x79\x1B\x2C\x6C\x0C\x34\x21\x32\x2A\x1F\x55\x57\x48\x5B\x3D\x44\x54\x50\x5A\x53\x4F\x56\x5E\x4D\x38",
                                                                31).c_str(), user_key,
                UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                if (result[/*status*/ StrEnc("(>_LBm", "\x5B\x4A\x3E\x38\x37\x1E", 6).c_str()] ==
                    true) {
                    std::string token = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20",
                                                               4).c_str()][/*token*/ StrEnc("{>3Lr",
                                                                                            "\x0F\x51\x58\x29\x1C",
                                                                                            5).c_str()].get<std::string>();
                    time_t rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20",
                                                        4).c_str()][/*rng*/ StrEnc("+n,",
                                                                                   "\x59\x00\x4B",
                                                                                   3).c_str()].get<time_t>();
                    //   expiredDate = result [/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*exdate*/ StrEnc("=So_ D", "\x58\x2B\x0B\x3E\x54\x21", 6).c_str()].get<std::string>();
                    //     FlotingText = result["data"]["FlotingText"].get<std::string>();
                    //   KeySlot = result["data"]["KeySlot"].get<std::string>();

                    if (rng + 30 > time(0)) {
                        std::string auth = /*PUBG*/ StrEnc("Q*) ", "\x01\x7F\x6B\x67", 4).c_str();;
                        auth += "-";
                        auth += user_key;
                        auth += "-";
                        auth += UUID;
                        auth += "-";
                        auth += /*Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E*/ StrEnc(
                                "-2:uwZdV^%]?{{wHs2V,+(^NJU;kC*_{",
                                "\x7B\x5F\x02\x39\x1C\x6D\x31\x3C\x6C\x6F\x30\x4C\x11\x38\x27\x1E\x23\x64\x3C\x5E\x67\x49\x69\x34\x2D\x33\x43\x58\x36\x50\x66\x3E",
                                32).c_str();
                        std::string outputAuth = Tools::CalcMD5(auth);

                        g_Token = token;
                        g_Auth = outputAuth;

                        bValid = g_Token == g_Auth;
                    }
                } else {
                    errMsg = result[/*reason*/ StrEnc("LW(3(c", "\x3E\x32\x49\x40\x47\x0D",
                                                      6).c_str()].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = "{";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += chunk.memory;
                errMsg += "}";
            }
        } else {
            errMsg = curl_easy_strerror(res);
        }
    }
    curl_easy_cleanup(curl);
    return bValid ? "OK" : errMsg;
}


SDK::FVector SubtractVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;
    result.Z = a.Z - b.Z;
    return result;
}


SDK::FVector AddVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z + b.Z;
    return result;
}


SDK::FVector MultiplyVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X * b.X;
    result.Y = a.Y * b.Y;
    result.Z = a.Z * b.Z;
    return result;
}


SDK::FVector DivideVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X / b.X;
    result.Y = a.Y / b.Y;
    result.Z = a.Z / b.Z;
    return result;
}


SDK::FVector MultiplyVectorFloat(SDK::FVector a, float scalar) {
    SDK::FVector result;
    result.X = a.X * scalar;
    result.Y = a.Y * scalar;
    result.Z = a.Z * scalar;
    return result;
}


FRotator ToRotator(FVector local, FVector target) {
    FVector Lund = SubtractVectors(target, local);
    FRotator newViewAngle;
    newViewAngle.Pitch =
            -std::atan2(Lund.Z, std::sqrt(Lund.X * Lund.X + Lund.Y * Lund.Y)) * (180.f / M_PI);
    newViewAngle.Yaw = std::atan2(Lund.Y, Lund.X) * (180.f / M_PI);
    newViewAngle.Roll = 0.f;
    if (newViewAngle.Yaw < 0.f) {
        newViewAngle.Yaw += 360.f;
    }
    return newViewAngle;
}


void RotateTriangle(std::array<Vector3, 3> &points, float Lund) {
    const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
    for (auto &point: points) {
        point = point - points_center;
        const auto temp_x = point.X;
        const auto temp_y = point.Y;
        const auto theta = DEG2RADD(Lund);
        const auto c = cosf(theta);
        const auto s = sinf(theta);
        point.X = temp_x * c - temp_y * s;
        point.Y = temp_x * s + temp_y * c;
        point = point + points_center;
    }
}


void VectorAnglesRadar(Vector3 &forward, FVector &angles) {
    if (forward.X == 0.f && forward.Y == 0.f) {
        angles.X = forward.Z > 0.f ? -360.f : 360.f;
        angles.Y = 0.f;
    } else {
        angles.X = RAD2DEG(atan2(-forward.Z, forward.Magnitude(forward)));
        angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
    }
    angles.Z = 360.f;
}

FVector
WorldToRadar(float Yaw, FVector Origin, FVector LocalOrigin, float PosX, float PosY, Vector3 Size,
             bool &outbuff) {
    bool flag = false;
    double num = (double) Yaw;
    double num2 = num * 0.017453292519943295;
    float num3 = (float) std::cos(num2);
    float num4 = (float) std::sin(num2);
    float num5 = Origin.X - LocalOrigin.X;
    float num6 = Origin.Y - LocalOrigin.Y;
    struct FVector Xector;
    Xector.X = (num6 * num3 - num5 * num4) / 150.f;
    Xector.Y = (num5 * num3 + num6 * num4) / 150.f;
    struct FVector Xector2;
    Xector2.X = Xector.X + PosX + Size.X / 2.f;
    Xector2.Y = -Xector.Y + PosY + Size.Y / 2.f;
    bool flag2 = Xector2.X > PosX + Size.X;
    if (flag2) {
        Xector2.X = PosX + Size.X;
    } else {
        bool flag3 = Xector2.X < PosX;
        if (flag3) {
            Xector2.X = PosX;
        }
    }
    bool flag4 = Xector2.Y > PosY + Size.Y;
    if (flag4) {
        Xector2.Y = PosY + Size.Y;
    } else {
        bool flag5 = Xector2.Y < PosY;
        if (flag5) {
            Xector2.Y = PosY;
        }
    }
    bool flag6 = Xector2.Y == PosY || Xector2.X == PosX;
    if (flag6) {
        flag = true;
    }
    outbuff = flag;
    return Xector2;
}



bool IsInsideFov(int x, int y) {
    if (!Cheat::BulletTrack::Radius)
        return true;                
    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = Cheat::BulletTrack::Radius;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

auto GetTargetByPussy() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = GetActors();

    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;
    FVector ViewPosY{0, 0, 0};
    if (localPlayer) {
        ViewPosY = localPlayer->GetBonePos("Head", {});
        ViewPosY.Z += -15.0f;
    }

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {

                auto Player = (ASTExtraPlayerCharacter *) Actor;
                float lund = localPlayer->GetDistanceTo(Player) / 100.0f;

                if (lund > Cheat::BulletTrack::Range)
                    continue;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                if (Player->bHidden)
                    continue;

                if (Cheat::BulletTrack::IgnoreKnock) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Cheat::BulletTrack::VisCheck) {

                    if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                        continue;
                }

                if (Cheat::BulletTrack::IgnoreBot) {
                    if (Player->bEnsure)
                        continue;
                }
                
                auto Root = Player->GetBonePos("Root", {});
				auto Head = Player->GetBonePos("Head", {});
				FVector2D RootSc, HeadSc;
				if (W2S(Root, &RootSc) && W2S(Head, &HeadSc))
				{
					float height = abs(HeadSc.Y - RootSc.Y);
					float width = height * 0.65f;

					FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
					if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight))
					{
						FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
						FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);
												
                        if(IsInsideFov((int)middlePoint.X, (int)middlePoint.Y)) {
                            float dist = FVector2D::Distance(v2Middle, v2Loc);
                             if (dist < max) {
                                 max = dist;
                                 result = Player;
                             }
                        }
                    }
                }
            }
        }
    }

    return result;
}

const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) {
    switch (Vehicle->VehicleShapeType) {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";
            break;
        default:
            return "Vehicle";
            break;
    }
    return "Vehicle";
}

void
(*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1,
                    int unk2) = 0;

void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot,
                 ASTExtraShootWeapon *weapon, int unk1) {
    if (Cheat::BulletTrack::Enable) {
        ASTExtraPlayerCharacter *Target = GetTargetByPussy();
        if (Target) {
            FVector targetAimPos = Target->GetBonePos("Head", {0, 0, 0});
            targetAimPos.Z -= -Cheat::BulletTrack::AimSet;
            FRotator sex = ToRotator(start, targetAimPos);
            return orig_shoot_event(thiz, targetAimPos, sex, weapon, unk1);
        }
    }
    return orig_shoot_event(thiz, start, rot, weapon, unk1);
}

void RenderESPPRIVATE(AHUD *HUD, int ScreenWidth, int ScreenHeight) {
    ASTExtraPlayerCharacter *localPlayer = 0;
    ASTExtraPlayerController *localPlayerController = 0;

    UCanvas *Canvas = HUD->Canvas;
    if (Canvas) {
        UGameplayStatics *gGameplayStatics = (UGameplayStatics *) UGameplayStatics::StaticClass();
        auto GWorld = GetWorld();
        if (GWorld) {
            UNetDriver *NetDriver = GWorld->NetDriver;
            if (NetDriver) {
                UNetConnection *ServerConnection = NetDriver->ServerConnection;
                if (ServerConnection) {
                    localPlayerController = (ASTExtraPlayerController *) ServerConnection->PlayerController;
                }
            }

            if (localPlayerController) {
                std::vector<ASTExtraPlayerCharacter *> PlayerCharacter;
                GetAllActors(PlayerCharacter);
                for (auto actor = PlayerCharacter.begin();
                     actor != PlayerCharacter.end(); actor++) {
                    auto Actor = *actor;

                    if (Actor->PlayerKey ==
                        ((ASTExtraPlayerController *) localPlayerController)->PlayerKey) {
                        localPlayer = Actor;
                        break;
                    }
                }

                {
                    if (localPlayer) {
                        auto infinity = std::numeric_limits<float>::infinity();
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;

                        if (Cheat::BulletTrack::AutoFire) {
                            if ((g_LocalPlayer && g_LocalPlayer->RootComponent) &&
                                localPlayerController) {
                                ASTExtraPlayerCharacter *Target;
                                Target = GetTargetByPussy();
                                auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                                if (WeaponManagerComponent) {
                                    auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                    if ((int) propSlot.GetValue() >= 1 &&
                                        (int) propSlot.GetValue() <= 3) {
                                        if (Cheat::BulletTrack::AutoFireOff) {
                                            g_LocalController->OnReleaseFire();
                                        }
                                        if (Target && Target->RootComponent) {
                                            localPlayerController->OnPressFire();
                                        } else {
                                            Cheat::BulletTrack::AutoFireOff = true;
                                        }
                                    }
                                }
                            }
                        } else {
                            Cheat::BulletTrack::AutoFireOff = true;
                        }
                        if (localPlayer->PartHitComponent) {
                            auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                            for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                                ConfigCollisionDistSqAngles[j].Angle = 180.0f;
                            }
                            localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                        }
                    }
                }
            }
            g_LocalPlayer = localPlayer;
            g_LocalController = localPlayerController;
        }
    }
}



namespace Settings {
    static int Tab = 1;
}

int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);

int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent) {
    if (initImGui) {
        ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float) screenWidth / (float) glWidth,
                                                        (float) screenHeight / (float) glHeight});
    }
    return orig_onInputEvent(app, inputEvent);
}

void *(*oProcessEvent)(UObject *pObj, UFunction *pFunc, void *pArgs);

void *hkProcessEvent(UObject *pObj, UFunction *pFunc, void *pArgs) {
    const char *EngineHUD = ("Function Engine.HUD.ReceiveDrawHUD");
    if (pFunc) {
        if (pFunc->GetFullName() == EngineHUD) {
            AHUD *pHUD = (AHUD *) pObj;
            if (pHUD) {
                auto Params = (AHUD_ReceiveDrawHUD_Params *) pArgs;
                if (Params) {
                    RenderESPPRIVATE(pHUD, Params->SizeX, Params->SizeY);
                }
            }
        }
    }
    return oProcessEvent(pObj, pFunc, pArgs);
}

void initOffset() {
    ProcessEvent = (Cheat::libUE4Base + 0x7065d3c);
    if (ProcessEvent) {
        Tools::Hook((void *) (ProcessEvent), (void *) hkProcessEvent,
                    (void **) &oProcessEvent);
    }
}


struct TeamColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

std::vector<TeamColor> teamColors = {
        {255, 0,   0},      // Red
        {0,   255, 0},      // Green
        {0,   0,   255},      // Blue
        {255, 255, 0},    // Yellow
        {255, 0,   255},    // Magenta
        {0,   255, 255},    // Cyan
        {255, 128, 0},    // Orange
        {128, 0,   255},    // Purple
        {0,   128, 255},    // Light Blue
        {128, 255, 0},    // Lime
        {0,   255, 128},    // Teal
        {128, 255, 255},  // Sky Blue
        {255, 128, 128},  // Pink
        {128, 128, 255},  // Lavender
        {255, 0,   128},    // Rose
        {255, 128, 255},  // Orchid
        {128, 255, 128},  // Lime Green
        {255, 192, 0},    // Gold
        {0,   255, 192},    // Turquoise
        {192, 0,   255},    // Fuchsia
        {255, 0,   192},    // Magenta Pink
        {192, 255, 0},    // Chartreuse
        {0,   192, 255},    // Light Sky Blue
        {255, 64,  0},     // Dark Orange
        {64,  0,   255},     // Indigo
};

TeamColor GetColorForTeam(int teamID) {
    if (teamID >= 1 && teamID <= 25) {
        return teamColors[teamID - 1];
    } else {
        return {128, 128, 128};
    }
}



