If Not @compiled Then
	#AutoIt3Wrapper_Change2CUI=y
EndIf

#Include <WinAPI.au3>
#include <SQLite.au3>

#Include <WindowsConstants.au3>
#Include <Constants.au3>

#include <GuiConstantsEx.au3>
#include <GuiImageList.au3>
#include <GuiListView.au3>
#Include <GuiMenu.au3>
#Include <GuiStatusBar.au3>
#Include <GuiTreeView.au3>

#include <Array.au3>
#include <Misc.au3>

#include "GUIFrame.au3"

;--------------------------------------------------------------
; CONSTANTS
;--------------------------------------------------------------

; VERSION
Global Const $sVersion = "0.1"
Global Const $sAboutMsg = "Version: " & $sVersion & @CRLF & @CRLF & _
					"Created by Francisco Iturrieta. Various code attributed to:" & @CRLF & _
					"- Larsj" & @CRLF & _
					"- pixelsearch" & @CRLF & _
					"- PaulIA" & @CRLF & @CRLF & _
					"- Melba23" & @CRLF & @CRLF & _
					"- Various AutoIT forum threads" & @CRLF & @CRLF & _
					"https://github.com/Lazin3ss/GreenLauncher"

Global Const $tagNMLVCACHEHINT = $tagNMHDR & ";int iFrom;int iTo"

;--------------------------------------------------------------
; GLOBAL VARIABLES
;--------------------------------------------------------------

; Forms
Global $mainForm, $editGameForm

; Handlers for game table data.
Global $idList, $hList, $hImage, $idSelectedItem, $B_DESCENDING
Global $aGameTableCache, $iGameTableCacheRows, $iGameTableCacheCols
Global $tText = DllStructCreate( "wchar[50]" )
Global $pText = DllStructGetPtr( $tText )
Global $iFrom = -1, $iTo = -1
Global $sCurrentQuery = "SELECT * FROM main.games"
Global $iTotalRows

; Handlers for tree view
Global $hTreeView, $bTreeViewClicked = false

; Context Menu
Global $idContextDummy, $hContextMenu

; Status Bar
Global $hStatusBar

;--------------------------------------------------------------
; MAIN OPERATIONS
;--------------------------------------------------------------


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

_SQLite_Open ("GameLibrary.db")
; Create metadata tables
_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS icons(icon_id INTEGER PRIMARY KEY ASC UNIQUE, path TEXT, unique (path));" & _ 
					"CREATE TABLE IF NOT EXISTS years(year INTEGER PRIMARY KEY ASC UNIQUE, gameCount INTEGER);" & _
					"CREATE TABLE IF NOT EXISTS developers(dev_id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL);" & _
					"CREATE TABLE IF NOT EXISTS publishers(publ_id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL);" & _
					"CREATE TABLE IF NOT EXISTS genres(genre_id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL);" & _
					"CREATE TABLE IF NOT EXISTS categories(category_id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL);" & _
					"CREATE TABLE IF NOT EXISTS tools(tool_id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, exePath TEXT NOT NULL, iconId INTEGER);")
; Create mapping tables for multiple metadata values
_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS developers_mapping(game_id INTEGER, dev_id INTEGER);" & _
					"CREATE TABLE IF NOT EXISTS publishers_mapping(game_id INTEGER, publ_id INTEGER);" & _
					"CREATE TABLE IF NOT EXISTS genres_mapping(game_id INTEGER, genre_id INTEGER);" & _
					"CREATE TABLE IF NOT EXISTS categories_mapping(game_id INTEGER, genre_id INTEGER);" & _
					"CREATE TABLE IF NOT EXISTS tools_mapping(game_id INTEGER, tool_id INTEGER);" & _
					"CREATE TABLE IF NOT EXISTS categories_mapping(game_id INTEGER, genre_id INTEGER);")
