#ifndef APP_H
#define APP_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyApp : public wxApp
{
	public:
		virtual bool OnInit();
};

#endif // APP_H
