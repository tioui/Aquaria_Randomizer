/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A window used as game launcher.
*/

#ifndef AQUARIA_RANDOMIZERLAUNCHERFRAME_H
#define AQUARIA_RANDOMIZERLAUNCHERFRAME_H


#include <wx/wx.h>
#include "Randomizer.h"

class RandomizerLauncherFrame : public wxFrame
{
public:
    /**
     * Initialisation of the window
     */
    RandomizerLauncherFrame();

    /**
     * Retreuve the generated randomizer.
     *
     * @return The randomizer
     */
    Randomizer *getRandomizer();

protected:
private:
    /**
     * Build the panel used in the Local randomizer tab
     *
     * @param parent The panel to put the local panel in.
     */
    void buildLocalPanel(wxWindow *parent);

    /**
     * Build the panel used in the archipelago randomizer tab
     *
     * @param parent The panel to put the archipelago panel in.
     */
    void buildArchipelagoPanel(wxWindow *parent);

    /**
     * The randomizer that is generated after clicking the OK button.
     */
    Randomizer *randomizer;

    /**
     * The panel of the local randomizer tab.
     */
    wxPanel* localPanel;

    /**
     * The text box used to get the json file path of the local randomizer.
     */
    wxTextCtrl *jsonFileText;

    /**
     * The panel of the archipelago randomizer tab.
     */
    wxPanel* archipelagoPanel;

    /**
     * Text box used to enter the slot name for the archipelago randomizer.
     */
    wxTextCtrl *slotNameText;

    /**
     * Text box used to enter the server host and port for the archipelago randomizer.
     */
    wxTextCtrl *serverText;

    /**
     * Text box used to enter the password for the archipelago randomizer.
     */
    wxTextCtrl *passwordText;

    /**
     * File dialog used to select the local randomizer json file.
     */
    wxFileDialog *openFileDialog;

    /**
     * Launched when the user click the "Select file..." button to select local randomizer json file
     * @param event Information about the event (Not used)
     */
    void OnOpenJsonFileButton(wxCommandEvent& event);

    /**
     * Launched when the user click the "OK" button of the local randomizer
     * @param event Information about the event (Not used)
     */
    void OnLocalOKButton(wxCommandEvent& event);

    /**
     * Launched when the user click the "OK" button of the archipelago randomizer
     * @param event Information about the event (Not used)
     */
    void OnArchipelagoOKButton(wxCommandEvent& event);

    /**
     * Launched when the user click one of the "Cancel" button
     * @param event Information about the event (Not used)
     */
    void OnCancelButton(wxCommandEvent& event);

    /**
     * Create the "OK" and "Cancel" panel.
     *
     * @param parent The panel to put the button panel in.
     * @param handler The event funtion to launch when the "OK" button is pressed.
     */
    void createButtonPanel(wxWindow *parent, std::function<void (wxCommandEvent &)> handler);

    /**
     * Create a panel that contain a label and a text view.
     *
     * @param parent the panel to put the new field panel in.
     * @param labelText The text to put on the label.
     * @return The text view of the field .
     */
    wxTextCtrl *createField(wxWindow *parent, std::string labelText);
};


#endif //AQUARIA_RANDOMIZERLAUNCHERFRAME_H
