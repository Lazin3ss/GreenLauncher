/***************************************************************
 * Name:      EditGame.cpp
 * Purpose:   Code for Add/Edit Game Dialog Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-08
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "EditGame.h"

//(*InternalHeaders(EditGame)
#include <wx/button.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(EditGame)
const long EditGame::ID_PANEL1 = wxNewId();
const long EditGame::ID_PANEL2 = wxNewId();
const long EditGame::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditGame,wxDialog)
    //(*EventTable(EditGame)
    //*)
END_EVENT_TABLE()

EditGame::EditGame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EditGame)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxStdDialogButtonSizer* StdDialogButtonSizer1;

    Create(parent, wxID_ANY, _("Add / Edit Game"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    Move(wxPoint(-1,-1));
    SetMinSize(wxSize(620,440));
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Notebook1->SetMinSize(wxSize(600,350));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    Panel1->SetSizer(FlexGridSizer2);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Notebook1->AddPage(Panel1, _("Launch Configuration"), false);
    Notebook1->AddPage(Panel2, _("Info / Metadata"), false);
    FlexGridSizer1->Add(Notebook1, 1, wxALL|wxEXPAND, 0);
    StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
    StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
    StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_SAVE, wxEmptyString));
    StdDialogButtonSizer1->Realize();
    FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 10);
    SetSizer(FlexGridSizer1);
    Fit();
    Center();
    //*)
}

EditGame::~EditGame()
{
    //(*Destroy(EditGame)
    //*)
}

