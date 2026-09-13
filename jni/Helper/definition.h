#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <limits>
#include <sys/mman.h>
#include <unistd.h>

enum EAimTrigger 
{
    None = 0,
    Shooting = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};

namespace Cheat 
{
    inline uintptr_t libUE4Base = 0;
    inline uintptr_t GName_Offest = 0x8be1bfc;
    inline uintptr_t GUObject_Offset = 0xf360880;
    inline uintptr_t GNativeAndroidApp_Offset = 0xf08f3a8;
    inline uintptr_t ActorArray_Offest = 0xa98c458;
    inline uintptr_t ProcessEvent = 0;
    inline uintptr_t ProcessEvent_Offset = 0x8e5753c;
    inline uintptr_t ReceiveDrawHUD_Offset = 0xafc6044;
    inline uintptr_t AInputQueue_GetEvent_Offset = 0xD494B60;
    inline uintptr_t eglSwapBuffers_Offset = 0xD495D50;
    inline uintptr_t ShootBulletInner_Offset = 0x6ff841c;

    inline SDK::ASTExtraPlayerCharacter *localPlayer = nullptr;
    inline SDK::ASTExtraPlayerController *localController = nullptr;

    enum EAimTarget 
    {
        Head = 0,
        Chest = 1
    };

    namespace Esp 
    {
        inline bool Line = false;
        inline bool Skeleton = false;
        inline bool Health = false;
        inline bool Distance = false;
        inline bool Name = false;
        inline bool Box = false;
        inline bool LootBox = false;
        inline bool Throwable = false;
        inline bool Counter = false;
        inline bool Target = false;
        inline bool ItemEsp = false;

        namespace Vehicle 
        {
            inline bool Name = true;
            inline bool Health = false;
            inline bool Fuel = false;
        }
    }

    namespace Aimbot 
    {
        inline bool Enable = false;
        inline bool VisCheck = true;
        inline bool IgnoreKnock = true;
        inline bool IgnoreBot = false;
        inline bool AimPrediction = false;
        inline EAimTarget Target = Head;
        inline EAimTrigger Trigger = None;
        inline bool RecoilControl = false;
        inline bool Position = false;

        inline float Recoil = 1.0f;
        inline float RecoilSet = 1.0f;
        inline float Range = 500.0f;
        inline float Fov = 250.0f;
        inline float Radius = 250.0f;
        inline float FireSpeed = 0.0f;
    }

    namespace BulletTrack 
    {
        inline bool Enable = false;
        inline bool VisCheck = true;
        inline bool IgnoreKnock = true;
        inline bool iGnoreBot = false;

        inline float Aimset = 0.0f;
        inline float Fov = 1000.0f;
        inline float Range = 600.0f;

        inline bool AutoFire = false;

        // New fields for new ShootBulletInner logic
        inline bool HitChance = false; // 3/3 mode
        inline bool SBullet = false;   // second bullet track
        inline bool HitWhere = false;  // false=Head, true=Body (spine_02)
    }

    namespace Memory 
    {
        inline bool Wide = false;
        inline bool Hit = false;
        inline bool Small = false;
        inline bool Skin = false;
        inline bool Magic = false;
        inline bool ShowDamage = false;
        
        inline float Size = 10000.0f;
    }
}

inline float Xpos = 0;
inline float Ypos = 0;
inline float UpScale = 0;
inline float Xs=2.4f, Ys=2.4f;

#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))
#define DEG2RADD(x) ((float)(x) * (float)(IM_PI / 360.f))
#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(Cheat::localController, w, true, s)
#define COLOR_BLACK FLinearColor(0, 0, 0, 0.2f)
#define COLOR_WHITE FLinearColor(1.f, 1.f, 1.f, 1.f)
#define COLOR_RED FLinearColor(1.f, 0.f, 0.f, 1.f)
#define COLOR_GREEN FLinearColor(0.f, 1.f, 0.f, 1.f)
#define COLOR_BLUE FLinearColor(0.68f, 0.85f, 0.90f, 1.0f)
#define COLOR_YELLOW FLinearColor(1.f, 1.f, 0.f, 1.f)
#define COLOR_NONE FLinearColor(0.f, 0.f, 0.f, 0.f)

#define TSL_FONT_DEFAULT_SIZE 20

using namespace SDK;

