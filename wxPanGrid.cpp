#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class Canvas : public wxScrolledWindow
{
private:
    wxPoint incrimentScrollDirection(wxPoint pt, wxPoint start);
    int subgridPixelSpacing{ 100 };
    bool panCanvas{ false };
    wxPoint virtualSize{};
    wxPoint startMousePos;

    void onCaptureLost(wxMouseCaptureLostEvent& event);
    void rightIsDragging(wxMouseEvent& event);
    void rightIsDown(wxMouseEvent& event);
    void rightIsUp(wxMouseEvent& event);
    void OnDraw(wxDC& dc);

public:
    Canvas(wxWindow* parent, wxWindowID id);
};

class MainFrame : public wxFrame
{
private:

public:
    MainFrame(wxWindow* parent, wxWindowID 	id, const wxString& title, const wxPoint& pos, const wxSize& size);
};

Canvas::Canvas(wxWindow* parent, wxWindowID id)
    : wxScrolledWindow(parent, id)
{
    this->SetBackgroundColour(wxColor(37, 37, 37));

    SetScrollbars(1, 1, 2000, 2000, 0, 0);

    GetVirtualSize(&virtualSize.x, &virtualSize.y);

    //Binding events
    Bind(wxEVT_MOUSE_CAPTURE_LOST, &Canvas::onCaptureLost, this);
    Bind(wxEVT_MOTION, &Canvas::rightIsDragging, this);
    Bind(wxEVT_LEFT_DOWN, &Canvas::rightIsDown, this);
    Bind(wxEVT_LEFT_UP, &Canvas::rightIsUp, this);
}

wxPoint Canvas::incrimentScrollDirection(wxPoint current, wxPoint start)
{
    //This should return a 1 or -1 in x and y when dragging
    //the mouse, the pan should feel like a 1:1 ratio for pixels
    //traveled on screen and pixels the canvas has moved/scrolled
    wxPoint mouseTravel{};

    //Get x/y direction mouse has traveled
    mouseTravel.x = (current.x - start.x);
    mouseTravel.y = (current.y - start.y);

    //Reset starting position so movement is 1:1
    startMousePos.x = current.x;
    startMousePos.y = current.y;

    return -mouseTravel;
}

void Canvas::rightIsDown(wxMouseEvent& event)
{
    startMousePos = event.GetPosition();
    panCanvas = true;
    CaptureMouse();
}

void Canvas::rightIsDragging(wxMouseEvent& event)
{
    wxPoint direction{};
    if (panCanvas) {
        wxSetCursor(wxCURSOR_HAND);

        //Get position of scrollbar in scroll units
        wxPoint scrolledPosition{};
        GetViewStart(&scrolledPosition.x, &scrolledPosition.y);

        wxPoint inProgressMousePos = event.GetPosition();
        direction = incrimentScrollDirection(event.GetPosition(), startMousePos);
        this->Scroll(scrolledPosition.x += direction.x, scrolledPosition.y += direction.y);
    }
}

void Canvas::rightIsUp(wxMouseEvent& event)
{
    if (HasCapture()) {
        ReleaseMouse();
    }

    panCanvas = false;
}

void Canvas::OnDraw(wxDC& dc)
{
    //Draw Subgrid
    dc.SetPen(wxPen(wxColor(41, 41, 41), 2));
    //Horizontal middle and down -Y -> (0,1750),(3500,0)
    for (int i{ virtualSize.y / 2 }; i < virtualSize.y; i += subgridPixelSpacing) {
        dc.DrawLine(wxPoint(0, i), wxPoint(virtualSize.y, i));
    }
    //Horizontal middle and up +Y -> (0,1750),(3500,0)
    for (int i{ virtualSize.y / 2 }; i > 0; i -= subgridPixelSpacing) {
        dc.DrawLine(wxPoint(0, i), wxPoint(virtualSize.y, i));
    }
    //Vertical middle and right to +X -> (1750,0),(0,3500)
    for (int i{ virtualSize.x / 2 }; i < virtualSize.x; i += subgridPixelSpacing) {
        dc.DrawLine(wxPoint(i, 0), wxPoint(i, virtualSize.y));
    }
    //Vertical middle and left to -X -> (1750,0),(0,3500)
    for (int i{ virtualSize.x / 2 }; i > 0; i -= subgridPixelSpacing) {
        dc.DrawLine(wxPoint(i, 0), wxPoint(i, virtualSize.y));
    }

    //Draw axis lines X and Y
    dc.SetPen(wxPen(wxColor(75, 55, 55), 4));
    dc.DrawLine(wxPoint(0, virtualSize.y / 2), wxPoint(virtualSize.y, virtualSize.y / 2));//H
    dc.SetPen(wxPen(wxColor(55, 55, 75), 4));
    dc.DrawLine(wxPoint(virtualSize.x / 2, 0), wxPoint(virtualSize.x / 2, virtualSize.x));//V
}

void Canvas::onCaptureLost(wxMouseCaptureLostEvent& event)
{
    if (HasCapture()) {
        ReleaseMouse();
    }

    panCanvas = false;
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID 	id, const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(parent, id, title, pos, size)
{
    CreateStatusBar();
    wxLogStatus("Left click and drag in grid to pan!");
}

bool MyApp::OnInit()
{
    MainFrame* mainFrame = new MainFrame(NULL, wxID_ANY, "panScrollbarWithMouseDrag", wxPoint(100, 100), wxSize(640, 640));
    Canvas* canvas = new Canvas(mainFrame, wxID_ANY);
    mainFrame->Show(true);
    canvas->Scroll(696, 719);
    mainFrame->Center();
    return true;

 
}

wxIMPLEMENT_APP(MyApp);
