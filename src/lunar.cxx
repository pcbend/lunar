
#include<cstdio>
#include<string>
#include<fstream>
#include<unistd.h>
#include<limits.h>

#include<TString.h>
#include<TEnv.h>
#include<TPluginManager.h>
#include<TThread.h>
#include<Gint.h>


bool file_exists(const char *fname) {
  return std::ifstream(fname).good();
}

std::string GetProgramPath() {
  char buff[PATH_MAX+1];
  size_t len = readlink("/proc/self/exe",buff,sizeof(buff)-1);
  buff[len] = '\0';
  std::string exe_path=buff;
  return exe_path.substr(0,exe_path.find_last_of('/'));
}

void LoadLunarEnv() {
  setenv("LUNSYS",(GetProgramPath()+"/..").c_str(),0);

  std::string lun_path = Form("%s/.lunrc",getenv("LUNSYS"));
  gEnv->ReadFile(lun_path.c_str(),kEnvChange);

  lun_path = Form("%s/.lunrc",getenv("HOME"));
  if(file_exists(lun_path.c_str())) {
    gEnv->ReadFile(lun_path.c_str(),kEnvChange);
  }

  lun_path = Form("%s/.lunrc",getenv("PWD"));
  if(file_exists(lun_path.c_str())) {
    gEnv->ReadFile(lun_path.c_str(),kEnvChange);
  }
}

void AclicUseCpp11() {
  TString cmd = gSystem->GetMakeSharedLib();
  cmd.ReplaceAll("g++","g++ -std=c++11");
  gSystem->SetMakeSharedLib(cmd.Data());
}


void SetGRUTPluginHandlers() {
  gPluginMgr->AddHandler("TGuiFactory","root","GROOTGuiFactory","Gui","GROOTGuiFactory()");
}

int main(int argc, char **argv) {
  LoadLunarEnv();
  SetGRUTPluginHandlers();
  AclicUseCpp11();

  TThread::Initialize();

  Gint *input = Gint::instance(argc,argv);
  input->Run(false);
  return 0;
}