; Create games table
_SQLite_Exec(-1, 	"CREATE TABLE IF NOT EXISTS main.games(game_id INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, exePath TEXT NOT NULL, iconId INTEGER, year INTEGER, favorite INTEGER, " & _
					"FOREIGN KEY(iconId) REFERENCES icons(icon_id), FOREIGN KEY(year) REFERENCES years(year));")
RefreshGameList()

; Run Main window
MainForm()

; Exit the program
_GUIFrame_Exit()
_SQLite_Close ()
_SQLite_Shutdown ()
Exit


;--------------------------------------------------------------
; FORM 1: MAIN WINDOW
;--------------------------------------------------------------


Func MainForm()
	; Create the Window
	$mainForm = GUICreate("Green Launcher", 600, 400, -1, -1, $WS_OVERLAPPEDWINDOW)
	GUISetIcon(@ScriptDir & "\icon.ico", 0)
	
	; Create Menus
	Local $filemenu = GUICtrlCreateMenu("File")
	Local $addgameitem = GUICtrlCreateMenuItem("Add Game", $filemenu)
	Local $launchitem = GUICtrlCreateMenuItem("Launch Game", $filemenu)
	Local $exititem = GUICtrlCreateMenuItem("Exit", $filemenu)
	Local $helpmenu = GUICtrlCreateMenu("Help")
	Local $aboutitem = GUICtrlCreateMenuItem("About Green Launcher...", $helpmenu)
	
	; Create Status Bar
	$hStatusBar = _GUICtrlStatusBar_Create($mainForm, -1, "Ready.", $SBARS_SIZEGRIP)
	
	; Set filters/game list view frame divisor
	$iFrame_A = _GUIFrame_Create($mainForm, 0, 150, 5, 0, 0, 0, 0)
	_GUIFrame_SetMin($iFrame_A, 100, 100)
	_GUIFrame_Switch($iFrame_A, 2)
	
	; Create Game List View
	$idList = GUICtrlCreateListView("Name|Year|Developer|Publisher", 0, 0, 444, 357, BitOR($LVS_REPORT, $LVS_OWNERDATA), BitOR($LVS_EX_FULLROWSELECT, $LVS_EX_DOUBLEBUFFER))
	$hList = GUICtrlGetHandle($idList)
	$hImage = _GUIImageList_Create(16, 16, 6, 3)
	ImageListFill($hImage)
	_GUICtrlListView_SetImageList($hList, $hImage, 1)
	_GUICtrlListView_RegisterSortCallBack($hList)
	
	; TEST
	AddGame("Warcraft III - Frozen Throne", "C:\Users\Laziness\Downloads\Warcraft III\Frozen Throne.exe", -1, 2003)
	
	; Create Context menu
	$idContextDummy = GUICtrlCreateDummy()
	Local $idContextMenu = GUICtrlCreateContextMenu($idContextDummy)
	Local $idLaunchGame = GUICtrlCreateMenuItem("Launch Game", $idContextMenu)
	Local $idEditGame = GUICtrlCreateMenuItem("Edit Game", $idContextMenu)
	Local $idDeleteGame = GUICtrlCreateMenuItem("Delete Game", $idContextMenu)
	$hContextMenu = GuiCtrlGetHandle($idContextMenu)
	
	_GUIFrame_Switch($iFrame_A, 1)
	$hTreeView = _GUICtrlTreeView_Create(_GUIFrame_GetHandle($iFrame_A, 1), 0, 0, 600, 400)
	Local $hTreeAllGames = _GUICtrlTreeView_Add($hTreeView, 0, "All Games")
	Local $hTreeYear = _GUICtrlTreeView_Add($hTreeView, 0, "Year")
	Local $aResult, $iRows, $iCols
	_SQLite_GetTable2d(-1, "SELECT * FROM years", $aResult, $iRows, $iCols)
	For $i = 0 to $iRows - 1
		_GUICtrlTreeView_AddChild($hTreeView, $hTreeYear, $aResult[$i+1][0])
	Next
	
	Local $hTreeDeveloper = _GUICtrlTreeView_Add($hTreeView, 0, "Developer")
	Local $hTreePublisher = _GUICtrlTreeView_Add($hTreeView, 0, "Publisher")
	
	_GUIFrame_ResizeSet(0)
	
	; GUI Message Loop
	GUIRegisterMsg($WM_NOTIFY, "WM_NOTIFY")
	GUIRegisterMsg($WM_SIZE, "RESIZECONTROLS")
	RefreshGameList()
	GUISetState(@SW_SHOW, $mainForm)
	While 1
		Switch GUIGetMsg()
		Case $hList
			_GUICtrlListView_SortItems($hList, GUICtrlGetState($hList))
		Case $addgameitem
			EditGameForm(-1)
		Case $idContextDummy
			Local $iMenu_Choice = _TrackPopupMenu($hContextMenu, $mainForm, MouseGetPos(0), MouseGetPos(1))
			If $iMenu_Choice Then
				Switch $iMenu_Choice
				Case $idLaunchGame
					RunGame($idSelectedItem)
				Case $idEditGame
					EditGameForm($idSelectedItem)
				Case $idDeleteGame
					DeleteGame($idSelectedItem)
				EndSwitch
			EndIf
		Case $aboutitem
			MsgBox(0, "About Green Launcher", $sAboutMsg)
		Case $GUI_EVENT_CLOSE, $exititem
			ExitLoop
		EndSwitch
		If $bTreeViewClicked Then
			$bTreeViewClicked = false
			$hSelection = _GUICtrlTreeView_GetSelection($hTreeView)
			$sSelectionItemText = _GUICtrlTreeView_GetText($hTreeView, $hSelection)
			If $sSelectionItemText == "All Games" Then
				RefreshGameList()
			ElseIf _GUICtrlTreeView_IsParent($hTreeView, $hTreeYear, $hSelection) Then
				RefreshGameList("WHERE year=" & $sSelectionItemText, "WHERE year=" & $sSelectionItemText)
			EndIf