inline bool BulletTrack = true;
inline uintptr_t ProcessEvent = 0;

inline android_app* g_App = nullptr;

inline bool WriteAddr(void *addr, void *buffer, size_t length) 
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size),
                    (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 &&
           memcpy(addr, buffer, length) != 0;
}

template<typename T>
inline void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}

inline int screenWidth = -1, glWidth = 0, screenHeight = -1, glHeight = 0;
inline float density = -1;

inline int Write_Float(long int addr, float value) {
    Tools::WriteAddr((void *) (addr), (void *) &value, 4);
    return 0;
}

inline FVector GetBoneLocationByName(ASTExtraPlayerCharacter *Actor, const char *BoneName) {
    return Actor->GetBonePos(BoneName, FVector());
}

inline AHUD *NewHUD = 0;
inline bool GunSkin = true;

using json = nlohmann::json;
inline bool ExtremeExp = true;
inline std::string EXP = " ";
inline bool isCircle = true;
inline time_t rng = 0;
inline std::string ESP = "";
inline std::string Item = "";
inline std::string AIM = "";
inline std::string Memory = "";
inline std::string SilentAim = "";
inline std::string Floating = "";
inline std::string Setting = "";
inline pthread_t t = 0;

inline void NekoHook(FRotator &angles) 
{
    if (angles.Pitch > 180)
        angles.Pitch -= 360;
    if (angles.Pitch < -180)
        angles.Pitch += 360;

    if (angles.Pitch < -75.f)
        angles.Pitch = -75.f;
    else if (angles.Pitch > 75.f)
        angles.Pitch = 75.f;

    while (angles.Yaw < -180.0f)
        angles.Yaw += 360.0f;
    while (angles.Yaw > 180.0f)
        angles.Yaw -= 360.0f;
}

inline void NekoHook(float *angles) 
{
    if (angles[0] > 180)
        angles[0] -= 360;
    if (angles[0] < -180)
        angles[0] += 360;

    if (angles[0] < -75.f)
        angles[0] = -75.f;
    else if (angles[0] > 75.f)
        angles[0] = 75.f;

    while (angles[1] < -180.0f)
        angles[1] += 360.0f;
    while (angles[1] > 180.0f)
        angles[1] -= 360.0f;
}

inline void NekoHook(Vector3 angles) 
{
    if (angles.X > 180)
        angles.X -= 360;
    if (angles.X < -180)
        angles.X += 360;

    if (angles.X < -75.f)
        angles.X = -75.f;
    else if (angles.X > 75.f)
        angles.X = 75.f;

    while (angles.Y < -180.0f)
        angles.Y += 360.0f;
    while (angles.Y > 180.0f)
        angles.Y -= 360.0f;
}

inline FRotator Rotation = { };

struct sRegion {
    uintptr_t start, end;
};

inline std::vector<sRegion> trapRegions;

inline int GetIndex(int currentIndex, int arrayNum) {
    if (arrayNum <= 0) {
        return 0;
    }
    return (currentIndex + 1) % arrayNum;
}

inline float Random[11] = {0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.9f, 2.0f};

