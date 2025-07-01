/***************************************************************
 * Name:      wxLaunchConfig.h
 * Purpose:   Defines Launch Configuration panel
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-15
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef WXLAUNCHCONFIG_H
#define WXLAUNCHCONFIG_H

//(*Headers(LaunchConfig)
#include <wx/bmpbuttn.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/filedlg.h>
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
        int lastTypeSelection = 0;
        long ActionId = 0;
        wxString iconPath;

        void SetIcon(wxString path);

        //(*Declarations(LaunchConfig)
        wxBitmapButton* ActionIcon;
        wxBitmapButton* AddActionButton;
        wxBitmapButton* DeleteActionButton;
        wxChoice* ActionType;
        wxComboBox* ActionSystem;
        wxDirPickerCtrl* ActionWorkingDirectory;
        wxFileDialog* IconFileDialog;
        wxFilePickerCtrl* ActionPath;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxStaticText* ArgText;
        wxStaticText* FileText;
        wxStaticText* IconText;
        wxStaticText* NameText;
        wxStaticText* SystemText;
        wxStaticText* TypeText;
        wxStaticText* WorkDirText;
        wxTextCtrl* ActionArguments;
        wxTextCtrl* ActionName;
        //*)

    protected:

        //(*Identifiers(LaunchConfig)
        static const long ID_NAMETEXT;
        static const long ID_ACTIONNAME;
        static const long ID_TYPETEXT;
        static const long ID_ACTIONTYPE;
        static const long ID_SYSTEMTEXT;
        static const long ID_ACTIONSYSTEM;
        static const long ID_FILETEXT;
        static const long ID_ACTIONFILE;
        static const long ID_WORKDIRTEXT;
        static const long ID_ACTIONWORKDIR;
        static const long ID_ARGTEXT;
        static const long ID_ACTIONARGS;
        static const long ID_ICONTEXT;
        static const long ID_ACTIONICON;
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
        void OnFileCtrlFileChanged(wxFileDirPickerEvent& event);
        void OnTypeChoiceSelect(wxCommandEvent& event);
        void OnActionNameText(wxCommandEvent& event);
        void OnActionIconClick(wxCommandEvent& event);
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
