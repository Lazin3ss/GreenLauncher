If Not @compiled Then
	#AutoIt3Wrapper_Change2CUI=y
EndIf

#Include <WinAPI.au3>
#include <SQLite.au3>

#Include <WindowsConstants.au3>
#Include <Constants.au3>
#Include <GuiMenu.au3>

#include <GuiConstantsEx.au3>
#include <GuiImageList.au3>
#include <GuiListView.au3>

#include <Array.au3>
#include <Misc.au3>

#include "database.au3"

;--------------------------------------------------------------
; GLOBAL VARIABLES
;--------------------------------------------------------------

; VERSION
Global $sVersion = "0.2"
Global $sAboutMsg = "Version: " & $sVersion & @CRLF & @CRLF & _
					"Created by Francisco Iturrieta. Various code may be attributed to:" & @CRLF & _
					"- Larsj" & @CRLF & _
					"- pixelsearch" & @CRLF & _
					"- PaulIA" & @CRLF & @CRLF & _
					"https://github.com/Lazin3ss"

; Forms
Global $mainForm, $editGameForm

; Handlers for game table data.
Global $aGameTable, $iGameTableRows, $iGameTableCols, $idList, $hList, $hImage, $idSelectedItem
Global $sLastQuery = "SELECT * FROM main.games;"

; Context Menu
Global $idContextDummy, $hContextMenu

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
	$mainForm = GUICreate("Green Launcher", 600, 400)
	GUISetIcon(@ScriptDir & "\icon.ico", 0)
	
	; Create Menus
	Local $filemenu = GUICtrlCreateMenu("File")
	Local $addgameitem = GUICtrlCreateMenuItem("Add Game", $filemenu)
	Local $launchitem = GUICtrlCreateMenuItem("Launch Game", $filemenu)
	Local $exititem = GUICtrlCreateMenuItem("Exit", $filemenu)
	Local $helpmenu = GUICtrlCreateMenu("Help")
	Local $aboutitem = GUICtrlCreateMenuItem("About Green Launcher...", $helpmenu)
	
	
	; Create Game List View
	$idList = GUICtrlCreateListView("Name|Year|Developer|Publisher", 0, 0, 600, 380, $LVS_REPORT, $LVS_EX_FULLROWSELECT)
	$hList = GUICtrlGetHandle($idList)
	$hImage = _GUIImageList_Create(16, 16, 6, 3)
	_GUICtrlListView_SetImageList($hList, $hImage, 1)
	
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
		Case $aboutitem
			MsgBox(0, "About Green Launcher", $sAboutMsg)
		Case $GUI_EVENT_CLOSE, $exititem
			ExitLoop
		EndSwitch
	WEnd
EndFunc   ;==>MainForm

;--------------------------------------------------------------
; FORM 2: ADD/EDIT GAME WINDOW
;--------------------------------------------------------------

Func EditGameForm($gameId)
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
			ExitLoop
		Case $GUI_EVENT_CLOSE
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
	$sLaunchingTitle = "Green Launcher - Launching " & $aGameTable[$gameTableIndex+1][1] & "..."
	WinSetTitle("Green Launcher", "", $sLaunchingTitle)
	$sGamePath = $aGameTable[$gameTableIndex+1][2]
	RunWait($sGamePath, StringRegExpReplace($sGamePath, "\\(?:.(?!\\))+$", ""))
	WinSetTitle($sLaunchingTitle, "", "Green Launcher")
EndFunc   ;==>RunGame

Func DeleteGame($gameTableIndex)
	_SQLite_Exec(-1, "DELETE FROM main.games WHERE rowid=" & $aGameTable[$gameTableIndex+1][0] & ";")
	FillListViewFromQuery($idList, $sLastQuery)
EndFunc   ;==>DeleteGame

