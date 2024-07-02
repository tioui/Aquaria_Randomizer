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
#include <wx/checkbox.h>

#include <utility>

/**
 * Initialisation of the window
 *
 * @param userDataFolder The folder to store the launcher.xml save file
 * @param boxing The box to store the generated randomizer
 */
RandomizerLauncherFrame::RandomizerLauncherFrame(std::string aUserDataFolder, RandomizerBoxing *aBoxing) :
                                wxFrame(nullptr, wxID_ANY, "Aquaria Randomizer Launcher") {
    userDataFolder = std::move(aUserDataFolder);
    randomizerBoxing = aBoxing;
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
    loadLauncherLocalInfo();
}

/**
 * Load the save XML values
 */
void RandomizerLauncherFrame::loadLauncherLocalInfo() {
    std::string filename;
    xmlLocalPath = "";
    xmlServer = "";
    xmlSlotName = "";
    xmlPassword = "";
    xmlFilter = false;

#if defined(BBGE_BUILD_UNIX)
    filename = userDataFolder + "/launcher.xml";
#elif defined(BBGE_BUILD_WINDOWS)
    filename = "launcher.xml";
#endif

    if (std::filesystem::exists(filename)) {
        std::ifstream fileStream(filename);
        std::stringstream fileBuffer;
        fileBuffer << fileStream.rdbuf();

        TinyXMLDocument doc;
        if (doc.Parse(fileBuffer.str().c_str()) == XML_SUCCESS) {
            XMLElement *xml_local = doc.FirstChildElement("Local");
            if (xml_local)
            {
                xmlLocalPath = xml_local->Attribute("path");
                jsonFileText->SetValue(wxString::FromUTF8(xml_local->Attribute("path")));
            }

            XMLElement *xml_archipelago = doc.FirstChildElement("Archipelago");
            if (xml_archipelago)
            {
                xmlServer = xml_archipelago->Attribute("server");
                serverText->SetValue(wxString::FromUTF8(xml_archipelago->Attribute("server")));
                xmlSlotName = xml_archipelago->Attribute("slotname");
                slotNameText->SetValue(wxString::FromUTF8(xml_archipelago->Attribute("slotname")));
                xmlPassword = xml_archipelago->Attribute("password");
                passwordText->SetValue(wxString::FromUTF8(xml_archipelago->Attribute("password")));
                xmlFilter = xml_archipelago->IntAttribute("filterself");
                filterSelf->SetValue(xmlFilter);
                xmlDeathLink = xml_archipelago->IntAttribute("deathLink");
                deathLink->SetValue(xmlDeathLink);
            }
        }
    }
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
 * Create a panel that contain a label.
 *
 * @param parent the panel to put the new field panel in.
 * @param labelText The text to put on the label.
 * @return The panel of the field .
 */
wxPanel *RandomizerLauncherFrame::prepareFieldPanel(wxWindow *aParent, const std::string& aLabelText) {
    wxPanel *lFieldPanel = new wxPanel(aParent,wxID_ANY);
    wxBoxSizer* lfieldPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    lFieldPanel->SetSizer(lfieldPanelSizer);
    aParent->GetSizer()->Add(lFieldPanel, 0, wxEXPAND);
    wxStaticText * lTextLabel = new wxStaticText(lFieldPanel, wxID_ANY, aLabelText);
    lfieldPanelSizer->Add(lTextLabel, 0, wxALIGN_CENTER_VERTICAL);
    return lFieldPanel;
}


/**
 * Create a panel that contain a label and a text view.
 *
 * @param aParent the panel to put the new field panel in.
 * @param aLabelText The text to put on the label.
 * @return The text view of the field .
 */
wxTextCtrl *RandomizerLauncherFrame::createField(wxWindow *aParent, const std::string& aLabelText) {
    wxPanel *lFieldPanel = prepareFieldPanel(aParent, aLabelText);
    wxTextCtrl *lText = new wxTextCtrl(lFieldPanel, wxID_EDIT);
    lFieldPanel->GetSizer()->Add(lText, 1, wxALIGN_TOP);
    return lText;
}

/**
 * Create a panel that contain a label and a checkbox
 *
 * @param aParent the panel to put the new field panel in.
 * @param aLabelText The text to put on the label.
 * @return The checkbox of the field .
 */
wxCheckBox *RandomizerLauncherFrame::createCheckBox(wxWindow *aParent, const std::string& aLabelText) {
    wxPanel *lFieldPanel = prepareFieldPanel(aParent, aLabelText);
    wxCheckBox *lCheckBox = new wxCheckBox(lFieldPanel, wxID_IGNORE, "");
    lFieldPanel->GetSizer()->Add(lCheckBox, 1, wxALIGN_TOP);
    return lCheckBox;
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
    lButtonPanelSizer->Add(lOk, 0, wxALIGN_TOP);
    lOk->Bind(wxEVT_BUTTON, aHandler, wxID_OK);
    wxButton *lCancel = new wxButton(lButtonPanel, wxID_CANCEL, "Cancel");
    lButtonPanelSizer->Add(lCancel, 0, wxALIGN_TOP);
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
        jsonFileText->SetValue(openFileDialog->GetPath());
    }
}

