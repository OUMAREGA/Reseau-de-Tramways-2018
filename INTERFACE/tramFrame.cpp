#include "TramFrame.h"

enum
{
    ID_IMPORTXML,
    ID_IMPORTEXE,
    ID_TXT_TMP_SIMU,
    ID_BTN_LANCER,
    ID_BTN_QUIT,
};
TramFrame::TramFrame(wxWindow *parent, wxWindowID id, const wxString &title)
    : wxFrame(parent, id, title)
{

    //Resize + panel + box definition
    SetSize(wxSize(325, 230));
    wxPanel * panel = new wxPanel(this);
    //panel->SetBackgroundColour(wxColour(* wxWHITE));
    wxBoxSizer * boxGlob = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * boxTop = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer * boxMid = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer * boxBot = new wxBoxSizer(wxHORIZONTAL);

    //MenuBar
    wxMenuBar * menuBar = new wxMenuBar(wxID_ANY);
    wxMenu * menuFichier = new wxMenu;
    menuFichier->Append(ID_IMPORTXML, "1- Charger le fichier XML");
    menuFichier->Append(ID_IMPORTEXE, "2- Charger le fichier.EXE");
    menuFichier->Append(ID_BTN_QUIT, "Quitter");
    menuBar->Append(menuFichier, "Fichier");
    SetMenuBar(menuBar);

    //Text controle informations -> TOP
    wxTextCtrl * txtInfos = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, 40), wxTE_MULTILINE | wxTE_NO_VSCROLL | wxTE_CENTRE | wxTE_RICH);
    txtInfos->SetDefaultStyle(wxTextAttr(*wxBLACK, panel->GetBackgroundColour()));
    txtInfos->AppendText("La fêntre de gestion de simulation de tramway : \n Veuillez importer un fichier XML valide.");
    txtInfos->Enable(false);
    d_txtAcceuil = txtInfos;
    boxTop->Add(txtInfos, 0, wxALL | wxALIGN_CENTER, 5);

    //Temps simulation -> MIDDLE
    wxStaticText * lblTmpSimu = new wxStaticText(panel, wxID_ANY, "Temps de simulation : ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    wxTextCtrl * txtTmpSimu = new wxTextCtrl(panel, ID_TXT_TMP_SIMU, "", wxDefaultPosition, wxSize(50, 20));
    txtTmpSimu->Enable(false);
    d_txtTmpSimu = txtTmpSimu;

    boxMid->Add(lblTmpSimu, 10, wxALL | wxALIGN_LEFT, 5);
    boxMid->Add(txtTmpSimu, 10, wxALL | wxALIGN_LEFT, 5);


    //Bouton de lancement ->  BOTTOM
    wxButton * btnLancer = new wxButton(panel, ID_BTN_LANCER, "Simuler !");
    wxButton * btnQuitter = new wxButton(panel, ID_BTN_QUIT, "Quitter");
    btnLancer->Enable(false);
    d_btnLancer = btnLancer;

    boxBot->Add(btnLancer, 0, wxALL | wxALIGN_CENTER, 5);
    boxBot->Add(btnQuitter, 0, wxALL | wxALIGN_CENTER, 5);

    //Boxing
    boxGlob->Add(boxTop, 40, wxALIGN_CENTER);
    boxGlob->Add(boxMid, 20, wxALIGN_CENTER);
    boxGlob->Add(boxBot, 40, wxALIGN_CENTER);
    SetSizer(boxGlob);

    //Bindings events
    Bind(wxEVT_COMMAND_MENU_SELECTED, &TramFrame::loadXML, this, ID_IMPORTXML); //Import XML menu
    Bind(wxEVT_COMMAND_MENU_SELECTED, &TramFrame::loadEXE, this, ID_IMPORTEXE); //Import EXE menu
    Bind(wxEVT_COMMAND_MENU_SELECTED, &TramFrame::onQuit, this, ID_BTN_QUIT); //Quit menu

    Bind(wxEVT_COMMAND_TEXT_UPDATED, &TramFrame::tmpSimuEntered, this, ID_TXT_TMP_SIMU);
    Bind(wxEVT_COMMAND_TEXT_ENTER, &TramFrame::onLancer, this, ID_TXT_TMP_SIMU);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TramFrame::onLancer, this, ID_BTN_LANCER);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &TramFrame::onQuit, this, ID_BTN_QUIT);
}
void TramFrame::loadXML(wxCommandEvent &event)
{
    wxFileDialog loadXML(this, "Selectionnez un fichier au format .xml", "", "", "Fichier XML (*.xml)|*.xml", wxFD_OPEN);
    if(loadXML.ShowModal() == wxID_OK)
    {
        d_pathXML = loadXML.GetPath(),
        wxMessageBox("Le fichier XML a été chargé avec succès.");
        d_txtAcceuil->SetValue("Fêntre de gestion de la simulation de tramway : \n Fichier XML chargé : " + loadXML.GetFilename());

        //Si le fichier EXE est saisi alors on active la suite
        if(d_pathEXE != "")
        {
            d_txtTmpSimu->Enable(true);
        }
        else
        {
            d_txtTmpSimu->Enable(false);
        }
    }
}
void TramFrame::loadEXE(wxCommandEvent &event)
{
    wxFileDialog loadEXE(this, "Selectionnez le fichier Tram au format .exe", "", "", "Fichier EXE (*.exe)|*.exe", wxFD_OPEN);
    if(loadEXE.ShowModal() == wxID_OK)
    {
        d_pathEXE = loadEXE.GetPath(),
        wxMessageBox("Le fichier EXE a été chargé avec succès.");

        //Si le fichier XML est saisi alors on active la suite
        if(d_pathXML != "")
        {
            d_txtTmpSimu->Enable(true);
        }
        else
        {
            d_txtTmpSimu->Enable(false);
        }
    }
}
void TramFrame::tmpSimuEntered(wxCommandEvent &event)
{
    if(d_txtTmpSimu->GetValue() == "")
    {
        d_btnLancer->Enable(false);
    }
    else
    {
        d_btnLancer->Enable(true);
        d_tmpSimu = d_txtTmpSimu->GetValue();
    }
}
void TramFrame::onLancer(wxCommandEvent &event)
{

    std::string req = "start " + d_pathEXE + " " + d_pathXML + " " + d_tmpSimu;
    system(req.c_str());
}
void TramFrame::onQuit(wxCommandEvent &event)
{
    Close(true);
}
