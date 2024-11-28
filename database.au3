#cs ----------------------------------------------------------------------------

 AutoIt Version: 3.2.12.1

 Script Function:
	SQLite database definition and methods for Green Launcher

#ce ----------------------------------------------------------------------------

#include <SQLite.au3>
#include <Misc.au3>

;--------------------------------------------------------------
; INITIALIZATION / CLOSURE
;--------------------------------------------------------------

Func _Database_Startup()
	; Initialize SQLite database
	_SQLite_Startup ( @ScriptDir & "\sqlite3.dll" )
	If @error > 0 Then
		MsgBox(16, "SQLite Error", "SQLite3.dll couldn't be loaded.")
		Exit - 1
	ElseIf _VersionCompare(_SQLite_LibVersion(), "3.6.19") == -1 Then
		MsgBox(16, "Error", "SQLite3.dll version must be equal or greater than 3.6.19! (Current version is " & _SQLite_LibVersion() & ")")
		_SQLite_Shutdown ()
		Exit - 1
	EndIf

	; Open/create database file
	_SQLite_Open ("GameLibrary.db")

	;Start transaction
	_SQLite_Exec(-1,	"BEGIN;")
	; Create general info
	_SQLite_Exec(-1,	"CREATE TABLE IF NOT EXISTS general(totalgames INTEGER, totaldevelopers INTEGER, totalpublishers INTEGER)")
	; Create metadata tables
	_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS years(year INTEGER PRIMARY KEY ASC UNIQUE, gameCount INTEGER); " & _
						"CREATE TABLE IF NOT EXISTS developers(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER); " & _
						"CREATE TABLE IF NOT EXISTS publishers(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER); " & _
						"CREATE TABLE IF NOT EXISTS genres(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER); " & _
						"CREATE TABLE IF NOT EXISTS categories(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, description TEXT, gameCount INTEGER); " & _
						"CREATE TABLE IF NOT EXISTS tools(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL UNIQUE, exePath TEXT NOT NULL, iconId INTEGER); ")
	; Create mapping tables for multiple metadata values
	_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS metadata_mapping(game_id INTEGER ASC, type TEXT ASC, metadata_id INTEGER, UNIQUE(game_id, type, metadata_id)); " & _
						"CREATE TABLE IF NOT EXISTS tools_mapping(game_id INTEGER, tools_id INTEGER, UNIQUE(game_id, tools_id));") ; This might get deleted
	; Create games table
	_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS games(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, exePath TEXT NOT NULL, iconPath TEXT NOT NULL ON CONFLICT REPLACE DEFAULT '', favorite BOOLEAN NOT NULL CHECK (favorite IN (0, 1)) DEFAULT 0, year INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT -1)")
	; Data integrity triggers
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS add_game_icon_integrity AFTER INSERT ON games WHEN new.iconPath == '' BEGIN " & _
							"UPDATE games SET iconPath=new.exePath WHERE id=new.id;" & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS add_game_year_task AFTER INSERT ON games BEGIN " & _
							"INSERT OR IGNORE INTO years VALUES(new.year, 0); " & _
							"UPDATE years SET gameCount=gameCount+1 WHERE year==new.year; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS update_game_year_task UPDATE ON games WHEN new.year <> old.year BEGIN " & _
							"INSERT OR IGNORE INTO years VALUES(new.year, 0); " & _
							"UPDATE years SET gameCount=gameCount+1 WHERE year==new.year; " & _
							"UPDATE years SET gameCount=gameCount-1 WHERE year==old.year; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS update_game_icon_integrity AFTER UPDATE ON games WHEN new.iconPath == '' BEGIN " & _
							"UPDATE games SET iconPath=new.exePath WHERE id=new.id;" & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS delete_game_task DELETE ON games BEGIN " & _
							"UPDATE years SET gameCount=gameCount-1 WHERE year==old.year; " & _
							"DELETE FROM metadata_mapping WHERE game_id==old.id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS clean_years_task AFTER UPDATE ON years WHEN new.gameCount==0 BEGIN " & _
							"DELETE FROM years WHERE year=new.year; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS delete_dev_task DELETE ON developers BEGIN " & _
							"DELETE FROM metadata_mapping WHERE type=='developers' AND metadata_id=old.id; "  & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS delete_publ_task DELETE ON publishers BEGIN " & _
							"DELETE FROM metadata_mapping WHERE type=='publishers' AND metadata_id=old.id; "  & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS delete_genre_task DELETE ON genres BEGIN " & _
							"DELETE FROM metadata_mapping WHERE type=='genres' AND metadata_id=old.id; "  & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS delete_cat_task DELETE ON categories BEGIN " & _
							"DELETE FROM metadata_mapping WHERE type=='categories' AND metadata_id=old.id; "  & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS map_developers_task INSERT ON metadata_mapping WHEN new.type='developers' BEGIN " & _
							"UPDATE developers SET gameCount=gameCount+1 WHERE id==new.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS unmap_developers_task DELETE ON metadata_mapping WHEN old.type='developers' BEGIN " & _
							"UPDATE developers SET gameCount=gameCount-1 WHERE id==old.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS map_publishers_task INSERT ON metadata_mapping WHEN new.type='publishers' BEGIN " & _
							"UPDATE publishers SET gameCount=gameCount+1 WHERE id==new.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS unmap_publishers_task DELETE ON metadata_mapping WHEN old.type='publishers' BEGIN " & _
							"UPDATE publishers SET gameCount=gameCount-1 WHERE id==old.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS map_genres_task INSERT ON metadata_mapping WHEN new.type='genres' BEGIN " & _
							"UPDATE genres SET gameCount=gameCount+1 WHERE id==new.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS unmap_genres_task DELETE ON metadata_mapping WHEN old.type='genres' BEGIN " & _
							"UPDATE genres SET gameCount=gameCount-1 WHERE id==old.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS map_categories_task INSERT ON metadata_mapping WHEN new.type='categories' BEGIN " & _
							"UPDATE categories SET gameCount=gameCount+1 WHERE id==new.metadata_id; " & _
						"END;")
	_SQLite_Exec(-1, 	"CREATE TRIGGER IF NOT EXISTS unmap_categories_task DELETE ON metadata_mapping WHEN old.type='categories' BEGIN " & _
							"UPDATE categories SET gameCount=gameCount-1 WHERE id==old.metadata_id; " & _
						"END;")
	; Game list/search interface
	_SQLite_Exec(-1,	"CREATE VIEW IF NOT EXISTS gameList AS SELECT " & _ 
							"games.name, " & _ 
							"REPLACE(REPLACE(games.favorite, 0, 'No'), 1, 'Yes'), " & _ 
							"REPLACE(games.year, -1, ''), " & _ 
							"(SELECT GROUP_CONCAT(name, ', ') FROM developers JOIN metadata_mapping ON game_id=games.id AND type=='developers' AND metadata_id==id) AS developer, " & _ 
							"(SELECT GROUP_CONCAT(name, ', ') FROM publishers JOIN metadata_mapping ON game_id=games.id AND type=='publishers' AND metadata_id==id) AS publisher, " & _ 
							"(SELECT GROUP_CONCAT(name, ', ') FROM genres JOIN metadata_mapping ON game_id=games.id AND type=='genres' AND metadata_id==id) AS genre, " & _ 
							"(SELECT GROUP_CONCAT(name, ', ') FROM categories JOIN metadata_mapping ON game_id=games.id AND type=='categories' AND metadata_id==id) AS category, " & _ 
							"games.exePath, " & _ 
							"games.iconPath, " & _ 
							"games.id " & _ 
						"FROM games ")
	; End transaction
	_SQLite_Exec(-1,	"END;")

