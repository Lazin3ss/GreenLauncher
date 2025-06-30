/***************************************************************
 * Name:      GreenLauncherApp.h
 * Purpose:   Defines Application Class
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2024-12-02
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef GREENLAUNCHERAPP_H
#define GREENLAUNCHERAPP_H

#include "GameManager.h"

#include <wx/app.h>

class GreenLauncherApp : public wxApp
{
    public:
        GameManager* gameManager;

        virtual bool OnInit();
        virtual int OnExit();
};

#endif // GREENLAUNCHERAPP_H