;~ 			If _GUICtrlTreeView_GetChildCount($hTreeView, $hSelection) = -1 Then
;~ 				ConsoleWrite($sSelectionItemText)
;~ 				If _GUICtrlTreeView_GetText($hTreeView, _GUICtrlTreeView_GetParentHandle($hSelection)) = "Year" Then
;~ 					FillListViewFromQuery($idList, "SELECT * FROM main.games WHERE year=" & $sSelectedItemText & ";");
;~ 				ElseIf $sSelectionItemText = "All Games" Then
;~ 					
;~ 				EndIf
;~ 			EndIf
		EndIf
	WEnd
EndFunc   ;==>MainForm


;--------------------------------------------------------------
; FORM 2: ADD/EDIT GAME WINDOW
;--------------------------------------------------------------


Func EditGameForm($gameId)
	_GUICtrlStatusBar_SetText($hStatusBar, _Iif($gameId > -1, "Editing " & $aGameTable[$gameId+1][1] & "...", "Adding game..."))
	GUISetState(@SW_DISABLE, $mainForm)
	; Create the Window
	$editGameForm = GUICreate(_Iif($gameId > -1, "Edit Game", "Add Game"),  300, 350, -1, -1, -1, -1, $mainForm)
	
	; Build form
	GUICtrlCreateLabel("Name", 20, 20)
	$sName = GUICtrlCreateInput(_Iif($gameId > -1, $aGameTable[$gameId+1][1], ""), 20, 40, 260)
	GUICtrlCreateLabel("Path to Executable", 20, 70)
	$sExePath = GUICtrlCreateInput(_Iif($gameId > -1, $aGameTable[$gameId+1][2], ""), 20, 90, 260)
	GUICtrlCreateLabel("Path to Icon (Optional)", 20, 120)
	$sIconPath = GUICtrlCreateInput(_Iif($gameId > -1, $aGameTable[$gameId+1][3], ""), 20, 140, 260)
	GUICtrlCreateLabel("Year", 20, 170)
	$sYear = GUICtrlCreateInput(_Iif($gameId > -1, $aGameTable[$gameId+1][4], ""), 20, 190, 260)
	GUICtrlCreateLabel("Developer", 20, 220)
	$sDeveloper = GUICtrlCreateInput(_Iif($gameId > -1, $aGameTable[$gameId+1][5], ""), 20, 240, 260)
	GUICtrlCreateLabel("Publisher", 20, 270)
	$sPublisher = GUICtrlCreateInput(_Iif($gameId > -1, $aGameTable[$gameId+1][6], ""), 20, 290, 260)
	
	$hFinishButton = GUICtrlCreateButton(_Iif($gameId > -1, "Save Changes", "Add Game!"), 130, 320)
	
	; GUI Message Loop
	GUISetState()
	While 1
		Switch GUIGetMsg()
		Case $hFinishButton
			if $gameId > -1 Then
				UpdateGameInDatabase($aGameTable[$gameId+1][0], GUICtrlRead($sName), GUICtrlRead($sExePath), GUICtrlRead($sIconPath), GUICtrlRead($sYear), GUICtrlRead($sDeveloper), GUICtrlRead($sPublisher))
			Else
				AddGameToDatabase(GUICtrlRead($sName), GUICtrlRead($sExePath), GUICtrlRead($sIconPath), GUICtrlRead($sYear), GUICtrlRead($sDeveloper), GUICtrlRead($sPublisher))
			EndIf
			_GUICtrlStatusBar_SetText($hStatusBar, "Done!")
			ExitLoop
		Case $GUI_EVENT_CLOSE
			_GUICtrlStatusBar_SetText($hStatusBar, "Operation canceled.")
			ExitLoop
		EndSwitch
	WEnd
	GUISetState(@SW_ENABLE, $mainForm)
	GUIDelete($editGameForm)
