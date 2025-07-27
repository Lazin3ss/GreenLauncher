/***************************************************************
 * Name:      GreenLauncherApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#include "GreenLauncherApp.h"
#include "GameManager.h"

//(*AppHeaders
#include "wxGreenLauncherMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(GreenLauncherApp);

bool GreenLauncherApp::OnInit()
{
    gameManager = new GameManager();
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        GreenLauncherFrame* Frame = new GreenLauncherFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

int GreenLauncherApp::OnExit()
{
    delete gameManager;
    return 0;
}
