If Not @compiled Then
	#AutoIt3Wrapper_Change2CUI=y
EndIf

#Include <WinAPI.au3>
#include <SQLite.au3>
#include <SQLite.dll.au3>

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
					"Created by Francisco Iturrieta. Some code attributed to:" & @CRLF & _
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
Global $aGameTableCache, $iGameTableCacheRows, $iGameTableCacheCols, $iTotalRows
Global $tText = DllStructCreate( "wchar[50]" )
Global $pText = DllStructGetPtr( $tText )
Global $iFrom = -1, $iTo = -1
Global $sAllGamesQuery = "SELECT * FROM main.games"
Global $sGamesCountQuery = "SELECT COUNT(1) FROM main.games"
Global $sLastQuery = $sAllGamesQuery
Global $displaying = false

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
_SQLite_Startup ()
If @error > 0 Then
    MsgBox(16, "SQLite Error", "SQLite.dll Can't be Loaded!")
    Exit - 1
EndIf

_SQLite_Open ("GameLibrary.db")
_SQLite_Exec(-1, "CREATE TABLE IF NOT EXISTS main.games(rowid INTEGER PRIMARY KEY ASC, name TEXT NOT NULL, exePath TEXT NOT NULL, iconPath TEXT, year INTEGER, developer TEXT, publisher TEXT);")
Local $aRow
_SQLite_QuerySingleRow( -1, $sGamesCountQuery, $aRow )
If IsArray( $aRow ) Then $iTotalRows = $aRow[0]

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
	
	$iFrame_A = _GUIFrame_Create($mainForm, 0, 150, 5, 0, 0, 0, 0)
	_GUIFrame_SetMin($iFrame_A, 100, 100)
	_GUIFrame_Switch($iFrame_A, 2)
	
	; Create Game List View
	$idList = GUICtrlCreateListView("Name|Year|Developer|Publisher", 0, 0, 444, 357, BitOR($LVS_REPORT, $LVS_OWNERDATA), BitOR($LVS_EX_FULLROWSELECT, $LVS_EX_DOUBLEBUFFER))
	$hList = GUICtrlGetHandle($idList)
	$hImage = _GUIImageList_Create(16, 16, 6, 3)
	_GUICtrlListView_SetImageList($hList, $hImage, 1)
	_GUICtrlListView_RegisterSortCallBack($hList)
	
;~ 	FillListViewFromQuery($idList, $sLastQuery)
	
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
	Local $hTreeDeveloper = _GUICtrlTreeView_Add($hTreeView, 0, "Developer")
	Local $hTreePublisher = _GUICtrlTreeView_Add($hTreeView, 0, "Publisher")
	
	Local $hYear2016 = _GUICtrlTreeView_AddChild($hTreeView, $hTreeYear, "2016")
	
	_GUIFrame_ResizeSet(0)
	
	; GUI Message Loop
	GUIRegisterMsg($WM_NOTIFY, "WM_NOTIFY")
	GUIRegisterMsg($WM_SIZE, "RESIZECONTROLS")
	GUICtrlSendMsg( $idList, $LVM_SETITEMCOUNT, Number($iTotalRows), 0 )
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
				$sLastQuery = $sAllGamesQuery
				_SQLite_QuerySingleRow( -1, $sGamesCountQuery, $aRow )
				If IsArray( $aRow ) Then $iTotalRows = $aRow[0]
				GUICtrlSendMsg( $idList, $LVM_SETITEMCOUNT, Number($iTotalRows), 0 )
			ElseIf _GUICtrlTreeView_IsParent($hTreeView, $hTreeYear, $hSelection) Then
				$sLastQuery = $sAllGamesQuery & " WHERE year=" & $sSelectionItemText
				_SQLite_QuerySingleRow( -1, $sGamesCountQuery & " WHERE year=" & $sSelectionItemText, $aRow )
				If IsArray( $aRow ) Then $iTotalRows = $aRow[0]
				GUICtrlSendMsg( $idList, $LVM_SETITEMCOUNT, Number($iTotalRows), 0 )
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
; FUNCTIONS AND HANDLERS
;--------------------------------------------------------------


Func AddGameToDatabase($Name, $ExePath, $IconPath = "NULL", $Year = "NULL", $Developer = "NULL", $Publisher = "NULL")
	_SQLite_Exec(-1, 'INSERT INTO main.games VALUES (NULL, ' & sanitize($Name) & ', ' & sanitize($ExePath) & ', ' & sanitize($IconPath) & ', ' & sanitize($Year) & ', ' & sanitize($Developer) & ', ' & sanitize($Publisher) & ');')
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>AddGameToDatabase

