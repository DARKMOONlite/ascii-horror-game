#ifndef PANEL_MANAGER_H
#define PANEL_MANAGER_H

#include <vector>
#include <memory>
#include "Panel.h"

namespace ASCIIDisplay {

// Manages multiple panels and their rendering order
class PanelManager {
public:
    PanelManager();
    ~PanelManager();
    
    // Add a panel to the manager
    void addPanel(std::shared_ptr<Panel> panel);
    
    // Remove a panel
    void removePanel(std::shared_ptr<Panel> panel);
    
    // Get panel by index
    std::shared_ptr<Panel> getPanel(size_t index);
    
    // Get number of panels
    size_t getPanelCount() const { return panels_.size(); }
    
    // Clear all panels
    void clearAllPanels();
    
    // Render all panels to the terminal
    void renderAll();
    
    // Initialize terminal (clear, hide cursor, etc.)
    void initialize();
    
    // Cleanup terminal (show cursor, reset formatting)
    void cleanup();
    
    // Move a panel to a different z-order
    void movePanelToFront(std::shared_ptr<Panel> panel);
    void movePanelToBack(std::shared_ptr<Panel> panel);

private:
    std::vector<std::shared_ptr<Panel>> panels_;
};

} // namespace ASCIIDisplay

#endif // PANEL_MANAGER_H
