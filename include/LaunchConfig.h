#ifndef LAUNCHCONFIG_H
#define LAUNCHCONFIG_H

//(*Headers(LaunchConfig)
#include <wx/bmpbuttn.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class LaunchConfig: public wxPanel
{
    public:

        LaunchConfig(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~LaunchConfig();

        //(*Declarations(LaunchConfig)
        wxBitmapButton* BitmapButton1;
        wxBitmapButton* BitmapButton2;
        wxBitmapButton* BitmapButton3;
        wxComboBox* SystemComboBox;
        wxComboBox* TypeComboBox;
        wxDirPickerCtrl* WorkingDirectoryCtrl;
        wxFilePickerCtrl* FileCtrl;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxTextCtrl* ArgumentsTextCtrl;
        wxTextCtrl* NameTextCtrl;
        //*)

    protected:

        //(*Identifiers(LaunchConfig)
        static const long ID_STATICTEXT7;
        static const long ID_NAMETEXT;
        static const long ID_STATICTEXT1;
        static const long ID_TYPECOMBOBOX;
        static const long ID_STATICTEXT2;
        static const long ID_SYSCOMBOBOX;
        static const long ID_STATICTEXT3;
        static const long ID_FILECTRL;
        static const long ID_STATICTEXT4;
        static const long ID_WORKDIRCTRL;
        static const long ID_STATICTEXT6;
        static const long ID_ARGTEX;
        static const long ID_STATICTEXT5;
        static const long ID_BITMAPBUTTON3;
        static const long ID_PANEL1;
        static const long ID_BITMAPBUTTON2;
        static const long ID_BITMAPBUTTON1;
        static const long ID_PANEL2;
        //*)

    private:

        //(*Handlers(LaunchConfig)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
