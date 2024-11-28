If Not @compiled Then
	#AutoIt3Wrapper_Change2CUI=y
EndIf

#Include <WinAPI.au3>

#Include <WindowsConstants.au3>
#Include <Constants.au3>

#include <GuiConstantsEx.au3>
#include <GuiImageList.au3>
#include <GuiListView.au3>
#Include <GuiMenu.au3>
#Include <GuiStatusBar.au3>

#include <Array.au3>
#include <Misc.au3>

#include "database.au3"

;--------------------------------------------------------------
; CONSTANTS
;--------------------------------------------------------------

; VERSION
Global Const $sVersion = "0.2"
Global Const $sWindowTitle = "GreenLauncher " & $sVersion
Global Const $sAboutMsg = "Version: " & $sVersion & @CRLF & @CRLF & _
					"By Francisco Iturrieta (Lazin3ss), with AutoIt 3.2.12.1." & @CRLF & @CRLF & _
					"https://github.com/Lazin3ss/GreenLauncher"
					
;--------------------------------------------------------------
; GLOBAL VARIABLES
;--------------------------------------------------------------

; Forms
Global $mainForm, $editGameForm

; Handlers for game table data.
Global $aGameTable, $iGameTableRows, $iGameTableCols
Global $idList, $hList, $hListIcons
Global $idSelectedItem = -1
Global $sLastQuery = "SELECT * FROM gameList;"

; Context Menu
Global $idContextDummy, $hContextMenu

; Status Bar
Global $hStatusBar

;--------------------------------------------------------------
; MAIN OPERATIONS
;--------------------------------------------------------------

; Initialize SQLite database
_Database_Startup()

; Run Main window
MainForm()

; Exit the program
_Database_Shutdown()

Exit

;--------------------------------------------------------------
; FORM 1: MAIN WINDOW
;--------------------------------------------------------------

Func MainForm()
	; Create the Window
	$mainForm = GUICreate($sWindowTitle, 600, 400, -1, -1, $WS_OVERLAPPEDWINDOW)
	GUISetIcon(@ScriptDir & "\icon.ico", 0)
	
	; Create Status Bar
	Local $vPartEdge[2] = [500, -1]
	Local $vPartText[2] = ["Ready.", "0 Games"]
	$hStatusBar = _GUICtrlStatusBar_Create($mainForm, $vPartEdge, $vPartText, $SBARS_SIZEGRIP)
	
	
	; Create Menus
	Local $filemenu = GUICtrlCreateMenu("File")
	Local $addgameitem = GUICtrlCreateMenuItem("Add Game", $filemenu)
	Local $launchitem = GUICtrlCreateMenuItem("Launch Game", $filemenu)
	Local $exititem = GUICtrlCreateMenuItem("Exit", $filemenu)
	Local $helpmenu = GUICtrlCreateMenu("Help")
	Local $aboutitem = GUICtrlCreateMenuItem("About Green Launcher...", $helpmenu)
	
	
	; Create Game List View
	$idList = GUICtrlCreateListView("Name|Favorite|Year|Developer|Publisher|Genre|Category", 0, 0, 600, 357, $LVS_REPORT, $LVS_EX_FULLROWSELECT)
	$hList = GUICtrlGetHandle($idList)
	GUICtrlSetResizing($idList, $GUI_DOCKBORDERS)
	
	FillListViewFromQuery($idList, $sLastQuery)
	
	; Create Context menu
	$idContextDummy = GUICtrlCreateDummy()
	Local $idContextMenu = GUICtrlCreateContextMenu($idContextDummy)
	Local $idLaunchGame = GUICtrlCreateMenuItem("Launch Game", $idContextMenu)
	Local $idEditGame = GUICtrlCreateMenuItem("Edit Game", $idContextMenu)
	Local $idDeleteGame = GUICtrlCreateMenuItem("Delete Game", $idContextMenu)
	$hContextMenu = GuiCtrlGetHandle($idContextMenu)
	
	; GUI Message Loop
	GUIRegisterMsg($WM_NOTIFY, "WM_NOTIFY")
	GUIRegisterMsg($WM_SIZE, "WM_RESIZECONTROLS")
	GUISetState(@SW_SHOW, $mainForm)
	While 1
		Switch GUIGetMsg()
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
		Case $launchitem
			RunGame($idSelectedItem)
		Case $aboutitem
			MsgBox(0, "About GreenLauncher", $sAboutMsg)
		Case $GUI_EVENT_CLOSE, $exititem
			ExitLoop
		EndSwitch
	WEnd
