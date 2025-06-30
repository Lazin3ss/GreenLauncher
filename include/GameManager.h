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

#include <wx/window.h>


class GameManager
{
    public:
        long selectedGameIdx;

        GameManager();
        virtual ~GameManager();

        void AddGame(GameData data);
        void EditGame(GameData data);
        void DeleteGame();
        void RunGame();

        long Query(wxString str);
        wxString ReturnTableItem(long row, long col);
        GameData GetSingleGameData();
    private:
        Database* db;
};

#endif // GAMEMANAGER_H
