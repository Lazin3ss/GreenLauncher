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
        long pRows = -1;
        long pCols = -1;

        char **fResult;
        long fRows = -1;
        long fCols = -1;

        Database();
        virtual ~Database();

        void Query(wxString str);
        wxString ReturnTableItem(long row, long col);
        void RunSQL(wxString name);
        void AddAction(long game_id, bool isMain, wxString name, long type, wxString path, wxString workingDir, wxString args, long systemId, wxString iconPath);
        void UpdateAction(long actionId, wxString name, long type, wxString path, wxString workingDir, wxString args, long systemId, wxString iconPath);
        void AddMetadataAndMap(const char* type, wxString name, long gameId);
        void UpdateMetadata(const char* type, wxString names, long gameId);
        void AddGame(GameData data);
        void EditGame(GameData data);
        void DeleteGame(long gameId);
        wxString ReturnMetadata(const char* type, long gameId);
        GameData ReturnGameData(long id);
        void GetMetadataTable(wxString type);
        wxString ReturnFilterTableItem(long row, long col);
        void FreeMetadataTable();

    private:
        sqlite3 *db;
};

#endif // DATABASE_H
