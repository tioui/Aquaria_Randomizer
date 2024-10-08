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
#include "RandomizerBoxing.h"

class wxNotebook;

class RandomizerLauncherFrame : public wxFrame
{
public:
    /**
     * Initialisation of the window
     *
     * @param userDataFolder The folder to store the launcher.xml save file
     * @param boxing The box to store the generated randomizer
     */
    RandomizerLauncherFrame(std::string userDataFolder, RandomizerBoxing *boxing);

private:
    /**
     * Creating a new page in a notebook with a text as title and a function to build the included panel.
     *
     * @param notebook The notebook to add the page.
     * @param text The text to used as tab title
     * @param panelBuilder A function that will be used to create the panel inside the page.
     */
    void createPage(wxNotebook *notebook, const wxString& text,
                    const std::function<wxWindow * (wxWindow *)>& panelBuilder);
    /**
     * Build the panel used in the Local randomizer tab
     *
     * @param parent The panel to put the local panel in.
     */
    wxWindow *buildLocalPanel(wxWindow *parent);

    /**
     * Build the panel used in the archipelago randomizer tab
     *
     * @param parent The panel to put the archipelago panel in.
     */
    wxWindow *buildArchipelagoPanel(wxWindow *parent);

    /**
     * Build the panel used in the archipelago randomizer offline tab
     *
     * @param parent The panel to put the archipelago offline panel in.
     */
    wxWindow *buildArchipelagoOfflinePanel(wxWindow *parent);

    /**
     * The text box used to get the json file path of the local randomizer.
     */
    wxTextCtrl *jsonFileText;

    /**
     * The text box used to get the seed number of the archipelago randomizer offline.
     */
    wxComboBox *seedNumberText;

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
     * Checkbox used to know if the randomizer should filter message.
     */
    wxCheckBox *filterSelf;

    /**
     * Checkbox used to know if the randomizer should filter chat message.
     */
    wxCheckBox *noChat;

    /**
     * Checkbox used to know if the randomizer should filter message.
     */
    wxCheckBox* deathLink;

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
     * Launched when the user click the "OK" button of the archipelago randomizer offline
     * @param event Information about the event (Not used)
     */
    void OnArchipelagoOfflineOKButton(wxCommandEvent& event);

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
    wxTextCtrl *createField(wxWindow *parent, const std::string& labelText);

    /**
     * Create a panel that contain a label and a checkbox.
     *
     * @param parent the panel to put the new field panel in.
     * @param labelText The text to put on the label.
     * @return The checkbox of the field .
     */
    wxCheckBox *createCheckBox(wxWindow *parent, const std::string& labelText);

    /**
     * Create a panel that contain a label and a combobox.
     *
     * @param parent the panel to put the new field panel in.
     * @param labelText The text to put on the label.
     * @param choices The choice in the combobox
     * @return The combobox of the field .
     */
    wxComboBox *createComboBox(wxWindow *parent, const std::string& labelText, const wxArrayString & choices);

    /**
    * Fill an array with every seed in the save directory
    * @param aChoice The array that has to be filled
    */
    void fillSeedNumber(wxArrayString *aChoice);

    /**
     * Create a panel that contain a label.
     *
     * @param parent the panel to put the new field panel in.
     * @param labelText The text to put on the label.
     * @return The panel of the field .
     */
    wxPanel *prepareFieldPanel(wxWindow *aParent, const std::string& aLabelText);

    /**
     * Add a visual space of a certain size in the parent layout
     * @param parent The panel to add the space
     * @param size the size of the space
     */
    void includeSpace(wxWindow *parent, int size);

    /**
     * Save the Archipelago launcher info in an XML file.
     */
    void saveLauncherArchipelagoInfo();

    /**
     * Save the offline Archipelago launcher info in an XML file.
     */
    void saveLauncherArchipelagoOfflineInfo();

    /**
     * Save the local launcher info in an XML file.
     */
    void saveLauncherLocalInfo();

    /**
     * Load the save XML values
     */
    void loadLauncherInfo();

    /**
     * The preference directory of the user
     */
    std::string userDataFolder;

    /**
     * The path of the local randomizer in the XML save file.
     */
    std::string xmlLocalPath;

    /**
     * The server address and port of the archipelago randomizer in the XML save file.
     */
    std::string xmlServer;

    /**
     * The slot name of the archipelago randomizer in the XML save file.
     */
    std::string xmlSlotName;

    /**
     * The slot password of the archipelago randomizer in the XML save file.
     */
    std::string xmlPassword;

    /**
     * The filter boolean of the archipelago randomizer in the XML save file.
     */
    bool xmlFilter;

    /**
     * The chat boolean of the archipelago randomizer in the XML save file.
     */
    bool xmlNoChat;

    /**
     * The seed number of the archipelago randomizer in the XML save file.
     */
    std::string xmlSeedNumber;

    /**
     * The filter boolean of the archipelago randomizer in the XML save file.
     */
    bool xmlDeathLink;

    /**
     * The tab to open at the start must be the local as specified in the XML save file.
     */
    bool xmlLocalTabOpen;

    /**
     * The tab to open at the start must be the archipelago tab as specified in the XML save file.
     */
    bool xmlArchipelagoTabOpen;

    /**
     * The tab to open at the start must be the Offline tab as specified in the XML save file.
     */
    bool xmlOfflineTabOpen;

    /**
     * The boxing used to store the generated randomizer
     */
    RandomizerBoxing *randomizerBoxing;
};


#endif //AQUARIA_RANDOMIZERLAUNCHERFRAME_H
