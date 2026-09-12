#include "Helper/include.h"
#include "Helper/definition.h"

void DrawESP(ImDrawList *draw) {

                    if(Cheat::BulletTrack::Enable)
                    {
                        draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), Cheat::BulletTrack::Radius, IM_COL32(0, 128, 255, 255), 0, 0.7f);
                   }
   
    std::string credit = OBFUSCATE("[0] Telegram Channel -> @GG_NEMESIS");
    auto textSize = ImGui::CalcTextSize2(credit.c_str(), 0, ((float) density / 14.0f));
    float centerX = ((float) glWidth / 2) - (textSize.x / 2);
    draw->AddText(NULL, ((float) density / 14.0f), {centerX, 29}, IM_COL32(255, 0, 0, 255),
                  credit.c_str());
                  
        auto Actors = GetActors();
        int totalEnemies = 0, totalBots = 0;

        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;
		
		
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *) Actor;
                break;
            }
        }
		
		

        if (localController) {
            for (int i = 0; i < Actors.size(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey ==
                        localController->PlayerKey) {
                        localPlayer = (ASTExtraPlayerCharacter *) Actor;
                        break;
                    }
                }
            }


            if (localPlayer) {
                if (localPlayer->PartHitComponent) {
                    auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                    for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                        ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                    }
                    localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                }

                if (localPlayer) {
                    if (localPlayer->PartHitComponent) {
                        auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                        for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
                            ConfigCollisionDistSqAngles[j].Angle = 180.0f;
                        }
                        localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
                    }
                    static bool bShooting = false;
                    if (BulletTrack) {
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent) {
                                        int shoot_event_idx = 169;
                                        auto VTable = (void **) ShootWeaponComponent->VTable;
                                        auto f_mprotect = [](uintptr_t addr, size_t len,
                                                             int32_t prot) -> int32_t {
                                            static_assert(PAGE_SIZE == 4096);
                                            constexpr
                                            size_t page_size = static_cast<size_t>(PAGE_SIZE);
                                            void *start = reinterpret_cast<void *>(addr &
                                                                                   -page_size);
                                            uintptr_t end =
                                                    (addr + len + page_size - 20) & -page_size;
                                            return mprotect(start, end -
                                                                   reinterpret_cast<uintptr_t>(start),
                                                            prot);
                                        };
                                        if (VTable && (VTable[shoot_event_idx] != shoot_event)) {
                                            orig_shoot_event = decltype(orig_shoot_event)(
                                                    VTable[shoot_event_idx]);

                                            f_mprotect((uintptr_t)(&VTable[shoot_event_idx]),
                                                       sizeof(uintptr_t), PROT_READ | PROT_WRITE);
                                            VTable[shoot_event_idx] = (void *) shoot_event;
                                        }
                                    }
                                }
                            }
                        }
                    }
     
                if (localController != 0)
                {
                
                    PATCH_LIB("libhdmpve.so","0xE631C", "00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x6791CB0","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x6791E74","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x6791F20","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x679B114","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x679B0A4","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x750CB40","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x750EA20","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x99652E4","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x9A01484","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0xA023560","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x750B9B0","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x750D9C8","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0x9964B1C","00 00 80 D2 C0 03 5F D6");
                    PATCH_LIB("libUE4.so","0xA0236B8","00 00 80 D2 C0 03 5F D6");



                    if (Cheat::Memory::SmallCrossHair || Cheat::Memory::FastShoot ||
                        Cheat::Memory::InstantHit || Cheat::Memory::ShowDamage || Cheat::Memory::InstantHitv1) {
                        auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                        if (WeaponManagerComponent) {
                            auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                            if ((int) propSlot.GetValue() >= 1 && (int) propSlot.GetValue() <= 3) {
                                auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                if (CurrentWeaponReplicated) {
                                    auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                    if (ShootWeaponComponent) {
                                        UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                        if (ShootWeaponEntityComponent) {

                                            if (Cheat::Memory::ShowDamage) {

                                                const int desiredGameReplayType = 2;
                                                ((ASTExtraPlayerController * )(
                                                        localPlayer->Controller))->GameReplayType = desiredGameReplayType;

                                            }
                                            if (Cheat::Memory::SmallCrossHair) {
                                                ShootWeaponEntityComponent->GameDeviationFactor = 0.0f;

                                            }
                                            if (Cheat::Memory::FastShoot) {
                                                ShootWeaponEntityComponent->ShootInterval = Cheat::Memory::ControlSpeed;
                                            }
                                            if (Cheat::Memory::InstantHit) {
                                                Write_Float(Cheat::libUE4Base + 0x68FF8DC, 0);
                                                Write_Float(Cheat::libUE4Base + 0x5A16F5C, 0);
                                                Write_Float(Cheat::libUE4Base + 0x68FE77C, 0);
                                            }
                                            if(Cheat::Memory::InstantHitv1){
                                              auto instashit = *(int*)(*(int*)(*(int*)(*(int*)(*(int*)(Cheat::libUE4Base + Cheat::localPlayer_Offset) + 0x0) + 0x1D5C) + 0x144) + 0x0) + 0x5C;
                                               Write<float>(instashit,40);
                                             }
                                           }
                                        }
                                    }
                                }
                            }
                        }
                        
                        
  

                             
                for (auto &i : Actors) {
                auto Actor = i;                
                if (isObjectInvalid(Actor))
                    continue;
                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    auto Actor = i;                    
                if (isObjectInvalid(Actor))
                    continue;
                            ImU32 PlayerBone;
                            ImU32 PlayerLine;
                            ImU32 BotLine;
                            ImU32 BotBone;
                            ImU32 PlayerAlert;
                            ImU32 BotAlert;
                            auto Player = (ASTExtraPlayerCharacter *) Actor;
                            bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0},
                                                                            true);

                            if (IsVisible) {
                                BotBone = IM_COL32(0, 240, 0, 255);
                                PlayerBone = IM_COL32(0, 240, 0, 255);
                                PlayerLine = IM_COL32(0, 240, 0, 255);
                                BotLine = IM_COL32(0, 240, 0, 255);
                            } else {
                                BotBone = IM_COL32(255, 255, 255, 255);
                                PlayerBone = IM_COL32(240, 0, 0, 255);
                                PlayerLine = IM_COL32(240, 255, 255, 255);
                                BotLine = IM_COL32(240, 255, 255, 255);
                            }
                            float Distance = localPlayer->GetDistanceTo(Player) / 100.0f;
                            if (Distance > 500.0f)
                                continue;

                            if (Player->PlayerKey == localController->PlayerKey)
                                continue;

                            if (Player->TeamID == localController->TeamID)
                                continue;

                            if (Player->bDead)
                                continue;

                            if (Player->bHidden)
                                continue;
								
                            if (Player->bEnsure)
                                totalBots++;
                            else
                                totalEnemies++;

              

                            float magic_number = (Distance);
                            float mx = (glWidth / 4) / magic_number;

                            float healthLength = glWidth / 17;
                            if (healthLength < mx)
                                healthLength = mx;
                            auto HeadPos = Player->GetBonePos("Head", {});
                            HeadPos.Z = HeadPos.Z + 35.0f;
                            ImVec2 headPosSC;

                            auto SexPos = Player->GetBonePos("Head", {});
                            SexPos.Z = SexPos.Z + 1.0f;
                            ImVec2 SexPosc;

                            auto RootPos = Player->GetBonePos("Root", {});
                            ImVec2 RootPosSC;
			
                            if (W2S(HeadPos, (FVector2D * ) & headPosSC) &&
                                W2S(RootPos, (FVector2D * ) & RootPosSC)) {

                                if (Cheat::Esp::Line) {
                                    if (Player->bEnsure) {
                                        draw->AddLine({(float) glWidth / 2, 10.5 + 50},
                                                      ImVec2(headPosSC.x, headPosSC.y - 10.0f),
                                                      BotBone, 0.8f);
                                    } else {
                                        draw->AddLine({(float) glWidth / 2, 10.5 + 50},
                                                      ImVec2(headPosSC.x, headPosSC.y - 10.0f),
                                                      PlayerBone, 0.8f);
                                    }
                                }


                                if (Cheat::Esp::Skeleton) {
                                    static std::vector <std::string> right_arm{"neck_01",
                                                                               "clavicle_r",
                                                                               "upperarm_r",
                                                                               "lowerarm_r",
                                                                               "hand_r", "item_r"};
                                    static std::vector <std::string> left_arm{"neck_01",
                                                                              "clavicle_l",
                                                                              "upperarm_l",
                                                                              "lowerarm_l",
                                                                              "hand_l", "item_l"};
                                    static std::vector <std::string> spine{"Head", "neck_01",
                                                                           "spine_03", "spine_02",
                                                                           "spine_01", "Pelvis"};
                                    static std::vector <std::string> lower_right{"Pelvis",
                                                                                 "thigh_r",
                                                                                 "calf_r",
                                                                                 "foot_r"};
                                    static std::vector <std::string> lower_left{"Pelvis", "thigh_l",
                                                                                "calf_l", "foot_l"};
                                    static std::vector <std::vector<std::string>> skeleton{
                                            right_arm, left_arm, spine, lower_right, lower_left};

                                    for (auto &boneStructure: skeleton) {
                                        std::string lastBone;
                                        for (std::string &currentBone: boneStructure) {
                                            if (!lastBone.empty()) {
                                                ImVec2 boneFrom, boneTo;
                                                if (W2S(Player->GetBonePos(lastBone.c_str(), {}),
                                                        (FVector2D * ) & boneFrom) &&
                                                    W2S(Player->GetBonePos(currentBone.c_str(), {}),
                                                        (FVector2D * ) & boneTo)) {
                                                    if (Player->bEnsure) {
                                                        draw->AddLine(boneFrom, boneTo, BotBone,
                                                                      0.8f);
                                                    } else {
                                                        draw->AddLine(boneFrom, boneTo, PlayerBone,
                                                                      1.0f);
                                                    }
                                                }
                                            }
                                            lastBone = currentBone;
                                        }
                                    }                                    
                                    ImVec2 headPos;
                                    if (W2S(Player->GetBonePos("Head", {}),
                                            (FVector2D * ) & headPos)) {
                                        float radius = 6.f - Distance * 0.03;

                                        if (Player->bEnsure) {
                                            draw->AddCircle(headPos, radius, BotBone, 12, 0.8f);
                                        } else {
                                            draw->AddCircle(headPos, radius, PlayerBone, 12, 1.0f);
                                        }
                                    }
                                }
                                if (Cheat::Esp::TeamID || Cheat::Esp::Name ||
                                    Cheat::Esp::Distance) {
                                    ImGuiStyle &style = ImGui::GetStyle();
                                    ImVec4 savedTextColor = style.Colors[ImGuiCol_Text];
                                    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

                                    std::string s;

                                    if (Cheat::Esp::TeamID) {
                                        s += "(" + std::to_string(Player->TeamID) + ") ";
                                    }

                                    if (Cheat::Esp::Name) {
                                        s += Player->bEnsure ? "Bot"
                                                             : Player->PlayerName.ToString();
                                    }

                                    if (Cheat::Esp::Distance) {
                                        s += (!s.empty() ? "  " : "") +
                                             std::to_string((int) Distance) + "m";
                                    }

                                    auto textSize = ImGui::CalcTextSize2(s.c_str(), 0,
                                                                         ((float) density / 25.0f));

                                    float strokeSize = 1.5f;
                                    for (float x = -strokeSize; x <= strokeSize; x += strokeSize) {
                                        for (float y = -strokeSize;
                                             y <= strokeSize; y += strokeSize) {
                                            draw->AddText(NULL, ((float) density / 25.0f),
                                                          {RootPosSC.x - (textSize.x / 2) + x,
                                                           RootPosSC.y + y}, IM_COL32(0, 0, 0, 255),
                                                          s.c_str());
                                        }
                                    }

                                    draw->AddText(NULL, ((float) density / 25.0f),
                                                  {RootPosSC.x - (textSize.x / 2), RootPosSC.y},
                                                  IM_COL32(255, 255, 255, 255), s.c_str());

                                    style.Colors[ImGuiCol_Text] = savedTextColor;
                                }


                                if (Cheat::Esp::Health) {
                                    int CurHP = (int) std::max(0, std::min((int) Player->Health,
                                                                           (int) Player->HealthMax));
                                    int MaxHP = (int) Player->HealthMax;

                                    float healthPercentage = (float) CurHP / MaxHP;

                                    float barWidth = density / 8.0f;
                                    float barHeight = barWidth * 0.10f;

                                    ImVec2 barStart = {headPosSC.x - (barWidth / 2),
                                                       headPosSC.y - 10.0f};
                                    ImVec2 barEndFilled = {barStart.x + barWidth * healthPercentage,
                                                           barStart.y + barHeight};
                                    ImVec2 barEndRect = {barStart.x + barWidth,
                                                         barStart.y + barHeight};

                                    ImU32 barColor = IM_COL32(255 * (1.0f - healthPercentage),
                                                              255 * healthPercentage, 0, 255);

                                    draw->AddRectFilled(barStart, barEndFilled, barColor);
                                    draw->AddRect(barStart, barEndRect, IM_COL32(0, 0, 0, 255));
                                }


                            }
                         

                            if (Cheat::Esp::Alert) {
                                bool shit = false;

                                FVector MyPosition, EnemyPosition;
                                ASTExtraVehicleBase *CurrentVehiclea = Player->CurrentVehicle;
                                if (CurrentVehiclea) {
                                    MyPosition = CurrentVehiclea->RootComponent->RelativeLocation;
                                } else {
                                    MyPosition = Player->RootComponent->RelativeLocation;
                                }
                                ASTExtraVehicleBase *CurrentVehicle = localPlayer->CurrentVehicle;
                                if (CurrentVehicle) {
                                    EnemyPosition = CurrentVehicle->RootComponent->RelativeLocation;
                                } else {
                                    EnemyPosition = localPlayer->RootComponent->RelativeLocation;
                                }
                                FVector EntityPos = WorldToRadar(
                                        localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw,
                                        MyPosition, EnemyPosition, NULL, NULL,
                                        Vector3(glWidth, glHeight, 0), shit);
                                FVector angle = FVector();
                                Vector3 forward = Vector3((float) (glWidth / 2) - EntityPos.X,
                                                          (float) (glHeight / 2) - EntityPos.Y,
                                                          0.0f);
                                VectorAnglesRadar(forward, angle);
                                const auto angle_yaw_rad = DEG2RAD(angle.Y + 180.f);
                                const auto new_point_x = (glWidth / 2) +
                                                         (30 /*alert dist from me*/) / 2 * 8 *
                                                         cosf(angle_yaw_rad);
                                const auto new_point_y = (glHeight / 2) +
                                                         (30 /*alert dist from me*/) / 2 * 8 *
                                                         sinf(angle_yaw_rad);
                                std::array<Vector3, 3> points{
                                        Vector3(new_point_x - ((90) / 4 + 3.5f) / 2,
                                                new_point_y - ((30) / 4 + 3.5f) / 2, 0.f),
                                        Vector3(new_point_x + ((90) / 4 + 3.5f) / 4, new_point_y,
                                                0.f), Vector3(new_point_x - ((30) / 4 + 3.5f) / 2,
                                                              new_point_y + ((20) / 4 + 3.5f) / 2,
                                                              0.f)};
                                RotateTriangle(points, angle.Y + 180.0f);
                                int TeamId = Player->TeamID;
                                TeamColor teamColor = GetColorForTeam(TeamId);
                                ImU32 imColor = IM_COL32(teamColor.r, teamColor.g, teamColor.b,
                                                         255); // Convert TeamColor to ImU32
                                draw->AddCircle(ImVec2(new_point_x, new_point_y), 8.0f, imColor, 64,
                                                8.0f);

                            }
						}
                    }
                }
            }
        }
    }
    
          if ( totalEnemies + totalBots > 0)
          {
    	    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(glWidth) / 2, 100), ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(210.0f, 35.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
            ImGui::Begin("x", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);                        
            ImVec2 windowPos = ImGui::GetWindowPos();
            ImVec2 windowSize = ImGui::GetWindowSize();	
            draw->AddRect(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), IM_COL32(0, 255, 0, 255), 3.0f, 0, 3.0f);
            ImGui::Text(" Total enemy around you : %d ", totalEnemies + totalBots);			
            ImGui::End();
            ImGui::PopStyleVar();
           }               
}




EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (glWidth <= 0 || glHeight <= 0)
        return orig_eglSwapBuffers(dpy, surface);

    if (!g_App)
        return orig_eglSwapBuffers(dpy, surface);

    screenWidth = ANativeWindow_getWidth(g_App->window);
    screenHeight = ANativeWindow_getHeight(g_App->window);
    density = AConfiguration_getDensity(g_App->config);

    if (!initImGui) {
        ImGui::CreateContext();
        ImGuiStyle &style = ImGui::GetStyle();
        ImGui::StyleColorsDark();

        style.WindowPadding = ImVec2(7, 7);
        style.WindowRounding = 0.0f;
        style.FramePadding = ImVec2(4, 4);
        style.FrameRounding = 5.5f;
        style.FrameBorderSize = 1.0f;
        style.WindowBorderSize = 0.0f;
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontFromMemoryTTF((void *) PIRO_data, PIRO_size, 20.0f, NULL,
                                       io.Fonts->GetGlyphRangesDefault());
        ImFontConfig cfg;
        cfg.SizePixels = ((float) density / 20.0f);
        io.Fonts->AddFontDefault(&cfg);
        initImGui = true;
    }

    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawESP(ImGui::GetBackgroundDrawList());

    ImGui::SetNextWindowSize(ImVec2((float) glWidth * 0.42f, (float) glHeight * 0.52f),
                             ImGuiCond_Once);

    char buf[128];
    sprintf(buf, OBFUSCATE("GG NEMESIS ~ FREE 64 BIT ~ %0.1f FPS ###AnimatedTitle"), (io.Framerate),
            ImGui::GetFrameCount());
    if (ImGui::Begin(buf), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
                                 ImGuiConfigFlags_NoMouseCursorChange) {

        static bool isLogin = false;
        static std::string err;

        if (!isLogin) {
            static char s[64];
            ImGui::InputText("##key", s, sizeof s);
            auto key = getClipboardText();
            strncpy(s, key.c_str(), sizeof s);

            err = Login(s);

            if (err == "OK") {
                isLogin = bValid && g_Auth == g_Token;
            }

            if (err != "OK") {
                abort();
            }

        } else {


            ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.6f);
            ImGui::PushStyleColor(ImGuiCol_Border, ImColor(100, 100, 100, 200).Value);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(9, 36, 89, 0).Value);
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
            ImGui::BeginChild("x", ImVec2(170, 0), true);
            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor(2);

            if (ImGui::Button("Player ESP", ImVec2(150, 40)))
                Settings::Tab = 1;

            if (ImGui::Button("Bullet Track", ImVec2(150, 40)))
                Settings::Tab = 3;

            if (ImGui::Button("Extra Features", ImVec2(150, 40)))
                Settings::Tab = 4;
                
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.6f);
            ImGui::PushStyleColor(ImGuiCol_Border, ImColor(100, 100, 100, 200).Value);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(9, 36, 89, 0).Value);
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
            ImGui::BeginChild("mainchild", ImVec2(0, 0), true);
            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor(2);





            if (Settings::Tab == 1) {
                ImGui::Checkbox("Esp Line", &Cheat::Esp::Line);
                ImGui::Checkbox("Esp Skeleton", &Cheat::Esp::Skeleton);
                ImGui::Checkbox("Esp Health", &Cheat::Esp::Health);
                ImGui::Checkbox("Esp Distance", &Cheat::Esp::Distance);
                ImGui::Checkbox("Esp Name", &Cheat::Esp::Name);
                ImGui::Checkbox("Esp TeamID", &Cheat::Esp::TeamID);
                ImGui::Checkbox("Esp Alert", &Cheat::Esp::Alert);                
            }
            if (Settings::Tab == 3) {
                ImGui::Checkbox("Bullet Track", &Cheat::BulletTrack::Enable);        
                ImGui::SliderFloat("Aim Radius", &Cheat::BulletTrack::Radius, (0.0f), (400.0f),"%.0f");                  
                ImGui::SliderFloat("Aim Range", &Cheat::BulletTrack::Range, (0.0f), (80.0f),"%.0f");
                ImGui::SliderFloat("Aim Position", &Cheat::BulletTrack::AimSet, (0.0f), (10.0f),"%.0f");
                ImGui::Checkbox("Visibility Check", &Cheat::BulletTrack::VisCheck);
                ImGui::Checkbox("Ignore Knocked", &Cheat::BulletTrack::IgnoreKnock);
                ImGui::Checkbox("Ignore Bot", &Cheat::BulletTrack::IgnoreBot);
            }

            if (Settings::Tab == 4) {
                ImGui::Checkbox("Small Cross", &Cheat::Memory::SmallCrossHair);                               
            }

            ImGui::Separator();
            ImGui::TreePop();
        }
    }
    ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return orig_eglSwapBuffers(dpy, surface);
}


void *main_thread(void *) {
    Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
    while (!Cheat::libUE4Base) {
        Cheat::libUE4Base = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }
    while (!g_App) {
        g_App = *(android_app * *)(Cheat::libUE4Base + Cheat::GNativeAndroidApp_Offset);
        sleep(1);
    }

    FName::GNames = GetGNames();
    while (!FName::GNames) {
        FName::GNames = GetGNames();
        sleep(1);
    }
    UObject::GUObjectArray = (FUObjectArray * )(Cheat::libUE4Base + Cheat::GUObject_Offset);

    orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
    g_App->onInputEvent = onInputEvent;
    initOffset();
	

    Tools::Hook((void *) DobbySymbolResolver(OBFUSCATE("/system/lib/libEGL.so"), OBFUSCATE("eglSwapBuffers")), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);


    return nullptr;
}

__attribute__((constructor)) void _init() {

    pthread_create(&t, NULL, main_thread, NULL);
   pthread_create(&t, NULL, anogs_thread, NULL);
  pthread_create(&t, NULL, ue4_thread, NULL);
}
