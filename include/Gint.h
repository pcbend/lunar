#ifndef __GINT_H__
#define __GINT_H__

#ifndef __CINT__
#include <thread>
#endif


#include<Rtypes.h>
#include<TRint.h>
#include<TSysEvtHandler.h>
#include<TSystem.h>

class Gint : public TRint {
  private: 
    Gint(int argc, char **argv, void *opts=0,int numOptions=0,
             bool noLogo = true, const char *appClassName = "grutinizer");
    static TEnv *fTEnv;
    static Gint *fGint;

  public: 
    static Gint *instance(int argc=0,char **argv=0,void *opts=0,int numOptions=-1,
                          bool noLogo=true,const char *appClassName="lunar");
    virtual ~Gint();
    //unique to gint
    void Init(); 
    void ApplyOptions();

    //from trint
    //
    void PrintLogo(bool lite=true);
    void Terminate(Int_t status=0);
  
    ///from tapplication.
    Int_t  TabCompletionHook(char *buf, int* pLoc, std::ostream &out);
    Long_t ProcessLine(const char *line,Bool_t sync=kTRUE,Int_t *error=0);

    
  private:
#ifndef __CINT__
    std::thread::id main_thread_id;
#endif
    bool fIsTabComplete;



  ClassDef(Gint,0)
};

class GInterruptHandler : public TSignalHandler {
  public:
    GInterruptHandler() : TSignalHandler(ESignals::kSigInterrupt,false) { }
    bool Notify();
  ClassDef(GInterruptHandler,0);
};


#endif
