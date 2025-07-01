#ifndef WXFILTERDATA_H
#define WXFILTERDATA_H

#include <wx/treebase.h>
#include <wx/string.h>

#include "GreenLauncherApp.h"

wxDECLARE_APP(GreenLauncherApp);

class wxFilterData : public wxTreeItemData
{
    public:
        wxString filterQueryStr;

        wxFilterData(wxString str)
        {
            filterQueryStr = str;
        }
        virtual ~wxFilterData() {

        }
};

#endif // WXFILTERDATA_H
