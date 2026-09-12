
namespace Cheat
{

  uintptr_t libUE4Base;
  int localPlayer_Offset = 0x8651A34;
  
namespace Esp
{
   bool Line = false;
   bool Skeleton = false;
   bool Health = false;
   bool Distance = false;
   bool Name = false;
   bool TeamID = false;
   bool Alert = false;
   bool OneClick = false;
}

namespace BulletTrack
{
  bool Enable = false;
  bool VisCheck = false;
  bool IgnoreKnock = false;
  bool IgnoreBot = false;
  bool AutoFire = false;
  bool AutoFireOff = false;
  float AimSet = 0.0f;
  auto AimPrediction = 0;
}

namespace Memory
{
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
   float XHitEffectSize = 10.0f;
   float ControlSpeed = 0.100f;
   float SetView = 220.0f;
   float GameSpeed = 22.5f;
   float PlayerSpeed = 0.15f;
 }
   
}
bool WriteAddr(void *addr, void *buffer, size_t length)
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *)((uintptr_t)addr - ((uintptr_t)addr % page_size) - page_size), (size_t)size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

template <typename T>
void Write(uintptr_t addr, T value)
{
    WriteAddr((void *)addr, &value, sizeof(T));
}

int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;
int Write_Float(long int addr, float value)
{
    Tools::WriteAddr((void *)(addr), (void *)&value, 4);
    return 0;
}
FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName)
{
    return Actor->GetBonePos(BoneName, FVector());
}

// Login && SDK Implement
bool initImGui;
bool bValid = false;
using json = nlohmann::json;
uintptr_t ProcessEvent_Offset;
time_t rng = 0;
std::string g_Token, g_Auth;
pthread_t t;
android_app *g_App = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;

using namespace SDK;

struct sRegion
{
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isObjectInvalid(UObject *obj)
{
    if (!Tools::IsPtrValid(obj))
    {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate))
    {
        return true;
    }

    if (obj->InternalIndex <= 0)
    {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0)
    {
        return true;
    }

    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4)
    {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region)
                    { return ((uintptr_t)obj) >= region.start && ((uintptr_t)obj) <= region.end; }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region)
                    { return ((uintptr_t)obj->ClassPrivate) >= region.start && ((uintptr_t)obj->ClassPrivate) <= region.end; }))
    {
        return true;
    }

    return false;
}

UWorld *GetWorld()
{
    auto GEngine = *(UEngine **)(Cheat::libUE4Base + 0x849CCC8);
    if (GEngine)
    {
        auto ViewPort = GEngine->GameViewport;
        if (ViewPort)
        {
            return ViewPort->World;
        }
    }
    return 0;
}
TNameEntryArray *GetGNames()
{
    return ((TNameEntryArray * (*)())(Cheat::libUE4Base + 0x437A13C))();
}

std::vector<AActor *> GetActors()
{
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();

    struct GovnoArray
    {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };
    static thread_local GovnoArray Actors{};

    Actors = *(((GovnoArray * (*)(uintptr_t))(Cheat::libUE4Base + 0x5C4E990))(reinterpret_cast<uintptr_t>(PersistentLevel)));

    if (Actors.count <= 0)
    {
        return {};
    }

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.count; i++)
    {
        auto Actor = *(uintptr_t *)(Actors.base + (i * sizeof(uintptr_t)));
        if (Actor)
        {
            actors.push_back(reinterpret_cast<AActor *const>(Actor));
        }
    }
    return actors;
}



template <class T>
void GetAllActors(std::vector<T *> &Actors)
{
    UGameplayStatics *gGameplayStatics = (UGameplayStatics *)gGameplayStatics->StaticClass();
    auto GWorld = GetWorld();
    if (GWorld)
    {
        TArray<AActor *> Actors2;
        gGameplayStatics->GetAllActorsOfClass((UObject *)GWorld, T::StaticClass(), &Actors2);
        for (int i = 0; i < Actors2.Num(); i++)
        {
            Actors.push_back((T *)Actors2[i]);
        }
    }
}





auto GetTargetByPussy()
{
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = GetActors();

    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;
    FVector ViewPosY{0, 0, 0};
    if (localPlayer)
    {
        ViewPosY = localPlayer->GetBonePos("Head", {});
        ViewPosY.Z += -15.0f;
    }

    if (localPlayer)
    {
        for (int i = 0; i < Actors.size(); i++)
        {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass()))
            {

                auto Player = (ASTExtraPlayerCharacter *)Actor;
                float lund = localPlayer->GetDistanceTo(Player) / 100.0f;

                if (lund > 500.0f)
                    continue;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;
					
				if (Player->bHidden)
					continue;

                if (Cheat::BulletTrack::IgnoreKnock)
                {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Cheat::BulletTrack::VisCheck)
                {

    				if(!localController->LineOfSightTo(Player, {0, 0, 0}, true))
    						continue;
				}

                if (Cheat::BulletTrack::IgnoreBot)
                {
                    if (Player->bEnsure)
                        continue;
                }
                float dist = localPlayer->GetDistanceTo(Player);
                if (dist < max)
                {
                    max = dist;
                    result = Player;
                }
            }
        }
    }

    return result;
}

