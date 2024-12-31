#include "Database.h"
#include "sqlite3/sqlite3.h"


#include <wx/wx.h>
#include <wx/log.h>
#include <wx/string.h>

Database::Database()
{
    int rc;
    char *error;
    // Open Database
    rc = sqlite3_open("GameLibrary.db", &db);
    if (rc != SQLITE_OK) {
        wxLogFatalError("Error opening SQLite3 database (%i): %s", rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    const char *sqlCreateTable =
    "BEGIN;"
    "CREATE TABLE IF NOT EXISTS general(totalgames INTEGER, totaldevelopers INTEGER, totalpublishers INTEGER);"
    "CREATE TABLE IF NOT EXISTS years(year INTEGER PRIMARY KEY ASC UNIQUE, gameCount INTEGER);"
    "CREATE TABLE IF NOT EXISTS developers(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER);"
    "CREATE TABLE IF NOT EXISTS publishers(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER);"
    "CREATE TABLE IF NOT EXISTS genres(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER);"
    "CREATE TABLE IF NOT EXISTS categories(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER);"
    "CREATE TABLE IF NOT EXISTS tools(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, exePath TEXT NOT NULL, iconId INTEGER);"
    "CREATE TABLE IF NOT EXISTS metadata_mapping(game_id INTEGER ASC, type TEXT ASC, metadata_id INTEGER, UNIQUE(game_id, type, metadata_id));"
    "CREATE TABLE IF NOT EXISTS tools_mapping(game_id INTEGER, tools_id INTEGER, UNIQUE(game_id, tools_id));"
    "CREATE TABLE IF NOT EXISTS games(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, exePath TEXT NOT NULL, iconPath TEXT NOT NULL ON CONFLICT REPLACE DEFAULT '', favorite BOOLEAN NOT NULL CHECK (favorite IN (0, 1)) DEFAULT 0, year INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT -1);"
    "CREATE TRIGGER IF NOT EXISTS add_game_icon_integrity AFTER INSERT ON games WHEN new.iconPath == '' BEGIN "
        "UPDATE games SET iconPath=new.exePath WHERE id=new.id;"
    "END;"
    "CREATE TRIGGER IF NOT EXISTS add_game_year_task AFTER INSERT ON games BEGIN "
        "INSERT OR IGNORE INTO years VALUES(new.year, 0);"
        "UPDATE years SET gameCount=gameCount+1 WHERE year==new.year;"
    "END;"
	"CREATE TRIGGER IF NOT EXISTS update_game_year_task UPDATE ON games WHEN new.year <> old.year BEGIN "
		"INSERT OR IGNORE INTO years VALUES(new.year, 0);"
		"UPDATE years SET gameCount=gameCount+1 WHERE year==new.year;"
		"UPDATE years SET gameCount=gameCount-1 WHERE year==old.year;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS update_game_icon_integrity AFTER UPDATE ON games WHEN new.iconPath == '' BEGIN "
		"UPDATE games SET iconPath=new.exePath WHERE id=new.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_game_task DELETE ON games BEGIN "
		"UPDATE years SET gameCount=gameCount-1 WHERE year==old.year;"
		"DELETE FROM metadata_mapping WHERE game_id==old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS clean_years_task AFTER UPDATE ON years WHEN new.gameCount==0 BEGIN "
		"DELETE FROM years WHERE year=new.year;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_dev_task DELETE ON developers BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='developers' AND metadata_id=old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_publ_task DELETE ON publishers BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='publishers' AND metadata_id=old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_genre_task DELETE ON genres BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='genres' AND metadata_id=old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS delete_cat_task DELETE ON categories BEGIN "
		"DELETE FROM metadata_mapping WHERE type=='categories' AND metadata_id=old.id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_developers_task INSERT ON metadata_mapping WHEN new.type='developers' BEGIN "
		"UPDATE developers SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_developers_task DELETE ON metadata_mapping WHEN old.type='developers' BEGIN "
		"UPDATE developers SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
    "CREATE TRIGGER IF NOT EXISTS map_publishers_task INSERT ON metadata_mapping WHEN new.type='publishers' BEGIN "
		"UPDATE publishers SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_publishers_task DELETE ON metadata_mapping WHEN old.type='publishers' BEGIN "
		"UPDATE publishers SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_genres_task INSERT ON metadata_mapping WHEN new.type='genres' BEGIN "
		"UPDATE genres SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_genres_task DELETE ON metadata_mapping WHEN old.type='genres' BEGIN "
		"UPDATE genres SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS map_categories_task INSERT ON metadata_mapping WHEN new.type='categories' BEGIN "
		"UPDATE categories SET gameCount=gameCount+1 WHERE id==new.metadata_id;"
	"END;"
	"CREATE TRIGGER IF NOT EXISTS unmap_categories_task DELETE ON metadata_mapping WHEN old.type='categories' BEGIN "
		"UPDATE categories SET gameCount=gameCount-1 WHERE id==old.metadata_id;"
	"END;"
	"CREATE VIEW IF NOT EXISTS gameList AS SELECT "
		"games.name, "
		"REPLACE(REPLACE(games.favorite, 0, 'No'), 1, 'Yes'), "
		"REPLACE(games.year, -1, ''), "
		"(SELECT GROUP_CONCAT(name, ', ') FROM developers JOIN metadata_mapping ON game_id=games.id AND type=='developers' AND metadata_id==id) AS developer, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM publishers JOIN metadata_mapping ON game_id=games.id AND type=='publishers' AND metadata_id==id) AS publisher, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM genres JOIN metadata_mapping ON game_id=games.id AND type=='genres' AND metadata_id==id) AS genre, "
		"(SELECT GROUP_CONCAT(name, ', ') FROM categories JOIN metadata_mapping ON game_id=games.id AND type=='categories' AND metadata_id==id) AS category, "
		"games.exePath, "
		"games.iconPath, "
		"games.id "
	"FROM games;"
	"END;";
	rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
	if (rc) {
      wxLogFatalError("Error creating games table in SQLite3: ", sqlite3_errmsg(db));
      sqlite3_free(error);
   }
}

Database::~Database()
{
    if (pCols != -1) {
        sqlite3_free_table(pResult);
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
        wxLogFatalError("Error querying SQLite3 database: ", wxString(errmsg));
        sqlite3_free(errmsg);
    }
}

wxString Database::ReturnTableItem(long row, long col)
{
    return wxString(pResult[(pCols) * (row + 1) + col]);
}
