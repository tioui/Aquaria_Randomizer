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
    wxPanel* lPanel = new wxPanel(this, wxID_ANY);
    lPanel->SetMinSize(wxSize(800, 600));
    wxNotebook *lNotebook = new wxNotebook(lPanel, wxID_ANY);
    buildLocalPanel(lNotebook);
    lNotebook->AddPage(localPanel, L"Local randomizer");
    buildArchipelagoPanel(lNotebook);
    lNotebook->AddPage(archipelagoPanel, L"Archipelago randomizer");
    wxBoxSizer* lPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    lPanelSizer->Add(lNotebook, 1, wxEXPAND);
    lPanel->SetSizer(lPanelSizer);
    wxBoxSizer* lTopSizer = new wxBoxSizer(wxHORIZONTAL);
    lTopSizer->SetMinSize(250, 100);
    lTopSizer->Add(lPanel, 1, wxEXPAND);
    SetSizerAndFit(lTopSizer);
    openFileDialog = new wxFileDialog(this, ("Open JSON file"),wxEmptyString, wxEmptyString,
                                      "JSON files (*.json)|*.json", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
}

/**
 * Build the panel used in the Local randomizer tab
 *
 * @param aParent The panel to put the local panel in.
 */
void RandomizerLauncherFrame::buildLocalPanel(wxWindow *aParent){
    localPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lPanelSizer = new wxBoxSizer(wxVERTICAL);
    localPanel->SetSizer(lPanelSizer);
    jsonFileText = createField(localPanel, "Json file:");
    wxButton *lOpenFileDialog = new wxButton(localPanel, wxID_FILE, "Select File...");
    lPanelSizer->Add(lOpenFileDialog, 0, wxALIGN_RIGHT);
    lOpenFileDialog->Bind(wxEVT_BUTTON, [this](wxCommandEvent &aEvent){
        OnOpenJsonFileButton(aEvent);
    }, wxID_FILE);
    createButtonPanel(localPanel, [&](wxCommandEvent &aEvent){
        OnLocalOKButton(aEvent);
    });
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
void RandomizerLauncherFrame::buildArchipelagoPanel(wxWindow *aParent){
    archipelagoPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lPanelSizer = new wxBoxSizer(wxVERTICAL);
    archipelagoPanel->SetSizer(lPanelSizer);

    serverText = createField(archipelagoPanel, "Server host (including port): ");
    slotNameText = createField(archipelagoPanel, "Slot name: ");
    passwordText = createField(archipelagoPanel, "Server password (leave empty if none): ");
    createButtonPanel(archipelagoPanel,[this](wxCommandEvent & aEvent){
        OnArchipelagoOKButton(aEvent);
    });
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
