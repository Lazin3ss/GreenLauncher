#ifndef WXGAMELIST_H
#define WXGAMELIST_H

#include <wx/wx.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/string.h>
#include <wx/log.h>
#include "database.h"


class wxGameList : public wxListCtrl
{
    private:
        Database *db;
        wxImageList *imgList;

    public:
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
};

#endif // WXGAMELIST_H
