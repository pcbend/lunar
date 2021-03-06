#ifndef GRUTCANVAS_H
#define GRUTCANVAS_H

#include "TROOT.h"
#include "TCanvas.h"
#include "TRootCanvas.h"
//#include "TPeak.h"

#include "TLine.h"
//#include "TBuffer.h"


class TF1;
class TH1;
class GH1;
class GH2;

class GMarker : public TObject{
public:
  GMarker():x(-1),y(-1),localx(0.0),localy(0.0),linex(0),liney(0) { }
  GMarker(const GMarker &m) : TObject(m) { ((GMarker&)m).Copy(*this); }
  virtual ~GMarker() { if(linex) linex->Delete(); if(liney) liney->Delete(); }
  void Draw(Option_t* opt="") { if(linex) linex->Draw(opt); if(liney) liney->Draw(opt); }

  void SetColor(Color_t color) {
    if(linex){
      linex->SetLineColor(color);
    }
    if(liney){
      liney->SetLineColor(color);
    }
  }

  // Pixel space
  int x,y;
  // Coordinate space (SetRangeUser() units)
  double localx, localy;
  // Bin space
  int binx, biny;
  TLine *linex;
  TLine *liney;
  void Copy(TObject &object) const;
  void Print(Option_t *opt="") const; 
  bool operator<(const GMarker &rhs) const { return x < rhs.x; }
  ClassDef(GMarker,0)
};

/*
class GPopup : public TGTransientFrame  {
  public:
    GPopup(const TGWindow *p=0,const TGWindow *m=0);
    virtual ~GPopup();
    virtual void CloseWindow();
    //bool ProcessMessage(Long_t,Long_t,Long_t);
  private:
    TGTextButton *fButton1,*fButton2;
  ClassDef(GPopup,0)
};
*/

class GCanvas : public TCanvas {
public:
  GCanvas(Bool_t build = kTRUE);
  GCanvas(int cols, int rows,Bool_t build=kTRUE);
  GCanvas(const char* name, const char* title = "", Int_t form = 1);
  GCanvas(const char* name, const char* title, Int_t ww, Int_t wh);
  GCanvas(const char* name, Int_t ww, Int_t wh, Int_t winid);
  GCanvas(const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh,bool gui=false);
  virtual ~GCanvas();

  //void ProcessEvent(Int_t event,Int_t x,Int_t y,TObject *obj);
  //void CatchEvent(Int_t event,Int_t x,Int_t y,TObject *obj);
  void HandleInput(Int_t event,Int_t x,Int_t y);
  void Draw(Option_t *opt="");

  static GCanvas *MakeDefCanvas();

  Int_t  GetNMarkers()               { return fMarkers.size();    }
  //Int_t  GetNBG_Markers()            { return fBG_Markers.size(); }
  void SetMarkerMode(bool flag=true) { fMarkerMode = flag;        }

  //static void SetBackGroundSubtractionType();

  TF1 *GetLastFit();
private:
  void GCanvasInit();

  void UpdateStatsInfo(int,int);

  static int lastx;
  static int lasty;

  bool fGuiEnabled;

  GH1 *gHist;

  //bool fStatsDisplayed;
  bool fMarkerMode;
  std::vector<GMarker*> fMarkers;
  std::vector<GMarker*> fBackgroundMarkers;
  //kBackgroundSubtraction fBackgroundMode;
public:
  void AddMarker(int,int,int dim=1);   //*SIGNAL*
  void RemoveMarker(Option_t *opt=""); //*SIGNAL*
  void OrderMarkers();
  void RedrawMarkers();
  
  std::vector<GMarker*> GetMarkers()           { return fMarkers; }
  std::vector<GMarker*> GetBackgroundMarkers() { return fBackgroundMarkers; }
    
  bool SetBackgroundMarkers();         //*SIGNAL*
  bool CycleBackgroundSubtraction();
private:
  //std::vector<GMarker*> fBG_Markers;
  //void AddBGMarker(GMarker *mark);
  //void RemoveBGMarker();
  //void ClearBGMarkers();
  //void OrderBGMarkers();

  std::vector<TH1*> FindHists(int dim=1);
  std::vector<TH1*> FindAllHists();

public:
  bool HandleArrowKeyPress(Event_t *event,UInt_t *keysym);
  bool HandleKeyboardPress(Event_t *event,UInt_t *keysym);
  bool HandleMousePress(Int_t event,Int_t x,Int_t y);
  bool HandleMouseShiftPress(Int_t event,Int_t x,Int_t y);
  bool HandleMouseControlPress(Int_t event,Int_t x,Int_t y);

private:
  bool ProcessNonHistKeyboardPress(Event_t* event, UInt_t* keysym);
  bool Process1DArrowKeyPress(Event_t *event,UInt_t *keysym);
  bool Process1DKeyboardPress(Event_t *event,UInt_t *keysym);
  bool Process1DMousePress(Int_t event,Int_t x,Int_t y);

  bool Process2DArrowKeyPress(Event_t *event,UInt_t *keysym);
  bool Process2DKeyboardPress(Event_t *event,UInt_t *keysym);
  bool Process2DMousePress(Int_t event,Int_t x,Int_t y);

private:
  Window_t fCanvasWindowID;
  TRootCanvas *fRootCanvas;

  bool control_key;
  bool toggle_control() { control_key = !control_key; return control_key; }

  ClassDef(GCanvas,10);
};

#endif
