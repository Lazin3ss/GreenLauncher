#include "LaunchConfig.h"
#include "EditGame.h"

//(*InternalHeaders(LaunchConfig)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LaunchConfig)
const long LaunchConfig::ID_STATICTEXT7 = wxNewId();
const long LaunchConfig::ID_NAMETEXT = wxNewId();
const long LaunchConfig::ID_STATICTEXT1 = wxNewId();
const long LaunchConfig::ID_TYPECOMBOBOX = wxNewId();
const long LaunchConfig::ID_STATICTEXT2 = wxNewId();
const long LaunchConfig::ID_SYSCOMBOBOX = wxNewId();
const long LaunchConfig::ID_STATICTEXT3 = wxNewId();
const long LaunchConfig::ID_FILECTRL = wxNewId();
const long LaunchConfig::ID_STATICTEXT4 = wxNewId();
const long LaunchConfig::ID_WORKDIRCTRL = wxNewId();
const long LaunchConfig::ID_STATICTEXT6 = wxNewId();
const long LaunchConfig::ID_ARGTEX = wxNewId();
const long LaunchConfig::ID_STATICTEXT5 = wxNewId();
const long LaunchConfig::ID_BITMAPBUTTON3 = wxNewId();
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
    StaticText7 = new wxStaticText(Panel1, ID_STATICTEXT7, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer1->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    NameTextCtrl = new wxTextCtrl(Panel1, ID_NAMETEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_NAMETEXT"));
    FlexGridSizer1->Add(NameTextCtrl, 1, wxALL|wxEXPAND, 5);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TypeComboBox = new wxComboBox(Panel1, ID_TYPECOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_TYPECOMBOBOX"));
    TypeComboBox->SetSelection( TypeComboBox->Append(_("Standalone")) );
    TypeComboBox->Append(_("Emulated"));
    TypeComboBox->Append(_("Tool"));
    TypeComboBox->Append(_("Other"));
    FlexGridSizer1->Add(TypeComboBox, 1, wxALL|wxEXPAND, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("System"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->Hide();
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SystemComboBox = new wxComboBox(Panel1, ID_SYSCOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_SYSCOMBOBOX"));
    SystemComboBox->Hide();
    FlexGridSizer1->Add(SystemComboBox, 1, wxALL|wxEXPAND, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Executable / ROM file"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FileCtrl = new wxFilePickerCtrl(Panel1, ID_FILECTRL, wxEmptyString, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL|wxFLP_SMALL, wxDefaultValidator, _T("ID_FILECTRL"));
    FlexGridSizer1->Add(FileCtrl, 1, wxALL|wxEXPAND, 5);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Working Directory"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WorkingDirectoryCtrl = new wxDirPickerCtrl(Panel1, ID_WORKDIRCTRL, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_WORKDIRCTRL"));
    FlexGridSizer1->Add(WorkingDirectoryCtrl, 1, wxALL|wxEXPAND, 5);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Arguments"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ArgumentsTextCtrl = new wxTextCtrl(Panel1, ID_ARGTEX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ARGTEX"));
    FlexGridSizer1->Add(ArgumentsTextCtrl, 1, wxALL|wxEXPAND, 5);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Icon"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton3 = new wxBitmapButton(Panel1, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    FlexGridSizer1->Add(BitmapButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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

    Connect(ID_ADDACTIONBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LaunchConfig::OnAddActionButtonClick);
    Connect(ID_DELETEACTIONBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LaunchConfig::OnDeleteActionButtonClick);
    //*)
    NameTextCtrl->SetValue(actionName);
    this->isMain = isMain;
    if (isMain) {
        NameTextCtrl->Disable();
        DeleteActionButton->Disable();
    }
}

LaunchConfig::~LaunchConfig()
{
    //(*Destroy(LaunchConfig)
    //*)
}

void LaunchConfig::OnAddActionButtonClick(wxCommandEvent& event)
{
    wxListbook* parent = GetParent();
    wxString actionName = wxString("New Action");
    LaunchConfig* LaunchPanel = new LaunchConfig(parent, actionName, false);
    parent->AddPage(LaunchPanel, actionName, true);
}

void LaunchConfig::OnDeleteActionButtonClick(wxCommandEvent& event)
{
    wxListbook* parent = GetParent();
    parent->DeletePage(parent->FindPage(this));
}
