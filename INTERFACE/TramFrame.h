#ifndef __TRAMFRAME_H__
#define __TRAMFRAME_H__

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

class TramFrame : public wxFrame
{

	public:
		TramFrame(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("TRAMWAY"));
		void WxEdit1Updated(wxCommandEvent& event);
	private:
        wxTextCtrl * d_txtAcceuil;
        wxTextCtrl * d_txtTmpSimu;
        wxButton * d_btnLancer;
        std::string d_tmpSimu;
        std::string d_pathXML;
        std::string d_pathEXE;

        void loadXML(wxCommandEvent &event);
        void loadEXE(wxCommandEvent &event);
        void tmpSimuEntered(wxCommandEvent &event);
        void onLancer(wxCommandEvent &event);
        void onQuit(wxCommandEvent &event);
};

#endif


