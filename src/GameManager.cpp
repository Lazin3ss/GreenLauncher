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
#include <wx/tokenzr.h>

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
}

void GameManager::DeleteGame()
{
    long id = wxAtoi(ReturnTableItem(selectedGameIdx, 0));
    db->DeleteGame(id);
}

void GameManager::RunAction(size_t idx)
{
    wxStringTokenizer paths = wxStringTokenizer(db->ReturnTableItem(selectedGameIdx, 1), ";");
    wxStringTokenizer workingDirs = wxStringTokenizer(db->ReturnTableItem(selectedGameIdx, 2), ";");
    while (paths.HasMoreTokens()) {
        wxString tokenPath = paths.GetNextToken();
        wxString tokenWorkDir = workingDirs.GetNextToken();
        if (paths.CountTokens() == idx) {
            wxExecuteEnv env;
            env.cwd = tokenWorkDir;
            wxProcess* process;
            wxExecute(tokenPath, wxEXEC_SYNC, process, &env);
            break;
        }
    }
}

long GameManager::Query()
{
    db->Query(currentQuery + _(" ") + currentOrder);
    return db->pRows;
}

wxString GameManager::ReturnTableItem(long row, long col)
{
    return db->ReturnTableItem(row, col);
}

GameData GameManager::GetSingleGameData()
{
    long id = wxAtoi(ReturnTableItem(selectedGameIdx, 0));
    return db->ReturnGameData(id);
}

long GameManager::GetFilterList(wxString type)
{
    db->GetMetadataTable(type);
    return db->fRows;
}

wxString GameManager::GetFilterLabel(long idx)
{
    return wxString::Format("%s (%s)", db->ReturnFilterTableItem(idx, 0), db->ReturnFilterTableItem(idx, 1));
}

wxString GameManager::GetFilterData(wxString type, long idx)
{
    return wxString::Format("SELECT * from gameList WHERE %s LIKE '%%%s%%'", type, db->ReturnFilterTableItem(idx, 0));
}

void GameManager::FreeFilterList()
{
    db->FreeMetadataTable();
}
