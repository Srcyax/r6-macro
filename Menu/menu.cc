#include "../Header Files/menu.hh" 
using namespace ImGui;
#include "../Header Files/globals.hh"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui.h"
#include "../font/icons.h"
#include "..\functions\Config.h"

static void HelpMarker(const char* desc);
void CenterText(const char* text);
std::string currentConfig;

std::vector<std::string> getExistingConfigs(const std::string& directory) {
    std::vector<std::string> configs;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            configs.push_back(entry.path().filename().string());
        }
    }

    return configs;
}

void Macro() {
    SetCursorPos(ImVec2(10, 10));
    ImGui::BeginChild("##child1", ImVec2(175, 190), true, ImGuiWindowFlags_NoScrollbar);
    {
        ImGui::SliderFloat("x", &mouse::x, -10, 10);
        ImGui::SliderFloat("y", &mouse::y, -10, 10);
        ImGui::SliderFloat("time", &mouse::time, 0, 10);
    }
    ImGui::EndChild();
    SameLine();
    ImGui::BeginChild("##child2", ImVec2(175, 190), true, ImGuiWindowFlags_NoScrollbar);
    {
        ImGui::Text("empty...");
    }
    ImGui::EndChild();
}

void Config() {
    SetCursorPos(ImVec2(10, 10));
    ImGui::BeginChild("##child1", ImVec2(360, 190), true, ImGuiWindowFlags_NoScrollbar);
    {
        InputText("##configName", globals.configName, 20);
        std::vector<std::string> configs = getExistingConfigs("C:\\Configs");

        static int selectedIndex = -1;
        std::vector<const char*> configNames;
        for (const auto& config : configs) {
            configNames.push_back(config.c_str());
        }

        ImGui::ListBox("##configs", &selectedIndex, configNames.data(), configNames.size());

        ImVec2 buttonSize(52, 30);

        if (Button("save", buttonSize) && globals.isValidIndex(selectedIndex)) {
            config::Save(configNames[selectedIndex]);
        }

        SameLine();

        if (Button("load", buttonSize) && globals.isValidIndex(selectedIndex)) {
            config::Load(configNames[selectedIndex]);
            currentConfig = configNames[selectedIndex];
        }

        SameLine();

        std::size_t configNameLengh = std::strlen(globals.configName);
        if (Button("create", buttonSize) && configNameLengh > 0) {
            config::Create();
        }

        SameLine();

        if (Button("remove", buttonSize) && globals.isValidIndex(selectedIndex)) {
            config::Remove(configNames[selectedIndex]);
        }
    }
    ImGui::EndChild();  
}


void ui::renderMenu() {
    if (!globals.active) 
        return;

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin((window_title + currentConfig).c_str(), &globals.active, window_flags);
    {
        BeginChild("##buttons" , ImVec2(100, 210));
        {
            SetCursorPosX(20);
            SetCursorPosY(35);
            if (Button(" \n\n " ICON_FA_LIST " \n ##1", ImVec2(60, 60))) globals.tab = 0;
            SetCursorPosX(20);
            if (Button(" \n\n  " ICON_FA_ADDRESS_CARD " \n ##2", ImVec2(60, 60))) globals.tab = 1;
        }
        EndChild();
        SameLine();
        SetCursorPosX(110); 
        BeginChild("##tabs", ImVec2(380, 210));
        {
            switch (globals.tab)
            {
            case 0:
                Macro();
                break;
            case 1:
                Config();
                break;
            }
        }
        EndChild();
    }
    ImGui::End();
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    ui::RunStyle();

	if (window_pos.x == 0) {
    	RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		window_pos = (screen_res - window_size) * 0.5f;
	}
}

void ui::RunStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_TitleBgActive] = ImColor(0, 0, 0, 155);
    style.Colors[ImGuiCol_WindowBg] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_ChildBg] = ImColor(5, 5, 5, 255);
    style.Colors[ImGuiCol_Button] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0, 255);
    style.Colors[ImGuiCol_ButtonHovered] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_CheckMark] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30, 205);
    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(35, 35, 35, 205);
    style.Colors[ImGuiCol_FrameBgActive] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_SliderGrab] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_SliderGrabActive] = ImColor(color.all[0], color.all[1], color.all[2], color.all[3]);
    style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);
}

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void CenterText(const char* text)
{
    if (text == nullptr)
        return;

    ImGui::Spacing();
    ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
    ImGui::Text(text);
    ImGui::Spacing();
}
