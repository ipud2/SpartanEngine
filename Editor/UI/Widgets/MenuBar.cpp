/*
Copyright(c) 2016-2017 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ========================
#include "MenuBar.h"
#include "../imgui/imgui.h"
#include "Core/Engine.h"
#include "Graphics/Model.h"
#include "Resource/ResourceManager.h"
#include "FileDialog.h"
#include "Scene/Scene.h"
//===================================

//= NAMESPACES ==========
using namespace std;
using namespace Directus;
//=======================

static bool g_showAboutWindow = false;
static bool g_showMetricsWindow = false;
static bool g_showStyleEditor = false;
static bool g_fileDialogVisible = false;
static string g_fileDialogSelection;
ResourceManager* g_resourceManager = nullptr;
Scene* g_scene = nullptr;

MenuBar::MenuBar()
{
	m_isWindow = false;
}

void MenuBar::Initialize(Context* context)
{
	Widget::Initialize(context);
	g_resourceManager = m_context->GetSubsystem<ResourceManager>();
	g_scene = m_context->GetSubsystem<Scene>();
	m_fileDialog = make_unique<FileDialog>(m_context, true, FileDialog_Filter_Scene);
}

void MenuBar::Update()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("New"))
			{
				m_context->GetSubsystem<Scene>()->Clear();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Load"))
			{
				m_fileDialog->SetStyle(FileDialog_Style_Load);
				g_fileDialogVisible = true;
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Save"))
			{
				m_fileDialog->SetStyle(FileDialog_Style_Save);
				g_fileDialogVisible = true;
			}

			if (ImGui::MenuItem("Save As..."))
			{
				m_fileDialog->SetStyle(FileDialog_Style_Save);
				g_fileDialogVisible = true;
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Editor"))
		{
			ImGui::MenuItem("Metrics", nullptr, &g_showMetricsWindow);
			ImGui::MenuItem("Style", nullptr, &g_showStyleEditor);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("About", nullptr, &g_showAboutWindow);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	if (g_fileDialogVisible)	ShowFileDialog();
	if (g_showAboutWindow)		ShowAboutWindow();
	if (g_showMetricsWindow)	ImGui::ShowMetricsWindow();
	if (g_showStyleEditor)		ImGui::ShowStyleEditor();
}

void MenuBar::ShowFileDialog()
{
	if (!m_fileDialog->Show(&g_fileDialogVisible, &g_fileDialogSelection))
		return;

	// LOAD
	if (m_fileDialog->GetStyle() == FileDialog_Style_Open || m_fileDialog->GetStyle() == FileDialog_Style_Load)
	{
		// Scene
		if (FileSystem::IsEngineSceneFile(g_fileDialogSelection))
		{
			g_scene->LoadFromFile(g_fileDialogSelection);
			g_fileDialogVisible = false;
		}
	}
	// SAVE
	else if (m_fileDialog->GetStyle() == FileDialog_Style_Save)
	{
		// Scene
		if (m_fileDialog->GetFilter() == FileDialog_Filter_Scene)
		{
			g_scene->SaveToFile(g_fileDialogSelection);
			g_fileDialogVisible = false;
		}
	}
}

void MenuBar::ShowAboutWindow()
{
	if (!g_showAboutWindow)
		return;

	ImGui::Begin("About", &g_showAboutWindow, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowFocus();
	ImGui::Text("Directus3D %s", ENGINE_VERSION);
	ImGui::Text("GitHub: https://github.com/PanosK92/Directus3D");
	ImGui::Text("By Panos Karabelas.");
	ImGui::Separator();
	ImGui::Text("MIT License");
	ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
	ImGui::Text("of this software and associated documentation files(the \"Software\"), to deal");
	ImGui::Text("in the Software without restriction, including without limitation the rights");
	ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and / or sell");
	ImGui::Text("copies of the Software, and to permit persons to whom the Software is furnished");
	ImGui::Text("to do so, subject to the following conditions :");
	ImGui::Text("The above copyright notice and this permission notice shall be included in");
	ImGui::Text("all copies or substantial portions of the Software.");
	ImGui::Text("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
	ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS");
	ImGui::Text("FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR");
	ImGui::Text("COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER");
	ImGui::Text("IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN");
	ImGui::Text("CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
	ImGui::Separator();
	ImGui::Text("Third party libraries");
	ImGui::Text("\tAngelScript");
	ImGui::Text("\tAssimp");
	ImGui::Text("\tBullet");
	ImGui::Text("\tFMOD");
	ImGui::Text("\tFreeImage");
	ImGui::Text("\tFreeType");
	ImGui::Text("\tImGui");
	ImGui::Text("\tPugiXML");
	ImGui::Text("\tSDL");
	ImGui::End();
}