inline float GetTimeInSeconds() 
{
    return std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

inline UFont *tslFont = 0;
inline UFont *robotoTinyFont = 0;

inline void *LoadFont(void *)
{
    while (!tslFont || !robotoTinyFont)
    {
        tslFont = UObject::FindObject<UFont>("Font Roboto.Roboto");
        robotoTinyFont = UObject::FindObject<UFont>("Font RobotoDistanceField.RobotoDistanceField");
        sleep(1);
    }
    return 0;
}

inline float ScaleRand = 0;
inline float TimeLift = 0;

inline FVector TargetPos = { };

inline void DrawOutlinedText(AHUD *HUD, FString Text, FVector2D Pos, FLinearColor Color, FLinearColor OutlineColor, bool isCenter = false) 
{
    if (!HUD || !HUD->Canvas || !tslFont) return;
    UCanvas *Canvas = HUD->Canvas;
    Canvas->K2_DrawText(tslFont, Text, Pos, Color, 1.f, {}, {}, isCenter, isCenter, true, OutlineColor);
}

struct D3DMatrix {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};

inline D3DMatrix QuatToMatrix(const FQuat &quat){
    D3DMatrix mat;
    float magnitude = std::sqrt(quat.X * quat.X + quat.Y * quat.Y + quat.Z * quat.Z + quat.W * quat.W);
    float qx = quat.X / magnitude;
    float qy = quat.Y / magnitude;
    float qz = quat.Z / magnitude;
    float qw = quat.W / magnitude;
    float xx = qx * qx;
    float xy = qx * qy;
    float xz = qx * qz;
    float xw = qx * qw;
    float yy = qy * qy;
    float yz = qy * qz;
    float yw = qy * qw;
    float zz = qz * qz;
    float zw = qz * qw;
    mat._11 = 1.0f - 2.0f * (yy + zz);
    mat._12 = 2.0f * (xy - zw);
    mat._13 = 2.0f * (xz + yw);
    mat._14 = 0.0f;
    mat._21 = 2.0f * (xy + zw);
    mat._22 = 1.0f - 2.0f * (xx + zz);
    mat._23 = 2.0f * (yz - xw);
    mat._24 = 0.0f;
    mat._31 = 2.0f * (xz - yw);
    mat._32 = 2.0f * (yz + xw);
    mat._33 = 1.0f - 2.0f * (xx + yy);
    mat._34 = 0.0f;
    mat._41 = 0.0f;
    mat._42 = 0.0f;
    mat._43 = 0.0f;
    mat._44 = 1.0f;
    return mat;
}

struct Matrix {float m[4][4];};
inline Matrix GetMatrix() {
    static UCanvas* Canvas = nullptr;
    if (Canvas == nullptr) {Canvas = UObject::FindObject<UCanvas>("Canvas Transient.DebugCanvasObject");}
    if (!Canvas) {return Matrix{};}
        uintptr_t lodalele;
    #if defined(__LP64__)
        lodalele = 0x270;
    #else
        lodalele = 0x200;
    #endif
    return *(Matrix*)((uintptr_t)Canvas + lodalele);
}

inline bool WorldToScreenPlayer(FVector pos, FVector &screen, int *distance) {
    Matrix ViewMatrix = GetMatrix();
    screen = {};
    *distance = 0;
    float screenW = (ViewMatrix.m[0][3] * pos.X) + (ViewMatrix.m[1][3] * pos.Y) + (ViewMatrix.m[2][3] * pos.Z + ViewMatrix.m[3][3]);
    if (screenW < 0.0001f)
        return false;
    *distance = (screenW / 100);
    float screenY = (ViewMatrix.m[0][1] * pos.X) + (ViewMatrix.m[1][1] * pos.Y) + (ViewMatrix.m[2][1] * (pos.Z + 85) + ViewMatrix.m[3][1]);
    float screenX = (ViewMatrix.m[0][0] * pos.X) + (ViewMatrix.m[1][0] * pos.Y) + (ViewMatrix.m[2][0] * pos.Z + ViewMatrix.m[3][0]);
    screen.Y = (glHeight / 2.f) - (glHeight / 2.f) * screenY / screenW;
    screen.X = (glWidth / 2.f) + (glWidth / 2.f) * screenX / screenW;
    float y1 = (glHeight / 2.f) - (ViewMatrix.m[0][1] * pos.X + ViewMatrix.m[1][1] * pos.Y + ViewMatrix.m[2][1] * (pos.Z - 95) + ViewMatrix.m[3][1]) * (glHeight / 2.f) / screenW;
    screen.Z = y1 - screen.Y;
    return !(screen.X == 0 && screen.Y == 0 && screen.Z == 0);
}

inline bool WorldToScreenBone(FVector Position, FVector2D *Screen) {
    Matrix ViewMatrix = GetMatrix();
    float ScreenW = (ViewMatrix.m[0][3] * Position.X) + (ViewMatrix.m[1][3] * Position.Y) + (ViewMatrix.m[2][3] * Position.Z + ViewMatrix.m[3][3]);
    if (ScreenW < 0.0001f)
        return false;
    ScreenW = 1 / ScreenW;
    float SightX = (glWidth / 2);
    float SightY = (glHeight / 2);
    Screen->X = SightX + (ViewMatrix.m[0][0] * Position.X + ViewMatrix.m[1][0] * Position.Y + ViewMatrix.m[2][0] * Position.Z + ViewMatrix.m[3][0]) * ScreenW * SightX;
    Screen->Y = SightY - (ViewMatrix.m[0][1] * Position.X + ViewMatrix.m[1][1] * Position.Y + ViewMatrix.m[2][1] * Position.Z + ViewMatrix.m[3][1]) * ScreenW * SightY;
    return true;
}

inline bool isObjectInvalid(UObject *obj) 
{
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

inline UEngine *GEngine = 0;
inline UWorld *GetWorld()
{
    while (!GEngine)
    {
        GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1");
        sleep(1);
    }
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

inline TNameEntryArray *GetGNames() 
{
    return ((TNameEntryArray *(*)()) (Cheat::libUE4Base + Cheat::GName_Offest))();
}

inline std::vector<AActor *> GetActors() 
{
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel) return std::vector<AActor *>();

    struct GovnoArray 
    {
        uintptr_t base;
        int32_t count;
        int32_t max;
    };
    static thread_local GovnoArray Actors{};

    Actors = *(((GovnoArray *(*)(uintptr_t)) (Cheat::libUE4Base + Cheat::ActorArray_Offest))( reinterpret_cast<uintptr_t>(PersistentLevel)));

    if (Actors.count <= 0) 
    {
        return {};
    }

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.count; i++) 
    {
        auto Actor = *(uintptr_t *) (Actors.base + (i * sizeof(uintptr_t)));
        if (Actor) 
        {
            actors.push_back(reinterpret_cast<AActor *const>(Actor));
        }
    }
    return actors;
}

template<class T>
inline void GetAllActors(std::vector<T *> &Actors) 
{
    UGameplayStatics *gGameplayStatics = (UGameplayStatics *) gGameplayStatics->StaticClass();
    auto GWorld = GetWorld();
    if (GWorld) 
    {
        TArray<AActor *> Actors2;
        gGameplayStatics->GetAllActorsOfClass((UObject *) GWorld, T::StaticClass(), &Actors2);
        for (int i = 0; i < Actors2.Num(); i++) 
        {
            Actors.push_back((T *) Actors2[i]);
        }
    }
}

inline FVector operator*(const FVector &vector, float scalar)
{
    return FVector({vector.X * scalar, vector.Y * scalar, vector.Z * scalar});
}

inline FVector operator+(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z};
}

