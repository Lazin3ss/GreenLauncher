/***************************************************************
 * Name:      wxGreenLauncherMain.h
 * Purpose:   Defines Application Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef WXGREENLAUNCHERMAIN_H
#define WXGREENLAUNCHERMAIN_H

#include "wxGameListCtrl.h"

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
        void ReloadFilters();

    private:

        //(*Handlers(GreenLauncherFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnListView1BeginDrag(wxListEvent& event);
        void OnTreeCtrl1BeginDrag(wxTreeEvent& event);
        void OnListView1CacheHint(wxListEvent& event);
        void OnGameList1ItemActivated(wxListEvent& event);
        void OnAddGameClick(wxCommandEvent& event);
        void OnTreeCtrl1BeginDrag1(wxTreeEvent& event);
        void OnGameList1ItemRClick(wxListEvent& event);
        void OnLaunchGameMenuItemSelected(wxCommandEvent& event);
        void OnGameList1ItemSelect(wxListEvent& event);
        void OnDeleteGameMenuItemSelected(wxCommandEvent& event);
        void OnEditGameMenuItemSelected(wxCommandEvent& event);
        void OnTreeCtrl1BeginDrag2(wxTreeEvent& event);
        void OnFilterTreeSelectionChanged(wxTreeEvent& event);
        void OnFilterTreeBeginDrag(wxTreeEvent& event);
        void OnFilterTreeBeginDrag1(wxTreeEvent& event);
        void OnMenuClose(wxMenuEvent& event);
        void OnMenuOpen(wxMenuEvent& event);
        void OnGameList1ColumnClick(wxListEvent& event);
        //*)

        //(*Identifiers(GreenLauncherFrame)
        static const long ID_FILTERTREE;
        static const long ID_GAMELIST1;
        static const long ID_SPLITTERWINDOW1;
        static const long idMenuAdd;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_EDITGAMEMENUITEM;
        static const long ID_DELETEGAMEMENUITEM;
        //*)

        //(*Declarations(GreenLauncherFrame)
        GameListCtrl* GameList1;
        wxMenu GameListMenu;
        wxMenuItem* DeleteGameMenuItem;
        wxMenuItem* EditGameMenuItem;
        wxMenuItem* MenuItem3;
        wxSplitterWindow* SplitterWindow1;
        wxStatusBar* StatusBar1;
        wxTreeCtrl* FilterTree;
        //*)

        DECLARE_EVENT_TABLE()

};

#endif // GREENLAUNCHERMAIN_H

