/***************************************************************
 * Name:      EditGame.cpp
 * Purpose:   Code for Add/Edit Game Dialog Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-08
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "EditGame.h".
#include "LaunchConfig.h"
#include "GreenLauncherMain.h"

//(*InternalHeaders(EditGame)
#include <wx/button.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EditGame)
const long EditGame::ID_STATICTEXT1 = wxNewId();
const long EditGame::ID_GAMENAME = wxNewId();
const long EditGame::ID_CHECKBOX1 = wxNewId();
const long EditGame::ID_CHECKBOX2 = wxNewId();
const long EditGame::ID_STATICTEXT8 = wxNewId();
const long EditGame::ID_COMBOBOX1 = wxNewId();
const long EditGame::ID_STATICTEXT10 = wxNewId();
const long EditGame::ID_COMBOBOX2 = wxNewId();
const long EditGame::ID_STATICTEXT4 = wxNewId();
const long EditGame::ID_DATEPICKERCTRL1 = wxNewId();
const long EditGame::ID_STATICTEXT5 = wxNewId();
const long EditGame::ID_TEXTCTRL2 = wxNewId();
const long EditGame::ID_STATICTEXT6 = wxNewId();
const long EditGame::ID_TEXTCTRL3 = wxNewId();
const long EditGame::ID_STATICTEXT7 = wxNewId();
const long EditGame::ID_CHOICE1 = wxNewId();
const long EditGame::ID_STATICTEXT2 = wxNewId();
const long EditGame::ID_DATEPICKERCTRL2 = wxNewId();
const long EditGame::ID_STATICTEXT9 = wxNewId();
const long EditGame::ID_CHOICE2 = wxNewId();
const long EditGame::ID_STATICTEXT3 = wxNewId();
const long EditGame::ID_TEXTCTRL4 = wxNewId();
const long EditGame::ID_TEXTCTRL5 = wxNewId();
const long EditGame::ID_PANEL6 = wxNewId();
const long EditGame::ID_LISTBOOK1 = wxNewId();
const long EditGame::ID_PANEL1 = wxNewId();
const long EditGame::ID_STATICTEXT11 = wxNewId();
const long EditGame::ID_DATEPICKERCTRL3 = wxNewId();
const long EditGame::ID_STATICTEXT12 = wxNewId();
const long EditGame::ID_COMBOBOX3 = wxNewId();
const long EditGame::ID_STATICTEXT13 = wxNewId();
const long EditGame::ID_COMBOBOX4 = wxNewId();
const long EditGame::ID_STATICTEXT14 = wxNewId();
const long EditGame::ID_COMBOBOX5 = wxNewId();
const long EditGame::ID_STATICTEXT15 = wxNewId();
const long EditGame::ID_COMBOBOX6 = wxNewId();
const long EditGame::ID_STATICTEXT16 = wxNewId();
const long EditGame::ID_COMBOBOX7 = wxNewId();
const long EditGame::ID_STATICTEXT17 = wxNewId();
const long EditGame::ID_COMBOBOX8 = wxNewId();
const long EditGame::ID_STATICTEXT18 = wxNewId();
const long EditGame::ID_COMBOBOX9 = wxNewId();
const long EditGame::ID_STATICTEXT19 = wxNewId();
const long EditGame::ID_COMBOBOX10 = wxNewId();
const long EditGame::ID_STATICTEXT20 = wxNewId();
const long EditGame::ID_COMBOBOX11 = wxNewId();
const long EditGame::ID_STATICTEXT21 = wxNewId();
const long EditGame::ID_CHOICE3 = wxNewId();
const long EditGame::ID_STATICTEXT22 = wxNewId();
const long EditGame::ID_TEXTCTRL6 = wxNewId();
const long EditGame::ID_PANEL5 = wxNewId();
const long EditGame::ID_PANEL7 = wxNewId();
const long EditGame::ID_CHOICEBOOK1 = wxNewId();
const long EditGame::ID_PANEL2 = wxNewId();
const long EditGame::ID_PANEL3 = wxNewId();
const long EditGame::ID_PANEL4 = wxNewId();
const long EditGame::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditGame,wxDialog)
    //(*EventTable(EditGame)
    //*)
END_EVENT_TABLE()

EditGame::EditGame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EditGame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStdDialogButtonSizer* StdDialogButtonSizer1;

    Create(parent, wxID_ANY, _("Add / Edit Game"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    Move(wxPoint(-1,-1));
    SetMinSize(wxSize(620,440));
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxNB_TOP, _T("ID_NOTEBOOK1"));
    Notebook1->SetMinSize(wxSize(600,350));
    Panel6 = new wxPanel(Notebook1, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel6, _("Basic Info"));
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(1);
    StaticText1 = new wxStaticText(Panel6, ID_STATICTEXT1, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameName = new wxTextCtrl(Panel6, ID_GAMENAME, wxEmptyString, wxDefaultPosition, wxSize(200,23), 0, wxDefaultValidator, _T("ID_GAMENAME"));
    FlexGridSizer2->Add(GameName, 1, wxALL|wxEXPAND, 5);
    CheckBox1 = new wxCheckBox(Panel6, ID_CHECKBOX1, _("Favorite"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    FlexGridSizer2->Add(CheckBox1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox2 = new wxCheckBox(Panel6, ID_CHECKBOX2, _("Hidden"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    FlexGridSizer2->Add(CheckBox2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer5->AddGrowableCol(1);
    StaticText8 = new wxStaticText(Panel6, ID_STATICTEXT8, _("Categories"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer5->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox1 = new wxComboBox(Panel6, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    FlexGridSizer5->Add(ComboBox1, 1, wxALL|wxEXPAND, 5);
    StaticText10 = new wxStaticText(Panel6, ID_STATICTEXT10, _("Source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer5->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox2 = new wxComboBox(Panel6, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    FlexGridSizer5->Add(ComboBox2, 1, wxALL|wxEXPAND, 5);
    BoxSizer7->Add(FlexGridSizer5, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer1->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3->Add(StaticBoxSizer1, 0, wxALL|wxEXPAND, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel6, _("Stats"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 2, -6, 0);
    FlexGridSizer3->AddGrowableCol(1);
    StaticText4 = new wxStaticText(Panel6, ID_STATICTEXT4, _("Last Played"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DatePickerCtrl1 = new wxDatePickerCtrl(Panel6, ID_DATEPICKERCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL1"));
    FlexGridSizer3->Add(DatePickerCtrl1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel6, ID_STATICTEXT5, _("Time Played"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel6, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer3->Add(TextCtrl2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(Panel6, ID_STATICTEXT6, _("Play Count"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer3->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl3 = new wxTextCtrl(Panel6, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer3->Add(TextCtrl3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(Panel6, ID_STATICTEXT7, _("Completion Status"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer3->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(Panel6, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("None")) );
    Choice1->Append(_("Completed"));
    Choice1->Append(_("Finished"));
    Choice1->Append(_("Playing"));
    Choice1->Append(_("Want to Play"));
    Choice1->Append(_("Stalled"));
    Choice1->Append(_("Abandoned"));
    FlexGridSizer3->Add(Choice1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel6, ID_STATICTEXT2, _("Completion Date"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->Disable();
    FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DatePickerCtrl2 = new wxDatePickerCtrl(Panel6, ID_DATEPICKERCTRL2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL2"));
    DatePickerCtrl2->Disable();
    FlexGridSizer3->Add(DatePickerCtrl2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel6, ID_STATICTEXT9, _("Ownership"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer3->Add(StaticText9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice2 = new wxChoice(Panel6, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    FlexGridSizer3->Add(Choice2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel6, _("Review"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText3 = new wxStaticText(Panel6, ID_STATICTEXT3, _("Rating"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl4 = new wxTextCtrl(Panel6, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    FlexGridSizer4->Add(TextCtrl4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(FlexGridSizer4, 0, wxALL|wxEXPAND, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrl5 = new wxTextCtrl(Panel6, ID_TEXTCTRL5, _("Write a review here!"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    BoxSizer6->Add(TextCtrl5, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer3->Add(BoxSizer6, 4, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer4, 2, wxALL|wxEXPAND, 0);
    Panel6->SetSizer(BoxSizer3);
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxPoint(253,189), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Listbook1 = new wxListbook(Panel1, ID_LISTBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_LISTBOOK1"));
    BoxSizer1->Add(Listbook1, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Choicebook1 = new wxChoicebook(Panel2, ID_CHOICEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHOICEBOOK1"));
    Panel5 = new wxPanel(Choicebook1, ID_PANEL5, wxPoint(174,16), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer6->AddGrowableCol(1);
    FlexGridSizer6->AddGrowableCol(3);
    StaticText11 = new wxStaticText(Panel5, ID_STATICTEXT11, _("Release Date"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer6->Add(StaticText11, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DatePickerCtrl3 = new wxDatePickerCtrl(Panel5, ID_DATEPICKERCTRL3, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL3"));
    FlexGridSizer6->Add(DatePickerCtrl3, 1, wxALL|wxEXPAND, 5);
    StaticText12 = new wxStaticText(Panel5, ID_STATICTEXT12, _("Platform"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer6->Add(StaticText12, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox3 = new wxComboBox(Panel5, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
    FlexGridSizer6->Add(ComboBox3, 1, wxALL|wxEXPAND, 5);
    StaticText13 = new wxStaticText(Panel5, ID_STATICTEXT13, _("Developer"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    FlexGridSizer6->Add(StaticText13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox4 = new wxComboBox(Panel5, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
    FlexGridSizer6->Add(ComboBox4, 1, wxALL|wxEXPAND, 5);
    StaticText14 = new wxStaticText(Panel5, ID_STATICTEXT14, _("Publisher"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer6->Add(StaticText14, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox5 = new wxComboBox(Panel5, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
    FlexGridSizer6->Add(ComboBox5, 1, wxALL|wxEXPAND, 5);
    StaticText15 = new wxStaticText(Panel5, ID_STATICTEXT15, _("Genre"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer6->Add(StaticText15, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox6 = new wxComboBox(Panel5, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
    FlexGridSizer6->Add(ComboBox6, 1, wxALL|wxEXPAND, 5);
    StaticText16 = new wxStaticText(Panel5, ID_STATICTEXT16, _("Series"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer6->Add(StaticText16, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox7 = new wxComboBox(Panel5, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
    FlexGridSizer6->Add(ComboBox7, 1, wxALL|wxEXPAND, 5);
    StaticText17 = new wxStaticText(Panel5, ID_STATICTEXT17, _("Region"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer6->Add(StaticText17, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox8 = new wxComboBox(Panel5, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
    FlexGridSizer6->Add(ComboBox8, 1, wxALL|wxEXPAND, 5);
    StaticText18 = new wxStaticText(Panel5, ID_STATICTEXT18, _("Language"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer6->Add(StaticText18, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox9 = new wxComboBox(Panel5, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
    FlexGridSizer6->Add(ComboBox9, 1, wxALL|wxEXPAND, 5);
    StaticText19 = new wxStaticText(Panel5, ID_STATICTEXT19, _("Business Model"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer6->Add(StaticText19, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox10 = new wxComboBox(Panel5, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX10"));
    FlexGridSizer6->Add(ComboBox10, 1, wxALL|wxEXPAND, 5);
    StaticText20 = new wxStaticText(Panel5, ID_STATICTEXT20, _("Format"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    FlexGridSizer6->Add(StaticText20, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox11 = new wxComboBox(Panel5, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
    FlexGridSizer6->Add(ComboBox11, 1, wxALL|wxEXPAND, 5);
    StaticText21 = new wxStaticText(Panel5, ID_STATICTEXT21, _("Age Rating"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    FlexGridSizer6->Add(StaticText21, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice3 = new wxChoice(Panel5, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    FlexGridSizer6->Add(Choice3, 1, wxALL|wxEXPAND, 5);
    StaticText22 = new wxStaticText(Panel5, ID_STATICTEXT22, _("Score"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    FlexGridSizer6->Add(StaticText22, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl6 = new wxTextCtrl(Panel5, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    FlexGridSizer6->Add(TextCtrl6, 1, wxALL|wxEXPAND, 5);
    Panel5->SetSizer(FlexGridSizer6);
    Panel7 = new wxPanel(Choicebook1, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    Choicebook1->AddPage(Panel5, _("Main Details"), false);
    Choicebook1->AddPage(Panel7, _("Gameplay"), false);
    BoxSizer2->Add(Choicebook1, 1, wxALL|wxEXPAND, 5);
    Panel2->SetSizer(BoxSizer2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Notebook1->AddPage(Panel6, _("General"), false);
    Notebook1->AddPage(Panel1, _("Launch Configuration"), false);
    Notebook1->AddPage(Panel2, _("Metadata"), false);
    Notebook1->AddPage(Panel3, _("Scripts"), false);
    Notebook1->AddPage(Panel4, _("Installation"), false);
    FlexGridSizer1->Add(Notebook1, 1, wxALL|wxEXPAND, 0);
    StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
    StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
    StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_SAVE, wxEmptyString));
    StdDialogButtonSizer1->Realize();
    FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 10);
    SetSizer(FlexGridSizer1);
    Fit();
    Center();
    //*)
    SetupAction(wxString("Main"), true);
    Bind(wxEVT_BUTTON, (wxObjectEventFunction)&EditGame::OnDialogButtonClick, this);
}

EditGame::~EditGame()
{
    //(*Destroy(EditGame)
    //*)
}

EditGame::SetupAction(wxString actionName, bool isMain)
{
    LaunchConfig* MainLaunchPanel = new LaunchConfig(Listbook1);
    MainLaunchPanel->NameTextCtrl->SetValue(actionName);
    if (isMain) {
        MainLaunchPanel->NameTextCtrl->Disable();
    }
    Listbook1->AddPage(MainLaunchPanel, actionName, false);
}

EditGame::SaveGameToDatabase()
{
    GreenLauncherFrame* MainFrame = EditGame::GetParentForModalDialog();
    wxGameList* GL = MainFrame->GetGameList();
    GL->db->AddGame(wxString("INSERT into games values(NULL, 'MagicISO', 'C:\\Program Files (x86)\\MagicISO\\MagicISO.exe', 'C:\\Program Files (x86)\\MagicISO\\MagicISO.exe', 0, 2002)"));

}

EditGame::OnDialogButtonClick(wxCommandEvent& event)
{
    switch (event.GetId()) {
    case wxID_SAVE:
        SaveGameToDatabase();
    }
    EndModal(wxOK);
    event.Skip();
}