EndFunc   ;==>MainForm

;--------------------------------------------------------------
; FORM 2: ADD/EDIT GAME WINDOW
;--------------------------------------------------------------

Func EditGameForm($listItemId)
	GUISetState(@SW_DISABLE, $mainForm)
	
	; Set status bar text
	If $listItemId > -1 Then
		_GUICtrlStatusBar_SetText($hStatusBar,"Editing " & $aGameTable[$listItemId][0] & "...", 0)
	Else
		_GUICtrlStatusBar_SetText($hStatusBar,"Adding game...", 0)
	EndIf
	
	; Create the Window
	$editGameForm = GUICreate(_Iif($listItemId > -1, "Edit Game", "Add Game"),  300, 360, -1, -1, -1, -1, $mainForm)
	
	; Build form
	GUICtrlCreateLabel("Name", 20, 20)
	$idName = GUICtrlCreateInput("", 20, 40, 260)
	GUICtrlCreateLabel("Path to Executable", 20, 70)
	$idExePath = GUICtrlCreateInput("", 20, 90, 260)
	GUICtrlCreateLabel("Path to Icon (Optional)", 20, 120)
	$idIconPath = GUICtrlCreateInput("", 20, 140, 260)
	GUICtrlCreateLabel("Year", 20, 170)
	$idYear = GUICtrlCreateInput("", 20, 190, 120)
	GUICtrlCreateLabel("Favorite?", 160, 170)
	$idFavorite = GUICtrlCreateCheckBox("", 160, 190)
	GUICtrlCreateLabel("Developer", 20, 220)
	$idDeveloper = GUICtrlCreateInput("", 20, 240, 120)
	GUICtrlCreateLabel("Publisher", 160, 220)
	$idPublisher = GUICtrlCreateInput("", 160, 240, 120)
	GUICtrlCreateLabel("Genre", 20, 270)
	$idGenre = GUICtrlCreateInput("", 20, 290, 120)
	GUICtrlCreateLabel("Category", 160, 270)
	$idCategory = GUICtrlCreateInput("", 160, 290, 120)
	
	$hFinishButton = GUICtrlCreateButton(_Iif($listItemId > -1, "Save Changes", "Add Game!"), _Iif($listItemId > -1, 113, 121), 330)
	
	; Set edit game data (in case we're editing something)
	If $listItemId > -1 Then
		GUICtrlSetData($idName, $aGameTable[$listItemId][0])
		GUICtrlSetData($idExePath, $aGameTable[$listItemId][7])
		GUICtrlSetData($idIconPath, $aGameTable[$listItemId][8])
		GUICtrlSetData($idYear, $aGameTable[$listItemId][2])
		GUICtrlSetState($idFavorite, _Iif($aGameTable[$listItemId][1] == "No", $GUI_UNCHECKED, $GUI_CHECKED))
		GUICtrlSetData($idDeveloper, StringReplace($aGameTable[$listItemId][3], ", ", ";"))
		GUICtrlSetData($idPublisher, StringReplace($aGameTable[$listItemId][4], ", ", ";"))
		GUICtrlSetData($idGenre, StringReplace($aGameTable[$listItemId][5], ", ", ";"))
		GUICtrlSetData($idCategory, StringReplace($aGameTable[$listItemId][6], ", ", ";"))
	EndIf
	
	; GUI Message Loop
	GUISetState()
	While 1
		Switch GUIGetMsg()
		Case $hFinishButton
			if $listItemId > -1 Then
				UpdateGameInDatabase($listItemId, _ 
					GUICtrlRead($idName), _ 
					GUICtrlRead($idExePath), _ 
					GUICtrlRead($idIconPath), _
					Number(GUICtrlRead($idFavorite) == $GUI_CHECKED), _ 					
					GUICtrlRead($idYear), _ 
					GUICtrlRead($idDeveloper), _ 
					GUICtrlRead($idPublisher), _ 
					GUICtrlRead($idGenre), _ 
					GUICtrlRead($idCategory))
			Else
				AddGameToDatabase(GUICtrlRead($idName), _ 
					GUICtrlRead($idExePath), _ 
					GUICtrlRead($idIconPath), _ 
					Number(GUICtrlRead($idFavorite) == $GUI_CHECKED), _ 
					GUICtrlRead($idYear), _ 
					GUICtrlRead($idDeveloper), _ 
					GUICtrlRead($idPublisher) , _ 
					GUICtrlRead($idGenre), _ 
					GUICtrlRead($idCategory))
			EndIf
			ExitLoop
		Case $GUI_EVENT_CLOSE
			_GUICtrlStatusBar_SetText($hStatusBar, "Canceled operation.", 0)
			ExitLoop
		EndSwitch
	WEnd
	GUISetState(@SW_ENABLE, $mainForm)
	GUIDelete($editGameForm)
EndFunc   ;==>EditGameForm

;--------------------------------------------------------------
; EVENT HANDLERS
;--------------------------------------------------------------

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
				; Get ID of game selected in list
				Case $NM_CLICK
					$tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
					$idSelectedItem = DllStructGetData($tInfo, "Index")
				; Run the GAME, Damnit!
				Case $NM_DBLCLK
                    $tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
					$idSelectedItem = DllStructGetData($tInfo, "Index")
					RunGame($idSelectedItem)
				; Contextual Menu
                Case $NM_RCLICK ; Sent by a list-view control when the user clicks an item with the right mouse button
                    $tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
					$idSelectedItem = DllStructGetData($tInfo, "Index")
					If $idSelectedItem > -1 Then
						GUICtrlSendToDummy($idContextDummy)
					EndIf
            EndSwitch
    EndSwitch
    Return $GUI_RUNDEFMSG
EndFunc   ;==>WM_NOTIFY

Func WM_RESIZECONTROLS($hWnd, $iMsg, $wParam, $lParam)
	#forceref $iMsg, $wParam, $lParam
	; Resize Status Bar
	_GUICtrlStatusBar_Resize($hStatusBar)
	Local $aSize = WinGetPos("Green Launcher")
	If IsArray($aSize) Then
		Local $vPartEdge[2] = [$aSize[2]-120, -1]
		_GUICtrlStatusBar_SetParts($hStatusBar, $vPartEdge)
	EndIf
    Return $GUI_RUNDEFMSG
EndFunc   ;==>WM_RESIZECONTROLS

;--------------------------------------------------------------
; FUNCTIONS
;--------------------------------------------------------------

Func AddGameToDatabase($sName, $sExePath, $sIconPath = "", $iFavorite = 0, $iYear = "", $sDevelopers = "", $sPublishers = "", $sGenres = "", $sCategories = "")
	_Database_BeginTransaction()
	$id = _Database_InsertGame($sName, $sExePath, $sIconPath, $iFavorite, _Iif($iYear == "", -1, Number($iYear)))
	If $sDevelopers <> "" Then
		SetMultipleMetadata($id, "developers", $sDevelopers, ";")
	EndIf
	If $sPublishers <> "" Then
		SetMultipleMetadata($id, "publishers", $sPublishers, ";")
	EndIf
	If $sGenres <> "" Then
		SetMultipleMetadata($id, "genres", $sGenres, ";")
	EndIf
	If $sCategories <> "" Then
		SetMultipleMetadata($id, "categories", $sCategories, ";")
	EndIf
	_Database_EndTransaction()
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>AddGameToDatabase

Func UpdateGameInDatabase($iListItemId, $sName, $sExePath, $sIconPath = "", $iFavorite = 0, $iYear = "", $sDevelopers = "", $sPublishers = "", $sGenres = "", $sCategories = "")
	Local $iGameId = $aGameTable[$iListItemId][9]
	_Database_BeginTransaction()
	_Database_UpdateGame($iGameId, $sName, $sExePath, $sIconPath, $iFavorite, $iYear)
	If $sDevelopers <> "" AND $sDevelopers <> StringReplace($aGameTable[$iListItemId][3], ", ", ";") Then
		SetMultipleMetadata($iGameId, "developers", $sDevelopers, ";")
	EndIf
	If $sPublishers <> "" AND $sPublishers <> StringReplace($aGameTable[$iListItemId][4], ", ", ";") Then
		SetMultipleMetadata($iGameId, "publishers", $sPublishers, ";")
	EndIf
	If $sGenres <> "" AND $sGenres <> StringReplace($aGameTable[$iListItemId][5], ", ", ";") Then
		SetMultipleMetadata($iGameId, "genres", $sGenres, ";")
	EndIf
	If $sCategories <> "" AND $sCategories <> StringReplace($aGameTable[$iListItemId][6], ", ", ";") Then
		SetMultipleMetadata($iGameId, "categories", $sCategories, ";")
	EndIf
	_Database_EndTransaction()
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>UpdateGameInDatabase

Func RunGame($iListItemId)
	If $iListItemId >= 0 Then
		$sLaunchingTitle = "Launching " & $aGameTable[$iListItemId][0] & "..."
		_GuiCtrlStatusBar_SetText($hStatusBar, $sLaunchingTitle, 0)
		$sGamePath = $aGameTable[$iListItemId][7]
		RunWait($sGamePath, StringRegExpReplace($sGamePath, "\\(?:.(?!\\))+$", ""))
		_GuiCtrlStatusBar_SetText($hStatusBar, "Ready.", 0)
	EndIf
EndFunc   ;==>RunGame

Func DeleteGame($iListItemId)
	_Database_DeleteGame($aGameTable[$iListItemId][9])
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>DeleteGame

Func SetMultipleMetadata($iGameId, $sType, $sString, $sSeparator)
	_Database_RemoveMetadataMap($iGameId, $sType)
	Local $aSplit = StringSplit($sString, $sSeparator, 1)
	If $aSplit[0] > 0 Then
		For $i = 1 to $aSplit[0]
			$metadata_id = _Database_InsertMappedMetadata($sType, StringStripWS($aSplit[$i], 3))
			_Database_MapGameToMetadata($iGameId, $sType, $metadata_id)
		Next
	EndIf
EndFunc

; TODO: Check if this routine leaks memory in large sessions (due to the Image List)
Func FillListViewFromQuery($idLV, $sSQL)
	_GuiCtrlStatusBar_SetText($hStatusBar, "Fetching games...", 0)
	; Remove previous ListView items (this should free memory)
	_GUICtrlListView_DeleteAllItems($hList)
	_GUIImageList_Destroy($hListIcons)
	; Perform search based on SQL statement
	_Database_GetGamesByQuery($sSQL, $aGameTable, $iGameTableRows, $iGameTableCols)
	_ArrayDelete($aGameTable, 0)
	_GUICtrlListView_AddArray($hList, $aGameTable)
	
	; Image list filling. NOTE: This can be optimized for duplicate icons!
	$hListIcons = _GUIImageList_Create(16, 16, 6, 3)
	For $i = 0 to $iGameTableRows - 1
		 _GUIImageList_AddIconEx($hListIcons, $aGameTable[$i][8], $i)
	 Next
	_GUICtrlListView_SetImageList($hList, $hListIcons, 1)

	If $iGameTableRows > 0 Then _GUICtrlListView_SetColumnWidth($hList, 0, $LVSCW_AUTOSIZE)

	_GuiCtrlStatusBar_SetText($hStatusBar, "Ready.", 0)
	_GUICtrlStatusBar_SetText($hStatusBar, 'Games: '&$iGameTableRows, 1)
EndFunc   ;==>FillListViewFromQuery

; ATTRIBUTION: Paul Campbell (PaulIA)
; REMARKS: This function was extracted and modified from AutoIT 3.2.12.1 included UDFs.
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

; ATTRIBUTION: pixelsearch on AutoIT Forums.
; https://www.autoitscript.com/forum/topic/205908-context-menu-in-listview/
Func _TrackPopupMenu($hMenu, $hWnd, $iX, $iY)
    ; $TPM_RETURNCMD returns the menu item identifier of the user's selection in the return value.
    Local $result = DllCall("user32.dll", "int", "TrackPopupMenuEx", "hwnd", $hMenu, "int", $TPM_RETURNCMD, "int", $iX, "int", $iY, "hwnd", $hWnd, "ptr", 0)
	If UBound($result) > 0 Then
		Return $result[0]
	Else
		Return -1
	EndIf
EndFunc   ;==>_TrackPopupMenu