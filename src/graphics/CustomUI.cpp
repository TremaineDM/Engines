#include "CustomUI.h"
#include <windows.h>
#include <psapi.h>
#include "core/Logger.h"
#include "core/Timer.h"
#include "imgui/imgui.h"

CustomUI::PropertiesPanel::PropertiesPanel(GameObject* obj)
{
	selectedObj = obj;
}

CustomUI::PropertiesPanel::~PropertiesPanel()
{
	delete selectedObj;
	selectedObj = nullptr;
}

void CustomUI::PropertiesPanel::Render() const
{
	if (selectedObj->isMenuActive)
	{
		// Gets the mesh's properties and then displays them with ImGui

		ImGui::Begin(selectedObj->name, &selectedObj->isMenuActive);
	
		char* tempName =  const_cast<char*>(selectedObj->name);
		
		ImGui::InputText("Mesh Name", tempName, size_t(tempName));

		// Change the standard transform components 
		ImGui::DragFloat3("Position", selectedObj->transform.pos);
		ImGui::DragFloat3("Rotation", selectedObj->transform.rotation);
		ImGui::DragFloat3("Scale", selectedObj->transform.scale, 0.0f, 10.0f);

		// Create a new color that is a copy of the meshes color
		ImGui::ColorEdit4("Mesh Color", selectedObj->GetComponent<MeshRenderer>()->meshColorTint);
		
		
		// MAKE SAVE MAP DATA A STATIC FUNCTION
		if (ImGui::Button("Save"))
		{
		
		}

		ImGui::End();
		tempName = nullptr;
		delete tempName;
	}

}





void CustomUI::PerformancePanel::Update(const float deltatime)
{
	fpsUpdateSpeed -= deltatime;

	if (fpsUpdateSpeed <= 0.0f)
	{
		if (fpsValues.size() == 100)
			fpsValues.erase(fpsValues.begin());

		fpsValues.push_back(PerformanceMonitor::GetFPS());
		fpsUpdateSpeed = initSpeed;

		lastestFPS = (int)PerformanceMonitor::GetFPS();
	}
}

void CustomUI::PerformancePanel::Render() const
{
	ImGui::Begin("Performance Monitor");

	ImGui::PlotLines("FPS", fpsValues.data(), fpsValues.size()); 	ImGui::SameLine();
	ImGui::Text("%i", lastestFPS);


	ImGui::Checkbox("Limit FPS", &PerformanceMonitor::LimitFPS); ImGui::SameLine();
	ImGui::InputInt("", &PerformanceMonitor::FPSLimit);

	ImGui::Text("Render Loop Time %f ms", PerformanceMonitor::RenderLoopTime);
	ImGui::Text("Update Loop Time %f ms", PerformanceMonitor::UpdateLoopTime);
	ImGui::Text("Physical Memory Usage %i MB", PerformanceMonitor::GetMemoryUsage());
	ImGui::Text("CPU Usage %f %%", PerformanceMonitor::GetCPUUsage());


	ImGui::End();
}

 

int PerformanceMonitor::FPSLimit = 60;
float PerformanceMonitor::RenderLoopTime = 0.0f;
float PerformanceMonitor::UpdateLoopTime = 0.0f;
bool PerformanceMonitor::LimitFPS = false;

 
// Varibables that are used to collect CPU data
ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
int numProcessors;
HANDLE self;

void PerformanceMonitor::InitMonitor()
{

	// This code block is used to find the CPU usage
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

void PerformanceMonitor::DebugFPS()
{
	EngineLogger::Trace("FPS: " + std::to_string(1 / Timer::GetDeltaTime()), "CustomUI.cpp", __LINE__);
}

float PerformanceMonitor::GetFPS()
{
	return 1 / Timer::GetDeltaTime();
}

int PerformanceMonitor::GetMemoryUsage()
{

	PROCESS_MEMORY_COUNTERS_EX pmc;
	bool GetMem = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));


	int physicalMemUsed_Bytes = pmc.WorkingSetSize;

	int physicalMemUsed_MB = physicalMemUsed_Bytes / 1000000;

	return physicalMemUsed_MB;
}

double PerformanceMonitor::GetCPUUsage()
{
	 FILETIME ftime, fsys, fuser;
	 ULARGE_INTEGER now, sys, user;


	 GetSystemTimeAsFileTime(&ftime);
	 memcpy(&now, &ftime, sizeof(FILETIME));

	 GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	 memcpy(&sys, &fsys, sizeof(FILETIME));
	 memcpy(&user, &fuser, sizeof(FILETIME));
	 double percent = static_cast<double>((sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart));
	 percent /= static_cast<double>((now.QuadPart - lastCPU.QuadPart));
	 percent /= static_cast<double>(numProcessors);
	 lastCPU = now;
	 lastUserCPU = user;
	 lastSysCPU = sys;

	 return percent * 100.0;
}

