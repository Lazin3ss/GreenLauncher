#cs ----------------------------------------------------------------------------

 AutoIt Version: 3.2.12.1

 Script Function:
	SQLite database definition and methods for Green Launcher

#ce ----------------------------------------------------------------------------

#include <SQLite.au3>
#include <Misc.au3>
#include <Array.au3>

;--------------------------------------------------------------
; INITIALIZATION / CLOSURE
;--------------------------------------------------------------

_Database_Startup()
_Database_Shutdown()

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
_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS metadata_mapping(type TEXT ASC, metadata_id INTEGER ASC, game_id INTEGER, UNIQUE(type, metadata_id, game_id)); " & _
					"CREATE TABLE IF NOT EXISTS tools_mapping(tools_id INTEGER, game_id INTEGER, UNIQUE(tools_id, game_id));") ; This might get deleted
; Create games table
_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS games(id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, exePath TEXT NOT NULL, iconPath TEXT NOT NULL ON CONFLICT REPLACE DEFAULT '', favorite INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT 0, year INTEGER NOT NULL ON CONFLICT REPLACE DEFAULT -1)")
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
; End transaction
_SQLite_Exec(-1,	"END;")

EndFunc   ;==>_Database_Startup()

Func _Database_Shutdown()
_SQLite_Close ()
_SQLite_Shutdown ()
EndFunc   ;==>_Database_Shutdown()


;--------------------------------------------------------------
; DATABASE METHODS
;--------------------------------------------------------------


; GAMES TABLE METHODS

Func Database_InsertGame($sName, $sExePath, $sIconPath = "NULL", $iFavorite = 0, $iYear = -1)
	Local $iReturnId = -1
	If _SQLite_Exec(-1,	'INSERT INTO games VALUES (NULL, '&sanitize($sName)&', '&sanitize($sExePath)&', '&sanitize($sIconPath)&', '&sanitize($iFavorite)&', '&sanitize($iYear)&')') == $SQLITE_OK Then
		Local $aRow
		_SQLite_QuerySingleRow(-1, "SELECT max(id) FROM games", $aRow)
		$iReturnId = Number($aRow[0])
	EndIf
	Return $iReturnId
EndFunc   ;==>Database_InsertGame

Func Database_UpdateGame($iGameId, $sName = -2, $sExePath = -2, $sIconPath = -2, $iFavorite = -2, $iYear = -2)
	Local $sUpdateSet = '' 
	If $sName <> -2 Then $sUpdateSet &= 'name='&sanitize($sName)&', '
	If $sExePath <> -2 Then $sUpdateSet &= 'exePath='&sanitize($sExePath)&', '
	If $sIconPath <> -2 Then $sUpdateSet &= 'iconPath='&sanitize($sIconPath)&', '
	If $iFavorite <> -2 Then $sUpdateSet &= 'favorite='&sanitize($iFavorite)&', '
	If $iYear <> -2 Then $sUpdateSet &= 'year='&sanitize($iYear)&', '
	Return _SQLite_Exec(-1, 'UPDATE games SET '&StringTrimRight($sUpdateSet, 2)&' WHERE id='&$iGameId) == $SQLITE_OK
EndFunc   ;==>Database_UpdateGame

Func Database_DeleteGame($iGameId)
	Return _SQLite_Exec(-1, 'DELETE FROM games WHERE id='&$iGameId) == $SQLITE_OK
EndFunc   ;==>Database_DeleteGame

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

Func Database_InsertMappedMetadata($sTableName, $sName, $sDescription = "NULL")
	Local $iReturnId = -1
	If _SQLite_Exec(-1,	'INSERT INTO '&$sTableName&' VALUES(NULL, '&sanitize($sName)&', '&sanitize($sDescription)&', 0)') == $SQLITE_OK Then
		Local $aRow
		_SQLite_QuerySingleRow(-1, 'SELECT max(id) FROM '&$sTableName&, $aRow)
		$iReturnId = Number($aRow[0])
	EndIf
	Return $iReturnId
EndFunc   ;==>Database_InsertMappedMetadata

Func Database_MapMetadataToGame($sTableName, $iMetadataId, $iGameId)
	Return _SQLite_Exec(-1,	'INSERT INTO metadata_mapping VALUES('&sanitize($sTableName)&', '&$iMetadataId&', '&$iGameId&'); ') == $SQLITE_OK
EndFunc   ;==>Database_MapMetadataToGame

Func Database_RemoveMetadataMap($sTableName, $iMetadataId, $iGameId)
	Return _SQLite_Exec(-1, 'DELETE FROM metadata_mapping WHERE type=='&sanitize($sTableName)&' AND metadata_id=='&$iMetadataId&' AND game_id=='&$iGameId&'; ') == $SQLITE_OK
EndFunc   ;==>Database_RemoveMetadataMap

Func Database_UpdateMappedMetadata($sTableName, $iMetadataId, $sName = -2, $sDescription = -2)
	Local $sUpdateSet = ''
	If $sName <> -1 Then $sUpdateSet &= 'name='&sanitize($sName)&', '
	If $sDescription <> -1 Then $sUpdateSet &= 'description='&sanitize($sDescription)&', '
	Return _SQLite_Exec(-1,	'UPDATE '&$sTableName&' SET '&StringTrimRight($sUpdateSet, 2)&' WHERE id=='&$iMetadataId&'; ') == $SQLITE_OK
EndFunc   ;==>Database_UpdateMappedMetadata

Func Database_DeleteMappedMetadata($sTableName, $iMetadataId)
	Return _SQLite_Exec(-1,	'DELETE FROM '&$sTableName&' WHERE id=='&$iMetadataId&'; ') == $SQLITE_OK
EndFunc   ;==>Database_DeleteMappedMetadata


;--------------------------------------------------------------
; GENERAL
;--------------------------------------------------------------

Func Database_BeginTransaction()
	_SQLite_Exec(-1,	'BEGIN TRANSACTION;')	
EndFunc   ;==>Database_BeginTransaction

Func Database_EndTransaction()
	_SQLite_Exec(-1,	'COMMIT;')	
EndFunc   ;==>Database_EndTransaction

Func sanitize($str)
	If $str = "" Or Not $str Then $Str = "NULL"
	If $str <> "NULL" And Not IsNumber($str) Then $str = '"' & $str & '"'
	Return $str
EndFunc   ;==>sanitize