#include "LaunchConfig.h"

//(*InternalHeaders(LaunchConfig)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LaunchConfig)
const long LaunchConfig::ID_STATICTEXT1 = wxNewId();
const long LaunchConfig::ID_COMBOBOX1 = wxNewId();
const long LaunchConfig::ID_STATICTEXT2 = wxNewId();
const long LaunchConfig::ID_COMBOBOX2 = wxNewId();
const long LaunchConfig::ID_STATICTEXT3 = wxNewId();
const long LaunchConfig::ID_FILEPICKERCTRL1 = wxNewId();
const long LaunchConfig::ID_STATICTEXT4 = wxNewId();
const long LaunchConfig::ID_DIRPICKERCTRL1 = wxNewId();
const long LaunchConfig::ID_STATICTEXT6 = wxNewId();
const long LaunchConfig::ID_TEXTCTRL1 = wxNewId();
const long LaunchConfig::ID_STATICTEXT5 = wxNewId();
const long LaunchConfig::ID_BITMAPBUTTON3 = wxNewId();
const long LaunchConfig::ID_BITMAPBUTTON2 = wxNewId();
const long LaunchConfig::ID_BITMAPBUTTON1 = wxNewId();
const long LaunchConfig::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LaunchConfig,wxPanel)
    //(*EventTable(LaunchConfig)
    //*)
END_EVENT_TABLE()

LaunchConfig::LaunchConfig(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(LaunchConfig)
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Action"));
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(1);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox1 = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_COMBOBOX1"));
    ComboBox1->Append(_("Executable"));
    ComboBox1->Append(_("Emulated"));
    ComboBox1->Append(_("Tool"));
    ComboBox1->Append(_("Other"));
    FlexGridSizer1->Add(ComboBox1, 1, wxALL|wxEXPAND, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("System"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->Hide();
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox2 = new wxComboBox(Panel1, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, wxTAB_TRAVERSAL, wxDefaultValidator, _T("ID_COMBOBOX2"));
    ComboBox2->Hide();
    FlexGridSizer1->Add(ComboBox2, 1, wxALL|wxEXPAND, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Executable / ROM file"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FilePickerCtrl1 = new wxFilePickerCtrl(Panel1, ID_FILEPICKERCTRL1, wxEmptyString, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL|wxFLP_SMALL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
    FlexGridSizer1->Add(FilePickerCtrl1, 1, wxALL|wxEXPAND, 5);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Working Directory"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DirPickerCtrl1 = new wxDirPickerCtrl(Panel1, ID_DIRPICKERCTRL1, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
    FlexGridSizer1->Add(DirPickerCtrl1, 1, wxALL|wxEXPAND, 5);
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Arguments"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer1->Add(TextCtrl1, 1, wxALL|wxEXPAND, 5);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Icon"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton3 = new wxBitmapButton(Panel1, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(32,32), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    FlexGridSizer1->Add(BitmapButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton2 = new wxBitmapButton(Panel1, ID_BITMAPBUTTON2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PLUS")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
    FlexGridSizer1->Add(BitmapButton2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton1 = new wxBitmapButton(Panel1, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_MINUS")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    FlexGridSizer1->Add(BitmapButton1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer1);
    StaticBoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND, 5);
    SetSizer(StaticBoxSizer1);
    //*)
}

LaunchConfig::~LaunchConfig()
{
    //(*Destroy(LaunchConfig)
    //*)
}

