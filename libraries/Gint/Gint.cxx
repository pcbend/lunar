
#include <pwd.h>

#include <Gint.h>
#include <TEnv.h>
#include <GRootGuiFactory.h>

#include <Globals.h>

Gint *Gint::fGint = NULL;
TEnv *Gint::fTEnv = NULL;


Gint *Gint::instance(int argc,char** argv, void *options, int numOptions, bool noLogo, const char *appClassName) {
  if(!fGint) {
    fGint = new Gint(argc,argv,options,numOptions,true,appClassName);
    fGint->Init();
  }
  return fGint;
}

Gint::Gint(int argc, char **argv,void *options, Int_t numOptions, Bool_t noLogo,const char *appClassName)
  :TRint(appClassName, &argc, argv, options, numOptions,noLogo),
   main_thread_id(std::this_thread::get_id())  {

  fTEnv = gEnv;
  GetSignalHandler()->Remove();
  GInterruptHandler *ih = new GInterruptHandler();
  ih->Add();

}

Gint::~Gint() {
}

void Gint::Init() {
  //std::string grutpath = getenv("LUNSYS");
  //gInterpreter->AddIncludePath(Form("%s/include",grutpath.c_str()));
  SetPrompt("lunar [%d] ");
  fIsTabComplete = false;

  ApplyOptions();

}

void Gint::ApplyOptions() {
  //get the options....
  if(!false) {
    GRootGuiFactory::Init();
  }
}




Int_t Gint::TabCompletionHook(char *buf,int *pLoc, std::ostream &out) {
  fIsTabComplete = true;
  int result = TRint::TabCompletionHook(buf,pLoc,out);
  fIsTabComplete = false;
  return result;
}


Long_t Gint::ProcessLine(const char *line,Bool_t sync,Int_t *error) {
  
  if(fIsTabComplete) {
    return TRint::ProcessLine(line,sync,error);
  }
  
  TString sline(line);
  if(!sline.Length()) {
    return 0;
  }
  sline.ReplaceAll("TCanvas","GCanvas");
  
  
  long result =  TRint::ProcessLine(sline.Data(),sync,error);
  return result;
}

void Gint::PrintLogo(bool lite) {
  printf("i'm a logo!\n");
  fflush(stdout);

}

void Gint::Terminate(Int_t status) {
  //Be polite when you leave.
  printf("\nbye,bye\t%s\n",getpwuid(getuid())->pw_name);
  //Cleanup(); 
  TRint::Terminate(status);
}



///**********************///
bool GInterruptHandler::Notify() {
  static int timespressed  = 0;
  timespressed++;
  if(timespressed>3) {
    printf("\n No you shutup! \n"); fflush(stdout);
    exit(1);
  }
  printf("\n Control-c was pressed.   \n"); fflush(stdout);
  Gint::instance()->Terminate();
  return true;
}
