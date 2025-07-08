/***************************************************************
 * Name:      wxLaunchConfig.cpp
 * Purpose:   Code for Launch Configuration panel, as part of wxEditGame dialog
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-15
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "wxEditGame.h"
#include "wxLaunchConfig.h"

#include <wx/msgdlg.h>

//(*InternalHeaders(LaunchConfig)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LaunchConfig)
const long LaunchConfig::ID_NAMETEXT = wxNewId();
const long LaunchConfig::ID_ACTIONNAME = wxNewId();
const long LaunchConfig::ID_TYPETEXT = wxNewId();
const long LaunchConfig::ID_ACTIONTYPE = wxNewId();
const long LaunchConfig::ID_SYSTEMTEXT = wxNewId();
const long LaunchConfig::ID_ACTIONSYSTEM = wxNewId();
const long LaunchConfig::ID_FILETEXT = wxNewId();
const long LaunchConfig::ID_ACTIONFILE = wxNewId();
const long LaunchConfig::ID_WORKDIRTEXT = wxNewId();
const long LaunchConfig::ID_ACTIONWORKDIR = wxNewId();
const long LaunchConfig::ID_ARGTEXT = wxNewId();
const long LaunchConfig::ID_ACTIONARGS = wxNewId();
const long LaunchConfig::ID_ICONTEXT = wxNewId();
const long LaunchConfig::ID_ACTIONICON = wxNewId();
const long LaunchConfig::ID_PANEL1 = wxNewId();
const long LaunchConfig::ID_ADDACTIONBUTTON = wxNewId();
const long LaunchConfig::ID_DELETEACTIONBUTTON = wxNewId();
const long LaunchConfig::ID_PANEL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LaunchConfig,wxPanel)
    //(*EventTable(LaunchConfig)
    //*)
END_EVENT_TABLE()

LaunchConfig::LaunchConfig(wxWindow* parent, wxString actionName, bool isMain, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(LaunchConfig)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* wxBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    wxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(1);
    NameText = new wxStaticText(Panel1, ID_NAMETEXT, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_NAMETEXT"));
    FlexGridSizer1->Add(NameText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionName = new wxTextCtrl(Panel1, ID_ACTIONNAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ACTIONNAME"));
    FlexGridSizer1->Add(ActionName, 1, wxALL|wxEXPAND, 5);
    TypeText = new wxStaticText(Panel1, ID_TYPETEXT, _("Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TYPETEXT"));
    FlexGridSizer1->Add(TypeText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionType = new wxChoice(Panel1, ID_ACTIONTYPE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ACTIONTYPE"));
    ActionType->SetSelection( ActionType->Append(_("Standalone")) );
    ActionType->Append(_("Emulated"));
    ActionType->Append(_("Tool"));
    ActionType->Append(_("Other"));
    FlexGridSizer1->Add(ActionType, 1, wxALL|wxEXPAND, 5);
    SystemText = new wxStaticText(Panel1, ID_SYSTEMTEXT, _("System"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SYSTEMTEXT"));
    SystemText->Hide();
    FlexGridSizer1->Add(SystemText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionSystem = new wxComboBox(Panel1, ID_ACTIONSYSTEM, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_ACTIONSYSTEM"));
    ActionSystem->Hide();
    FlexGridSizer1->Add(ActionSystem, 1, wxALL|wxEXPAND, 5);
    FileText = new wxStaticText(Panel1, ID_FILETEXT, _("Executable Path"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_FILETEXT"));
    FlexGridSizer1->Add(FileText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionPath = new wxFilePickerCtrl(Panel1, ID_ACTIONFILE, _T("C:\\"), wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL|wxFLP_SMALL, wxDefaultValidator, _T("ID_ACTIONFILE"));
    FlexGridSizer1->Add(ActionPath, 1, wxALL|wxEXPAND, 5);
    WorkDirText = new wxStaticText(Panel1, ID_WORKDIRTEXT, _("Working Directory"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WORKDIRTEXT"));
    FlexGridSizer1->Add(WorkDirText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionWorkingDirectory = new wxDirPickerCtrl(Panel1, ID_ACTIONWORKDIR, _T("C:\\"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_ACTIONWORKDIR"));
    FlexGridSizer1->Add(ActionWorkingDirectory, 1, wxALL|wxEXPAND, 5);
    ArgText = new wxStaticText(Panel1, ID_ARGTEXT, _("Arguments"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ARGTEXT"));
    FlexGridSizer1->Add(ArgText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionArguments = new wxTextCtrl(Panel1, ID_ACTIONARGS, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ACTIONARGS"));
    FlexGridSizer1->Add(ActionArguments, 1, wxALL|wxEXPAND, 5);
    IconText = new wxStaticText(Panel1, ID_ICONTEXT, _("Icon"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ICONTEXT"));
    FlexGridSizer1->Add(IconText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ActionIcon = new wxBitmapButton(Panel1, ID_ACTIONICON, wxNullBitmap, wxDefaultPosition, wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_ACTIONICON"));
    FlexGridSizer1->Add(ActionIcon, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    wxBoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND, 5);
    wxBoxSizer1->Add(-1,-1,1, wxALL|wxEXPAND, 5);
    Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    AddActionButton = new wxBitmapButton(Panel2, ID_ADDACTIONBUTTON, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PLUS")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_ADDACTIONBUTTON"));
    BoxSizer1->Add(AddActionButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(-1,-1,1, wxALL|wxEXPAND, 5);
    DeleteActionButton = new wxBitmapButton(Panel2, ID_DELETEACTIONBUTTON, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_MINUS")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_DELETEACTIONBUTTON"));
    BoxSizer1->Add(DeleteActionButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(BoxSizer1);
    wxBoxSizer1->Add(Panel2, 0, wxALL|wxEXPAND, 5);
    SetSizer(wxBoxSizer1);
    IconFileDialog = new wxFileDialog(this, _("Select file for icon"), _("C:\\"), wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_ACTIONNAME,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&LaunchConfig::OnActionNameText);
    Connect(ID_ACTIONTYPE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&LaunchConfig::OnTypeChoiceSelect);
    Connect(ID_ACTIONFILE,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&LaunchConfig::OnFileCtrlFileChanged);
    Connect(ID_ACTIONICON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LaunchConfig::OnActionIconClick);
    Connect(ID_ADDACTIONBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LaunchConfig::OnAddActionButtonClick);
    Connect(ID_DELETEACTIONBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LaunchConfig::OnDeleteActionButtonClick);
    //*)
    // Here we set the name of the action and if it's the main one, we disable it so the name can't be changed
    // We also disable the delete button for this panel
    ActionName->ChangeValue(actionName);
    this->isMain = isMain;
    if (isMain) {
        ActionName->Disable();
        DeleteActionButton->Disable();
    }
}

LaunchConfig::~LaunchConfig()
{
    //(*Destroy(LaunchConfig)
    IconFileDialog->Destroy();
    //*)
}

void LaunchConfig::SetIcon(wxString path) {
    ActionIcon->SetBitmap(wxIcon(wxIconLocation(path, 0)));
    IconFileDialog->SetPath(path);
    //if (isMain) {
        //wxListbook* parent1 = GetParent();
        //EditGame* parent = ((wxListbook*) GetParent())->GetParent();
        //if (parent->GameIcon
    //}
}

void LaunchConfig::OnAddActionButtonClick(wxCommandEvent& event)
{
    wxListbook* parent = GetParent();
    wxString actionName = wxString("New Action");
    LaunchConfig* launchPanel = new LaunchConfig(parent, actionName, false);
    parent->AddPage(launchPanel, actionName, true);
}

void LaunchConfig::OnDeleteActionButtonClick(wxCommandEvent& event)
{
    wxListbook* parent = GetParent();
    parent->DeletePage(parent->FindPage(this));
}

void LaunchConfig::OnFileCtrlFileChanged(wxFileDirPickerEvent& event)
{
    ActionWorkingDirectory->SetPath(ActionPath->GetFileName().GetPath());
    SetIcon(ActionPath->GetFileName().GetFullPath());
}

void LaunchConfig::OnTypeChoiceSelect(wxCommandEvent& event)
{
    if (ActionType->GetSelection() != this->lastTypeSelection) {
        lastTypeSelection = ActionType->GetSelection();
        switch(ActionType->GetSelection()) {
            case 0:
                FileText->SetLabel(wxString("Executable File"));
                SystemText->Show(false);
                ActionSystem->Show(false);
                WorkDirText->Show(true);
                ActionWorkingDirectory->Show(true);
                Layout();
                break;
            case 1:
                FileText->SetLabel(wxString("ROM File"));
                SystemText->Show(true);
                ActionSystem->Show(true);
                WorkDirText->Show(false);
                ActionWorkingDirectory->Show(false);
                Layout();
                break;
        }
        // Reset values
        ActionPath->SetPath(wxString(""));
        ActionWorkingDirectory->SetPath(wxString(""));
        ActionSystem->SetValue(wxString(""));
    }
}

void LaunchConfig::OnActionNameText(wxCommandEvent& event)
{
    wxListbook* parent = GetParent();
    if (parent->GetSelection() != 0) {
         parent->SetPageText(parent->GetSelection(), ActionName->GetValue());
    }

}

void LaunchConfig::OnActionIconClick(wxCommandEvent& event)
{
    int rc = IconFileDialog->ShowModal();
    if (rc == wxID_OK) {
        SetIcon(IconFileDialog->GetPath());
    }
}
