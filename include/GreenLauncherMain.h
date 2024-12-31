#ifndef HEADER_F89662E16ADB0C82
#define HEADER_F89662E16ADB0C82

/***************************************************************
 * Name:      GreenLauncherMain.h
 * Purpose:   Defines Application Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:
 **************************************************************/

#ifndef GREENLAUNCHERMAIN_H
#define GREENLAUNCHERMAIN_H

#include "wxGameList.h"

//(*Headers(GreenLauncherFrame)
#include <wx/frame.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/treectrl.h>
//*)

class GreenLauncherFrame: public wxFrame
{
    public:

        GreenLauncherFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~GreenLauncherFrame();

    private:

        //(*Handlers(GreenLauncherFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnListView1BeginDrag(wxListEvent& event);
        void OnTreeCtrl1BeginDrag(wxTreeEvent& event);
        void OnListView1CacheHint(wxListEvent& event);
        //*)

        //(*Identifiers(GreenLauncherFrame)
        static const long ID_TREECTRL1;
        static const long ID_GAMELIST1;
        static const long ID_SPLITTERWINDOW1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(GreenLauncherFrame)
        wxGameList* GameList1;
        wxSplitterWindow* SplitterWindow1;
        wxStatusBar* StatusBar1;
        wxTreeCtrl* TreeCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // GREENLAUNCHERMAIN_H
#endif // header guard

