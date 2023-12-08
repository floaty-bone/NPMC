#pragma once
#include "imgui.h"
#include "frontend.h"
#include "implot.h"
#include <vector>
#include <iostream>
#include <string>
#include "backend.h"
//function implementations
void RenderMainMenu(){
	//menu bar structure
	if (ImGui::BeginMainMenuBar()) {
		// File menu options
		if (ImGui::BeginMenu("File")) {
			if (ImGui::BeginMenu("New")) {
				if (ImGui::MenuItem("Session")) {
					//to complete:  window to enter information and name of session then create navigation tree on the left 
					//with main top tree element carying session name. 
				}
				if (ImGui::MenuItem("object")) {
					//to complete
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Open")) {
				if (ImGui::MenuItem("Saved Session")) {
					//to complete
				}
				if(ImGui::MenuItem("Data/Telemetry File")) {
					//to complete
				}
				ImGui::EndMenu();

			}
			if (ImGui::MenuItem("Save As")) {
				//to complete
			}
			if (ImGui::MenuItem("Save")) {
				//to complete
			}
			if (ImGui::MenuItem("Exit")) {
				//to complete 
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			// Edit menu options
			if (ImGui::MenuItem("Undo", nullptr)) {

			}
			if (ImGui::MenuItem("Redo", nullptr)) {

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", nullptr)) {

			}
			if (ImGui::MenuItem("Copy", nullptr)) {

			}
			if (ImGui::MenuItem("Paste", nullptr)) {

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			// View menu options
			ImGui::MenuItem("Fullscreen", nullptr);
			ImGui::MenuItem("Zoom In", nullptr);
			ImGui::MenuItem("Zoom Out", nullptr);
			ImGui::Separator();
			ImGui::MenuItem("Reset View", nullptr);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			// Help menu options
			ImGui::MenuItem("About", nullptr);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			// Help menu options
			ImGui::MenuItem("About", nullptr);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	
	}

}
void RenderBrowser()
{ 
	// Render the browser window
	ImGui::Begin("Browser");
	ImGui::Text("Browse");
	ImGui::Separator();
	ImGui::Separator();
	ImGui::TextUnformatted("Session: Session name");

	// Section 1: Plots/Graphics
	if (ImGui::TreeNode("Plots/Graphics"))
	{
		// Clickable and draggable text
		if (ImGui::Selectable("Plot 1", false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			// Handle click action for "Plot 1"
		}
		if (ImGui::Selectable("Plot 2", false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			// Handle click action for "Plot 2"
		}

		ImGui::TreePop();
	}

	// Section 2: Data streams
	if (ImGui::TreeNode("Data Streams"))
	{
		// Clickable and draggable text
		if (ImGui::Selectable("Data Stream 1", false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			// Handle click action for "Data Stream 1"
		}
		if (ImGui::Selectable("Data Stream 2", false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			// Handle click action for "Data Stream 2"
		}
		if (ImGui::Selectable("Data Stream 3", false, ImGuiSelectableFlags_AllowDoubleClick))
		{
			// Handle click action for "Data Stream 3"
		}

		ImGui::TreePop();
	}
	ImGui::Separator();
	ImGui::End();
}
//class LinePlot
  //constructer
LinePlot::LinePlot(const char* _Name,std::vector<DataStreamBack*> _AssociatedDataStreamBacks){
	Name = _Name;
	AssociatedDataStreamBacks = _AssociatedDataStreamBacks;
}
  // rendering view toggle (free view or locked view on live time)
void LinePlot::RenderViewToggle() {
	const char* items[] = { "Live Lock","Free" }; // here are the selectable view modes you can add some if you need later
	const char* combo_preview_value = items[Item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x - 110, 28)); // position 
	ImGui::SetNextItemWidth(100); //width
	if (ImGui::BeginCombo(" ", combo_preview_value))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			const bool is_selected = (Item_current_idx == n);
			if (ImGui::Selectable(items[n], is_selected))
				Item_current_idx = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}
  // rendering the actual plot
void LinePlot::RenderPlot(double _CurrentTime) {

	if (ImPlot::BeginPlot(Name,ImVec2(-1,-1))) {
			ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
			if (LinePlot::Item_current_idx == 0) {
				ImPlot::SetupAxisLimits(ImAxis_X1, _CurrentTime - 15, _CurrentTime, 1);
			}
			int Length = static_cast<int>(AssociatedDataStreamBacks.size());
			for (int i = 0; i < Length; i = i + 1) {
				DataStreamBack* PDatastream = AssociatedDataStreamBacks[i];
				std::vector<double>* PTimeBuffer = &PDatastream->TimeBuffer;
				std::vector<double>* PDataBuffer = &PDatastream->DataBuffer;
				ImPlot::PlotLine("one", PTimeBuffer->data(), PDataBuffer->data(), PTimeBuffer->size()); //u changed here
				ImPlot::EndPlot();

			}
		}

}
  // rendering the entire window 
void LinePlot::RenderWindow(double _CurrentTime) {
	if (ImGui::Begin(Name)) {
		RenderViewToggle();
		RenderPlot(_CurrentTime);
	}
	ImGui::End();
}

//class DataStreamFront
   //constructer; it receives a name and a pointer to DataStream back ( normaly the name should be the same as the DataStreamBack (might automate this later)
   //every DataStreamFront is associated to a DataStreamBack and one unique. thus a datastreamback instance  should be created first
DataStreamFront::DataStreamFront(const char* _Name,DataStreamBack* _PDataStreamBack) {
	Name = _Name;
	PDataStreamBack = _PDataStreamBack;
}
void DataStreamFront::RenderTable (double _CurrentTime) { 
	static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

	ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);

	// When using ScrollX or ScrollY we need to specify a size for our table container!
	// Otherwise by default the table will fit all available space, like a BeginChild() call.
	if (ImGui::BeginTable("table_scrolly", 2, flags))
	{
		ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
		ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_None);
		ImGui::TableSetupColumn("Data Point", ImGuiTableColumnFlags_None);
		ImGui::TableHeadersRow();
		// using clipper for large vertical lists (i think maybe this makes the program only render 1000 rows to nut cluster memory (maybe graphic memory something cause i don't think ram will have any problem). everytime )
		ImGuiListClipper clipper;
		clipper.Begin(PDataStreamBack->DataBuffer.size());
		while (clipper.Step())
		{
			int counter = 0;
			for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
			{
				double time = PDataStreamBack->TimeBuffer[row];
				double data = PDataStreamBack->DataBuffer[row];
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(UtcTimeInSecondsToDateTime(time));
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%f",data );
			}
		}
		ImGui::EndTable();
	}
}
void DataStreamFront::RenderWindow(double _CurrentTime) {
	if (ImGui::Begin(Name)) {
		RenderTable(_CurrentTime);
	}
	ImGui::End();
}





