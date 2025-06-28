/***************************************************************
 * Name:      GameData.h
 * Purpose:   Game Data Transfer Object
 * Author:    Francisco Iturrieta (laziness@protonmail.com)
 * Created:   2025-06-24
 * Copyright: Francisco Iturrieta (https://lisa734.neocities.org)
 * License:   GPL-3.0
 **************************************************************/

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <vector>

#include <wx/string.h>
#include <wx/datetime.h>

struct GameMetadata {
    wxDateTime releaseDate;
    wxString platform;
    wxString developer;
    wxString publisher;
    wxString genre;
    wxString series;
    wxString region;
    wxString language;
    wxString license;
    wxString format;
    wxString ageRating;
    wxString score;
    wxString description;
};

struct ActionData {
    long id;
    wxString name;
    bool isMain;
    long type;
    long systemId;
    wxString path;
    wxString workingDir;
    wxString args;
    wxString iconPath;
};

struct GameData {
    long id;
    wxString name;
    bool favorite;
    bool hidden;
    wxString category;
    wxString source;
    GameMetadata metadata;
    std::vector<ActionData> actions;
};

#endif // GAMEDATA_H
