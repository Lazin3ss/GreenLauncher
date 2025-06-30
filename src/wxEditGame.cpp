/***************************************************************
 * Name:      wxEditGame.cpp
 * Purpose:   Code for Add/Edit Game Dialog Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-08
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "Database.h"
#include "GameData.h"

#include "wxEditGame.h".
#include "wxLaunchConfig.h"
#include "wxGreenLauncherMain.h"

//(*InternalHeaders(EditGame)
#include <wx/button.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

wxDECLARE_APP(GreenLauncherApp);

//(*IdInit(EditGame)
const long EditGame::ID_STATICTEXT1 = wxNewId();
const long EditGame::ID_GAMENAME = wxNewId();
const long EditGame::ID_GAMEFAVORITE = wxNewId();
const long EditGame::ID_GAMEHIDDEN = wxNewId();
const long EditGame::ID_STATICTEXT8 = wxNewId();
const long EditGame::ID_GAMECATEGORY = wxNewId();
const long EditGame::ID_STATICTEXT10 = wxNewId();
const long EditGame::ID_GAMESOURCE = wxNewId();
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
const long EditGame::ID_GAMERELEASEDATE = wxNewId();
const long EditGame::ID_STATICTEXT12 = wxNewId();
const long EditGame::ID_GAMEPLATFORM = wxNewId();
const long EditGame::ID_STATICTEXT13 = wxNewId();
const long EditGame::ID_GAMEDEVELOPER = wxNewId();
const long EditGame::ID_STATICTEXT14 = wxNewId();
const long EditGame::ID_GAMEPUBLISHER = wxNewId();
const long EditGame::ID_STATICTEXT15 = wxNewId();
const long EditGame::ID_GameGenre = wxNewId();
const long EditGame::ID_STATICTEXT16 = wxNewId();
const long EditGame::ID_GAMESERIES = wxNewId();
const long EditGame::ID_STATICTEXT17 = wxNewId();
const long EditGame::ID_GAMEREGION = wxNewId();
const long EditGame::ID_STATICTEXT18 = wxNewId();
const long EditGame::ID_GAMELANGUAGE = wxNewId();
const long EditGame::ID_STATICTEXT19 = wxNewId();
const long EditGame::ID_GAMELICENSE = wxNewId();
const long EditGame::ID_STATICTEXT20 = wxNewId();
const long EditGame::ID_GAMEFORMAT = wxNewId();
const long EditGame::ID_STATICTEXT21 = wxNewId();
const long EditGame::ID_GAMEAGERATING = wxNewId();
const long EditGame::ID_STATICTEXT22 = wxNewId();
const long EditGame::ID_GAMESCORE = wxNewId();
const long EditGame::ID_STATICTEXT32 = wxNewId();
const long EditGame::ID_GAMEDESCRIPTION = wxNewId();
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

EditGame::EditGame(wxWindow* parent, GameData data, wxWindowID id)
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

    Create(parent, wxID_ANY, _("Edit Game"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
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
    GameFavorite = new wxCheckBox(Panel6, ID_GAMEFAVORITE, _("Favorite"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEFAVORITE"));
    GameFavorite->SetValue(false);
    FlexGridSizer2->Add(GameFavorite, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameHidden = new wxCheckBox(Panel6, ID_GAMEHIDDEN, _("Hidden"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEHIDDEN"));
    GameHidden->SetValue(false);
    FlexGridSizer2->Add(GameHidden, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer5->AddGrowableCol(1);
    StaticText8 = new wxStaticText(Panel6, ID_STATICTEXT8, _("Categories"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer5->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameCategory = new wxTextCtrl(Panel6, ID_GAMECATEGORY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMECATEGORY"));
    FlexGridSizer5->Add(GameCategory, 1, wxALL|wxEXPAND, 5);
    StaticText10 = new wxStaticText(Panel6, ID_STATICTEXT10, _("Source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer5->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameSource = new wxTextCtrl(Panel6, ID_GAMESOURCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMESOURCE"));
    FlexGridSizer5->Add(GameSource, 1, wxALL|wxEXPAND, 5);
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
    GameReleaseDate = new wxDatePickerCtrl(Panel5, ID_GAMERELEASEDATE, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_GAMERELEASEDATE"));
    FlexGridSizer6->Add(GameReleaseDate, 1, wxALL|wxEXPAND, 5);
    StaticText12 = new wxStaticText(Panel5, ID_STATICTEXT12, _("Platform"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer6->Add(StaticText12, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GamePlatform = new wxTextCtrl(Panel5, ID_GAMEPLATFORM, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEPLATFORM"));
    FlexGridSizer6->Add(GamePlatform, 1, wxALL|wxEXPAND, 5);
    StaticText13 = new wxStaticText(Panel5, ID_STATICTEXT13, _("Developer"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    FlexGridSizer6->Add(StaticText13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameDeveloper = new wxTextCtrl(Panel5, ID_GAMEDEVELOPER, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEDEVELOPER"));
    FlexGridSizer6->Add(GameDeveloper, 1, wxALL|wxEXPAND, 5);
    StaticText14 = new wxStaticText(Panel5, ID_STATICTEXT14, _("Publisher"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer6->Add(StaticText14, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GamePublisher = new wxTextCtrl(Panel5, ID_GAMEPUBLISHER, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEPUBLISHER"));
    FlexGridSizer6->Add(GamePublisher, 1, wxALL|wxEXPAND, 5);
    StaticText15 = new wxStaticText(Panel5, ID_STATICTEXT15, _("Genre"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer6->Add(StaticText15, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameGenre = new wxTextCtrl(Panel5, ID_GameGenre, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GameGenre"));
    FlexGridSizer6->Add(GameGenre, 1, wxALL|wxEXPAND, 5);
    StaticText16 = new wxStaticText(Panel5, ID_STATICTEXT16, _("Series"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer6->Add(StaticText16, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameSeries = new wxTextCtrl(Panel5, ID_GAMESERIES, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMESERIES"));
    FlexGridSizer6->Add(GameSeries, 1, wxALL|wxEXPAND, 5);
    StaticText17 = new wxStaticText(Panel5, ID_STATICTEXT17, _("Region"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer6->Add(StaticText17, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameRegion = new wxTextCtrl(Panel5, ID_GAMEREGION, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEREGION"));
    FlexGridSizer6->Add(GameRegion, 1, wxALL|wxEXPAND, 5);
    StaticText18 = new wxStaticText(Panel5, ID_STATICTEXT18, _("Language"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer6->Add(StaticText18, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameLanguage = new wxTextCtrl(Panel5, ID_GAMELANGUAGE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMELANGUAGE"));
    FlexGridSizer6->Add(GameLanguage, 1, wxALL|wxEXPAND, 5);
    StaticText19 = new wxStaticText(Panel5, ID_STATICTEXT19, _("License Model"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer6->Add(StaticText19, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameLicense = new wxTextCtrl(Panel5, ID_GAMELICENSE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMELICENSE"));
    FlexGridSizer6->Add(GameLicense, 1, wxALL|wxEXPAND, 5);
    StaticText20 = new wxStaticText(Panel5, ID_STATICTEXT20, _("Format"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    FlexGridSizer6->Add(StaticText20, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameFormat = new wxTextCtrl(Panel5, ID_GAMEFORMAT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMEFORMAT"));
    FlexGridSizer6->Add(GameFormat, 1, wxALL|wxEXPAND, 5);
    StaticText21 = new wxStaticText(Panel5, ID_STATICTEXT21, _("Age Rating"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    FlexGridSizer6->Add(StaticText21, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameAgeRating = new wxChoice(Panel5, ID_GAMEAGERATING, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GAMEAGERATING"));
    FlexGridSizer6->Add(GameAgeRating, 1, wxALL|wxEXPAND, 5);
    StaticText22 = new wxStaticText(Panel5, ID_STATICTEXT22, _("Score"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    FlexGridSizer6->Add(StaticText22, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GameScore = new wxTextCtrl(Panel5, ID_GAMESCORE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAMESCORE"));
    FlexGridSizer6->Add(GameScore, 1, wxALL|wxEXPAND, 5);
    StaticText32 = new wxStaticText(Panel5, ID_STATICTEXT32, _("Description"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
    FlexGridSizer6->Add(StaticText32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GameDescription = new wxTextCtrl(Panel5, ID_GAMEDESCRIPTION, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_GAMEDESCRIPTION"));
    GameDescription->SetToolTip(_("Add a description!"));
    GameDescription->SetHelpText(_("Add a description!"));
    FlexGridSizer6->Add(GameDescription, 1, wxALL|wxEXPAND, 5);
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
    LaunchConfig* LaunchPanel = new LaunchConfig(ActionListbook, wxString("Main"), true);
    ActionListbook->AddPage(LaunchPanel, wxString("Main"), true);
    Bind(wxEVT_BUTTON, (wxObjectEventFunction)&EditGame::OnDialogButtonClick, this);
    this->data = data;
    if (data.id > 0) {
        SetLabel(wxString::Format("Editing %s", data.name));
        LoadData();
    } else {
        SetLabel("Add a new game");
    }
}

EditGame::~EditGame()
{
    //(*Destroy(EditGame)
    //*)
}

void EditGame::LoadData()
{
    // Game base data
    GameName->SetValue(data.name);
    GameFavorite->SetValue(data.favorite);
    GameHidden->SetValue(data.hidden);
    GameCategory->SetValue(data.category);
    GameSource->SetValue(data.source);
    // Actions data
    for (int i = 0; i < data.actions.size(); i++) {
        if (!data.actions[i].isMain) {
            LaunchConfig* panel = new LaunchConfig(ActionListbook, data.actions[i].name, false);
            ActionListbook->AddPage(panel, data.actions[i].name, true);
            panel->ActionType->SetSelection(data.actions[i].type);
            panel->ActionSystem->SetSelection(data.actions[i].systemId);
            panel->ActionPath->SetPath(data.actions[i].path);
            panel->ActionWorkingDirectory->SetPath(data.actions[i].workingDir);
            panel->ActionArguments->SetValue(data.actions[i].args);
            panel->ActionId = data.actions[i].id;
        } else {
            ((LaunchConfig*) ActionListbook->GetPage(0))->ActionType->SetSelection(data.actions[i].type);
            ((LaunchConfig*) ActionListbook->GetPage(0))->ActionSystem->SetSelection(data.actions[i].systemId);
            ((LaunchConfig*) ActionListbook->GetPage(0))->ActionPath->SetPath(data.actions[i].path);
            ((LaunchConfig*) ActionListbook->GetPage(0))->ActionWorkingDirectory->SetPath(data.actions[i].workingDir);
            ((LaunchConfig*) ActionListbook->GetPage(0))->ActionArguments->SetValue(data.actions[i].args);
            ((LaunchConfig*) ActionListbook->GetPage(0))->ActionId = data.actions[i].id;
        }
    }
    // Metadata
    GameReleaseDate->SetValue(data.metadata.releaseDate);
    GamePlatform->SetValue(data.metadata.platform);
    GameDeveloper->SetValue(data.metadata.developer);
    GamePublisher->SetValue(data.metadata.publisher);
    GameGenre->SetValue(data.metadata.genre);
    GameSeries->SetValue(data.metadata.series);
    GameRegion->SetValue(data.metadata.region);
    GameLanguage->SetValue(data.metadata.language);
    GameLicense->SetValue(data.metadata.license);
    //GameAgeRating->SetString(0, data.metadata.ageRating);
    //GameAgeRating->SetSelection(0);
    GameScore->SetValue(data.metadata.score);
    GameDescription->SetValue(data.metadata.description);
}

void EditGame::SaveData()
{
    // Gather General info
    data.name = GameName->GetValue();
    data.favorite = GameFavorite->GetValue();
    data.hidden = GameHidden->GetValue();
    data.category = GameCategory->GetValue();
    data.source = GameSource->GetValue();
    // Gather Action data info
    data.actions.clear();
    for (int i = 0; i < ActionListbook->GetPageCount(); i++) {
        ActionData actData;
        actData.id = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionId;
        actData.name = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionName->GetValue();
        actData.isMain = ((LaunchConfig*) ActionListbook->GetPage(i))->isMain;
        actData.type = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionType->GetSelection();
        actData.systemId = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionSystem->GetCurrentSelection();
        actData.path = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionPath->GetPath();
        actData.workingDir = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionWorkingDirectory->GetPath();
        actData.args = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionArguments->GetValue();
        actData.iconPath = ((LaunchConfig*) ActionListbook->GetPage(i))->ActionPath->GetPath(); // Not implemented yet, just use same path as executable
        data.actions.push_back(actData);
    }
    // Gather Metadata info
    data.metadata.releaseDate = GameReleaseDate->GetValue();
    data.metadata.platform = GamePlatform->GetValue();
    data.metadata.developer = GameDeveloper->GetValue();
    data.metadata.publisher = GamePublisher->GetValue();
    data.metadata.genre = GameGenre->GetValue();
    data.metadata.series = GameSeries->GetValue();
    data.metadata.region = GameRegion->GetValue();
    data.metadata.language = GameLanguage->GetValue();
    data.metadata.license = GameLicense->GetValue();
    data.metadata.ageRating = GameAgeRating->GetString(GameAgeRating->GetSelection());
    data.metadata.score = GameScore->GetValue();
    data.metadata.description = GameDescription->GetValue();
}

EditGame::OnDialogButtonClick(wxCommandEvent& event)
{
    switch (event.GetId()) {
        case wxID_SAVE:
            SaveData();
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
