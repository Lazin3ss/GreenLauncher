/***************************************************************
 * Name:      GameManager.h
 * Purpose:   Defines Game Manager
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-06-28
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <wx/string.h>

#include "Database.h"
#include "GameData.h"


class GameManager
{
    public:
        long selectedGameIdx;
        wxString currentQuery = wxString("SELECT * from gameList");

        GameManager();
        virtual ~GameManager();

        void AddGame(GameData data);
        void EditGame(GameData data);
        void DeleteGame();

        void RunAction(long idx);

        long Query();
        wxString ReturnTableItem(long row, long col);
        GameData GetSingleGameData();

        long GetFilterList(wxString type);
        wxString GetFilterLabel(long idx);
        wxString GetFilterData(wxString type, long idx);
        void FreeFilterList();
    private:
        Database* db;
};

#endif // GAMEMANAGER_H