EndFunc   ;==>EditGameForm


;--------------------------------------------------------------
; DATABASE METHODS
;--------------------------------------------------------------


; GAMES TABLE METHODS

Func Database_InsertGame($Name, $ExePath, $IconId = "NULL", $YearId = "NULL", $Favorite = 0)
	Return _SQLite_Exec(-1, 	'INSERT INTO main.games VALUES (NULL, ' & _ 
						sanitize($Name) & ', ' & _
						sanitize($ExePath) & ', ' & _
						sanitize($IconId) & ', ' & _
						sanitize($YearId) & ', ' & _
						sanitize($Favorite) & ')') == $SQLITE_OK
;~ 	Local $aRow
;~ 	_SQLite_QuerySingleRow(-1, 'SELECT MAX(game_id) FROM main.games', $aRow)
;~ 	Return $aRow
EndFunc   ;==>Database_InsertGame

Func Database_UpdateGame($GameId, $Name = -1, $ExePath = -1, $IconId = -1, $YearId = -1, $Favorite = -1)
	Local $sSQL = 'UPDATE main.games SET '
	If $Name <> -1 Then $sSQL = $sQL & 'name=' & sanitize($Name) & ', '
	If $ExePath <> -1 Then $sSQL = $sQL & 'exePath=' & sanitize($ExePath) & ', '
	If $IconId <> -1 Then $sSQL = $sQL & 'iconId=' & sanitize($IconId) & ', '
	If $YearId <> -1 Then $sSQL = $sQL & 'yearId=' & sanitize($YearId) & ', '
	If $Favorite <> -1 Then $sSQL = $sQL & 'favorite=' & sanitize($Favorite) & ', '
	Return _SQLite_Exec(-1, StringTrimRight($sSQL, 2) & ' WHERE game_id=' & $GameId) == $SQLITE_OK
EndFunc   ;==>Database_UpdateGame

Func Database_DeleteGame($GameId)
	Return _SQLite_Exec(-1, 'DELETE FROM main.games WHERE game_id=' & $GameId) == $SQLITE_OK
EndFunc   ;==>Database_DeleteGame

