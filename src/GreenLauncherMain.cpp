/***************************************************************
 * Name:      GreenLauncherMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "GreenLauncherMain.h"
#include <wx/msgdlg.h>
#include "wxGameList.h"
#include "EditGame.h"
#include "Database.h"

//(*InternalHeaders(GreenLauncherFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

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
const long GreenLauncherFrame::ID_TREECTRL1 = wxNewId();
const long GreenLauncherFrame::ID_GAMELIST1 = wxNewId();
const long GreenLauncherFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long GreenLauncherFrame::idMenuAdd = wxNewId();
const long GreenLauncherFrame::idMenuQuit = wxNewId();
const long GreenLauncherFrame::idMenuAbout = wxNewId();
const long GreenLauncherFrame::ID_STATUSBAR1 = wxNewId();
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
    SplitterWindow1->SetMinimumPaneSize(130);
    SplitterWindow1->SetSashGravity(0);
    TreeCtrl1 = new wxTreeCtrl(SplitterWindow1, ID_TREECTRL1, wxPoint(53,132), wxDefaultSize, wxTR_HIDE_ROOT|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    wxTreeItemId TreeCtrl1_Item1 = TreeCtrl1->AddRoot(_T("Root"));
    wxTreeItemId TreeCtrl1_Item2 = TreeCtrl1->AppendItem(TreeCtrl1_Item1, _T("Games"));
    wxTreeItemId TreeCtrl1_Item3 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("All Games"));
    wxTreeItemId TreeCtrl1_Item4 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Categories"));
    wxTreeItemId TreeCtrl1_Item5 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Developers"));
    wxTreeItemId TreeCtrl1_Item6 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Genres"));
    wxTreeItemId TreeCtrl1_Item7 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Platforms"));
    wxTreeItemId TreeCtrl1_Item8 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Publishers"));
    wxTreeItemId TreeCtrl1_Item9 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Years"));
    wxTreeItemId TreeCtrl1_Item10 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Features"));
    wxTreeItemId TreeCtrl1_Item11 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Series"));
    wxTreeItemId TreeCtrl1_Item12 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Regions"));
    wxTreeItemId TreeCtrl1_Item13 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Age Rating"));
    wxTreeItemId TreeCtrl1_Item14 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("User Rating"));
    wxTreeItemId TreeCtrl1_Item15 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Languages"));
    wxTreeItemId TreeCtrl1_Item16 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Licenses"));
    wxTreeItemId TreeCtrl1_Item17 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Favorites"));
    wxTreeItemId TreeCtrl1_Item18 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Installed"));
    wxTreeItemId TreeCtrl1_Item19 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Completion"));
    wxTreeItemId TreeCtrl1_Item20 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Ownership"));
    wxTreeItemId TreeCtrl1_Item21 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Source"));
    wxTreeItemId TreeCtrl1_Item22 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Perspective"));
    wxTreeItemId TreeCtrl1_Item23 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Player Mode"));
    wxTreeItemId TreeCtrl1_Item24 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Theme"));
    wxTreeItemId TreeCtrl1_Item25 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Engine"));
    wxTreeItemId TreeCtrl1_Item26 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Staff"));
    wxTreeItemId TreeCtrl1_Item27 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Hours Played"));
    wxTreeItemId TreeCtrl1_Item28 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Length"));
    wxTreeItemId TreeCtrl1_Item29 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Description"));
    wxTreeItemId TreeCtrl1_Item30 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Review"));
    wxTreeItemId TreeCtrl1_Item31 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Links"));
    wxTreeItemId TreeCtrl1_Item32 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Photos"));
    wxTreeItemId TreeCtrl1_Item33 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Videos"));
    wxTreeItemId TreeCtrl1_Item34 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Controller"));
    wxTreeItemId TreeCtrl1_Item35 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Renderer"));
    wxTreeItemId TreeCtrl1_Item36 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Game Type"));
    wxTreeItemId TreeCtrl1_Item37 = TreeCtrl1->AppendItem(TreeCtrl1_Item2, _T("Connection"));
    wxTreeItemId TreeCtrl1_Item38 = TreeCtrl1->AppendItem(TreeCtrl1_Item1, _T("Tools"));
    TreeCtrl1->ScrollTo(TreeCtrl1_Item2);
    TreeCtrl1->ExpandAll();
    GameList1 = new wxGameList(SplitterWindow1, ID_GAMELIST1, wxPoint(248,135), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL, wxDefaultValidator, _T("ID_GAMELIST1"));
    SplitterWindow1->SplitVertically(TreeCtrl1, GameList1);
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

    Connect(ID_GAMELIST1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&GreenLauncherFrame::OnGameList1ItemActivated);
    Connect(idMenuAdd,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnAddGameClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnAbout);
    //*)
    #if SQLITE_OS_WINNT==0
        TreeCtrl1->SetWindowStyle(wxTR_DEFAULT_STYLE|wxBORDER_NONE);
        GameList1->SetWindowStyle(wxLC_REPORT|wxLC_VIRTUAL|wxBORDER_NONE);
    #endif // SQLITE_OS_WINNT
    db = new Database;
    GameList1->SetDatabase(db);
    GameList1->GetGames("SELECT * from gameList");
}

GreenLauncherFrame::~GreenLauncherFrame()
{
    //(*Destroy(GreenLauncherFrame)
    //*)
    delete db;
}

void GreenLauncherFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void GreenLauncherFrame::OnAbout(wxCommandEvent& event)
{
    // wxString msg = wxbuildinfo(long_f);
    wxString msg = db->ReturnGameData(1);
    wxMessageBox(msg, _("Welcome to..."));
}

void GreenLauncherFrame::OnGameList1ItemActivated(wxListEvent& event)
{
    GameList1->RunGame(event.GetIndex());
}

void GreenLauncherFrame::OnAddGameClick(wxCommandEvent& event)
{
    EditGame dialog(this);
    dialog.SetDatabase(db);
    int rc = dialog.ShowModal();
    if (rc == wxOK) {
        GameList1->GetGames("SELECT * from gameList");
    }

}

void GreenLauncherFrame::OnTreeCtrl1BeginDrag1(wxTreeEvent& event)
{
}