inline FVector operator-(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z};
}

inline FVector operator*(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z};
}

inline FVector operator/(const FVector &lhs, const FVector &rhs) 
{
    return {lhs.X / rhs.X, lhs.Y / rhs.Y, lhs.Z / rhs.Z};
}

inline SDK::FVector MultiplyVectorFloat(SDK::FVector a, float scalar) 
{
    return {a.X * scalar, a.Y * scalar, a.Z * scalar};
}

inline SDK::FVector SubtractVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X - b.X;
    result.Y = a.Y - b.Y;
    result.Z = a.Z - b.Z;
    return result;
}

inline SDK::FVector AddVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X + b.X;
    result.Y = a.Y + b.Y;
    result.Z = a.Z + b.Z;
    return result;
}

inline SDK::FVector MultiplyVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X * b.X;
    result.Y = a.Y * b.Y;
    result.Z = a.Z * b.Z;
    return result;
}

inline SDK::FVector DivideVectors(SDK::FVector a, SDK::FVector b) {
    SDK::FVector result;
    result.X = a.X / b.X;
    result.Y = a.Y / b.Y;
    result.Z = a.Z / b.Z;
    return result;
}

inline FVector Minus_VectorVector(const FVector& A, const FVector& B)
{
    return FVector{A.X - B.X, A.Y - B.Y, A.Z - B.Z};
}

inline FVector Add_VectorVector(const FVector& A, const FVector& B)
{
    return FVector{A.X + B.X, A.Y + B.Y, A.Z + B.Z};
}

inline FVector Multiply_VectorFloat(const FVector& A, float Scalar)
{
    return FVector{A.X * Scalar, A.Y * Scalar, A.Z * Scalar};
}

inline FVector CalculateWeaponMuzzlePosition(const FVector& weaponLocation, const FRotator& weaponRotation, float weaponBodyLength) {

    float radPitch = weaponRotation.Pitch * (3.14159265358979323846 / 180.0f);
    float radYaw = weaponRotation.Yaw * (3.14159265358979323846 / 180.0f);


    float forwardX = std::cos(radPitch) * std::cos(radYaw);
    float forwardY = std::cos(radPitch) * std::sin(radYaw);
    float forwardZ = std::sin(radPitch);


    FVector muzzlePosition = {
        weaponLocation.X + forwardX * weaponBodyLength,
        weaponLocation.Y + forwardY * weaponBodyLength,
        weaponLocation.Z + forwardZ * weaponBodyLength
    };
    return muzzlePosition;
}