; ICONS TABLE METHODS

Func Database_InsertIcon($iconPath, ByRef $IconId)
	Local $aRow, $added = 0
	; Check if the icon already exists
	_SQLite_QuerySingleRow(-1, 'SELECT icon_id FROM icons WHERE path=' & sanitize($iconPath), $aRow)
	If $aRow[0] == "" Then
		; It doesn't exist, so we add it to the table
		$added = _SQLite_Exec(-1, 'INSERT INTO icons VALUES(NULL, ' & sanitize($iconPath) & ')') == $SQLITE_OK
		_SQLite_QuerySingleRow(-1, 'SELECT MAX(icon_id) FROM icons', $aRow)
	EndIf
	$IconId = Number($aRow[0])
	Return $added
EndFunc   ;==>Database_InsertIcon

Func Database_UpdateIcon($iconId, $iconPath = -1)
	Local $sSQL = 'UPDATE icons SET '
	If $iconPath <> -1 Then $sSQL = $sSQL & 'path=' & sanitize($iconPath)
	Return _SQLite_Exec(-1, $sSQL & ' WHERE icon_id=' & $iconId) == $SQLITE_OK
EndFunc   ;==>Database_UpdateIcon

Func Database_DeleteIcon($iconId)
	Return _SQLite_Exec(-1, 'DELETE FROM icons WHERE icon_id=' & $iconId) == $SQLITE_OK
EndFunc   ;==>Database_DeleteIcon

; YEARS TABLE METHODS

Func Database_InsertYear($Year)
	Return _SQLite_Exec(-1, 'INSERT INTO years VALUES(' & sanitize($Year) & ', 1)') == $SQLITE_OK
EndFunc   ;==>Database_InsertYear

Func Database_SelectYearField($Year, $sField)
	Local $aRow
	_SQLite_QuerySingleRow(-1, 'SELECT ' & $sField & ' FROM years WHERE year=' & sanitize($year), $aRow)
	Return Number($aRow[0])
EndFunc  ;==>Database_UpdateYear

; Mostly update Game Count
Func Database_UpdateYear($Year, $GameCount = -1)
	Local $sSQL = 'UPDATE years SET '
	If $GameCount <> -1 Then $sSQL = $sSQL & 'gameCount=' & sanitize($GameCount)
	Return _SQLite_Exec(-1, $sSQL & ' WHERE year=' & $Year) == $SQLITE_OK
EndFunc  ;==>Database_UpdateYear

; We shouldn't delete a year from the database, but the method is there anyway
Func Database_DeleteYear($Year)
	Return _SQLite_Exec(-1, 'DELETE FROM years WHERE year=' & $Year) == $SQLITE_OK
EndFunc  ;==>Database_DeleteYear

Func sanitize($str)
	If $str = "" Or Not $str Then $Str = "NULL"
	If $str <> "NULL" And Not IsNumber($str) Then $str = '"' & $str & '"'
	Return $str
EndFunc   ;==>sanitize


;--------------------------------------------------------------
; LIST VIEW AND TREE VIEW METHODS
;--------------------------------------------------------------

Func AddGame($Name, $ExePath, $IconPath = -1, $Year = -1, $Developer = -1, $Publisher = -1, $Genre = -1, $Category = -1)
	If $IconPath == -1 Then $IconPath = $ExePath
	Local $iconid
	If Database_InsertIcon($IconPath, $iconid) Then 
		_GUIImageList_AddIconEx($hImage, $IconPath, 0, $iconid) ; This should probably be moved to a ImageList handling function
	EndIf
	If Not Database_InsertYear($Year) Then
		$gameCount = Database_SelectYearField($Year, "gameCount")
		Database_UpdateYear($Year, $gameCount + 1)
	EndIf
	Database_InsertGame($Name, $ExePath, $iconid, $Year, 1)
EndFunc


