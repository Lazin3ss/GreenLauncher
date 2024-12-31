/***************************************************************
 * Name:      GreenLauncherMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:
 **************************************************************/

#include "GreenLauncherMain.h"
#include <wx/msgdlg.h>
#include "wxGameList.h"

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
    SplitterWindow1->SetMinimumPaneSize(100);
    SplitterWindow1->SetSashGravity(0);
    TreeCtrl1 = new wxTreeCtrl(SplitterWindow1, ID_TREECTRL1, wxPoint(53,132), wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
    GameList1 = new wxGameList(SplitterWindow1, ID_GAMELIST1, wxPoint(248,135), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL, wxDefaultValidator, _T("ID_GAMELIST1"));
    SplitterWindow1->SplitVertically(TreeCtrl1, GameList1);
    SplitterWindow1->SetSashPosition(1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxALWAYS_SHOW_SB, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GreenLauncherFrame::OnAbout);
    //*)
    #if SQLITE_OS_WINNT==0
        TreeCtrl1->SetWindowStyle(wxTR_DEFAULT_STYLE|wxBORDER_NONE);
        GameList1->SetWindowStyle(wxLC_REPORT|wxLC_VIRTUAL|wxBORDER_NONE);
    #endif // SQLITE_OS_WINNT
    GameList1->GetGames("SELECT * from gameList");
}

GreenLauncherFrame::~GreenLauncherFrame()
{
    //(*Destroy(GreenLauncherFrame)
    //*)
}

void GreenLauncherFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void GreenLauncherFrame::OnAbout(wxCommandEvent& event)
{
    // wxString msg = wxbuildinfo(long_f);
    wxString msg = GameList1->GetItemData(0, 0);
    wxMessageBox(msg, _("Welcome to..."));
}

void GreenLauncherFrame::OnTreeCtrl1BeginDrag(wxTreeEvent& event)
{
}
