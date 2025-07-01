/***************************************************************
 * Name:      Database.cpp
 * Purpose:   SQLite3 database handler
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-31
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "Database.h"
#include "GameData.h"
#include "sqlite3/sqlite3.h"

#include <wx/wx.h>
#include <wx/log.h>
#include <wx/string.h>
#include <wx/tokenzr.h>
#include <wx/datetime.h>

Database::Database()
{
    int rc;
    char *errmsg;
    // Open Database
    rc = sqlite3_open("GameLibrary.db", &db);
    if (rc != SQLITE_OK) {
        wxLogError("Error opening SQLite3 database (%i): %s", rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    const char *sqlCreateTable =
    "BEGIN;"
    "CREATE TABLE IF NOT EXISTS general(totalgames INTEGER, totaldevelopers INTEGER, totalpublishers INTEGER);"
    "CREATE TABLE IF NOT EXISTS games(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, favorite BOOLEAN NOT NULL CHECK (favorite IN (0, 1)) DEFAULT 0, hidden BOOLEAN NOT NULL CHECK (favorite IN (0, 1)) DEFAULT 0, year INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT -1, actionCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS tools(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, exePath TEXT NOT NULL, iconId INTEGER);"
    "CREATE TABLE IF NOT EXISTS actions(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, type INTEGER NOT NULL, path TEXT NOT NULL, workingDir TEXT NOT NULL, args TEXT NOT NULL, system_id INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT -1, iconPath TEXT NOT NULL ON CONFLICT REPLACE DEFAULT '');"
    "CREATE TABLE IF NOT EXISTS categories(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS sources(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS years(name INTEGER PRIMARY KEY ASC UNIQUE, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS platforms(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS developers(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS publishers(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS genres(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS series(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS regions(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS languages(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS license_models(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0);"
    "CREATE TABLE IF NOT EXISTS actions_mapping(game_id INTEGER, isMain BOOLEAN, action_id INTEGER, UNIQUE(game_id, isMain, action_id));"
    "CREATE TABLE IF NOT EXISTS metadata_mapping(game_id INTEGER ASC, type TEXT ASC, metadata_id INTEGER, UNIQUE(game_id, type, metadata_id));"
    "CREATE TABLE IF NOT EXISTS tools_mapping(game_id INTEGER, tools_id INTEGER, UNIQUE(game_id, tools_id));"
    "CREATE TRIGGER IF NOT EXISTS add_action_icon_integrity AFTER INSERT ON actions WHEN new.iconPath == '' BEGIN "
        "UPDATE actions SET iconPath=new.path WHERE id=new.id;"
    "END;"
    "CREATE TRIGGER IF NOT EXISTS update_action_icon_integrity AFTER UPDATE ON actions WHEN new.iconPath == '' BEGIN "
		"UPDATE actions SET iconPath=new.path WHERE id=new.id;"
	"END;"
    "CREATE TRIGGER IF NOT EXISTS add_game_year_task AFTER INSERT ON games BEGIN "
        "INSERT OR IGNORE INTO years VALUES(new.year, 0);"
        "UPDATE years SET gameCount=gameCount+1 WHERE name==new.year;"
    "END;"
	"CREATE TRIGGER IF NOT EXISTS update_game_year_task UPDATE ON games WHEN new.year <> old.year BEGIN "
		"INSERT OR IGNORE INTO years VALUES(new.year, 0);"
		"UPDATE years SET gameCount=gameCount+1 WHERE name==new.year;"
		"UPDATE years SET gameCount=gameCount-1 WHERE name==old.year;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_game_task DELETE ON games BEGIN "
		"UPDATE years SET gameCount=gameCount-1 WHERE name==old.year;"
		"DELETE FROM actions_mapping WHERE game_id==old.id;"
		"DELETE FROM metadata_mapping WHERE game_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_actions_task INSERT ON actions_mapping BEGIN "
        "UPDATE games SET actionCount=actionCount+1 WHERE id==new.game_id;"
    "END;"
	"CREATE TRIGGER IF NOT EXISTS delete_action_task DELETE ON actions BEGIN "
		"DELETE FROM actions_mapping WHERE action_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_action_map_task DELETE ON actions_mapping BEGIN "
		"UPDATE games SET actionCount=actionCount-1 WHERE id==old.game_id;"
		"DELETE FROM actions WHERE id==old.action_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS clean_years_task AFTER UPDATE ON years WHEN new.gameCount==0 BEGIN "
		"DELETE FROM years WHERE name=new.name;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_categories_task INSERT ON metadata_mapping WHEN new.type='categories' BEGIN "
		"UPDATE categories SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_categories_task DELETE ON metadata_mapping WHEN old.type='categories' BEGIN "
		"UPDATE categories SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_categories_task DELETE ON categories BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='categories' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_sources_task INSERT ON metadata_mapping WHEN new.type='sources' BEGIN "
		"UPDATE sources SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_sources_task DELETE ON metadata_mapping WHEN old.type='sources' BEGIN "
		"UPDATE sources SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_sources_task DELETE ON sources BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='sources' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_platforms_task INSERT ON metadata_mapping WHEN new.type='platforms' BEGIN "
		"UPDATE platforms SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_platforms_task DELETE ON metadata_mapping WHEN old.type='platforms' BEGIN "
		"UPDATE platforms SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_platforms_task DELETE ON platforms BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='platforms' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_developers_task INSERT ON metadata_mapping WHEN new.type='developers' BEGIN "
		"UPDATE developers SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_developers_task DELETE ON metadata_mapping WHEN old.type='developers' BEGIN "
		"UPDATE developers SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_developers_task DELETE ON developers BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='developers' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_publishers_task INSERT ON metadata_mapping WHEN new.type='publishers' BEGIN "
		"UPDATE publishers SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_publishers_task DELETE ON metadata_mapping WHEN old.type='publishers' BEGIN "
		"UPDATE publishers SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_publishers_task DELETE ON publishers BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='publishers' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_genres_task INSERT ON metadata_mapping WHEN new.type='genres' BEGIN "
		"UPDATE genres SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_genres_task DELETE ON metadata_mapping WHEN old.type='genres' BEGIN "
		"UPDATE genres SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_genres_task DELETE ON genres BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='genres' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_series_task INSERT ON metadata_mapping WHEN new.type='series' BEGIN "
		"UPDATE series SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_series_task DELETE ON metadata_mapping WHEN old.type='series' BEGIN "
		"UPDATE series SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_series_task DELETE ON series BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='series' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_regions_task INSERT ON metadata_mapping WHEN new.type='regions' BEGIN "
		"UPDATE regions SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_regions_task DELETE ON metadata_mapping WHEN old.type='regions' BEGIN "
		"UPDATE regions SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_regions_task DELETE ON regions BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='regions' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_languages_task INSERT ON metadata_mapping WHEN new.type='languages' BEGIN "
		"UPDATE languages SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_languages_task DELETE ON metadata_mapping WHEN old.type='languages' BEGIN "
		"UPDATE languages SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_languages_task DELETE ON languages BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='languages' AND metadata_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_license_models_task INSERT ON metadata_mapping WHEN new.type='license_models' BEGIN "
		"UPDATE license_models SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_license_models_task DELETE ON metadata_mapping WHEN old.type='license_models' BEGIN "
		"UPDATE license_models SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_license_models_task DELETE ON license_models BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='license_models' AND metadata_id==old.id;"
	"END;"
	"CREATE VIEW IF NOT EXISTS gameList AS SELECT "
        "games.id, "
        "(SELECT GROUP_CONCAT(path || ' ' || args, ';') FROM actions JOIN actions_mapping ON game_id=games.id AND action_id=id ) AS exePath, "
        "(SELECT GROUP_CONCAT(workingDir, ';') FROM actions JOIN actions_mapping ON game_id=games.id AND action_id=id ) AS workingDir, "
        "(SELECT GROUP_CONCAT(name, ';') FROM actions JOIN actions_mapping ON game_id=games.id AND action_id=id) AS actionNames, "
        "(SELECT iconPath FROM actions JOIN actions_mapping ON game_id=games.id AND isMain==1 AND action_id=id) AS iconPath, "
		"games.name, "
		"REPLACE(REPLACE(games.favorite, 0, 'No'), 1, 'Yes') AS favorite, "
		"REPLACE(games.year, -1, '') AS years, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM developers JOIN metadata_mapping ON game_id=games.id AND type=='developers' AND metadata_id==id) AS developers, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM publishers JOIN metadata_mapping ON game_id=games.id AND type=='publishers' AND metadata_id==id) AS publishers, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM platforms JOIN metadata_mapping ON game_id=games.id AND type=='platforms' AND metadata_id==id) AS platforms, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM genres JOIN metadata_mapping ON game_id=games.id AND type=='genres' AND metadata_id==id) AS genres, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM series JOIN metadata_mapping ON game_id=games.id AND type=='series' AND metadata_id==id) AS series, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM regions JOIN metadata_mapping ON game_id=games.id AND type=='regions' AND metadata_id==id) AS regions, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM languages JOIN metadata_mapping ON game_id=games.id AND type=='languages' AND metadata_id==id) AS languages, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM license_models JOIN metadata_mapping ON game_id=games.id AND type=='license_models' AND metadata_id==id) AS license_models, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM categories JOIN metadata_mapping ON game_id=games.id AND type=='categories' AND metadata_id==id) AS categories, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM sources JOIN metadata_mapping ON game_id=games.id AND type=='sources' AND metadata_id==id) AS sources "
	"FROM games;"
	"END;";
	rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &errmsg);
	if (rc) {
      wxLogError("Error creating games table in SQLite3: ", wxString(errmsg));
      sqlite3_free(errmsg);
   }
}

Database::~Database()
{
    if (pCols != -1) {
        sqlite3_free_table(pResult);
    }
    if (fCols != -1) {
        sqlite3_free_table(fResult);
    }
    sqlite3_close(db);
}

void Database::Query(wxString str)
{
    if (pCols != -1) {
        sqlite3_free_table(pResult);
    }
    int rc;
    char *errmsg;
    rc = sqlite3_get_table(
        db,
        str.mb_str(),
        &pResult,
        &pRows,
        &pCols,
        &errmsg
    );
    if (rc != SQLITE_OK ) {
        sqlite3_free_table(pResult);
        wxLogError("Error querying SQLite3 database: ", wxString(errmsg));
        sqlite3_free(errmsg);
    }
}

wxString Database::ReturnTableItem(long row, long col)
{
    return wxString(pResult[(pCols) * (row + 1) + col]);
}

void Database::RunSQL(wxString stmtStr)
{
    int rc;
    char* errmsg;
    //sqlite3_stmt *stmt = NULL;
    rc = sqlite3_exec(db, stmtStr.mb_str(), NULL, NULL, &errmsg);
    if (rc) {
      wxLogError("Error running SQL in Database: ", wxString(errmsg));
      sqlite3_free(errmsg);
   }
}

void Database::AddAction(long game_id, bool isMain, wxString name, long type, wxString path, wxString workingDir, wxString args, long systemId, wxString iconPath)
{
    int rc;
    sqlite3_int64 action_id;
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, "INSERT INTO actions (id, name, type, path, workingDir, args, system_id, iconPath) values(NULL, ?, ?, ?, ?, ?, ?, ?);", -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, type);
        sqlite3_bind_text(stmt, 3, path.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, workingDir.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, args.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 6, systemId);
        sqlite3_bind_text(stmt, 7, iconPath.mb_str(), -1, SQLITE_TRANSIENT);
    }
    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    action_id = sqlite3_last_insert_rowid(db);
    RunSQL(wxString::Format(wxString("INSERT INTO actions_mapping values(%d, %d, %d)"), long(game_id), int(isMain), long(action_id)));
}

void Database::UpdateAction(long actionId, wxString name, long type, wxString path, wxString workingDir, wxString args, long systemId, wxString iconPath)
{
    int rc;
    sqlite3_int64 action_id;
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, wxString::Format("UPDATE actions SET name=?, type=?, path=?, workingDir=?, args=?, system_id=?, iconPath=? WHERE id==%d", actionId), -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, type);
        sqlite3_bind_text(stmt, 3, path.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, workingDir.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, args.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 6, systemId);
        sqlite3_bind_text(stmt, 7, iconPath.mb_str(), -1, SQLITE_TRANSIENT);
    }
    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
}

void Database::AddMetadataAndMap(const char* type, wxString names, long gameId)
{
    wxStringTokenizer tokenizer(names, ";");
    int rc;
    sqlite3_stmt *stmt;
    while (tokenizer.HasMoreTokens()) {
        wxString token = tokenizer.GetNextToken();
        // Try to insert the metadata in its table
        rc = sqlite3_prepare_v2(db, wxString::Format("INSERT INTO %s (id, name) values(NULL, ?);", type).mb_str(), -1, &stmt, NULL);
        if (rc == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, token.mb_str(), -1, SQLITE_TRANSIENT);
        }
        rc = sqlite3_step(stmt);
        rc = sqlite3_finalize(stmt);
        // Then, try to map it to its game
        rc = sqlite3_prepare_v2(db, wxString::Format("INSERT INTO metadata_mapping (game_id, type, metadata_id) values(?, ?, (SELECT id FROM %s WHERE name==?));", type).mb_str(), -1, &stmt, NULL);
        if (rc == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, gameId);
            sqlite3_bind_text(stmt, 2, type, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, token.mb_str(), -1, SQLITE_TRANSIENT);
        }
        rc = sqlite3_step(stmt);
        rc = sqlite3_finalize(stmt);
    }
}

void Database::UpdateMetadata(const char* type, wxString names, long gameId)
{
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, wxString::Format("DELETE FROM metadata_mapping WHERE game_id==%d AND type=='%s'", gameId, type).mb_str(), -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    AddMetadataAndMap(type, names, gameId);
}

void Database::AddGame(GameData data)
{
    int rc;
    sqlite3_stmt *stmt;
    sqlite3_int64 game_id;
    // First, insert the game (plus date)
    rc = sqlite3_prepare_v2(db, "INSERT INTO games (id, name, favorite, hidden, year) values(NULL, ?, ?, ?, ?);", -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, data.name.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, int(data.favorite));
        sqlite3_bind_int(stmt, 3, int(data.hidden));
        sqlite3_bind_int(stmt, 4, data.metadata.releaseDate.GetYear());
    }
    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    game_id = sqlite3_last_insert_rowid(db);
    // Then, insert the actions
    for (int i = 0; i<data.actions.size(); i++) {
        AddAction(game_id, data.actions[i].isMain, data.actions[i].name, data.actions[i].type, data.actions[i].path, data.actions[i].workingDir, data.actions[i].args, data.actions[i].systemId, data.actions[i].iconPath);
    }
    // And then, all other metadata
    AddMetadataAndMap("categories", data.category, game_id);
    AddMetadataAndMap("sources", data.source, game_id);
    AddMetadataAndMap("developers", data.metadata.developer, game_id);
    AddMetadataAndMap("publishers", data.metadata.publisher, game_id);
    AddMetadataAndMap("platforms", data.metadata.platform, game_id);
    AddMetadataAndMap("genres", data.metadata.genre, game_id);
    AddMetadataAndMap("series", data.metadata.series, game_id);
    AddMetadataAndMap("regions", data.metadata.region, game_id);
    AddMetadataAndMap("languages", data.metadata.language, game_id);
    AddMetadataAndMap("license_models", data.metadata.license, game_id);
}

void Database::EditGame(GameData data)
{
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, wxString::Format("UPDATE games SET name=?, favorite=?, hidden=?, year=? WHERE id==%d", data.id).mb_str(), -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, data.name.mb_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, int(data.favorite));
        sqlite3_bind_int(stmt, 3, int(data.hidden));
        sqlite3_bind_int(stmt, 4, data.metadata.releaseDate.GetYear());
    }
    rc = sqlite3_step(stmt);
    rc = sqlite3_finalize(stmt);
    // We only keep actions from GameData which have an ID, we assume the other ones were deleted
    wxString actionsFilter = wxString::Format("DELETE FROM actions_mapping WHERE game_id==%d", data.id);
    for (int i = 0; i<data.actions.size(); i++) {
        if (data.actions[i].id > 0) {
            actionsFilter += wxString::Format(" AND action_id!=%d", data.actions[i].id);
            UpdateAction(data.actions[i].id, data.actions[i].name, data.actions[i].type, data.actions[i].path, data.actions[i].workingDir, data.actions[i].args, data.actions[i].systemId, data.actions[i].iconPath);
        }
    }
    RunSQL(actionsFilter);
    for (int i = 0; i<data.actions.size(); i++) {
        if (data.actions[i].id == 0) {
            AddAction(data.id, false, data.actions[i].name, data.actions[i].type, data.actions[i].path, data.actions[i].workingDir, data.actions[i].args, data.actions[i].systemId, data.actions[i].iconPath);
        }
    }
    AddMetadataAndMap("categories", data.category, data.id);
    AddMetadataAndMap("sources", data.source, data.id);
    AddMetadataAndMap("developers", data.metadata.developer, data.id);
    AddMetadataAndMap("publishers", data.metadata.publisher, data.id);
    AddMetadataAndMap("platforms", data.metadata.platform, data.id);
    AddMetadataAndMap("genres", data.metadata.genre, data.id);
    AddMetadataAndMap("series", data.metadata.series, data.id);
    AddMetadataAndMap("regions", data.metadata.region, data.id);
    AddMetadataAndMap("languages", data.metadata.language, data.id);
    AddMetadataAndMap("license_models", data.metadata.license, data.id);
}

void Database::DeleteGame(long gameId)
{
    RunSQL(wxString::Format("DELETE FROM games WHERE id==%d;", gameId));
}

wxString Database::ReturnMetadata(const char* type, long gameId)
{
    int rc;
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, wxString::Format("SELECT GROUP_CONCAT(name, ';') FROM %s WHERE id IN (SELECT metadata_id FROM metadata_mapping WHERE game_id==%d)", type, gameId).mb_str(), -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    wxString result = wxString(sqlite3_column_text(stmt, 0));
    rc = sqlite3_finalize(stmt);
    return result;
}

GameData Database::ReturnGameData(long id)
{
    GameData data;
    int rc;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, wxString::Format("SELECT * FROM games WHERE id==%d", id).mb_str(), -1, &stmt, NULL);
    rc = sqlite3_step(stmt);
    // Get base game data
    data.id = id;
    data.name = wxString(sqlite3_column_text(stmt, 1));
    data.favorite = sqlite3_column_int(stmt, 2);
    data.hidden = sqlite3_column_int(stmt, 3);
    data.metadata.releaseDate = wxDateTime(wxDateTime::wxDateTime_t(1), wxDateTime::Month(wxDateTime::Jan), sqlite3_column_int(stmt, 4));
    long actionCount = sqlite3_column_int(stmt, 5);
    rc = sqlite3_finalize(stmt);
    // Get actions
    rc = sqlite3_prepare_v2(db, wxString::Format("SELECT * FROM actions WHERE id IN (SELECT action_id FROM actions_mapping  WHERE game_id==%d)", id).mb_str(), -1, &stmt, NULL);
    while (rc != SQLITE_DONE) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            ActionData aData;
            aData.id = sqlite3_column_int(stmt, 0);
            aData.name = wxString(sqlite3_column_text(stmt, 1));
            aData.isMain = aData.name.IsSameAs(wxString("Launch Game"));
            aData.type = sqlite3_column_int(stmt, 2);
            aData.path = wxString(sqlite3_column_text(stmt, 3));
            aData.workingDir = wxString(sqlite3_column_text(stmt, 4));
            aData.args = wxString(sqlite3_column_text(stmt, 5));
            aData.systemId = sqlite3_column_int(stmt, 6);
            aData.iconPath = wxString(sqlite3_column_text(stmt, 7));
            data.actions.push_back(aData);
        }
    }
    rc = sqlite3_finalize(stmt);
    // Get metadata
    data.category = ReturnMetadata("categories", data.id);
    data.source = ReturnMetadata("sources", data.id);
    data.metadata.developer = ReturnMetadata("developers", data.id);
    data.metadata.publisher = ReturnMetadata("publishers", data.id);
    data.metadata.platform = ReturnMetadata("platforms", data.id);
    data.metadata.genre = ReturnMetadata("genres", data.id);
    data.metadata.series = ReturnMetadata("series", data.id);
    data.metadata.region = ReturnMetadata("regions", data.id);
    data.metadata.language = ReturnMetadata("languages", data.id);
    data.metadata.license = ReturnMetadata("license_models", data.id);
    return data;
}

void Database::GetMetadataTable(wxString type)
{
    if (fCols != -1) {
        sqlite3_free_table(fResult);
    }
    int rc;
    char *errmsg;
    rc = sqlite3_get_table(
        db,
        wxString::Format("SELECT name, gameCount FROM %s;", type).mb_str(),
        &fResult,
        &fRows,
        &fCols,
        &errmsg
    );
    if (rc != SQLITE_OK ) {
        sqlite3_free_table(fResult);
        wxLogError("Error getting filters from SQLite3 database: ", wxString(errmsg));
        sqlite3_free(errmsg);
    }
}

wxString Database::ReturnFilterTableItem(long row, long col)
{
    return wxString(fResult[(fCols) * (row + 1) + col]);
}

void Database::FreeMetadataTable()
{
    sqlite3_free(fResult);
    fRows = -1;
    fCols = -1;
}
