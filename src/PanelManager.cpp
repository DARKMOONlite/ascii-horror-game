#include "PanelManager.h"
#include <algorithm>

namespace ASCIIDisplay {

PanelManager::PanelManager() {
}

PanelManager::~PanelManager() {
    cleanup();
}

void PanelManager::addPanel(std::shared_ptr<Panel> panel) {
    panels_.push_back(panel);
}

void PanelManager::removePanel(std::shared_ptr<Panel> panel) {
    auto it = std::find(panels_.begin(), panels_.end(), panel);
    if (it != panels_.end()) {
        panels_.erase(it);
    }
}

std::shared_ptr<Panel> PanelManager::getPanel(size_t index) {
    if (index < panels_.size()) {
        return panels_[index];
    }
    return nullptr;
}

void PanelManager::clearAllPanels() {
    for (auto& panel : panels_) {
        panel->clear();
    }
}

void PanelManager::renderAll() {
    for (auto& panel : panels_) {
        panel->render();
    }
}

void PanelManager::initialize() {
    TerminalUtils::clearScreen();
    TerminalUtils::hideCursor();
}

void PanelManager::cleanup() {
    TerminalUtils::showCursor();
    TerminalUtils::resetFormat();
}

void PanelManager::movePanelToFront(std::shared_ptr<Panel> panel) {
    auto it = std::find(panels_.begin(), panels_.end(), panel);
    if (it != panels_.end()) {
        panels_.erase(it);
        panels_.push_back(panel);
    }
}

void PanelManager::movePanelToBack(std::shared_ptr<Panel> panel) {
    auto it = std::find(panels_.begin(), panels_.end(), panel);
    if (it != panels_.end()) {
        panels_.erase(it);
        panels_.insert(panels_.begin(), panel);
    }
}

} // namespace ASCIIDisplay