inline FRotator ClampAngles(FRotator inRot) {
    FRotator outRot = inRot;
    if (outRot.Pitch > 180)
        outRot.Pitch -= 360;
    if (outRot.Pitch < -180)
        outRot.Pitch += 360;

    if (outRot.Pitch < -75.f)
        outRot.Pitch = -75.f;
    else if (outRot.Pitch > 75.f)
        outRot.Pitch = 75.f;

    while (outRot.Yaw < -180.0f)
        outRot.Yaw += 360.0f;
    while (outRot.Yaw > 180.0f)
        outRot.Yaw -= 360.0f;
    return outRot;
}

inline FLinearColor UIntToLinearColor(uint32_t color)
{
    float A = ((color >> 24) & 0xFF) / 255.f;
    float R = ((color >> 16) & 0xFF) / 255.f;
    float G = ((color >> 8) & 0xFF) / 255.f;
    float B = (color & 0xFF) / 255.f;
    return FLinearColor(R, G, B, A);
}

inline FRotator ToRotator(FVector local, FVector target) {
    FVector rotation = Minus_VectorVector(local, target);
    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);
    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;
    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;
    return newViewAngle;
}

inline void DrawRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, float Thickness, FLinearColor Color) 
{
    HUD->DrawLine(Pos.X, Pos.Y, Pos.X + Width, Pos.Y, Color, Thickness);
    HUD->DrawLine(Pos.X, Pos.Y, Pos.X, Pos.Y + Height, Color, Thickness);
    HUD->DrawLine(Pos.X + Width, Pos.Y, Pos.X + Width, Pos.Y + Height, Color, Thickness);
    HUD->DrawLine(Pos.X, Pos.Y + Height, Pos.X + Width, Pos.Y + Height, Color, Thickness);
}

inline void DrawFilledRectangle(AHUD *HUD, FVector2D Pos, float Width, float Height, FLinearColor Color) 
{
    HUD->DrawRect(Color, Pos.X, Pos.Y, Width, Height);
}

