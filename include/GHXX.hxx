#include <cstdio>

#include <TRandom.h>
#include <TF1.h>

//template<typename HistType>
//Int_t GHX<HistType>::Fill(Double_t x) {
//  printf("no.\n");
//  return 0;
//}


//template<typename HistType>
//Int_t GHX<HistType>::Fill(Double_t x, Double_t w) {
//  printf("no.no.\n");
//  return 0;
//}


template<typename HistType>
TF1* GHXX<HistType,1>::ConstructTF1() const  {
  ROOT::Math::ParamFunctor *f = new  ROOT::Math::ParamFunctor(this,&GHXX::FitEval);
  double low  = this->GetXaxis()->GetBinLowEdge(1);
  double high = this->GetXaxis()->GetBinUpEdge(this->GetXaxis()->GetNbins());

  TF1 *tf1 = new TF1(Form("%s_tf1",this->GetName()),*f,low,high,1,1);
  tf1->SetParameter(0,1.0);
  tf1->SetNpx(this->GetXaxis()->GetNbins());
  return tf1;
}

template<typename HistType>
double GHXX<HistType,1>::FitEval(double *dim,double *par) const {
  double x     = dim[0];
  double scale = par[0];

  int binNum    = this->GetXaxis()->FindBin(x);
  int nBins     = this->GetNbinsX();
  int kevPerBin = this->GetXaxis()->GetXmax()/nBins;
  int curBinX   = this->GetBinCenter(binNum);
  int nextBinX  = this->GetBinCenter(binNum+1);
  int prevBinX  = this->GetBinCenter(binNum-1);

  if (x > prevBinX && x <= curBinX){
    double leftDiff = x - prevBinX;
    double rightDiff = curBinX - x;

    leftDiff = 1.0 - leftDiff/(double)kevPerBin;   //These numbers are now less than 1
    rightDiff = 1.0 - rightDiff/(double)kevPerBin; //and a measure of how close it is to bin
    double binContentLeft = this->GetBinContent(binNum-1);
    double binContentRight = this->GetBinContent(binNum);
    return scale * (leftDiff*binContentLeft+rightDiff*binContentRight);
  }

  else if (x > curBinX && x < nextBinX){
    double leftDiff = x - curBinX;
    double rightDiff = nextBinX - x;

    leftDiff = 1.0 - leftDiff/(double)kevPerBin;
    rightDiff = 1.0 - rightDiff/(double)kevPerBin;
    double binContentLeft = this->GetBinContent(binNum);
    double binContentRight = this->GetBinContent(binNum+1);
    return scale * (leftDiff*binContentLeft+rightDiff*binContentRight);
  }
  //std::cout << "FAILED IN HISTVALUE!" << std::endl;
  return scale * this->GetBinContent(binNum); 

}



template<typename HistType>
void GHXX<HistType,2>::Draw(Option_t *opt) {
  TString sopt = opt;
  if(sopt.Length()==0)
    sopt="colz2";
  //using TH1::Draw;
  HistType::Draw(sopt.Data());
  return;
}

template<typename HistType>
void GHXX<HistType,2>::FillRandom(double cent,double sigma,int entries) {
  TRandom r;
  for(int i=0;i<entries;i++) 
    this->Fill(r.Gaus(cent,sigma),r.Gaus(cent,sigma));
  return;
}
