#include "TramApplic.h"
#include "TramFrame.h"

IMPLEMENT_APP(TramFrameApplication)

bool TramFrameApplication::OnInit()
{
    TramFrame* frame = new TramFrame(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
int TramFrameApplication::OnExit()
{
	return 0;
}
