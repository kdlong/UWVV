///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


// system includes
#include <memory>
#include <vector>
#include <string>
#include <iostream>

// CMS includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Common/interface/View.h"

#include "UWVV/Utilities/interface/helpers.h"

typedef pat::CompositeCandidate CCand;

class CleanedJetCollectionEmbedder : public edm::stream::EDProducer<>
{

public:
  explicit CleanedJetCollectionEmbedder(const edm::ParameterSet& iConfig);
  virtual ~CleanedJetCollectionEmbedder() {};

private:
  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);

  edm::PtrVector<pat::Jet> getCleanedJetCollection(edm::Event& iEvent,
      const edm::EDGetTokenT<edm::View<pat::Jet>>& jetToken, 
      const reco::CompositeCandidate& initialState);

  const edm::EDGetTokenT<edm::View<CCand> > srcToken;
  const edm::EDGetTokenT<edm::View<pat::Jet> > jetSrcToken;

  edm::EDGetTokenT<edm::View<pat::Jet> > jesUpJetSrcToken;
  edm::EDGetTokenT<edm::View<pat::Jet> > jesDownJetSrcToken;
  edm::EDGetTokenT<edm::View<pat::Jet> > jerUpJetSrcToken;
  edm::EDGetTokenT<edm::View<pat::Jet> > jerDownJetSrcToken;
  bool jesUpTagExists;
  bool jesDownTagExists;
  bool jerUpTagExists;
  bool jerDownTagExists;

  typedef const edm::Ptr<reco::Candidate> (FType) (const reco::Candidate* const);
};


CleanedJetCollectionEmbedder::CleanedJetCollectionEmbedder(const edm::ParameterSet& iConfig) :
  srcToken(consumes<edm::View<CCand> >(iConfig.getParameter<edm::InputTag>("src"))),
  jetSrcToken(consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jetSrc"))),
  jesUpTagExists(iConfig.existsAs<edm::InputTag>("jesUpJetSrc")),
  jesDownTagExists(iConfig.existsAs<edm::InputTag>("jesDownJetSrc")),
  jerUpTagExists(iConfig.existsAs<edm::InputTag>("jerUpJetSrc")),
  jerDownTagExists(iConfig.existsAs<edm::InputTag>("jerDownJetSrc"))
{
  if (jesUpTagExists) 
      jesUpJetSrcToken = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jesUpJetSrc"));
  if (jesDownTagExists) 
      jesDownJetSrcToken = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jesDownJetSrc"));
  if (jerUpTagExists) 
      jerUpJetSrcToken = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jerUpJetSrc"));
  if (jerDownTagExists) 
      jerDownJetSrcToken = consumes<edm::View<pat::Jet> >(iConfig.getParameter<edm::InputTag>("jerDownJetSrc"));
  produces<std::vector<CCand> >();
}


void CleanedJetCollectionEmbedder::produce(edm::Event& iEvent,
                                            const edm::EventSetup& iSetup)
{
  edm::Handle<edm::View<CCand> > in;
  std::unique_ptr<std::vector<CCand> > out(new std::vector<CCand>);

  iEvent.getByToken(srcToken, in);

  for(size_t i = 0; i < in->size(); ++i)
    {
      edm::PtrVector<pat::Jet> cleanedJesUpJets;
      edm::Ptr<CCand> cand = in->ptrAt(i);

      out->push_back(*cand);
      edm::PtrVector<pat::Jet> cleanedJets = getCleanedJetCollection(iEvent, jetSrcToken, *cand);
      out->back().addUserData<edm::PtrVector<pat::Jet>>("cleanedJets", cleanedJets);
      
      if(jesUpTagExists) 
        { 
          edm::PtrVector<pat::Jet> cleanedJesUpJets = getCleanedJetCollection(iEvent, jesUpJetSrcToken, *cand);
          out->back().addUserData<edm::PtrVector<pat::Jet>>("cleanedJets_jesUp", cleanedJesUpJets);
        }
      if(jesDownTagExists) 
        { 
          edm::PtrVector<pat::Jet> cleanedJesDownJets = getCleanedJetCollection(iEvent, jesDownJetSrcToken, *cand);
          out->back().addUserData<edm::PtrVector<pat::Jet>>("cleanedJets_jesDown", cleanedJesDownJets);
        }
      if(jerUpTagExists) 
        { 
          edm::PtrVector<pat::Jet> cleanedJerUpJets = getCleanedJetCollection(iEvent, jerUpJetSrcToken, *cand);
          out->back().addUserData<edm::PtrVector<pat::Jet>>("cleanedJets_jerUp", cleanedJerUpJets);
        }
      if(jerDownTagExists) 
        { 
          edm::PtrVector<pat::Jet> cleanedJerDownJets = getCleanedJetCollection(iEvent, jerDownJetSrcToken, *cand);
          out->back().addUserData<edm::PtrVector<pat::Jet>>("cleanedJets_jerDown", cleanedJerDownJets);
        }
    }
      
  iEvent.put(std::move(out));
}

edm::PtrVector<pat::Jet> CleanedJetCollectionEmbedder::getCleanedJetCollection(edm::Event& iEvent,
    const edm::EDGetTokenT<edm::View<pat::Jet>>& jetToken, 
    const reco::CompositeCandidate& initialState) 
{
  edm::Handle<edm::View<pat::Jet> > uncleanedJets;
  edm::PtrVector<pat::Jet> cleanedJets; 

  iEvent.getByToken(jetToken, uncleanedJets);

  for(size_t j = 0; j < uncleanedJets->size(); ++j)
    {
      if(!uwvv::helpers::overlapWithAnyDaughter(uncleanedJets->at(j), initialState, 0.4)) 
          cleanedJets.push_back(uncleanedJets->ptrAt(j));
    }
    return cleanedJets;
}

DEFINE_FWK_MODULE(CleanedJetCollectionEmbedder);

