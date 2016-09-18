#ifndef UWVV_Ntuplizer_FunctionLibrary_h
#define UWVV_Ntuplizer_FunctionLibrary_h


#include <functional>
#include <unordered_map>
#include <string>

#include "UWVV/Ntuplizer/interface/EventInfo.h"
#include "UWVV/Ntuplizer/interface/StringFunctionMaker.h"
#include "UWVV/Utilities/interface/helpers.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/Common/interface/Ptr.h"



namespace
{
  //// Separate templates to allow easier partial specialization

  template<typename B>
    struct GeneralFunctionList
    {
      // Null version for types we don't specify anything
      template<class T> static void
      addFunctions(std::unordered_map<std::string, std::function<B(const edm::Ptr<T>&,uwvv::EventInfo&)> >& addTo) {;}
    };

  template<>
    struct GeneralFunctionList<float>
    {
      template<class T> static void
      addFunctions(std::unordered_map<std::string, std::function<float(const edm::Ptr<T>&, uwvv::EventInfo&)> >& addTo)
      {
        typedef float (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

        addTo["pvZ"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) 
                               {
                                 return (evt.pv().isNonnull() ? evt.pv()->z() : -999.);
                               });

        addTo["pvndof"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) 
                               {
                                 return (evt.pv().isNonnull() ? evt.pv()->ndof() : -999.);
                               });

        addTo["pvRho"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) 
                               {
                                 return (evt.pv().isNonnull() ? evt.pv()->position().Rho() : -999.);
                               });

