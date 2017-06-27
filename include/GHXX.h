#ifndef GHXX_H
#define GHXX_H

#include <iostream>
#include <type_traits>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

template<typename HistType>
class GHX : public HistType {
public:
  GHX() { }
  GHX(const HistType& hist)
    : HistType(hist) { }
  using HistType::HistType;

  virtual Int_t Write(const char* name = 0,
                               Int_t option = 0,
                               Int_t bufsize = 0) const {
    HistType temp(*this);
    return temp.Write();
  }

  void print_base() {
    std::cout << "method common to all histogram types" << std::endl;
  }

  ClassDef(GHX, 1);
};

template<typename HistType,
         int Dimension = (std::is_base_of<TH3,HistType>::value ? 3 :
                          std::is_base_of<TH2,HistType>::value ? 2 :
                          1) >
class GHXX;

template<typename HistType>
class GHXX<HistType, 1> : public GHX<HistType> {
public:
  GHXX() { }
  GHXX(const HistType& hist)
    : GHX<HistType>(hist) { }

  using GHX<HistType>::GHX;
  void print() {
    std::cout << "Subclass of TH1, but not TH2 or TH3" << std::endl;
  }

  ClassDef(GHXX, 1);
};

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

  ClassDef(GHXX, 1);
};

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

  ClassDef(GHXX, 1);
};

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


#endif /* GHXX_H */
