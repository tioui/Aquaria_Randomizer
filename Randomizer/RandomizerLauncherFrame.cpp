/**
 * @author      : Louis M (prog@tioui.com)
 * @created     : Fri, 26 Apr 2024 22:54:43 +0000
 * @license     : MIT
 * A window used as game launcher.
*/

#include "RandomizerLauncherFrame.h"
#include "RandomizerLocal.h"
#include "RandomizerArchipelago.h"
#include <wx/notebook.h>

/**
 * Initialisation of the window
 */
RandomizerLauncherFrame::RandomizerLauncherFrame() : wxFrame(nullptr, wxID_ANY, "Aquaria Randomizer Launcher") {
    randomizer = nullptr;
    wxPanel* lMainPanel = new wxPanel(this, wxID_ANY);
    lMainPanel->SetMinSize(wxSize(600, 300));
    wxNotebook *lNotebook = new wxNotebook(lMainPanel, wxID_ANY);
    createPage(lNotebook, L"Local randomizer", [this](wxWindow *aParent) -> wxWindow*{
        return buildLocalPanel(aParent);
    });
    createPage(lNotebook, L"Archipelago randomizer", [this](wxWindow *aParent) -> wxWindow*{
        return buildArchipelagoPanel(aParent);
    });
    wxBoxSizer* lMainPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    lMainPanelSizer->Add(lNotebook, 1, wxEXPAND);
    lMainPanel->SetSizer(lMainPanelSizer);
    wxBoxSizer* lTopSizer = new wxBoxSizer(wxHORIZONTAL);
    lTopSizer->SetMinSize(250, 100);
    lTopSizer->Add(lMainPanel, 1, wxEXPAND);
    SetSizerAndFit(lTopSizer);
    openFileDialog = new wxFileDialog(this, ("Open JSON file"),wxEmptyString, wxEmptyString,
                                      "JSON files (*.json)|*.json", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
}

/**
 * Creating a new page in a notebook with a text as title and a function to build the included panel.
 *
 * @param aNotebook The notebook to add the page.
 * @param aText The text to used as tab title
 * @param aPanelBuilder A function that will be used to create the panel inside the page.
 */
void RandomizerLauncherFrame::createPage(wxNotebook *aNotebook, const wxString& aText,
                                         const std::function<wxWindow * (wxWindow *)>& aPanelBuilder) {
    wxPanel* lPanel = new wxPanel(aNotebook, wxID_ANY);
    lPanel->SetSizer(new wxBoxSizer(wxHORIZONTAL));
    includeSpace(lPanel, 10);
    lPanel->GetSizer()->Add(aPanelBuilder(lPanel), 1, wxEXPAND);
    includeSpace(lPanel, 10);
    aNotebook->AddPage(lPanel, aText);
}

/**
 * Build the panel used in the Local randomizer tab
 *
 * @param aParent The panel to put the local panel in.
 */
wxWindow *RandomizerLauncherFrame::buildLocalPanel(wxWindow *aParent){
    wxPanel *lLocalPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lPanelSizer = new wxBoxSizer(wxVERTICAL);
    lLocalPanel->SetSizer(lPanelSizer);
    includeSpace(lLocalPanel, 10);
    jsonFileText = createField(lLocalPanel, "Json file: ");
    wxButton *lOpenFileDialog = new wxButton(lLocalPanel, wxID_FILE, "Select File...");
    lPanelSizer->Add(lOpenFileDialog, 0, wxALIGN_RIGHT);
    lOpenFileDialog->Bind(wxEVT_BUTTON, [this](wxCommandEvent &aEvent){
        OnOpenJsonFileButton(aEvent);
    }, wxID_FILE);
    includeSpace(lLocalPanel, 10);
    createButtonPanel(lLocalPanel, [&](wxCommandEvent &aEvent){
        OnLocalOKButton(aEvent);
    });
    return lLocalPanel;
}

/**
 * Create a panel that contain a label and a text view.
 *
 * @param aParent the panel to put the new field panel in.
 * @param aLabelText The text to put on the label.
 * @return The text view of the field .
 */
wxTextCtrl *RandomizerLauncherFrame::createField(wxWindow *aParent, std::string aLabelText) {
    wxPanel *lFieldPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lfieldPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    lFieldPanel->SetSizer(lfieldPanelSizer);
    aParent->GetSizer()->Add(lFieldPanel, 0, wxEXPAND);

    wxStaticText * lTextLabel = new wxStaticText(lFieldPanel, wxID_ANY, aLabelText);
    lfieldPanelSizer->Add(lTextLabel, 0, wxALIGN_CENTER_VERTICAL);
    wxTextCtrl *lText = new wxTextCtrl(lFieldPanel, wxID_EDIT);
    lfieldPanelSizer->Add(lText, 1, wxALIGN_RIGHT);
    return lText;
}

/**
 * Create the "OK" and "Cancel" panel.
 *
 * @param aParent The panel to put the button panel in.
 * @param aHandler The event funtion to launch when the "OK" button is pressed.
 */
void RandomizerLauncherFrame::createButtonPanel(wxWindow *aParent,std::function<void (wxCommandEvent &)> aHandler) {
    wxPanel *lButtonPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lButtonPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    lButtonPanel->SetSizer(lButtonPanelSizer);
    aParent->GetSizer()->Add(lButtonPanel, 0, wxCENTER);

    wxButton *lOk = new wxButton(lButtonPanel, wxID_OK, "OK");
    lButtonPanelSizer->Add(lOk, 0, wxALIGN_RIGHT);
    lOk->Bind(wxEVT_BUTTON, aHandler, wxID_OK);
    wxButton *lCancel = new wxButton(lButtonPanel, wxID_CANCEL, "Cancel");
    lButtonPanelSizer->Add(lCancel, 0, wxALIGN_RIGHT);
    lCancel->Bind(wxEVT_BUTTON, [this](wxCommandEvent &aEvent){
        OnCancelButton(aEvent);
    }, wxID_CANCEL);
}

/**
  * Launched when the user click the "Select file..." button to select local randomizer json file
  * @param aEvent Information about the event (Not used)
  */
void RandomizerLauncherFrame::OnOpenJsonFileButton(wxCommandEvent& aEvent) {
    int lResult = openFileDialog->ShowModal();
    if (lResult == wxID_OK) {
        jsonFileText->WriteText(openFileDialog->GetPath());
    }
}

/**
 * Launched when the user click the "OK" button of the local randomizer
 * @param aEvent Information about the event (Not used)
 */
void RandomizerLauncherFrame::OnLocalOKButton(wxCommandEvent& aEvent) {
    RandomizerLocal *lRandomizer = new RandomizerLocal(jsonFileText->GetValue().ToStdString());
    if (lRandomizer->hasError()) {
        wxMessageBox(lRandomizer->getErrorMessage(), wxT("Randomizer error"), wxICON_ERROR);
    } else {
        randomizer = lRandomizer;
        Close();
    }
}

/**
 * Build the panel used in the archipelago randomizer tab
 *
 * @param aParent The panel to put the archipelago panel in.
 */
wxWindow *RandomizerLauncherFrame::buildArchipelagoPanel(wxWindow *aParent){
    wxPanel *lArchipelagoPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lPanelSizer = new wxBoxSizer(wxVERTICAL);
    lArchipelagoPanel->SetSizer(lPanelSizer);
    includeSpace(lArchipelagoPanel, 10);
    serverText = createField(lArchipelagoPanel, "Server host (including port): ");
    includeSpace(lArchipelagoPanel, 10);
    slotNameText = createField(lArchipelagoPanel, "Slot name: ");
    includeSpace(lArchipelagoPanel, 10);
    passwordText = createField(lArchipelagoPanel, "Server password (leave empty if none): ");
    includeSpace(lArchipelagoPanel, 10);
    createButtonPanel(lArchipelagoPanel,[this](wxCommandEvent & aEvent){
        OnArchipelagoOKButton(aEvent);
    });
    return lArchipelagoPanel;
}

/**
 * Add a visual space of a certain size in the parent layout
 * @param aParent The panel to add the space
 * @param aSize the size of the space
 */
void RandomizerLauncherFrame::includeSpace(wxWindow *aParent, int aSize) {
    aParent->GetSizer()->Add(new wxPanel(aParent,wxID_ANY, wxDefaultPosition, wxSize(aSize, aSize)));
}

/**
 * Launched when the user click one of the "Cancel" button
 * @param aEvent Information about the event (Not used)
 */
void RandomizerLauncherFrame::OnCancelButton(wxCommandEvent& aEvent) {
    Close();
}

/**
 * Launched when the user click the "OK" button of the archipelago randomizer
 * @param aEvent Information about the event (Not used)
 */
void RandomizerLauncherFrame::OnArchipelagoOKButton(wxCommandEvent& aEvent) {
    Randomizer *lRandomizer = new RandomizerArchipelago(
            serverText->GetValue().ToStdString(),
            slotNameText->GetValue().ToStdString(),
            passwordText->GetValue().ToStdString(),
            false);
    if (lRandomizer->hasError()) {
        wxMessageBox(lRandomizer->getErrorMessage(), wxT("Randomizer error"), wxICON_ERROR);
    } else {
        randomizer = lRandomizer;
        Close();
    }
}

/**
 * Retreuve the generated randomizer.
 *
 * @return The randomizer
 */
Randomizer *RandomizerLauncherFrame::getRandomizer() {
    return randomizer;
}