void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1, int unk2) = 0;
void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1)
{
    if (Cheat::BulletTrack::Enable)
    {
        ASTExtraPlayerCharacter *Target = GetTargetByPussy();
        if (Target)
        {
                    FVector targetAimPos = Target->GetBonePos("Head", {});
                    targetAimPos.Z -= Cheat::BulletTrack::AimSet;
                    FRotator sex = ToRotator(start,targetAimPos);                
                    return orig_shoot_event(thiz, targetAimPos, sex, weapon, unk1);             
        }              
    }
    return orig_shoot_event(thiz, start, rot, weapon, unk1);
}

void RenderESPPRIVATE(AHUD *HUD, int ScreenWidth, int ScreenHeight)
{
    ASTExtraPlayerCharacter *localPlayer = 0;
    ASTExtraPlayerController *localPlayerController = 0;
    
    UCanvas *Canvas = HUD->Canvas;
    if (Canvas)
    {
        UGameplayStatics *gGameplayStatics = (UGameplayStatics *)UGameplayStatics::StaticClass();
        auto GWorld = GetWorld();
        if (GWorld)
        {
            UNetDriver *NetDriver = GWorld->NetDriver;
            if (NetDriver)
            {
                UNetConnection *ServerConnection = NetDriver->ServerConnection;
                if (ServerConnection)
                {
                    localPlayerController = (ASTExtraPlayerController *)ServerConnection->PlayerController;
                }
            }

            if (localPlayerController)
            {
                std::vector<ASTExtraPlayerCharacter *> PlayerCharacter;
                GetAllActors(PlayerCharacter);
                for (auto actor = PlayerCharacter.begin();
                     actor != PlayerCharacter.end(); actor++)
                {
                    auto Actor = *actor;

                    if (Actor->PlayerKey ==
                        ((ASTExtraPlayerController *)localPlayerController)->PlayerKey)
                    {
                        localPlayer = Actor;
                        break;
                    }
                }

                {
                    if (localPlayer)
                    {
                        auto infinity = std::numeric_limits<float>::infinity();
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;

                        if (Cheat::BulletTrack::AutoFire)
                        {
                            if ((g_LocalPlayer && g_LocalPlayer->RootComponent) && localPlayerController)
                            {
                                ASTExtraPlayerCharacter *Target;
                                Target = GetTargetByPussy();
                                auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                                if (WeaponManagerComponent)
                                {
                                    auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                    if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3)
                                    {
                                                if (Cheat::BulletTrack::AutoFireOff)
                                                {
                                                   g_LocalController->OnReleaseFire();
                                                }
                                                if (Target && Target->RootComponent)
                                                {
                                                    localPlayerController->OnPressFire();
                                                }
                                                else
                                                {
                                                    Cheat::BulletTrack::AutoFireOff = true;
                                                }                                            
                                    }
                                }
                            }
                        }
                        else
                        {
                          Cheat::BulletTrack::AutoFireOff = true;
                        }
                        if (localPlayer->PartHitComponent)
                        {
                            auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                            for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++)

                            {
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



int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);
int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent)
{
    if (initImGui)
    {
        ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float)screenWidth / (float)glWidth, (float)screenHeight / (float)glHeight});
    }
    return orig_onInputEvent(app, inputEvent);
}

void *(*oProcessEvent)(UObject *pObj, UFunction *pFunc, void *pArgs);

void *hkProcessEvent(UObject *pObj, UFunction *pFunc, void *pArgs)
{
    const char *EngineHUD = ("Function Engine.HUD.ReceiveDrawHUD");
    if (pFunc)
    {
        if (pFunc->GetFullName() == EngineHUD)
        {
            AHUD *pHUD = (AHUD *)pObj;
            if (pHUD)
            {
                auto Params = (AHUD_ReceiveDrawHUD_Params *)pArgs;
                if (Params)
                {
                    RenderESPPRIVATE(pHUD, Params->SizeX, Params->SizeY);
                }
            }
        }
    }
    return oProcessEvent(pObj, pFunc, pArgs);
}

void initOffset()
{
    ProcessEvent_Offset = (Cheat::libUE4Base + 0x57E7DC8);
    if (ProcessEvent_Offset)
    {
        Tools::Hook((void *)(ProcessEvent_Offset), (void *)hkProcessEvent,
                    (void **)&oProcessEvent);
    }
}