Func UpdateGameInDatabase($RowId, $Name, $ExePath, $IconPath = "NULL", $Year = "NULL", $Developer = "NULL", $Publisher = "NULL")
	_SQLite_Exec(-1, 'UPDATE main.games SET name=' & sanitize($Name) & ', exePath=' & sanitize($ExePath) & ', iconPath=' & sanitize($IconPath) & ', year=' & sanitize($Year) & ', developer=' & sanitize($Developer) & ', publisher=' & sanitize($Publisher) & ' WHERE rowid=' & $RowId & ';')
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>UpdateGameInDatabase

Func RunGame($gameTableIndex)
	$sLaunchingTitle = "Launching " & $aGameTable[$gameTableIndex+1][1] & "..."
	_GuiCtrlStatusBar_SetText($hStatusBar, $sLaunchingTitle)
	$sGamePath = $aGameTable[$gameTableIndex+1][2]
	RunWait($sGamePath, StringRegExpReplace($sGamePath, "\\(?:.(?!\\))+$", ""))
	_GuiCtrlStatusBar_SetText($hStatusBar, "Ready.")
EndFunc   ;==>RunGame

Func DeleteGame($gameTableIndex)
	_SQLite_Exec(-1, "DELETE FROM main.games WHERE rowid=" & $aGameTable[$gameTableIndex+1][0] & ";")
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>DeleteGame

Func sanitize($str)
	If $str = "" Or Not $str Then $Str = "NULL"
	If $str <> "NULL" Then $str = '"' & $str & '"'
	Return $str
EndFunc   ;==>sanitize

; TODO: Check if this routine leaks memory in large sessions
Func FillListViewFromQuery($idLV, $sSQL)
	; Remove previous ListView items (this should free memory)
	_GUICtrlListView_DeleteAllItems($hList)
	_GUIImageList_Destroy($hImage)
	; Perform search based on SQL statement
	Local $hQuery, $aNames, $aRow
	_SQLite_Query(-1, $sSQL, $hQuery)
	_SQLite_FetchNames($hQuery, $aNames)
;~ 	_SQLite_GetTableEx(-1, $sSQL, $pGameTable, $iGameTableRows, $iGameTableCols)
;~ 	If $iGameTableCols > 0 And $iGameTableRows > 0 Then
;~ 		Local $struct1, $struct2, $iColCnt, $iRowCnt
;~ 		$iResultSize = (($iGameTableRows) + 1) * ($iGameTableCols)
;~ 		For $i = 1 To $iResultSize - 1
;~ 			$struct1 &= "ptr;"
;~ 		Next
;~ 		$struct1 &= "ptr"
;~ 		$struct2 = DllStructCreate($struct1, $pGameTable)
;~ 		
;~ 		Local $sItemString = "", $sExe = "", $sIcon = "", $sValue = ""
;~ 		
;~ 		$hImage = _GUIImageList_Create(16, 16, 6, 3)
;~ 		_GUICtrlListView_SetImageList($hList, $hImage, 1)
;~ 		
;~ 		Local $tLVITEM = DllStructCreate($tagLVITEM)
;~ 		Local $pLVITEM = DllStructGetPtr($tLVITEM)
;~ 		DllStructSetData($tLVITEM, "Mask", $LVIF_IMAGE) ; Icon (or image)
;~ 		DllStructSetData($tLVITEM, "SubItem", 0)        ; First column
;~ 		
;~ 		For $i = 1 To $iResultSize
;~ 			$sValue = __SQLite_szStringRead(DllStructGetData($struct2, $i), -1)
;~ 			If $iColCnt == 2 Then $sExe = $sValue
;~ 			If $iColCnt == 3 Then $sIcon = $sValue
;~ 			$sItemString += $sValue & "|"
;~ 			$iColCnt += 1
;~ 			If ($i / $iGameTableCols) = Round($i / $iGameTableCols, 0) Then
;~ 				$iRowCnt += 1
;~ 				$iColCnt = 0
;~ 				
;~ 				Local $itemId = GUICtrlCreateListViewItem($sItemString, $idLV)
;~ 				If $sIcon == "" Then
;~ 					; Add icon from executable instead of icon path
;~ 					_GUIImageList_AddIconEx($hImage, $sExe, 0)
;~ 				Else
;~ 					_GUIImageList_AddIconEx($hImage, $sIcon, 0)
;~ 				EndIf
;~ 				DllStructSetData($tLVITEM, "Image", $iRowCnt-1)
;~ 				DllStructSetData($tLVITEM, "Item", $iRowCnt-1) ; Row
;~ 				GUICtrlSendMsg($idLV, $LVM_SETITEMW, 0, $pLVITEM) ; Add icon
;~ 				$sItemString = ""
;~ 				$sExe = ""
;~ 				$sIcon = ""
;~ 				$sValue = ""
;~ 			EndIf
;~ 		Next
;~ 	EndIf
;~ 	_SQLite_FreeTable($pGameTable)
	
	$hImage = _GUIImageList_Create(16, 16, 6, 3)
	_GUICtrlListView_SetImageList($hList, $hImage, 1)
	Local $tLVITEM = DllStructCreate($tagLVITEM)
	Local $pLVITEM = DllStructGetPtr($tLVITEM)
	DllStructSetData($tLVITEM, "Mask", $LVIF_IMAGE) ; Icon (or image)
	DllStructSetData($tLVITEM, "SubItem", 0)        ; First column
	Local $j = 0
	While _SQLite_FetchData($hQuery, $aRow) == $SQLITE_OK
		; Text
		Local $itemId = GUICtrlCreateListViewItem($aRow[1] & "|" & $aRow[4] & "|" & $aRow[5] & "|" & $aRow[6], $idLV) ; Add item and all texts
		; Icon
		If $aRow[3] == "" Then
			; Add icon from executable instead of icon path
			_GUIImageList_AddIconEx($hImage, $aRow[2], 0)
		Else
			_GUIImageList_AddIconEx($hImage, $aRow[3], 0)
		EndIf
		DllStructSetData($tLVITEM, "Image", $j)
		
		DllStructSetData($tLVITEM, "Item", $j)        ; Row
		GUICtrlSendMsg($idLV, $LVM_SETITEMW, 0, $pLVITEM) ; Add icon
		$j = $j + 1
	WEnd
	_GUICtrlListView_SetColumnWidth($hList, 0, $LVSCW_AUTOSIZE)
	
	$sLastQuery = $sSQL
