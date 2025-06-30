/***************************************************************
 * Name:      GameManager.cpp
 * Purpose:   Code for Game Manager
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-06-28
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include <wx/string.h>
#include <wx/process.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/msgdlg.h>
#include <wx/frame.h>
#include <wx/dialog.h>

#include "GameManager.h"
#include "GameData.h"
#include "wxEditGame.h"

GameManager::GameManager()
{
    db = new Database;
}

GameManager::~GameManager()
{
    delete db;
}

void GameManager::AddGame(GameData data)
{
    db->AddGame(data);
}

void GameManager::EditGame(GameData data)
{
    db->EditGame(data);
    //long id = wxAtoi(ReturnTableItem(selectedGameIdx, 9));
    //EditGame dialog(&parent, "Editing "+ReturnTableItem(selectedGameIdx, 0));
    //int rc = dialog.ShowModal();
    //if (rc == wxOK) {
//
    //}
   // db->GetGameData(gameId);
}

void GameManager::DeleteGame()
{
    long id = wxAtoi(ReturnTableItem(selectedGameIdx, 9));
    db->DeleteGame(id);
}

void GameManager::RunGame()
{
    wxFileName path(db->ReturnTableItem(selectedGameIdx, 7));
    wxExecuteEnv env;
    env.cwd = path.GetPath();
    wxProcess* process;
    wxExecute(path.GetFullPath(), wxEXEC_ASYNC, process, &env);
}

long GameManager::Query(wxString str)
{
    db->Query(str);
    return db->pRows;
}

wxString GameManager::ReturnTableItem(long row, long col)
{
    return db->ReturnTableItem(row, col);
}

GameData GameManager::GetSingleGameData()
{
    long id = wxAtoi(ReturnTableItem(selectedGameIdx, 9));
    return db->ReturnGameData(id);
}