inline bool isInsideFOVs(int x, int y) {
    // New logic: use Aimbot Radius if set, else BulletTrack Fov
    if (Cheat::Aimbot::Enable) {
        if (Cheat::Aimbot::Radius <= 0) return true;
        int circle_x = glWidth / 2;
        int circle_y = glHeight / 2;
        int rad = (int)(Cheat::Aimbot::Radius * 0.5f);
        return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
    }
    if (!Cheat::BulletTrack::Enable) return true;
    int circle_x = glWidth / 2;
    int circle_y = glHeight / 2;
    int rad = (int)(Cheat::BulletTrack::Fov * 400.0f);
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

// Globals for bone visibility - used by aimbot/bullettrack
inline bool isHead = false;
inline bool isPelvis = false;
inline bool isNeck = false;
inline bool isLeftHand = false;
inline bool isRightHand = false;
inline bool isLeftFoot = false;
inline bool isRightFoot = false;
inline bool isLeftCalf = false;
inline bool isRightCalf = false;
inline bool isLeftLowerArm = false;
inline bool isRightLowerArm = false;
inline bool isLeftThigh = false;
inline bool isRightThigh = false;
inline bool isLeftUpperArm = false;
inline bool isRightUpperArm = false;
inline int algorithm = 0;

inline auto GetTargetForAimBot()
{
    ASTExtraPlayerCharacter *result = nullptr;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = GetActors();
    auto localPlayer = Cheat::localPlayer;
    auto localController = Cheat::localController;

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto Player = (ASTExtraPlayerCharacter *)Actor;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;
                if (Player->TeamID == localPlayer->TeamID)
                    continue;
                if (Player->bDead)
                    continue;

                if (Cheat::Aimbot::IgnoreKnock) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                // Bone-to-bone visibility check - if no bone visible, skip
                if (Cheat::Aimbot::VisCheck) {
                    if (!localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("Head", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("neck_01", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("upperarm_r", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("upperarm_l", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("lowerarm_r", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("lowerarm_l", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_03", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_02", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_01", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("pelvis", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("thigh_l", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("thigh_r", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("calf_l", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("calf_r", {0,0,0}), false))
                        continue;

                    // Detailed bone visibility for algorithm selection
                    bool alreadySelected = false;
                    algorithm = 0;

                    isHead = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("Head", {0,0,0}), false);
                    isPelvis = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("pelvis", {0,0,0}), false);
                    isNeck = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("neck_01", {0,0,0}), false);
                    isLeftHand = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("hand_l", {0,0,0}), false);
                    isRightHand = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("hand_r", {0,0,0}), false);
                    isLeftFoot = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("foot_l", {0,0,0}), false);
                    isRightFoot = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("foot_r", {0,0,0}), false);
                    isLeftCalf = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("calf_l", {0,0,0}), false);
                    isRightCalf = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("calf_r", {0,0,0}), false);
                    isLeftLowerArm = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("lowerarm_l", {0,0,0}), false);
                    isRightLowerArm = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("lowerarm_r", {0,0,0}), false);
                    isLeftThigh = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("thigh_l", {0,0,0}), false);
                    isRightThigh = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("thigh_r", {0,0,0}), false);
                    isLeftUpperArm = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("upperarm_l", {0,0,0}), false);
                    isRightUpperArm = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("upperarm_r", {0,0,0}), false);

                    if (!alreadySelected && isHead) { algorithm = 1; alreadySelected = true; }
                    if (!alreadySelected && isPelvis) { algorithm = 2; alreadySelected = true; }
                    if (!alreadySelected && isLeftCalf) { algorithm = 3; alreadySelected = true; }
                    if (!alreadySelected && isRightCalf) { algorithm = 4; alreadySelected = true; }
                    if (!alreadySelected && isLeftLowerArm) { algorithm = 5; alreadySelected = true; }
                    if (!alreadySelected && isRightLowerArm) { algorithm = 6; alreadySelected = true; }
                    if (!alreadySelected && isLeftUpperArm) { algorithm = 7; alreadySelected = true; }
                    if (!alreadySelected && isRightUpperArm) { algorithm = 8; alreadySelected = true; }
                    if (!alreadySelected && isLeftThigh) { algorithm = 9; alreadySelected = true; }
                    if (!alreadySelected && isRightThigh) { algorithm = 10; alreadySelected = true; }
                    if (!alreadySelected && isLeftFoot) { algorithm = 11; alreadySelected = true; }
                    if (!alreadySelected && isRightFoot) { algorithm = 12; alreadySelected = true; }
                }

                if (Cheat::Aimbot::IgnoreBot) {
                    if (Player->bEnsure || Player->bIsAI)
                        continue;
                }

                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});
                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.20f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                            (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

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

    return result;
}

