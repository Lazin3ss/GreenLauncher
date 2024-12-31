#ifndef WXGAMELIST_H
#define WXGAMELIST_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/string.h>
#include "database.h"


class wxGameList : public wxListCtrl
{
    private:
        Database *db;
        wxString currentQuery;

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
        };

        virtual ~wxGameList()
        {
            delete db;
        }

        virtual wxString OnGetItemText(long row, long column) const override
        {
            return db->ReturnTableItem(row, column);
        };

        void GetGames(wxString str)
        {
            db->Query(str);
            SetItemCount(db->pRows);
            Refresh();
        };

        wxString GetItemData(long row, long col)
        {
            return wxString(""+db->pRows);
        }
};

#endif // WXGAMELIST_H