EndFunc   ;==>_Database_Startup()

Func _Database_Shutdown()
	_SQLite_Close ()
	_SQLite_Shutdown ()
EndFunc   ;==>_Database_Shutdown()

;--------------------------------------------------------------
; QUERY METHODS
;--------------------------------------------------------------

Func _Database_GetGamesByQuery($sSQL, ByRef $aData, ByRef $iRows, ByRef $iCols)
	_SQLite_GetTable2d(-1, $sSQL, $aData, $iRows, $iCols)
EndFunc   ;==>_Database_GetGamesByQuery

;--------------------------------------------------------------
; DATA MANIPULATION METHODS
;--------------------------------------------------------------


; GAMES TABLE METHODS

Func _Database_InsertGame($sName, $sExePath, $sIconPath = "NULL", $iFavorite = 0, $iYear = -1)
	Local $iReturnId = -1
	If _SQLite_Exec(-1,	'INSERT INTO games VALUES (NULL, '&sanitize($sName)&', '&sanitize($sExePath)&', '&sanitize($sIconPath)&', '&sanitize($iFavorite)&', '&sanitize($iYear)&')') == $SQLITE_OK Then
		Local $aRow
		_SQLite_QuerySingleRow(-1, "SELECT max(id) FROM games", $aRow)
		$iReturnId = Number($aRow[0])
	EndIf
	Return $iReturnId
EndFunc   ;==>_Database_InsertGame

Func _Database_UpdateGame($iGameId, $sName = -2, $sExePath = -2, $sIconPath = -2, $iFavorite = -2, $iYear = -2)
	Local $sUpdateSet = '' 
	If $sName <> -2 Then $sUpdateSet &= 'name='&sanitize($sName)&', '
	If $sExePath <> -2 Then $sUpdateSet &= 'exePath='&sanitize($sExePath)&', '
	If $sIconPath <> -2 Then $sUpdateSet &= 'iconPath='&sanitize($sIconPath)&', '
	If $iFavorite <> -2 Then $sUpdateSet &= 'favorite='&sanitize($iFavorite)&', '
	If $iYear <> -2 Then $sUpdateSet &= 'year='&sanitize($iYear)&', '
	Return _SQLite_Exec(-1, 'UPDATE games SET '&StringTrimRight($sUpdateSet, 2)&' WHERE id='&$iGameId) == $SQLITE_OK