Func RunGame($gameTableIndex)
	$sLaunchingTitle = "Launching " & $aGameTable[$gameTableIndex+1][1] & "..."
	_GuiCtrlStatusBar_SetText($hStatusBar, $sLaunchingTitle)
	$sGamePath = $aGameTable[$gameTableIndex+1][2]
	RunWait($sGamePath, StringRegExpReplace($sGamePath, "\\(?:.(?!\\))+$", ""))
	_GuiCtrlStatusBar_SetText($hStatusBar, "Ready.")
EndFunc   ;==>RunGame

Func ImageListFill($hImage)
	Local $aResult, $iRows, $iCols
	_SQLite_GetTable2d(-1, 'SELECT * FROM icons', $aResult, $iRows, $iCols)
	_GUIImageList_SetImageCount($hImage, $iRows)
	For $i = 0 to $iRows - 1
		_GUIImageList_AddIconEx($hImage, $aResult[$i+1][1], 0, Number($aResult[$i+1][0])-1)
	Next
	$aResult = 0
EndFunc

Func RefreshGameList($newQuery = "", $newCountQuery = "")
	If $newQuery <> -1 Then
		$sCurrentQuery = "SELECT * FROM main.games "& $newQuery
	EndIf
	Local $aRow
	_SQLite_QuerySingleRow( -1, "SELECT COUNT(1) FROM main.games " & $newCountQuery, $aRow )
	If IsArray( $aRow ) Then $iTotalRows = Number($aRow[0])
	GUICtrlSendMsg( $idList, $LVM_SETITEMCOUNT, $iTotalRows, 0 )
	_GUICtrlListView_SetColumnWidth($hList, 0, $LVSCW_AUTOSIZE)
EndFunc
  
