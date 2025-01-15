#ifndef HEADER_EC3AD1CEED7403C2
#define HEADER_EC3AD1CEED7403C2

/***************************************************************
 * Name:      wxGameList.h
 * Purpose:   Defines wxListCtrl class extension for game list displaying
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-31
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef WXGAMELIST_H
#define WXGAMELIST_H

#include <wx/wx.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/string.h>
#include <wx/log.h>
#include <wx/process.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#include "database.h"


class wxGameList : public wxListCtrl
{
    private:
        wxImageList *imgList;

    public:
        Database *db;
        wxGameList(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
            : wxListCtrl(parent, id, pos, size, style, validator, name)
        {
            this->InsertColumn(0, wxString("Name"));
            this->InsertColumn(1, wxString("Favorite"));
            this->InsertColumn(2, wxString("Year"));
            this->InsertColumn(3, wxString("Developer"));
            this->InsertColumn(4, wxString("Publisher"));
            this->InsertColumn(5, wxString("Genre"));
            this->InsertColumn(6, wxString("Category"));
            db = new Database;
            imgList = new wxImageList(16, 16, true, 1);
            this->AssignImageList(imgList, wxIMAGE_LIST_SMALL);
        };

        virtual ~wxGameList()
        {
            delete db;
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
            db->Query(str);
            SetItemCount(db->pRows);
            // Set icons for Game List's Image list
            for (long i = 0; i < db->pRows; i++) {
                bool res = imgList->Add(wxIcon(wxIconLocation(db->ReturnTableItem(i, 8), 0)));
            };
            // Refresh list
            Refresh();
        };

        wxString GetItemData(long row, long col)
        {
            return db->ReturnTableItem(row, col);
        }

        bool RunGame(long id)
        {
            wxFileName path(db->ReturnTableItem(id, 7));
            wxExecuteEnv env;
            env.cwd = path.GetPath();
            wxProcess* process;
            wxExecute(path.GetFullPath(), wxEXEC_ASYNC, process, &env);
        }
};

#endif // WXGAMELIST_H
#endif // header guard 

