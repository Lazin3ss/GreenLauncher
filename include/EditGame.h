/***************************************************************
 * Name:      EditGame.h
 * Purpose:   Defines Add/Edit Game Dialog Frame
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-01-08
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef EDITGAME_H
#define EDITGAME_H

//(*Headers(EditGame)
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
//*)

class EditGame: public wxDialog
{
    public:

        EditGame(wxWindow* parent,wxWindowID id=wxID_ANY);
        virtual ~EditGame();

        //(*Declarations(EditGame)
        wxChoice* Choice1;
        wxNotebook* Notebook1;
        wxPanel* Panel1;
        wxPanel* Panel2;
        //*)

    protected:

        //(*Identifiers(EditGame)
        static const long ID_CHOICE1;
        static const long ID_PANEL1;
        static const long ID_PANEL2;
        static const long ID_NOTEBOOK1;
        //*)

    private:

        //(*Handlers(EditGame)
        void OnNotebook1PageChanged(wxNotebookEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnNotebook1PageChanged1(wxNotebookEvent& event);
        //*)

        DECLARE_EVENT_TABLE()
};

#endif