; EVENT HANDLER
Func WM_NOTIFY($hWnd, $iMsg, $iwParam, $ilParam)
    #forceref $hWnd, $iMsg, $iwParam
	
    Local $hWndFrom, $iIDFrom, $iCode, $tNMHDR, $tInfo

    $tNMHDR = DllStructCreate($tagNMHDR, $ilParam)
    $hWndFrom = HWnd(DllStructGetData($tNMHDR, "hWndFrom"))
    $iIDFrom = DllStructGetData($tNMHDR, "IDFrom")
    $iCode = DllStructGetData($tNMHDR, "Code")
    Switch $hWndFrom
	Case $hList
        Switch $iCode
		Case $LVN_ODCACHEHINT
			Local $tNMLVCACHEHINT = DllStructCreate( $tagNMLVCACHEHINT, $ilParam )
			$iFrom = DllStructGetData( $tNMLVCACHEHINT, "iFrom" )
			$iTo = DllStructGetData( $tNMLVCACHEHINT, "iTo" )
			Local $sSQL = $sCurrentQuery & " LIMIT " & _GUICtrlListView_GetCounterPage($hList) + 1 & " OFFSET " & $iFrom
			_SQLite_GetTable2d(-1, $sSQL, $aGameTableCache, $iGameTableCacheRows, $iGameTableCacheCols)
		Case $LVN_GETDISPINFOW
			Local $tNMLVDISPINFO = DllStructCreate( $tagNMLVDISPINFO, $ilParam )
			If BitAND( DllStructGetData( $tNMLVDISPINFO, "Mask" ), $LVIF_TEXT ) Then
				Local $iIndex = DllStructGetData( $tNMLVDISPINFO, "Item" ) - $iFrom + 1
				If $iIndex > 0 And $iIndex < $iGameTableCacheRows + 1 Then
					Switch DllStructGetData($tNMLVDISPINFO,"SubItem")
					Case 0 ; Name
						$sItem = $aGameTableCache[$iIndex][1]
						DllStructSetData($tNMLVDISPINFO, "Image", Number($aGameTableCache[$iIndex][3])-1)
					Case 1 ; Year
						$sItem = $aGameTableCache[$iIndex][4]
					Case 2 ; Developer
						$sItem = "" ; $aGameTableCache[$iIndex][5]
					Case 3 ; Publisher
						$sItem = "" ; $aGameTableCache[$iIndex][6]
					EndSwitch
					DllStructSetData( $tText, 1, $sItem )
					DllStructSetData( $tNMLVDISPINFO, "Text", $pText )
					DllStructSetData( $tNMLVDISPINFO, "TextMax", StringLen( $sItem ) )
				EndIf
			EndIf
		Case $LVN_COLUMNCLICK
			$tInfo = DllStructCreate($tagNMLISTVIEW, $ilParam)
			ConsoleWrite(DllStructGetData($tInfo, "SubItem") & @CRLF)
			_GUICtrlListView_SortItems($hWndFrom, DllStructGetData($tInfo, "SubItem"))
		; Run the GAME, Damnit!
		Case $NM_DBLCLK
			$tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
			$idSelectedItem = DllStructGetData($tInfo, "Index")
			RunGame($idSelectedItem)
		; Contextual Menu
		Case $NM_RCLICK ; Sent by a list-view control when the user clicks an item with the right mouse button
			$tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
			If Not @compiled Then
				_DebugPrint("$NM_RCLICK" & @LF & "--> hWndFrom:" & @TAB & $hWndFrom & @LF & _
						"-->IDFrom:" & @TAB & $iIDFrom & @LF & _
						"-->Code:" & @TAB & $iCode & @LF & _
						"-->Index:" & @TAB & DllStructGetData($tInfo, "Index") & @LF & _
						"-->SubItem:" & @TAB & DllStructGetData($tInfo, "SubItem") & @LF & _
						"-->NewState:" & @TAB & DllStructGetData($tInfo, "NewState") & @LF & _
						"-->OldState:" & @TAB & DllStructGetData($tInfo, "OldState") & @LF & _
						"-->Changed:" & @TAB & DllStructGetData($tInfo, "Changed") & @LF & _
						"-->ActionX:" & @TAB & DllStructGetData($tInfo, "ActionX") & @LF & _
						"-->ActionY:" & @TAB & DllStructGetData($tInfo, "ActionY") & @LF & _
						"-->lParam:" & @TAB & DllStructGetData($tInfo, "lParam") & @LF & _
						"-->KeyFlags:" & @TAB & DllStructGetData($tInfo, "KeyFlags"))
			EndIf
			$idSelectedItem = DllStructGetData($tInfo, "Index")
			If $idSelectedItem > -1 Then ; valid row
				GUICtrlSendToDummy($idContextDummy)
			EndIf
		EndSwitch
	Case $hTreeView
		Switch $iCode
		Case $NM_CLICK
			$bTreeViewClicked = true
		EndSwitch
    EndSwitch
    Return $GUI_RUNDEFMSG
EndFunc   ;==>WM_NOTIFY

Func RESIZECONTROLS($hWnd, $iMsg, $wParam, $lParam)
	#forceref $iMsg, $wParam, $lParam
	; Resize Frames
	_GUIFrame_SIZE_Handler($hWnd, $iMsg, $wParam, $lParam)
	; Resize Status Bar
	_GUICtrlStatusBar_Resize($hStatusBar)
    Return $GUI_RUNDEFMSG
EndFunc   ;==>RESIZECONTROLS

Func _TrackPopupMenu($hMenu, $hWnd, $iX, $iY)
    ; $TPM_RETURNCMD returns the menu item identifier of the user's selection in the return value.
    Local $result = DllCall("user32.dll", "int", "TrackPopupMenuEx", "hwnd", $hMenu, "int", $TPM_RETURNCMD, "int", $iX, "int", $iY, "hwnd", $hWnd, "ptr", 0)
	If UBound($result) > 0 Then
		Return $result[0]
	Else
		Return -1
	EndIf
EndFunc   ;==>_TrackPopupMenu

Func _DebugPrint($s_text, $line = @ScriptLineNumber)
    ConsoleWrite( _
            "!===========================================================" & @LF & _
            "+======================================================" & @LF & _
            "-->Line(" & StringFormat("%04d", $line) & "):" & @TAB & $s_text & @LF & _
            "+======================================================" & @LF)