/**
 * Launched when the user click the "OK" button of the local randomizer
 * @param aEvent Information about the event (Not used)
 */
void RandomizerLauncherFrame::OnLocalOKButton(wxCommandEvent& aEvent) {
    const char* test = (const char *) jsonFileText->GetValue().mb_str();
    wxCSConv cs( wxFONTENCODING_UTF8 );
    std::string lFilename = std::string(cs.cWC2MB(jsonFileText->GetValue().wc_str()));
    RandomizerLocal *lRandomizer = new RandomizerLocal(lFilename);
    if (lRandomizer->hasError()) {
        wxMessageBox(lRandomizer->getErrorMessage(), wxT("Randomizer error"), wxICON_ERROR);
    } else {
        saveLauncherLocalInfo();
        randomizerBoxing->setRandomizer(lRandomizer);
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
    filterSelf = createCheckBox(lArchipelagoPanel, "Filter messages not related to me: ");
    includeSpace(lArchipelagoPanel, 10);
    deathLink = createCheckBox(lArchipelagoPanel, "Activate Death Link: ");
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
            filterSelf->GetValue(),
            deathLink->GetValue());
    if (lRandomizer->hasError()) {
        wxMessageBox(lRandomizer->getErrorMessage(), wxT("Randomizer error"), wxICON_ERROR);
    } else {
        saveLauncherArchipelagoInfo();
        randomizerBoxing->setRandomizer(lRandomizer);
        Close();
    }
}

void RandomizerLauncherFrame::saveLauncherArchipelagoInfo() {
    TinyXMLDocument doc;
    {
        XMLElement *xml_local = doc.NewElement("Local");
        {
            xml_local->SetAttribute("path", xmlLocalPath.c_str());
        }
        doc.InsertEndChild(xml_local);
        XMLElement *xml_archipelago = doc.NewElement("Archipelago");
        {
            xml_archipelago->SetAttribute("server", serverText->GetValue().utf8_str());
            xml_archipelago->SetAttribute("slotname", slotNameText->GetValue().utf8_str());
            xml_archipelago->SetAttribute("password", passwordText->GetValue().utf8_str());
            xml_archipelago->SetAttribute("filterself", filterSelf->GetValue());
            xml_archipelago->SetAttribute("deathLink", deathLink->GetValue());
        }
        doc.InsertEndChild(xml_archipelago);
    }
#if defined(BBGE_BUILD_UNIX)
    doc.SaveFile((userDataFolder + "/launcher.xml").c_str());
#elif defined(BBGE_BUILD_WINDOWS)
    doc.SaveFile("launcher.xml");
#endif
}

void RandomizerLauncherFrame::saveLauncherLocalInfo() {
    TinyXMLDocument doc;
    {
        XMLElement *xml_local = doc.NewElement("Local");
        {
            xml_local->SetAttribute("path", jsonFileText->GetValue().utf8_str());
        }
        doc.InsertEndChild(xml_local);
        XMLElement *xml_archipelago = doc.NewElement("Archipelago");
        {
            xml_archipelago->SetAttribute("server", xmlServer.c_str());
            xml_archipelago->SetAttribute("slotname", xmlSlotName.c_str());
            xml_archipelago->SetAttribute("password", xmlPassword.c_str());
            xml_archipelago->SetAttribute("filterself", xmlFilter);
            xml_archipelago->SetAttribute("deathLink", xmlDeathLink);
        }
        doc.InsertEndChild(xml_archipelago);
    }
#if defined(BBGE_BUILD_UNIX)
    doc.SaveFile((userDataFolder + "/launcher.xml").c_str());
#elif defined(BBGE_BUILD_WINDOWS)
    doc.SaveFile("launcher.xml");
#endif
}