EndFunc   ;==>FillListViewFromQuery

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
			Local $sSQL = $sLastQuery & " LIMIT " & _GUICtrlListView_GetCounterPage($hList) + 1 & " OFFSET " & $iFrom
			_SQLite_GetTable2d(-1, $sSQL, $aGameTableCache, $iGameTableCacheRows, $iGameTableCacheCols)
		Case $LVN_GETDISPINFOW
			Local $tNMLVDISPINFO = DllStructCreate( $tagNMLVDISPINFO, $ilParam )
			If BitAND( DllStructGetData( $tNMLVDISPINFO, "Mask" ), $LVIF_TEXT ) Then
				Local $iIndex = DllStructGetData( $tNMLVDISPINFO, "Item" ) - $iFrom + 1
				If $iIndex > 0 And $iIndex < $iGameTableCacheRows + 1 Then
					Switch DllStructGetData($tNMLVDISPINFO,"SubItem")
					Case 0
						$sItem = $aGameTableCache[$iIndex][1]
						; NOTE: ICONS SHOULD BE BUFFERED BEFORE UPDATING THE LIST
						If $aGameTableCache[$iIndex][2] == "" Then
							; Add icon from executable instead of icon path
							_GUIImageList_AddIconEx($hImage, $aGameTableCache[$iIndex][1], 0, DllStructGetData( $tNMLVDISPINFO, "Item" ))
						Else
							_GUIImageList_AddIconEx($hImage, $aGameTableCache[$iIndex][2], 0, DllStructGetData( $tNMLVDISPINFO, "Item" ))
						EndIf
						DllStructSetData($tNMLVDISPINFO, "Image", DllStructGetData( $tNMLVDISPINFO, "Item" ))
					Case 1
						$sItem = $aGameTableCache[$iIndex][4]
					Case 2
						$sItem = $aGameTableCache[$iIndex][5]
					Case 3
						$sItem = $aGameTableCache[$iIndex][6]
					EndSwitch
					DllStructSetData( $tText, 1, $sItem )
					DllStructSetData( $tNMLVDISPINFO, "Text", $pText )
					DllStructSetData( $tNMLVDISPINFO, "TextMax", StringLen( $sItem ) )
				EndIf
			EndIf
		Case $LVN_COLUMNCLICK
			$tInfo = DllStructCreate($tagNMLISTVIEW, $ilParam)
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