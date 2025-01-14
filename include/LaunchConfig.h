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
        wxComboBox* ComboBox1;
        wxComboBox* ComboBox2;
        wxDirPickerCtrl* DirPickerCtrl1;
        wxFilePickerCtrl* FilePickerCtrl1;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxTextCtrl* TextCtrl1;
        //*)

    protected:

        //(*Identifiers(LaunchConfig)
        static const long ID_STATICTEXT1;
        static const long ID_COMBOBOX1;
        static const long ID_STATICTEXT2;
        static const long ID_COMBOBOX2;
        static const long ID_STATICTEXT3;
        static const long ID_FILEPICKERCTRL1;
        static const long ID_STATICTEXT4;
        static const long ID_DIRPICKERCTRL1;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT5;
        static const long ID_BITMAPBUTTON3;
        static const long ID_BITMAPBUTTON2;
        static const long ID_BITMAPBUTTON1;
        static const long ID_PANEL1;
        //*)

    private:

        //(*Handlers(LaunchConfig)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif
