/***************************************************************
 * Name:      wxEditGame.h
 * Purpose:   Defines Add/Edit Game Dialog Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-08
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef WXEDITGAME_H
#define WXEDITGAME_H

#include <wx/string.h>

#include "Database.h"

#include "wxLaunchConfig.h"

//(*Headers(EditGame)
#include <wx/bmpbuttn.h>
#include <wx/checkbox.h>
#include <wx/checklst.h>
#include <wx/choice.h>
#include <wx/choicebk.h>
#include <wx/combobox.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/dialog.h>
#include <wx/listbook.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class EditGame: public wxDialog
{
    public:
        GameData data;

        EditGame(wxWindow* parent, GameData data=GameData(), wxWindowID id=wxID_ANY);
        virtual ~EditGame();

        void AddAction(wxString name, bool isMain);
        void DeleteAction(size_t pageId);
        void LoadData();
        void SaveData();
        bool IntegrityCheck();
        void OnDialogButtonClick(wxCommandEvent& event);

        //(*Declarations(EditGame)
        wxBitmapButton* GameIcon;
        wxCheckBox* GameFavorite;
        wxCheckBox* GameHidden;
        wxCheckListBox* CheckListBox1;
        wxCheckListBox* CheckListBox2;
        wxCheckListBox* CheckListBox3;
        wxCheckListBox* CheckListBox4;
        wxCheckListBox* CheckListBox5;
        wxCheckListBox* CheckListBox6;
        wxCheckListBox* CheckListBox7;
        wxCheckListBox* CheckListBox8;
        wxCheckListBox* CheckListBox9;
        wxChoice* Choice1;
        wxChoice* Choice2;
        wxChoice* GameAgeRating;
        wxChoicebook* Choicebook1;
        wxComboBox* ComboBox12;
        wxComboBox* ComboBox13;
        wxDatePickerCtrl* DatePickerCtrl1;
        wxDatePickerCtrl* DatePickerCtrl2;
        wxDatePickerCtrl* GameReleaseDate;
        wxListbook* ActionListbook;
        wxNotebook* Notebook1;
        wxPanel* Panel10;
        wxPanel* Panel11;
        wxPanel* Panel13;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxPanel* Panel4;
        wxPanel* Panel5;
        wxPanel* Panel6;
        wxPanel* Panel7;
        wxPanel* Panel8;
        wxPanel* Panel9;
        wxStaticText* StaticText10;
        wxStaticText* StaticText11;
        wxStaticText* StaticText12;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticText* StaticText16;
        wxStaticText* StaticText17;
        wxStaticText* StaticText18;
        wxStaticText* StaticText19;
        wxStaticText* StaticText1;
        wxStaticText* StaticText20;
        wxStaticText* StaticText21;
        wxStaticText* StaticText22;
        wxStaticText* StaticText23;
        wxStaticText* StaticText24;
        wxStaticText* StaticText25;
        wxStaticText* StaticText26;
        wxStaticText* StaticText27;
        wxStaticText* StaticText28;
        wxStaticText* StaticText29;
        wxStaticText* StaticText2;
        wxStaticText* StaticText30;
        wxStaticText* StaticText31;
        wxStaticText* StaticText32;
        wxStaticText* StaticText33;
        wxStaticText* StaticText34;
        wxStaticText* StaticText35;
        wxStaticText* StaticText36;
        wxStaticText* StaticText37;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxTextCtrl* GameCategory;
        wxTextCtrl* GameDescription;
        wxTextCtrl* GameDeveloper;
        wxTextCtrl* GameFormat;
        wxTextCtrl* GameGenre;
        wxTextCtrl* GameLanguage;
        wxTextCtrl* GameLicense;
        wxTextCtrl* GameName;
        wxTextCtrl* GamePlatform;
        wxTextCtrl* GamePublisher;
        wxTextCtrl* GameRegion;
        wxTextCtrl* GameScore;
        wxTextCtrl* GameSeries;
        wxTextCtrl* GameSource;
        wxTextCtrl* TextCtrl10;
        wxTextCtrl* TextCtrl11;
        wxTextCtrl* TextCtrl12;
        wxTextCtrl* TextCtrl13;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl3;
        wxTextCtrl* TextCtrl4;
        wxTextCtrl* TextCtrl5;
        wxTextCtrl* TextCtrl7;
        wxTextCtrl* TextCtrl8;
        wxTextCtrl* TextCtrl9;
        //*)

    protected:

        //(*Identifiers(EditGame)
        static const long ID_STATICTEXT1;
        static const long ID_GAMENAME;
        static const long ID_GAMEFAVORITE;
        static const long ID_GAMEHIDDEN;
        static const long ID_GAMEICON;
        static const long ID_STATICTEXT8;
        static const long ID_GAMECATEGORY;
        static const long ID_STATICTEXT10;
        static const long ID_GAMESOURCE;
        static const long ID_STATICTEXT4;
        static const long ID_DATEPICKERCTRL1;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT7;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT2;
        static const long ID_DATEPICKERCTRL2;
        static const long ID_STATICTEXT9;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL4;
        static const long ID_TEXTCTRL5;
        static const long ID_PANEL6;
        static const long ID_ACTIONLISTBOOK;
        static const long ID_PANEL1;
        static const long ID_STATICTEXT11;
        static const long ID_GAMERELEASEDATE;
        static const long ID_STATICTEXT12;
        static const long ID_GAMEPLATFORM;
        static const long ID_STATICTEXT13;
        static const long ID_GAMEDEVELOPER;
        static const long ID_STATICTEXT14;
        static const long ID_GAMEPUBLISHER;
        static const long ID_STATICTEXT15;
        static const long ID_GameGenre;
        static const long ID_STATICTEXT16;
        static const long ID_GAMESERIES;
        static const long ID_STATICTEXT17;
        static const long ID_GAMEREGION;
        static const long ID_STATICTEXT18;
        static const long ID_GAMELANGUAGE;
        static const long ID_STATICTEXT19;
        static const long ID_GAMELICENSE;
        static const long ID_STATICTEXT20;
        static const long ID_GAMEFORMAT;
        static const long ID_STATICTEXT21;
        static const long ID_GAMEAGERATING;
        static const long ID_STATICTEXT22;
        static const long ID_GAMESCORE;
        static const long ID_STATICTEXT32;
        static const long ID_GAMEDESCRIPTION;
        static const long ID_PANEL5;
        static const long ID_STATICTEXT25;
        static const long ID_COMBOBOX12;
        static const long ID_STATICTEXT28;
        static const long ID_COMBOBOX13;
        static const long ID_STATICTEXT33;
        static const long ID_TEXTCTRL7;
        static const long ID_TEXTCTRL8;
        static const long ID_TEXTCTRL9;
        static const long ID_PANEL11;
        static const long ID_STATICTEXT34;
        static const long ID_TEXTCTRL10;
        static const long ID_TEXTCTRL11;
        static const long ID_TEXTCTRL12;
        static const long ID_PANEL13;
        static const long ID_STATICTEXT23;
        static const long ID_CHECKLISTBOX1;
        static const long ID_STATICTEXT24;
        static const long ID_CHECKLISTBOX2;
        static const long ID_STATICTEXT27;
        static const long ID_CHECKLISTBOX4;
        static const long ID_STATICTEXT26;
        static const long ID_CHECKLISTBOX3;
        static const long ID_PANEL7;
        static const long ID_STATICTEXT35;
        static const long ID_CHECKLISTBOX5;
        static const long ID_STATICTEXT31;
        static const long ID_CHECKLISTBOX6;
        static const long ID_STATICTEXT29;
        static const long ID_CHECKLISTBOX7;
        static const long ID_STATICTEXT30;
        static const long ID_CHECKLISTBOX8;
        static const long ID_STATICTEXT36;
        static const long ID_CHECKLISTBOX9;
        static const long ID_STATICTEXT37;
        static const long ID_TEXTCTRL13;
        static const long ID_PANEL8;
        static const long ID_PANEL9;
        static const long ID_PANEL10;
        static const long ID_CHOICEBOOK1;
        static const long ID_PANEL2;
        static const long ID_PANEL3;
        static const long ID_PANEL4;
        static const long ID_NOTEBOOK1;
        //*)

    private:

        //(*Handlers(EditGame)
        void OnNotebook1PageChanged(wxNotebookEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnNotebook1PageChanged1(wxNotebookEvent& event);
        void OnChoicebook1PageChanged(wxChoicebookEvent& event);
        void OnChoicebook1PageChanged1(wxChoicebookEvent& event);
        void OnListbook1PageChanged(wxListbookEvent& event);
        void OnCheckListBox1Toggled(wxCommandEvent& event);
        //*)

        DECLARE_EVENT_TABLE()
};

#endif

