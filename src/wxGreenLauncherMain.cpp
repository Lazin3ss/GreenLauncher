/***************************************************************
 * Name:      wxGreenLauncherMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "GreenLauncherApp.h"

#include "wxEditGame.h"
#include "wxFilterData.h"
#include "wxGameListCtrl.h"
#include "wxGreenLauncherMain.h"

#include "GameData.h"

#include <wx/msgdlg.h>
#include <wx/tokenzr.h>

//(*InternalHeaders(GreenLauncherFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

wxDECLARE_APP(GreenLauncherApp);

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(GreenLauncherFrame)
const long GreenLauncherFrame::ID_FILTERTREE = wxNewId();
const long GreenLauncherFrame::ID_GAMELIST1 = wxNewId();
const long GreenLauncherFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long GreenLauncherFrame::idMenuAdd = wxNewId();
const long GreenLauncherFrame::idMenuQuit = wxNewId();
const long GreenLauncherFrame::idMenuAbout = wxNewId();
const long GreenLauncherFrame::ID_STATUSBAR1 = wxNewId();
const long GreenLauncherFrame::ID_EDITGAMEMENUITEM = wxNewId();
const long GreenLauncherFrame::ID_DELETEGAMEMENUITEM = wxNewId();
//*)

BEGIN_EVENT_TABLE(GreenLauncherFrame,wxFrame)
    //(*EventTable(GreenLauncherFrame)
    //*)
END_EVENT_TABLE()

GreenLauncherFrame::GreenLauncherFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(GreenLauncherFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("GreenLauncher"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxBORDER_RAISED|wxFULL_REPAINT_ON_RESIZE, _T("wxID_ANY"));
    SetClientSize(wxSize(600,400));
    SetMinSize(wxSize(320,200));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    // This code will set a smaller font if Win 3.11 is detected:
    int majorVer; int minorVer;
    wxGetOsVersion(&majorVer, &minorVer);
    if (minorVer == 30 || majorVer == 30 || majorVer == 3)
    {
        wxFont thisFont(8,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
        SetFont(thisFont);
    }
    {
        wxIcon FrameIcon;
        FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("icon.ico"))));
        SetIcon(FrameIcon);
    }
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinimumPaneSize(150);
    SplitterWindow1->SetSashGravity(0);
    FilterTree = new wxTreeCtrl(SplitterWindow1, ID_FILTERTREE, wxPoint(53,132), wxDefaultSize, wxTR_HIDE_ROOT|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_FILTERTREE"));
    wxTreeItemId FilterTree_Item1 = FilterTree->AddRoot(_T("Root"));
    wxTreeItemId FilterTree_Item2 = FilterTree->AppendItem(FilterTree_Item1, _T("Games"));
    wxTreeItemId FilterTree_Item3 = FilterTree->AppendItem(FilterTree_Item2, _T("All Games"));
    wxTreeItemId FilterTree_Item4 = FilterTree->AppendItem(FilterTree_Item2, _T("Favorites"));
    wxTreeItemId FilterTree_Item5 = FilterTree->AppendItem(FilterTree_Item2, _T("Categories"));
    wxTreeItemId FilterTree_Item6 = FilterTree->AppendItem(FilterTree_Item2, _T("Sources"));
    wxTreeItemId FilterTree_Item7 = FilterTree->AppendItem(FilterTree_Item2, _T("Years"));
    wxTreeItemId FilterTree_Item8 = FilterTree->AppendItem(FilterTree_Item2, _T("Platforms"));
    wxTreeItemId FilterTree_Item9 = FilterTree->AppendItem(FilterTree_Item2, _T("Developers"));
    wxTreeItemId FilterTree_Item10 = FilterTree->AppendItem(FilterTree_Item2, _T("Publishers"));
    wxTreeItemId FilterTree_Item11 = FilterTree->AppendItem(FilterTree_Item2, _T("Genres"));
    wxTreeItemId FilterTree_Item12 = FilterTree->AppendItem(FilterTree_Item2, _T("Series"));
    wxTreeItemId FilterTree_Item13 = FilterTree->AppendItem(FilterTree_Item2, _T("Regions"));
    wxTreeItemId FilterTree_Item14 = FilterTree->AppendItem(FilterTree_Item2, _T("Languages"));
    wxTreeItemId FilterTree_Item15 = FilterTree->AppendItem(FilterTree_Item2, _T("License Models"));
    wxTreeItemId FilterTree_Item16 = FilterTree->AppendItem(FilterTree_Item1, _T("Tools"));
    FilterTree->ScrollTo(FilterTree_Item2);
    FilterTree->ExpandAll();
    GameList1 = new GameListCtrl(SplitterWindow1, ID_GAMELIST1, wxPoint(248,135), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL, wxDefaultValidator, _T("ID_GAMELIST1"));
    SplitterWindow1->SplitVertically(FilterTree, GameList1);
    SplitterWindow1->SetSashPosition(1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuAdd, _("Add Game"), _("Add a game to the database"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxALWAYS_SHOW_SB, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[2] = { -10, -1 };
    int __wxStatusBarStyles_1[2] = { wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(2,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(2,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    GameListMenu.AppendSeparator();
    EditGameMenuItem = new wxMenuItem((&GameListMenu), ID_EDITGAMEMENUITEM, _("Edit Game"), wxEmptyString, wxITEM_NORMAL);
    GameListMenu.Append(EditGameMenuItem);
    DeleteGameMenuItem = new wxMenuItem((&GameListMenu), ID_DELETEGAMEMENUITEM, _("Delete Game"), wxEmptyString, wxITEM_NORMAL);
    GameListMenu.Append(DeleteGameMenuItem);

    Connect(ID_FILTERTREE,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&GreenLauncherFrame::OnFilterTreeSelectionChanged);
    Connect(ID_GAMELIST1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnGameList1ItemSelect);
    Connect(ID_GAMELIST1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&GreenLauncherFrame::OnGameList1ItemActivated);
    Connect(ID_GAMELIST1,wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&GreenLauncherFrame::OnGameList1ItemRClick);
    Connect(idMenuAdd,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnAddGameClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnAbout);
    Connect(ID_EDITGAMEMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnEditGameMenuItemSelected);
    Connect(ID_DELETEGAMEMENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnDeleteGameMenuItemSelected);
    Connect(wxID_ANY,wxEVT_MENU_OPEN,(wxObjectEventFunction)&GreenLauncherFrame::OnMenuOpen);
    //*)
    #if SQLITE_OS_WINNT==0
        TreeCtrl1->SetWindowStyle(wxTR_DEFAULT_STYLE|wxBORDER_NONE);
        GameList1->SetWindowStyle(wxLC_REPORT|wxLC_VIRTUAL|wxBORDER_NONE);
    #endif // SQLITE_OS_WINNT
    wxFilterData* filterData = new wxFilterData(wxString("SELECT * from gameList"));
    FilterTree->SetItemData(FilterTree_Item3, filterData);
    wxFilterData* filterData2 = new wxFilterData(wxString("SELECT * from gameList WHERE favorite=='Yes'"));
    FilterTree->SetItemData(FilterTree_Item4, filterData2);
    GameList1->ReloadGames();
    ReloadFilters();
}

GreenLauncherFrame::~GreenLauncherFrame()
{
    //(*Destroy(GreenLauncherFrame)
    //*)
}

void GreenLauncherFrame::ReloadFilters()
{
    wxTreeItemIdValue cookie;
    wxTreeItemId filterType = FilterTree->GetFirstChild(FilterTree->GetFirstChild(FilterTree->GetRootItem(), cookie), cookie);
    while (filterType.IsOk()) {
        if (FilterTree->GetItemText(filterType).IsSameAs(wxString("All Games")) == false &&
            FilterTree->GetItemText(filterType).IsSameAs(wxString("Favorites")) == false) {
            if (FilterTree->ItemHasChildren(filterType)) {
                FilterTree->DeleteChildren(filterType);
            }
            wxString filterStr = FilterTree->GetItemText(filterType).Lower();
            filterStr.Replace(" ", "_");
            long totalFilters = wxGetApp().gameManager->GetFilterList(filterStr);
            for (long i = 0; i < totalFilters; i++) {
                wxTreeItemId filter = FilterTree->AppendItem(filterType, wxGetApp().gameManager->GetFilterLabel(i));
                wxFilterData* filterData = new wxFilterData(wxGetApp().gameManager->GetFilterData(FilterTree->GetItemText(filterType).Lower(), i));
                FilterTree->SetItemData(filter, filterData);
            }
            wxGetApp().gameManager->FreeFilterList();
        }
        filterType = FilterTree->GetNextSibling(filterType);
    }
}

void GreenLauncherFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void GreenLauncherFrame::OnAbout(wxCommandEvent& event)
{
    // wxString msg = wxbuildinfo(long_f);
    wxString msg = wxString("GreenLauncher 0.1");
    wxMessageBox(msg, _("Welcome to..."));
}

void GreenLauncherFrame::OnAddGameClick(wxCommandEvent& event)
{
    EditGame dialog(this);
    int rc = dialog.ShowModal();
    if (rc == wxOK) {
        wxGetApp().gameManager->AddGame(dialog.data);
    }
    GameList1->ReloadGames();
    ReloadFilters();
}

void GreenLauncherFrame::OnGameList1ItemSelect(wxListEvent& event)
{
    wxGetApp().gameManager->selectedGameIdx = event.GetIndex();
}

void GreenLauncherFrame::OnGameList1ItemRClick(wxListEvent& event)
{
    PopupMenu(&GameListMenu);
}

void GreenLauncherFrame::OnGameList1ItemActivated(wxListEvent& event)
{
    wxGetApp().gameManager->RunAction(0);
}

void GreenLauncherFrame::OnLaunchGameMenuItemSelected(wxCommandEvent& event)
{
    wxMenuItem* selectedItem = GameListMenu.FindItem(event.GetId());
    for (long i = 0; true; i++) {
        wxMenuItem* listItem = GameListMenu.FindItemByPosition(i);
        if (listItem->IsSeparator()) {
            break;
        }
        if (selectedItem == listItem) {
            wxGetApp().gameManager->RunAction(i);
        }
    }
}

void GreenLauncherFrame::OnDeleteGameMenuItemSelected(wxCommandEvent& event)
{
    wxGetApp().gameManager->DeleteGame();
    GameList1->ReloadGames();
    ReloadFilters();
}

void GreenLauncherFrame::OnEditGameMenuItemSelected(wxCommandEvent& event)
{
    EditGame dialog(this, wxGetApp().gameManager->GetSingleGameData());
    int rc = dialog.ShowModal();
    if (rc == wxOK) {
        wxGetApp().gameManager->EditGame(dialog.data);
    }
    GameList1->ReloadGames();
    ReloadFilters();
}

void GreenLauncherFrame::OnFilterTreeSelectionChanged(wxTreeEvent& event)
{
    wxFilterData* data = static_cast<wxFilterData*>(FilterTree->GetItemData(event.GetItem()));
    if (data != NULL) {
        if (!wxGetApp().gameManager->currentQuery.IsSameAs(data->filterQueryStr)) {
            wxGetApp().gameManager->currentQuery = data->filterQueryStr;
            GameList1->ReloadGames();
        }
    }
}

void GreenLauncherFrame::OnMenuOpen(wxMenuEvent& event)
{
    if (event.GetMenu() == &GameListMenu) {
        // First, attempt to delete previous launch crap
        while (true) {
            wxMenuItem* item = GameListMenu.FindItemByPosition(0);
            if (item->IsSeparator()) {
                break;
            }
            GameListMenu.Remove(item->GetId());
        }
        // Then, try to fill the menu with new launch shit
        wxStringTokenizer actNames = wxStringTokenizer(wxGetApp().gameManager->ReturnTableItem(wxGetApp().gameManager->selectedGameIdx, 3), ";");
        while (actNames.HasMoreTokens()) {
            wxString name = actNames.GetNextToken();
            int id = wxNewId();
            GameListMenu.Insert(0, id, name, _(""), false);
            Bind(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&GreenLauncherFrame::OnLaunchGameMenuItemSelected, this, id);
        }
    }
}
