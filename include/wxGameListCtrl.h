/***************************************************************
 * Name:      wxGameListCtrl.h
 * Purpose:   Defines wxListCtrl class extension for game list displaying
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-31
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef WXGAMELISTCTRL_H
#define WXGAMELISTCTRL_H

#include <wx/wx.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/string.h>

#include "GreenLauncherApp.h"

wxDECLARE_APP(GreenLauncherApp);

class GameListCtrl : public wxListCtrl
{
    private:
        wxImageList* imgList;
        wxIcon emptyIcon;

    public:
        long selectedGameId = -1;
        GameListCtrl(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
            : wxListCtrl(parent, id, pos, size, style, validator, name)
        {
            this->InsertColumn(0, wxString("Name"));
            this->InsertColumn(1, wxString("Favorite"));
            this->InsertColumn(2, wxString("Year"));
            this->InsertColumn(3, wxString("Developer"));
            this->InsertColumn(4, wxString("Publisher"));
            this->InsertColumn(5, wxString("Platform"));
            this->InsertColumn(6, wxString("Genre"));
            this->InsertColumn(7, wxString("Series"));
            this->InsertColumn(8, wxString("Region"));
            this->InsertColumn(9, wxString("Language"));
            this->InsertColumn(10, wxString("License Model"));
            this->InsertColumn(11, wxString("Category"));
            this->InsertColumn(12, wxString("Source"));
            imgList = new wxImageList(16, 16, true, 1);
            this->AssignImageList(imgList, wxIMAGE_LIST_SMALL);
        };

        virtual ~GameListCtrl()
        {
            delete imgList;
        }

        virtual wxString OnGetItemText(long row, long column) const override
        {
            return wxGetApp().gameManager->ReturnTableItem(row, column+5);
        };

        virtual int OnGetItemImage(long row) const override
        {
            return row;
        };

        void ReloadGames()
        {
            // Remove previous icons
            imgList->RemoveAll();
            // Get games from database and set count
            long queryRows = wxGetApp().gameManager->Query();
            SetItemCount(queryRows);
            // Set icons for Game List's Image list
            for (long i = 0; i < queryRows; i++) {
                if (wxGetApp().gameManager->ReturnTableItem(i, 4).Len() > 0) {
                    imgList->Add(wxIcon(wxIconLocation(wxGetApp().gameManager->ReturnTableItem(i, 4), 0)));
                } else {
                    imgList->Add(wxIcon(wxIconLocation(wxString("GreenLauncher.exe"), 0)));
                }
            };
            // Refresh list
            Refresh();
            for (int i = 0; i<GetColumnCount(); i++) {
                SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
            }
        };
};

#endif // WXGAMELIST_H

