#include "upgrade.h"

#include "../../../gui/floodgui/flood_gui.h"
#include "../../../gui/floodgui/flood_gui_win.h"
#include "../../../gui/floodgui/flood_gui_draw.h"

template<typename T>
void CreateUpgradeWindow(UpgradeWindow* window, std::vector<Upgrade<T>>& upgrades) {
	const std::string& winName = window->window_name;
	FloodGui::BeginWindow(winName.c_str());
	for (const Upgrade<T>& upgrade : upgrades)
	{
		const double& cost = upgrade.nextLevelCost;
		// IDFK
	}
	FloodGui::EndWindow();
}