EndFunc   ;==>_DebugPrint
		
Func _SQLite_GetTableEx( $hDB, $sSQL, ByRef $pTable, ByRef $iRows, ByRef $iCols )
  If Not __SQLite_hChk($hDB, $SQLITE_DBHANDLE) = $SQLITE_OK Then Return SetError(3, 0, $SQLITE_MISUSE)
  If @error Then Return SetError(3, @error, 0)
  Local $avRval = DllCall($g_hDll_SQLite, "int:cdecl", "sqlite3_get_table", _
    "ptr", $hDB, _       ; An open database
    "str", $sSQL, _      ; SQL to be executed
    "long*", 0, _         ; Results of the query
    "long*", 0, _         ; Number of result rows
    "long*", 0, _         ; Number of result columns
    "long*", 0)          ; Error msg written here
  If @error Then Return SetError(1, @error, $SQLITE_MISUSE) ; DllCall error
  $pTable = $avRval[3]
  $iRows = $avRval[4]
  $iCols = $avRval[5]
EndFunc

Func _SQLite_FreeTable( $pTable )
  DllCall($g_hDll_SQLite, "int:cdecl", "sqlite3_free_table", "ptr", $pTable)
  If @error Then Return SetError(1, @error, $SQLITE_MISUSE) ; DllCall error
EndFunc
  
; #FUNCTION# ====================================================================================================================
; Name...........: _GUIImageList_AddIconEx
; Description ...: Adds an icon to an image list
; Syntax.........: _GUIImageList_AddIconEx($hWnd, $sFile[, $iIndex=0[, $fLarge = False])
; Parameters ....: $hWnd        - Handle to the control
;                  $sFile       - Path to the icon that contains the image
;                  $iIndex      - Specifies the zero-based index of the icon to extract
;                  $fLarge      - Extract Large Icon
; Return values .: Success      - The index of the image
;                  Failrue      - -1
; Author ........: Paul Campbell (PaulIA)
; Modified.......: Francisco Iturrieta (Laziness)
; Remarks .......:
; Related .......: _GUIImageList_Add, _GUIImageList_AddBitmap
; Link ..........;
; Example .......; Yes
; ===============================================================================================================================
Func _GUIImageList_AddIconEx($hWnd, $sFile, $iIndex = 0, $iPos = -1, $fLarge = False)
	Local $tIcon, $iResult, $hIcon

	$tIcon = DllStructCreate("int Handle")
	If $fLarge Then
		$iResult = _WinAPI_ExtractIconEx($sFile, $iIndex, DllStructGetPtr($tIcon), 0, 1)
	Else
		$iResult = _WinAPI_ExtractIconEx($sFile, $iIndex, 0, DllStructGetPtr($tIcon), 1)
	EndIf
	
	If $iResult <= 0 Then
		If $fLarge Then
		$iResult = _WinAPI_ExtractIconEx(@SystemDir & "\shell32.dll", 2, DllStructGetPtr($tIcon), 0, 1)
		Else
			$iResult = _WinAPI_ExtractIconEx(@SystemDir & "\shell32.dll", 2, 0, DllStructGetPtr($tIcon), 1)
		EndIf
	EndIf
	_WinAPI_Check("_GUIImageList_AddIcon", ($iResult <= 0), -1)

	$hIcon = DllStructGetData($tIcon, "Handle")
	$iResult = _GUIImageList_ReplaceIcon($hWnd, $iPos, $hIcon)
	If $iResult == -1 Then
		$iResult = _GUIImageList_ReplaceIcon($hWnd, -1, $hIcon)
	EndIf
	_WinAPI_Check("_GUIImageList_AddIcon", ($iResult = -1), -2)
	_WinAPI_DestroyIcon($hIcon)
	Return $iResult
EndFunc   ;==>_GUIImageList_AddIconEx