/***************************************************************
 * Name:      Database.h
 * Purpose:   SQLite3 database handler definitions
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-31
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3/sqlite3.h"
#include "GameData.h"

#include <wx/string.h>


class Database
{
    public:
        char **pResult;
        int pRows = -1;
        int pCols = -1;

        Database();
        virtual ~Database();

        void Query(wxString str);
        void RunSQL(wxString name);
        void AddMetadataAndMap(const char* type, wxString name, long gameId);
        void AddGame(GameData data);
        wxString ReturnTableItem(long row, long col);
        wxString ReturnGameData(long id);

    private:
        sqlite3 *db;
};

#endif // DATABASE_H