        addTo["nTruePU"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return (evt.puInfo().isValid() && evt.puInfo()->size() > 0 ?
                                        evt.puInfo()->at(1).getTrueNumInteractions() :
                                        -1.);});

        addTo["type1_pfMETEt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.met().pt();});

        addTo["type1_pfMETPhi"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.met().phi();});

        addTo["genWeight"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.genEventInfo().isValid() ? evt.genEventInfo()->weight() : 0.);
                               });

        addTo["mtToMET"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 float totalEt = obj->et() + evt.met().et();
                                 float totalPt = obj->pt() + evt.met().pt();
                                 float mtSqr = totalEt * totalEt - totalPt * totalPt;

                                 return std::sqrt(std::abs(mtSqr));
                               });

        addTo["jet1Pt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 1 ? 
                                         evt.jets()->at(0).pt() :
                                         -1.);
                               });

        addTo["jet1Eta"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 1 ? 
                                         evt.jets()->at(0).eta() :
                                         -999.);
                               });

        addTo["jet1Phi"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 1 ? 
                                         evt.jets()->at(0).phi() :
                                         -999.);
                               });

        addTo["jet2Pt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         evt.jets()->at(1).pt() :
                                         -1.);
                               });

        addTo["jet2Eta"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         evt.jets()->at(1).eta() :
                                         -999.);
                               });

        addTo["jet2Phi"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         evt.jets()->at(1).phi() :
                                         -999.);
                               });

        addTo["dijetMass"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         (evt.jets()->at(0).p4() + evt.jets()->at(1).p4()).mass() :
                                         -1.);
                               });
        
        addTo["dijetPt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         (evt.jets()->at(0).p4() + evt.jets()->at(1).p4()).phi() :
                                         -1.);
                               });

        addTo["dijetEta"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         (evt.jets()->at(0).p4() + evt.jets()->at(1).p4()).eta() :
                                         -999.);
                               });
        
        addTo["dijetPhi"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 ? 
                                         (evt.jets()->at(0).p4() + evt.jets()->at(1).p4()).phi() :
                                         -999.);
                               });

        addTo["jet1QGLikelihood"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 1 && evt.jets()->at(0).hasUserFloat("qgLikelihood") ?
                                         evt.jets()->at(0).userFloat("qgLikelihood") :
                                         -1.);
                               });

        addTo["jet2QGLikelihood"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.jets()->size() >= 2 && evt.jets()->at(1).hasUserFloat("qgLikelihood") ?
                                         evt.jets()->at(1).userFloat("qgLikelihood") :
                                         -1.);
                               });

        addTo["genJet1Pt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.genJets()->size() >= 1 ? 
                                         evt.genJets()->at(0).pt() :
                                         -1.);
                               });

        addTo["genJet2Pt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.genJets()->size() >= 2 ? 
                                         evt.genJets()->at(1).pt() :
                                         -1.);
                               });

        addTo["genJet1Eta"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.genJets()->size() >= 1 ? 
                                         evt.genJets()->at(0).eta() :
                                         -999.);
                               });

        addTo["genJet2Eta"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.genJets()->size() >= 2 ? 
                                         evt.genJets()->at(1).eta() :
                                         -999.);
                               });

        addTo["mjjGen"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return (evt.genJets()->size() >= 2 ? 
                                         (evt.genJets()->at(0).p4()+evt.genJets()->at(1).p4()).mass() :
                                         -999.);
                               });
      }
    };
        
  template<>
    struct GeneralFunctionList<bool>
    {
      template<class T> static void
      addFunctions(std::unordered_map<std::string, std::function<bool(const edm::Ptr<T>&, uwvv::EventInfo&)> >& addTo)
      {
        typedef bool (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

        addTo["pvIsValid"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) 
                               {
                                 return evt.pv().isNonnull() && evt.pv()->isValid();
                               });

        addTo["pvIsFake"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) 
                               {
                                 return evt.pv().isNull() || evt.pv()->isFake();
                               });
      }
    };

  template<>
    struct GeneralFunctionList<int>
    {
      template<class T> static void
      addFunctions(std::unordered_map<std::string, std::function<int(const edm::Ptr<T>&, uwvv::EventInfo&)> >& addTo)
      {
        typedef int (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

        addTo["Charge"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) {return obj->charge();});
        
        addTo["PdgId"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt) {return obj->pdgId();});  
      }      
    };

  template<>
    struct GeneralFunctionList<unsigned>
    {
      template<class T> static void
      addFunctions(std::unordered_map<std::string, std::function<unsigned(const edm::Ptr<T>&, uwvv::EventInfo&)> >& addTo)
      {
        typedef unsigned (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

        addTo["lumi"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.id().luminosityBlock();});

        addTo["run"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.id().run();});
  
        addTo["nvtx"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.nVertices();});

        addTo["nJets"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.jets()->size();});
        addTo["nGenJets"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.genJets()->size();});
      }
    };

  template<>
    struct GeneralFunctionList<unsigned long long>
    {
      template<class T> static void
      addFunctions(std::unordered_map<std::string, std::function<unsigned long long(const edm::Ptr<T>&, uwvv::EventInfo&)> >& addTo)
      {
        typedef unsigned long long (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

        addTo["evt"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {return evt.id().event();});
      }
    };



  //// Functions specific to a particular object type

  // null if it's some type combination we don't have functions for
  template<typename B, class T> 
    struct ObjectFunctionList
    {
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);
      static void addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo) {;}
    }; 

  template<>
    struct ObjectFunctionList<unsigned, pat::Electron>
    {
      // cheating with typedefs for standardization
      typedef pat::Electron T;
      typedef unsigned B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["MissingHits"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return obj->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                               });
      }
    };
  
  template<>
    struct ObjectFunctionList<float, pat::Electron>
    {
      // cheating with typedefs for standardization
      typedef pat::Electron T;
      typedef float B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["SIP3D"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return fabs(obj->dB(T::PV3D)) / obj->edB(T::PV3D);
                               });
  
        addTo["PVDZ"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return obj->gsfTrack()->dz(evt.pv()->position());
                               });
  
        addTo["PVDXY"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return obj->gsfTrack()->dxy(evt.pv()->position());
                               });
      }
    };
  
  template<>
    struct ObjectFunctionList<float, pat::Muon>
    {
      // cheating with typedefs for standardization
      typedef pat::Muon T;
      typedef float B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["SIP3D"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return fabs(obj->dB(T::PV3D)) / obj->edB(T::PV3D);
                               });
  
        addTo["PVDZ"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return obj->muonBestTrack()->dz(evt.pv()->position());
                               });
  
        addTo["PVDXY"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return obj->muonBestTrack()->dxy(evt.pv()->position());
                               });
      }
    };
  
  template<>
    struct ObjectFunctionList<bool, pat::Muon>
    {
      // cheating with typedefs for standardization
      typedef pat::Muon T;
      typedef bool B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["IsPFMuon"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt){return obj->isPFMuon();});
  
        addTo["IsGlobal"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt){return obj->isGlobalMuon();});
  
        addTo["IsTracker"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt){return obj->isTrackerMuon();});
      }
    };
  
  template<>
    struct ObjectFunctionList<unsigned, pat::Muon>
    {
      // cheating with typedefs for standardization
      typedef pat::Muon T;
      typedef unsigned B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["BestTrackType"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt){return obj->muonBestTrackType();});
  
        addTo["MatchedStations"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt){return obj->numberOfMatchedStations();});
      }
    };
  
  template<>
    struct ObjectFunctionList<float, pat::CompositeCandidate>
    {
      // cheating with typedefs for standardization
      typedef pat::CompositeCandidate T;
      typedef float B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["DR"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return reco::deltaR(obj->daughter(0)->p4(),
                                                     obj->daughter(1)->p4());
                               });

        addTo["massNoFSR"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return uwvv::helpers::p4WithoutFSR(obj).mass();
                               });

        addTo["ptNoFSR"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return uwvv::helpers::p4WithoutFSR(obj).pt();
                               });

        addTo["etaNoFSR"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return uwvv::helpers::p4WithoutFSR(obj).eta();
                               });

        addTo["phiNoFSR"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return uwvv::helpers::p4WithoutFSR(obj).phi();
                               });

        addTo["energyNoFSR"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return uwvv::helpers::p4WithoutFSR(obj).energy();
                               });
      }
    };
  
  template<>
    struct ObjectFunctionList<bool, pat::CompositeCandidate>
    {
      // cheating with typedefs for standardization
      typedef pat::CompositeCandidate T;
      typedef bool B;
      typedef B (FType) (const edm::Ptr<T>&, uwvv::EventInfo&);

      static void 
        addFunctions(std::unordered_map<std::string, std::function<FType> >& addTo)
      {
        addTo["SS"] = 
          std::function<FType>([](const edm::Ptr<T>& obj, uwvv::EventInfo& evt)
                               {
                                 return obj->daughter(0)->charge() == obj->daughter(1)->charge();
                               });
      }
    };
  
}


namespace uwvv
{

  template<typename B, class T>
  class FunctionLibrary
  {
   public:

    // Declare signature of these functions as FType
    typedef B (FType) (const edm::Ptr<T>&, EventInfo&);
    
    FunctionLibrary()
      {
        ::GeneralFunctionList<B>::addFunctions(functions);
        ::ObjectFunctionList<B,T>::addFunctions(functions);
      }
    ~FunctionLibrary() {;}
  
    std::function<FType>
    getFunction(const std::string& f)
      {
        if(functions.find(f) != functions.end())
          return functions.at(f);
        return StringFunctionMaker::makeStringFunction<B, T, uwvv::EventInfo&>(f);
      }

    // for testing purposes
    // const std::unordered_map<std::string, std::function<FType> >&
    //   getAllFunctions() const {return functions;}
  
   private:
    std::unordered_map<std::string, 
      std::function<FType> > functions;
  };
  

} // namespace


#endif // header guard