inline auto GetTargetByPussy() 
{
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = GetActors();

    auto localPlayer = Cheat::localPlayer;
    auto localController = Cheat::localController;

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {

                auto Player = (ASTExtraPlayerCharacter *) Actor;
                float distx = localPlayer->GetDistanceTo(Player) / 100.0f;

                if (distx > Cheat::BulletTrack::Range)
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

                // Bone-to-bone visibility - whatever bone visible will be tracked, default body
                if (Cheat::BulletTrack::VisCheck) {
                    if (!localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("Head", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_02", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_01", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("pelvis", {0,0,0}), false) &&
                        !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("neck_01", {0,0,0}), false))
                        continue;
                }

                if (Cheat::BulletTrack::iGnoreBot) {
                    if (Player->bEnsure || Player->bIsAI)
                        continue;
                }
                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});
                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.20f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                            (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                    if (isInsideFOVs((int)middlePoint.X, (int)middlePoint.Y)) 
                    {
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

// New cross-based target - bone visibility, default body
inline auto GetTargetByCross()
{
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();
    auto Actors = GetActors();

    auto localPlayer = Cheat::localPlayer;
    auto localController = Cheat::localController;

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {

                auto Player = (ASTExtraPlayerCharacter *) Actor;
                float distx = localPlayer->GetDistanceTo(Player) / 100.0f;

                if (distx > Cheat::BulletTrack::Range)
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

                // Bone-to-bone visibility - default body
                if (Cheat::BulletTrack::VisCheck) {
                    // Check head and body bones
                    bool headVisible = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("Head", {0,0,0}), false);
                    bool bodyVisible = localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_02", {0,0,0}), false) ||
                                       localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("spine_01", {0,0,0}), false) ||
                                       localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("pelvis", {0,0,0}), false);
                    if (!headVisible && !bodyVisible) {
                        // Check other bones as fallback
                        if (!localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("neck_01", {0,0,0}), false) &&
                            !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("upperarm_r", {0,0,0}), false) &&
                            !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("upperarm_l", {0,0,0}), false) &&
                            !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("thigh_l", {0,0,0}), false) &&
                            !localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos("thigh_r", {0,0,0}), false))
                            continue;
                    }
                }

                if (Cheat::BulletTrack::iGnoreBot) {
                    if (Player->bEnsure || Player->bIsAI)
                        continue;
                }
                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});
                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.20f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) &&
                            (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                        if (isInsideFOVs((int)middlePoint.X, (int)middlePoint.Y)) 
                        {
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

// --- New BulletTrack ShootBulletInner hook at 0x6ff841c ---
inline void (*ShootBulletInner)(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID) = nullptr;
inline int BulletCounter = 0;

inline void xShootBulletInner(uintptr_t Weapon, FVector StartLoc, FRotator StartRot, int ShootID)
{
    if (Cheat::BulletTrack::Enable) // Master switch
    {
        ASTExtraPlayerCharacter* Target = GetTargetByCross();
        if (Target)
        {
            // Determine if this bullet should track
            bool shouldTrack = false;
            if (Cheat::BulletTrack::HitChance) // If using 3/3 mode (all bullets track)
            {
                shouldTrack = true;
            }
            else // 1/3 or 2/3 mode
            {
                switch(BulletCounter % 3)
                {
                    case 0: shouldTrack = true; break; // First bullet always tracks
                    case 1: shouldTrack = Cheat::BulletTrack::SBullet; break; // Second bullet tracks if SBullet is true
                    case 2: shouldTrack = false; break; // Third bullet never tracks in this setup
                }
            }
            
            BulletCounter++;
            if (BulletCounter >= 3) BulletCounter = 0;

            if (shouldTrack)
            {
                FVector targetAimPos = Target->GetBonePos(
                    Cheat::BulletTrack::HitWhere ? "spine_02" : "Head", // Body or head
                    {}
                );
                
                // Adjust position
                if (Cheat::BulletTrack::HitWhere) {
                    targetAimPos.Z += 5.0f; // Body adjustment
                } else {
                    targetAimPos.Z -= -19.0f; // Head adjustment (Z +19)
                }
                
                FRotator adjustedRot = ToRotator(StartLoc, targetAimPos);
                return ShootBulletInner(Weapon, StartLoc, adjustedRot, ShootID);
            }
        }
    }
    return ShootBulletInner(Weapon, StartLoc, StartRot, ShootID);
}

// Keep old shoot_event as alias for compatibility if needed, but not used
inline void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1, int unk2, float a6, float a7, float a8) = nullptr;
inline void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1, float a6, float a7, float a8)
{
    // Deprecated - now using ShootBulletInner at 0x6ff841c
    if (orig_shoot_event) {
        return orig_shoot_event(thiz, start, rot, weapon, unk1, a6, a7, a8);
    }
}

inline const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) 
{
    switch (Vehicle->VehicleShapeType) 
    {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";

        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";

        default:
            return "Vehicle";
    }
    return "Vehicle";
}

namespace Settings 
{
    inline int Tab = 1;
}

