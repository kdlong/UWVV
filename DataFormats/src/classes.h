#include "UWVV/DataFormats/interface/DressedGenParticleFwd.h"
#include "UWVV/DataFormats/interface/DressedGenParticle.h"

namespace {
    struct UWVV_DataFormats_dicts {
        DressedGenParticleCollection p1;
        edm::Wrapper<DressedGenParticleCollection> dummy1;
        edm::RefProd<DressedGenParticleCollection> dummyRefProd;
        edm::RefVector<DressedGenParticleCollection> dummyRefVector;

        edm::OwnVector<DressedGenParticle,
            edm::ClonePolicy<DressedGenParticle> > dummyOV1;
        edm::OwnVector<DressedGenParticle,
            edm::ClonePolicy<DressedGenParticle> >::const_iterator dummyit; 
    };
}
