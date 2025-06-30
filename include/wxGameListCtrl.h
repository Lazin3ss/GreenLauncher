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
            this->InsertColumn(5, wxString("Genre"));
            this->InsertColumn(6, wxString("Category"));
            imgList = new wxImageList(16, 16, true, 1);
            this->AssignImageList(imgList, wxIMAGE_LIST_SMALL);
        };

        virtual ~GameListCtrl()
        {
            delete imgList;
        }

        virtual wxString OnGetItemText(long row, long column) const override
        {
            return GetItemData(row, column);
        };

        virtual int OnGetItemImage(long row) const override
        {
            return row;
        };

        void GetGames(wxString str)
        {
            // Remove previous icons
            imgList->RemoveAll();
            // Get games from database and set count
            long queryRows = wxGetApp().gameManager->Query(str);
            SetItemCount(queryRows);
            // Set icons for Game List's Image list
            for (long i = 0; i < queryRows; i++) {
                bool res = imgList->Add(wxIcon(wxIconLocation(wxGetApp().gameManager->ReturnTableItem(i, 8), 0)));
            };
            // Refresh list
            Refresh();
        };

        wxString GetItemData(long row, long col)
        {
            return wxGetApp().gameManager->ReturnTableItem(row, col);
        }
};

#endif // WXGAMELIST_H