; TODO: Check if this routine leaks memory in large sessions
Func FillListViewFromQuery($idLV, $sSQL)
	; Remove previous ListView items (this should free memory)
	_GUICtrlListView_DeleteAllItems($hList)
	_GUIImageList_Destroy($hImage)
	; Perform search based on SQL statement
	_SQLite_GetTable2d(-1, $sSQL, $aGameTable, $iGameTableRows, $iGameTableCols)
	$hImage = _GUIImageList_Create(16, 16, 6, 3)
	_GUICtrlListView_SetImageList($hList, $hImage, 1)
	
	Local $tLVITEM = DllStructCreate($tagLVITEM)
	Local $pLVITEM = DllStructGetPtr($tLVITEM)
	DllStructSetData($tLVITEM, "Mask", $LVIF_IMAGE) ; Icon (or image)
	DllStructSetData($tLVITEM, "SubItem", 0)        ; First column
	For $j = 0 To $iGameTableRows - 1
		; Text
		Local $itemId = GUICtrlCreateListViewItem($aGameTable[$j+1][1] & "|" & $aGameTable[$j+1][4] & "|" & $aGameTable[$j+1][5] & "|" & $aGameTable[$j+1][6], $idLV) ; Add item and all texts
		; Icon
		If $aGameTable[$j+1][3] == "" Then
			; Add icon from executable instead of icon path
			_GUIImageList_AddIconEx($hImage, $aGameTable[$j+1][2], 0)
		Else
			_GUIImageList_AddIconEx($hImage, $aGameTable[$j+1][3], 0)
		EndIf
		DllStructSetData($tLVITEM, "Image", $j)
		
		DllStructSetData($tLVITEM, "Item", $j)        ; Row
		GUICtrlSendMsg($idLV, $LVM_SETITEMW, 0, $pLVITEM) ; Add icon
	Next
	_GUICtrlListView_SetColumnWidth($hList, 0, $LVSCW_AUTOSIZE)
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
Func _GUIImageList_AddIconEx($hWnd, $sFile, $iIndex = 0, $fLarge = False)
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
	$iResult = _GUIImageList_ReplaceIcon($hWnd, -1, $hIcon)
	_WinAPI_Check("_GUIImageList_AddIcon", ($iResult = -1), -2)
	_WinAPI_DestroyIcon($hIcon)
	Return $iResult
EndFunc   ;==>_GUIImageList_AddIconEx
  
; EVENT HANDLER
Func WM_NOTIFY($hWnd, $iMsg, $iwParam, $ilParam)
    #forceref $hWnd, $iMsg, $iwParam
	
    Local $hWndFrom, $iIDFrom, $iCode, $tNMHDR, $hWndListView, $tInfo
    $hWndListView = $hList
    If Not IsHWnd($hList) Then $hWndListView = GUICtrlGetHandle($hList)

    $tNMHDR = DllStructCreate($tagNMHDR, $ilParam)
    $hWndFrom = HWnd(DllStructGetData($tNMHDR, "hWndFrom"))
    $iIDFrom = DllStructGetData($tNMHDR, "IDFrom")
    $iCode = DllStructGetData($tNMHDR, "Code")
    Switch $hWndFrom
        Case $hWndListView
            Switch $iCode
				; Run the GAME, Damnit!
				Case $NM_DBLCLK
                    $tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
					$idSelectedItem = DllStructGetData($tInfo, "Index")
					RunGame($idSelectedItem)
				; Contextual Menu (Perhaps)
                Case $NM_RCLICK ; Sent by a list-view control when the user clicks an item with the right mouse button
                    $tInfo = DllStructCreate($tagNMITEMACTIVATE, $ilParam)
;~                     _DebugPrint("$NM_RCLICK" & @LF & "--> hWndFrom:" & @TAB & $hWndFrom & @LF & _
;~                             "-->IDFrom:" & @TAB & $iIDFrom & @LF & _
;~                             "-->Code:" & @TAB & $iCode & @LF & _
;~                             "-->Index:" & @TAB & DllStructGetData($tInfo, "Index") & @LF & _
;~                             "-->SubItem:" & @TAB & DllStructGetData($tInfo, "SubItem") & @LF & _
;~                             "-->NewState:" & @TAB & DllStructGetData($tInfo, "NewState") & @LF & _
;~                             "-->OldState:" & @TAB & DllStructGetData($tInfo, "OldState") & @LF & _
;~                             "-->Changed:" & @TAB & DllStructGetData($tInfo, "Changed") & @LF & _
;~                             "-->ActionX:" & @TAB & DllStructGetData($tInfo, "ActionX") & @LF & _
;~                             "-->ActionY:" & @TAB & DllStructGetData($tInfo, "ActionY") & @LF & _
;~                             "-->lParam:" & @TAB & DllStructGetData($tInfo, "lParam") & @LF & _
;~                             "-->KeyFlags:" & @TAB & DllStructGetData($tInfo, "KeyFlags"))
					$idSelectedItem = DllStructGetData($tInfo, "Index")
					If $idSelectedItem > -1 Then ; valid row
						GUICtrlSendToDummy($idContextDummy)
					EndIf
            EndSwitch
    EndSwitch
    Return $GUI_RUNDEFMSG
EndFunc   ;==>WM_NOTIFY

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