inline void RenderESPPRIVATE(AHUD* HUD, int ScreenWidth, int ScreenHeight) 
{
    ASTExtraPlayerCharacter* localPlayer = nullptr;
    ASTExtraPlayerController* localPlayerController = nullptr;
    glWidth = ScreenWidth;
    glHeight = ScreenHeight;
    
    if (Cheat::Esp::Target)
    {
        auto Target = GetTargetByPussy();
        if (Target)
        {
            auto targetHead = Target->GetBonePos("Head", {});
            FVector2D targetSC, footPos;
            if (W2S(targetHead, &targetSC) && W2S(targetHead, &footPos))
            {
                HUD->DrawLine((float)glWidth / 2, 716, footPos.X - 2, footPos.Y, COLOR_RED, 1.0f);
            }
        }
    }
    
    UCanvas* Canvas = HUD->Canvas;
    if (Canvas)
    {
        static bool loadFont = false;
        if (!loadFont) 
        {
            pthread_t t2;
            pthread_create(&t2, NULL, LoadFont, NULL);
            loadFont = true;
        }

        if (!tslFont || !robotoTinyFont) return;
        
        tslFont->LegacyFontSize = 25;
        DrawOutlinedText(HUD, FString("SANKE - AIM"), {glWidth / 2.0f, 65}, COLOR_RED, COLOR_BLACK, true);
        tslFont->LegacyFontSize = TSL_FONT_DEFAULT_SIZE;

        auto GWorld = GetWorld();
        if (GWorld && GWorld->NetDriver && GWorld->NetDriver->ServerConnection)
        {
            localPlayerController = reinterpret_cast<ASTExtraPlayerController*>(GWorld->NetDriver->ServerConnection->PlayerController);
        }

        if (localPlayerController) 
        {
            std::vector<ASTExtraPlayerCharacter*> PlayerCharacter;
            GetAllActors(PlayerCharacter);
            for (auto Actor : PlayerCharacter) 
            {
                if (Actor->PlayerKey == localPlayerController->PlayerKey) 
                {
                    localPlayer = Actor;
                    break;
                }
            }
        }

        Cheat::localPlayer = localPlayer;
        Cheat::localController = localPlayerController;
    }
}

inline void* (*pProcessEvent)(UObject*, UFunction*, void*) = nullptr;
inline void* kProcessEvent(UObject* a1, UFunction* a, void* b) 
{
    if (!a1 || !a) 
        return pProcessEvent(a1, a, b);

    auto fnc = a->GetFullName();

    if (Cheat::localPlayer && Cheat::localController && Cheat::Memory::ShowDamage && fnc.find("ClientOnDamageToOther") != std::string::npos) 
    {
        auto localContrller = reinterpret_cast<ASTExtraPlayerController*>(a1);
        auto Params = reinterpret_cast<ASTExtraPlayerController_ClientOnDamageToOther_Params*>(b);
        if (Params) 
        {
            float damage = Params->_DamageToOther;
            if (auto HUD = reinterpret_cast<ASurviveHUD*>(localContrller->MyHUD)) 
            {
                HUD->AddHitDamageNumberWithConfig(damage, Cheat::localPlayer, Cheat::localController, 0, 1, 1, 1);
            }
        }
    }

    return pProcessEvent(a1, a, b);
}

inline void Box4LineHUD(
    AHUD* HUD,
    float X, 
    float Y, 
    float W, 
    float H, 
    float Thickness, 
    float CornerRatio, 
    FLinearColor Color
)
{
    float cornerW = W * CornerRatio;
    float cornerH = H * CornerRatio;

    HUD->DrawLine(X, Y, X + cornerW, Y, Color, Thickness);
    HUD->DrawLine(X, Y, X, Y + cornerH, Color, Thickness);

    HUD->DrawLine(X + W - cornerW, Y, X + W, Y, Color, Thickness);
    HUD->DrawLine(X + W, Y, X + W, Y + cornerH, Color, Thickness);

    HUD->DrawLine(X, Y + H - cornerH, X, Y + H, Color, Thickness);
    HUD->DrawLine(X, Y + H, X + cornerW, Y + H, Color, Thickness);

    HUD->DrawLine(X + W - cornerW, Y + H, X + W, Y + H, Color, Thickness);
    HUD->DrawLine(X + W, Y + H - cornerH, X + W, Y + H, Color, Thickness);
}

#include <cmath>

template<typename HUD_T, typename COLOR_T>
inline void DrawCircleHelper(HUD_T* HUD, float X, float Y, float Radius, COLOR_T Color,
                             int NumSegments = 36, float Thickness = 1.0f)
{
    if (!HUD) return;
    const float PI = 3.14159265358979323846f;
    float angleStep = 2.0f * PI / NumSegments;

    float prevX = X + Radius;
    float prevY = Y;
    for (int i = 1; i <= NumSegments; ++i)
    {
        float angle = i * angleStep;
        float newX = X + cosf(angle) * Radius;
        float newY = Y + sinf(angle) * Radius;

        HUD->DrawLine(prevX, prevY, newX, newY, Color, Thickness);

        prevX = newX;
        prevY = newY;
    }
}