EndFunc   ;==>_Database_UpdateGame

Func _Database_DeleteGame($iGameId)
	Return _SQLite_Exec(-1, 'DELETE FROM games WHERE id='&$iGameId) == $SQLITE_OK
EndFunc   ;==>_Database_DeleteGame

; ICONS TABLE METHODS

;~ Func Database_InsertIcon($sIconPath)
;~ 	_SQLite_Exec(-1, 'INSERT OR IGNORE INTO icons VALUES(NULL, '&sanitize($sIconPath)&', 0)')
;~ 	Local $aRow
;~ 	_SQLite_QuerySingleRow(-1, 'SELECT id FROM icons WHERE path='&sanitize($sIconPath), $aRow)
;~ 	Return Number($aRow[0])
;~ EndFunc   ;==>Database_InsertIcon

;~ Func Database_UpdateIcon($iIconId, $sIconPath)
;~ 	Return _SQLite_Exec(-1, 'UPDATE icons SET '&$sIconPath&' WHERE id=' & $iIconId) == $SQLITE_OK
;~ EndFunc   ;==>Database_UpdateIcon

;~ Func Database_DeleteIcon($iIconId)
;~ 	Return _SQLite_Exec(-1, 'DELETE FROM icons WHERE id=' & $iIconId) == $SQLITE_OK
;~ EndFunc   ;==>Database_DeleteIcon

; METADATA METHODS

Func _Database_InsertMappedMetadata($sTableName, $sName, $sDescription = "NULL")
	Local $aRow, $iReturnId = -1
	If _SQLite_Exec(-1,	'INSERT INTO '&$sTableName&' VALUES(NULL, '&sanitize($sName)&', '&sanitize($sDescription)&', 0)') == $SQLITE_OK Then
		_SQLite_QuerySingleRow(-1, 'SELECT max(id) FROM '&$sTableName, $aRow)
		$iReturnId = Number($aRow[0])
	Else
		_SQLite_QuerySingleRow(-1, 'SELECT id FROM '&$sTableName&' WHERE name=='&sanitize($sName), $aRow)
		$iReturnId = Number($aRow[0])
	EndIf
	Return $iReturnId
EndFunc   ;==>_Database_InsertMappedMetadata

Func _Database_MapGameToMetadata($iGameId, $sTableName, $iMetadataId)
	Return _SQLite_Exec(-1,	'INSERT INTO metadata_mapping VALUES('&$iGameId&', '&sanitize($sTableName)&', '&$iMetadataId&'); ') == $SQLITE_OK
EndFunc   ;==>_Database_MapMetadataToGame

Func _Database_RemoveMetadataMap($iGameId, $sTableName = -1, $iMetadataId = -1)
	; Default: Delete all maps related to a game
	Local $sSQL = 'DELETE FROM metadata_mapping WHERE game_id=='&$iGameId
	; Additional: Delete all maps related to a metadata type
	If $sTableName <> -1 Then
		$sSQL &= ' AND type=='&sanitize($sTableName)
	EndIf
	; Additional: Delete a specific metadata map
	If $iMetadataId > 0 Then
		$sSQL &= ' AND metadata_id=='&$iMetadataId
	EndIf
	Return _SQLite_Exec(-1, $sSQL) == $SQLITE_OK
EndFunc   ;==>Database_RemoveMetadataMap

Func _Database_UpdateMappedMetadata($sTableName, $iMetadataId, $sName = -2, $sDescription = -2)
	Local $sUpdateSet = ''
	If $sName <> -1 Then $sUpdateSet &= 'name='&sanitize($sName)&', '
	If $sDescription <> -1 Then $sUpdateSet &= 'description='&sanitize($sDescription)&', '
	Return _SQLite_Exec(-1,	'UPDATE '&$sTableName&' SET '&StringTrimRight($sUpdateSet, 2)&' WHERE id=='&$iMetadataId&'; ') == $SQLITE_OK
EndFunc   ;==>_Database_UpdateMappedMetadata

Func _Database_DeleteMappedMetadata($sTableName, $iMetadataId)
	Return _SQLite_Exec(-1,	'DELETE FROM '&$sTableName&' WHERE id=='&$iMetadataId&'; ') == $SQLITE_OK
EndFunc   ;==>_Database_DeleteMappedMetadata


;--------------------------------------------------------------
; GENERAL
;--------------------------------------------------------------

Func _Database_BeginTransaction()
	_SQLite_Exec(-1,	'BEGIN TRANSACTION;')	
EndFunc   ;==>_Database_BeginTransaction

Func _Database_EndTransaction()
	_SQLite_Exec(-1,	'COMMIT;')	
EndFunc   ;==>_Database_EndTransaction

Func sanitize($val)
	If Not IsNumber($val) Then
		If $val == "" Or Not $val Then $val = "NULL"
		If $val <> "NULL" Then $val = '"' & $val & '"'
	EndIf
	Return $val
EndFunc   ;==>sanitize