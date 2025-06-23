/***************************************************************
 * Name:      EditGame.h
 * Purpose:   Defines Launch Configuration panel
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-15
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef LAUNCHCONFIG_H
#define LAUNCHCONFIG_H

//(*Headers(LaunchConfig)
#include <wx/bmpbuttn.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include <wx/string.h>

class LaunchConfig: public wxPanel
{
    public:

        LaunchConfig(wxWindow* parent, wxString actionName, bool isMain, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~LaunchConfig();

        size_t pageId;
        bool isMain;

        //(*Declarations(LaunchConfig)
        wxBitmapButton* AddActionButton;
        wxBitmapButton* BitmapButton3;
        wxBitmapButton* DeleteActionButton;
        wxComboBox* SystemComboBox;
        wxComboBox* TypeComboBox;
        wxDirPickerCtrl* WorkingDirectoryCtrl;
        wxFilePickerCtrl* FileCtrl;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxTextCtrl* ArgumentsTextCtrl;
        wxTextCtrl* NameTextCtrl;
        //*)

    protected:

        //(*Identifiers(LaunchConfig)
        static const long ID_STATICTEXT7;
        static const long ID_NAMETEXT;
        static const long ID_STATICTEXT1;
        static const long ID_TYPECOMBOBOX;
        static const long ID_STATICTEXT2;
        static const long ID_SYSCOMBOBOX;
        static const long ID_STATICTEXT3;
        static const long ID_FILECTRL;
        static const long ID_STATICTEXT4;
        static const long ID_WORKDIRCTRL;
        static const long ID_STATICTEXT6;
        static const long ID_ARGTEX;
        static const long ID_STATICTEXT5;
        static const long ID_BITMAPBUTTON3;
        static const long ID_PANEL1;
        static const long ID_ADDACTIONBUTTON;
        static const long ID_DELETEACTIONBUTTON;
        static const long ID_PANEL2;
        //*)

    private:

        //(*Handlers(LaunchConfig)
        void OnBitmapButton2Click(wxCommandEvent& event);
        void OnAddActionButtonClick(wxCommandEvent& event);
        void OnDeleteActionButtonClick(wxCommandEvent& event);
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
