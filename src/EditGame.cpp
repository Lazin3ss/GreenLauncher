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
#include "Database.h"

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
const long EditGame::ID_ACTIONLISTBOOK = wxNewId();
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
const long EditGame::ID_STATICTEXT32 = wxNewId();
const long EditGame::ID_TEXTCTRL1 = wxNewId();
const long EditGame::ID_PANEL5 = wxNewId();
const long EditGame::ID_STATICTEXT25 = wxNewId();
const long EditGame::ID_COMBOBOX12 = wxNewId();
const long EditGame::ID_STATICTEXT28 = wxNewId();
const long EditGame::ID_COMBOBOX13 = wxNewId();
const long EditGame::ID_STATICTEXT33 = wxNewId();
const long EditGame::ID_TEXTCTRL7 = wxNewId();
const long EditGame::ID_TEXTCTRL8 = wxNewId();
const long EditGame::ID_TEXTCTRL9 = wxNewId();
const long EditGame::ID_PANEL11 = wxNewId();
const long EditGame::ID_STATICTEXT34 = wxNewId();
const long EditGame::ID_TEXTCTRL10 = wxNewId();
const long EditGame::ID_TEXTCTRL11 = wxNewId();
const long EditGame::ID_TEXTCTRL12 = wxNewId();
const long EditGame::ID_PANEL13 = wxNewId();
const long EditGame::ID_STATICTEXT23 = wxNewId();
const long EditGame::ID_CHECKLISTBOX1 = wxNewId();
const long EditGame::ID_STATICTEXT24 = wxNewId();
const long EditGame::ID_CHECKLISTBOX2 = wxNewId();
const long EditGame::ID_STATICTEXT27 = wxNewId();
const long EditGame::ID_CHECKLISTBOX4 = wxNewId();
const long EditGame::ID_STATICTEXT26 = wxNewId();
const long EditGame::ID_CHECKLISTBOX3 = wxNewId();
const long EditGame::ID_PANEL7 = wxNewId();
const long EditGame::ID_STATICTEXT35 = wxNewId();
const long EditGame::ID_CHECKLISTBOX5 = wxNewId();
const long EditGame::ID_STATICTEXT31 = wxNewId();
const long EditGame::ID_CHECKLISTBOX6 = wxNewId();
const long EditGame::ID_STATICTEXT29 = wxNewId();
const long EditGame::ID_CHECKLISTBOX7 = wxNewId();
const long EditGame::ID_STATICTEXT30 = wxNewId();
const long EditGame::ID_CHECKLISTBOX8 = wxNewId();
const long EditGame::ID_STATICTEXT36 = wxNewId();
const long EditGame::ID_CHECKLISTBOX9 = wxNewId();
const long EditGame::ID_STATICTEXT37 = wxNewId();
const long EditGame::ID_TEXTCTRL13 = wxNewId();
const long EditGame::ID_PANEL8 = wxNewId();
const long EditGame::ID_PANEL9 = wxNewId();
const long EditGame::ID_PANEL10 = wxNewId();
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

EditGame::EditGame(wxWindow* parent, wxWindowID id)
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
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
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
    StaticText4->Disable();
    FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DatePickerCtrl1 = new wxDatePickerCtrl(Panel6, ID_DATEPICKERCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL1"));
    DatePickerCtrl1->Disable();
    FlexGridSizer3->Add(DatePickerCtrl1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel6, ID_STATICTEXT5, _("Time Played"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText5->Disable();
    FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel6, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl2->Disable();
    FlexGridSizer3->Add(TextCtrl2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(Panel6, ID_STATICTEXT6, _("Play Count"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText6->Disable();
    FlexGridSizer3->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl3 = new wxTextCtrl(Panel6, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl3->Disable();
    FlexGridSizer3->Add(TextCtrl3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText7 = new wxStaticText(Panel6, ID_STATICTEXT7, _("Completion Status"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    StaticText7->Disable();
    FlexGridSizer3->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(Panel6, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("None")) );
    Choice1->Append(_("Completed"));
    Choice1->Append(_("Finished"));
    Choice1->Append(_("Playing"));
    Choice1->Append(_("Want to Play"));
    Choice1->Append(_("Stalled"));
    Choice1->Append(_("Abandoned"));
    Choice1->Disable();
    FlexGridSizer3->Add(Choice1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel6, ID_STATICTEXT2, _("Completion Date"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->Disable();
    FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DatePickerCtrl2 = new wxDatePickerCtrl(Panel6, ID_DATEPICKERCTRL2, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL2"));
    DatePickerCtrl2->Disable();
    FlexGridSizer3->Add(DatePickerCtrl2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel6, ID_STATICTEXT9, _("Ownership"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText9->Disable();
    FlexGridSizer3->Add(StaticText9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Choice2 = new wxChoice(Panel6, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    Choice2->Disable();
    FlexGridSizer3->Add(Choice2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel6, _("Review"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText3 = new wxStaticText(Panel6, ID_STATICTEXT3, _("Rating"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText3->Disable();
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl4 = new wxTextCtrl(Panel6, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    TextCtrl4->Disable();
    FlexGridSizer4->Add(TextCtrl4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(FlexGridSizer4, 0, wxALL|wxEXPAND, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    TextCtrl5 = new wxTextCtrl(Panel6, ID_TEXTCTRL5, _("Write a review here!"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    TextCtrl5->Disable();
    BoxSizer6->Add(TextCtrl5, 1, wxALL|wxEXPAND, 5);
    StaticBoxSizer3->Add(BoxSizer6, 4, wxALL|wxEXPAND, 5);
    BoxSizer4->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND, 5);
    BoxSizer3->Add(BoxSizer4, 2, wxALL|wxEXPAND, 0);
    Panel6->SetSizer(BoxSizer3);
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxPoint(253,189), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    ActionListbook = new wxListbook(Panel1, ID_ACTIONLISTBOOK, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT, _T("ID_ACTIONLISTBOOK"));
    BoxSizer1->Add(ActionListbook, 1, wxALL|wxEXPAND, 5);
    Panel1->SetSizer(BoxSizer1);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Choicebook1 = new wxChoicebook(Panel2, ID_CHOICEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHOICEBOOK1"));
    Panel5 = new wxPanel(Choicebook1, ID_PANEL5, wxPoint(174,16), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer6->AddGrowableCol(1);
    FlexGridSizer6->AddGrowableCol(3);
    FlexGridSizer6->AddGrowableRow(6);
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
    StaticText19 = new wxStaticText(Panel5, ID_STATICTEXT19, _("License Model"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
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
    StaticText32 = new wxStaticText(Panel5, ID_STATICTEXT32, _("Description"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
    FlexGridSizer6->Add(StaticText32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel5, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetToolTip(_("Add a description!"));
    TextCtrl1->SetHelpText(_("Add a description!"));
    FlexGridSizer6->Add(TextCtrl1, 1, wxALL|wxEXPAND, 5);
    Panel5->SetSizer(FlexGridSizer6);
    Panel7 = new wxPanel(Choicebook1, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    FlexGridSizer7 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer7->AddGrowableCol(1);
    FlexGridSizer7->AddGrowableCol(3);
    StaticText25 = new wxStaticText(Panel7, ID_STATICTEXT25, _("Gameplay Type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    StaticText25->Disable();
    FlexGridSizer7->Add(StaticText25, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox12 = new wxComboBox(Panel7, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX12"));
    ComboBox12->Disable();
    FlexGridSizer7->Add(ComboBox12, 1, wxALL|wxEXPAND, 5);
    StaticText28 = new wxStaticText(Panel7, ID_STATICTEXT28, _("Theme / Setting"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
    StaticText28->Disable();
    FlexGridSizer7->Add(StaticText28, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox13 = new wxComboBox(Panel7, ID_COMBOBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX13"));
    ComboBox13->Disable();
    FlexGridSizer7->Add(ComboBox13, 1, wxALL|wxEXPAND, 5);
    StaticText33 = new wxStaticText(Panel7, ID_STATICTEXT33, _("Main Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
    StaticText33->Disable();
    FlexGridSizer7->Add(StaticText33, 2, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel11 = new wxPanel(Panel7, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
    TextCtrl7 = new wxTextCtrl(Panel11, ID_TEXTCTRL7, wxEmptyString, wxPoint(0,0), wxSize(48,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    TextCtrl7->Disable();
    TextCtrl7->SetHelpText(_("hh"));
    TextCtrl8 = new wxTextCtrl(Panel11, ID_TEXTCTRL8, wxEmptyString, wxPoint(56,0), wxSize(48,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    TextCtrl8->Disable();
    TextCtrl9 = new wxTextCtrl(Panel11, ID_TEXTCTRL9, wxEmptyString, wxPoint(112,0), wxSize(48,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    TextCtrl9->Disable();
    FlexGridSizer7->Add(Panel11, 1, wxALL|wxEXPAND, 5);
    StaticText34 = new wxStaticText(Panel7, ID_STATICTEXT34, _("Completion Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
    StaticText34->Disable();
    FlexGridSizer7->Add(StaticText34, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel13 = new wxPanel(Panel7, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    TextCtrl10 = new wxTextCtrl(Panel13, ID_TEXTCTRL10, wxEmptyString, wxPoint(0,0), wxSize(48,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    TextCtrl10->Disable();
    TextCtrl11 = new wxTextCtrl(Panel13, ID_TEXTCTRL11, wxEmptyString, wxPoint(56,0), wxSize(48,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
    TextCtrl11->Disable();
    TextCtrl12 = new wxTextCtrl(Panel13, ID_TEXTCTRL12, wxEmptyString, wxPoint(112,0), wxSize(48,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    TextCtrl12->Disable();
    TextCtrl12->SetHelpText(_("ss"));
    FlexGridSizer7->Add(Panel13, 1, wxALL|wxEXPAND, 5);
    StaticText23 = new wxStaticText(Panel7, ID_STATICTEXT23, _("Player Modes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    StaticText23->Disable();
    FlexGridSizer7->Add(StaticText23, 2, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox1 = new wxCheckListBox(Panel7, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    CheckListBox1->Append(_("Singleplayer"));
    CheckListBox1->Append(_("Multiplayer"));
    CheckListBox1->Append(_("Local Cooperative"));
    CheckListBox1->Append(_("Local Competitive"));
    CheckListBox1->Append(_("Online Cooperative"));
    CheckListBox1->Append(_("Online Competitive"));
    CheckListBox1->Disable();
    FlexGridSizer7->Add(CheckListBox1, 2, wxALL|wxEXPAND, 5);
    StaticText24 = new wxStaticText(Panel7, ID_STATICTEXT24, _("Perspective"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    StaticText24->Disable();
    FlexGridSizer7->Add(StaticText24, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox2 = new wxCheckListBox(Panel7, ID_CHECKLISTBOX2, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX2"));
    CheckListBox2->Append(_("Bird\'s Eye"));
    CheckListBox2->Append(_("Side View"));
    CheckListBox2->Append(_("Isometric"));
    CheckListBox2->Append(_("First Person"));
    CheckListBox2->Append(_("Third Person"));
    CheckListBox2->Append(_("Auditory"));
    CheckListBox2->Append(_("Text"));
    CheckListBox2->Disable();
    FlexGridSizer7->Add(CheckListBox2, 1, wxALL|wxEXPAND, 5);
    StaticText27 = new wxStaticText(Panel7, ID_STATICTEXT27, _("Interface / Control"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    StaticText27->Disable();
    FlexGridSizer7->Add(StaticText27, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox4 = new wxCheckListBox(Panel7, ID_CHECKLISTBOX4, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX4"));
    CheckListBox4->Append(_("Direct Control"));
    CheckListBox4->Append(_("Menu Structures"));
    CheckListBox4->Append(_("Motion Control"));
    CheckListBox4->Append(_("Multiple units/characters Control"));
    CheckListBox4->Append(_("Point and Select"));
    CheckListBox4->Append(_("Text Parser"));
    CheckListBox4->Append(_("Voice Control"));
    CheckListBox4->Disable();
    FlexGridSizer7->Add(CheckListBox4, 1, wxALL|wxEXPAND, 5);
    StaticText26 = new wxStaticText(Panel7, ID_STATICTEXT26, _("Pacing"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    StaticText26->Disable();
    FlexGridSizer7->Add(StaticText26, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox3 = new wxCheckListBox(Panel7, ID_CHECKLISTBOX3, wxDefaultPosition, wxSize(-1,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX3"));
    CheckListBox3->Append(_("Meditative / Zen"));
    CheckListBox3->Append(_("Persistent"));
    CheckListBox3->Append(_("Real-Time"));
    CheckListBox3->Append(_("Turn-Based"));
    CheckListBox3->Disable();
    FlexGridSizer7->Add(CheckListBox3, 1, wxALL|wxEXPAND, 5);
    Panel7->SetSizer(FlexGridSizer7);
    Panel8 = new wxPanel(Choicebook1, ID_PANEL8, wxPoint(115,14), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 4, 0, 0);
    FlexGridSizer8->AddGrowableCol(1);
    FlexGridSizer8->AddGrowableCol(3);
    StaticText35 = new wxStaticText(Panel8, ID_STATICTEXT35, _("Input Devices"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
    StaticText35->Disable();
    FlexGridSizer8->Add(StaticText35, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox5 = new wxCheckListBox(Panel8, ID_CHECKLISTBOX5, wxDefaultPosition, wxSize(0,72), 0, 0, wxLB_MULTIPLE, wxDefaultValidator, _T("ID_CHECKLISTBOX5"));
    CheckListBox5->Append(_("Keyboard"));
    CheckListBox5->Append(_("Mouse"));
    CheckListBox5->Append(_("2-Button Joystick"));
    CheckListBox5->Append(_("3-Button Joystick"));
    CheckListBox5->Append(_("4-Button Joystick"));
    CheckListBox5->Append(_("6-Button Joystick"));
    CheckListBox5->Append(_("DirectInput Joystick"));
    CheckListBox5->Append(_("XInput Joystick"));
    CheckListBox5->Append(_("Flight Stick"));
    CheckListBox5->Append(_("Racing Wheel Controller"));
    CheckListBox5->Disable();
    FlexGridSizer8->Add(CheckListBox5, 1, wxALL|wxEXPAND, 5);
    StaticText31 = new wxStaticText(Panel8, ID_STATICTEXT31, _("Drivers/APIs"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
    StaticText31->Disable();
    FlexGridSizer8->Add(StaticText31, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox6 = new wxCheckListBox(Panel8, ID_CHECKLISTBOX6, wxDefaultPosition, wxSize(0,0), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX6"));
    CheckListBox6->Append(_("DirectDraw"));
    CheckListBox6->Append(_("Direct3D"));
    CheckListBox6->Append(_("S3 MeTaL"));
    CheckListBox6->Append(_("Glide"));
    CheckListBox6->Append(_("OpenGL"));
    CheckListBox6->Append(_("Vulkan"));
    CheckListBox6->Append(_("SVGALib"));
    CheckListBox6->Append(_("X11R5"));
    CheckListBox6->Append(_("X11R6"));
    CheckListBox6->Append(_("Warp3D"));
    CheckListBox6->Disable();
    FlexGridSizer8->Add(CheckListBox6, 1, wxALL|wxEXPAND, 5);
    StaticText29 = new wxStaticText(Panel8, ID_STATICTEXT29, _("Video Modes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
    StaticText29->Disable();
    FlexGridSizer8->Add(StaticText29, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox7 = new wxCheckListBox(Panel8, ID_CHECKLISTBOX7, wxDefaultPosition, wxSize(0,72), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX7"));
    CheckListBox7->Append(_("Windowed"));
    CheckListBox7->Append(_("Borderless Fullscreen"));
    CheckListBox7->Append(_("Fullscreen"));
    CheckListBox7->Append(_("4:3"));
    CheckListBox7->Append(_("16:9"));
    CheckListBox7->Disable();
    FlexGridSizer8->Add(CheckListBox7, 1, wxALL|wxEXPAND, 5);
    StaticText30 = new wxStaticText(Panel8, ID_STATICTEXT30, _("Video Resolutions"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
    StaticText30->Disable();
    FlexGridSizer8->Add(StaticText30, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox8 = new wxCheckListBox(Panel8, ID_CHECKLISTBOX8, wxDefaultPosition, wxSize(0,72), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX8"));
    CheckListBox8->Append(_("3840x2160"));
    CheckListBox8->Append(_("2560x1440"));
    CheckListBox8->Append(_("1920x1280"));
    CheckListBox8->Append(_("1600x900"));
    CheckListBox8->Append(_("1366x768"));
    CheckListBox8->Append(_("1280x1024"));
    CheckListBox8->Append(_("1280x720"));
    CheckListBox8->Append(_("1024x768"));
    CheckListBox8->Append(_("800x600"));
    CheckListBox8->Append(_("640x480"));
    CheckListBox8->Append(_("320x240"));
    CheckListBox8->Disable();
    FlexGridSizer8->Add(CheckListBox8, 1, wxALL|wxEXPAND, 5);
    StaticText36 = new wxStaticText(Panel8, ID_STATICTEXT36, _("Sound Capabilities"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
    StaticText36->Disable();
    FlexGridSizer8->Add(StaticText36, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox9 = new wxCheckListBox(Panel8, ID_CHECKLISTBOX9, wxDefaultPosition, wxSize(0,72), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX9"));
    CheckListBox9->Append(_("A3D"));
    CheckListBox9->Append(_("DirectSound3D"));
    CheckListBox9->Append(_("Dolby Digital"));
    CheckListBox9->Append(_("Dolby Digital 5.1"));
    CheckListBox9->Append(_("Dolby Digital 7.1"));
    CheckListBox9->Append(_("Dolby Pro Logic II"));
    CheckListBox9->Append(_("Dolby Surround"));
    CheckListBox9->Append(_("Dolby Surround Pro Logic"));
    CheckListBox9->Append(_("DTS"));
    CheckListBox9->Append(_("DTS-HD"));
    CheckListBox9->Append(_("EAX"));
    CheckListBox9->Append(_("EAX Advanced HD"));
    CheckListBox9->Append(_("MIDI"));
    CheckListBox9->Append(_("Mono"));
    CheckListBox9->Append(_("OpenAL"));
    CheckListBox9->Append(_("Sound Blaster"));
    CheckListBox9->Append(_("Stereo"));
    CheckListBox9->Append(_("THX"));
    CheckListBox9->Append(_("Built-In Speaker"));
    CheckListBox9->Disable();
    FlexGridSizer8->Add(CheckListBox9, 1, wxALL|wxEXPAND, 5);
    StaticText37 = new wxStaticText(Panel8, ID_STATICTEXT37, _("Engine"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
    StaticText37->Disable();
    FlexGridSizer8->Add(StaticText37, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl13 = new wxTextCtrl(Panel8, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
    TextCtrl13->Disable();
    FlexGridSizer8->Add(TextCtrl13, 1, wxALL|wxEXPAND, 5);
    Panel8->SetSizer(FlexGridSizer8);
    Panel9 = new wxPanel(Choicebook1, ID_PANEL9, wxPoint(79,13), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    Panel10 = new wxPanel(Choicebook1, ID_PANEL10, wxPoint(186,18), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    Choicebook1->AddPage(Panel5, _("Main Details"), false);
    Choicebook1->AddPage(Panel7, _("Gameplay"), false);
    Choicebook1->AddPage(Panel8, _("Technical Details"), false);
    Choicebook1->AddPage(Panel9, _("Credits"), false);
    Choicebook1->AddPage(Panel10, _("Media & Links"), false);
    BoxSizer2->Add(Choicebook1, 1, wxALL|wxEXPAND, 5);
    Panel2->SetSizer(BoxSizer2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Notebook1->AddPage(Panel6, _("General"), false);
    Notebook1->AddPage(Panel1, _("Launch Configuration"), false);
    Notebook1->AddPage(Panel2, _("Metadata"), false);
    Notebook1->AddPage(Panel3, _("Scripts"), false);
    Notebook1->AddPage(Panel4, _("Installation / Sync"), false);
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
    this->db = db;
    LaunchConfig* LaunchPanel = new LaunchConfig(ActionListbook, wxString("Main"), true);
    ActionListbook->AddPage(LaunchPanel, wxString("Main"), true);
    Bind(wxEVT_BUTTON, (wxObjectEventFunction)&EditGame::OnDialogButtonClick, this);
}

EditGame::~EditGame()
{
    //(*Destroy(EditGame)
    //*)
}

EditGame::SetDatabase(Database* db)
{
    this->db = db;
}

EditGame::SaveGameToDatabase()
{
    const wxString name = GameName->GetLineText(0);
    name.Replace("'", "''", true);
    const wxString path = ((LaunchConfig*) ActionListbook->GetPage(0))->FilePickerCtrl->GetPath();
    db->AddGame(name, path);
}

EditGame::OnDialogButtonClick(wxCommandEvent& event)
{
    switch (event.GetId()) {
        case wxID_SAVE:
            SaveGameToDatabase();
            EndModal(wxOK);
            break;
        case wxID_CANCEL:
            EndModal(wxCANCEL);
            break;
    }
    event.Skip();
}

void EditGame::OnCheckListBox1Toggled(wxCommandEvent& event)
{
}
