#ifndef GHXX_H
#define GHXX_H

#include <iostream>
#include <type_traits>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

#include "TRef.h"

//////////////////////////////////////////////
/////////   common additions /////////////////
//////////////////////////////////////////////

template<typename HistType>
class GHX : public HistType {
  public:
    GHX() { }
    GHX(const HistType& hist)
      : HistType(hist) { }

    using HistType::HistType;
    virtual Int_t Write(const char* name=0,Int_t option=0,Int_t bufsize=0) const override{
      HistType temp(*this);
      return temp.Write();
    }

    void print_base() const {
      std::cout << "method common to all histogram types" << std::endl;
    }

    //virtual Int_t Fill(Double_t x) override;
    //virtual Int_t Fill(Double_t x,Double_t w) override;

    TObject *GetParent() const       { return fParent.GetObject(); }
    void     SetParent(TObject *obj) { fParent = obj;              }

  private:
    TRef fParent;

  ClassDefOverride(GHX, 1);
};

template<typename HistType,
         int Dimension = (std::is_base_of<TH3,HistType>::value ? 3 :
                          std::is_base_of<TH2,HistType>::value ? 2 :
                          1) >
class GHXX;

//////////////////////////////////////////////
///////////   1-d additions //////////////////
//////////////////////////////////////////////

template<typename HistType>
class GHXX<HistType, 1> : public GHX<HistType> {
  public:
    GHXX() { }
    GHXX(const HistType& hist)
      : GHX<HistType>(hist) { }
    template <class T> GHXX(const T &hist) : GHX<T>(hist) {;}

    using GHX<HistType>::GHX;
    void print() const {
      std::cout << "Subclass of TH1, but not TH2 or TH3" << std::endl;
    }

    TF1 *ConstructTF1() const;
  private:
    double FitEval(double *dim,double *par) const;

  ClassDefOverride(GHXX, 1);
};

//////////////////////////////////////////////
///////////   2-d additions //////////////////
//////////////////////////////////////////////

template<typename HistType>
class GHXX<HistType, 2> : public GHX<HistType> {
  public:
    GHXX() { }
    GHXX(const HistType& hist)
      : GHX<HistType>(hist) { }
    using GHX<HistType>::GHX;

    void print() {
      std::cout << "Subclass of TH2" << std::endl;
    }

    void Draw(Option_t *opt="") override;
    void FillRandom(double cent=50.,double sigma=5.0,int entries=10000);


  ClassDefOverride(GHXX, 1);
};

//////////////////////////////////////////////
///////////   3-d additions //////////////////
//////////////////////////////////////////////

template<typename HistType>
class GHXX<HistType, 3> : public GHX<HistType> {
public:
  GHXX() { }
  GHXX(const HistType& hist)
    : GHX<HistType>(hist) { }
  using GHX<HistType>::GHX;

  void print() {
    std::cout << "Subclass of TH3" << std::endl;
  }

  ClassDefOverride(GHXX, 1);
};


//////////////////////////////////////////////
///////////   typedefs      //////////////////
//////////////////////////////////////////////

//typedef GHXX<TH1> GH1;

typedef GHXX<TH1D> GH1D;
typedef GHXX<TH1F> GH1F;
typedef GHXX<TH1I> GH1I;
typedef GHXX<TH1S> GH1S;
typedef GHXX<TH1C> GH1C;

typedef GHXX<TH2D> GH2D;
typedef GHXX<TH2F> GH2F;
typedef GHXX<TH2I> GH2I;
typedef GHXX<TH2S> GH2S;
typedef GHXX<TH2C> GH2C;

typedef GHXX<TH3D> GH3D;
typedef GHXX<TH3F> GH3F;
typedef GHXX<TH3I> GH3I;
typedef GHXX<TH3S> GH3S;
typedef GHXX<TH3C> GH3C;

#include "GHXX.hxx"


#endif /* GHXX_H */
