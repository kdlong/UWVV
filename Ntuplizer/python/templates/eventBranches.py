import FWCore.ParameterSet.Config as cms


eventBranches = cms.PSet(
    floats = cms.PSet(
        pvndof = cms.string('pvndof'),
        pvZ = cms.string('pvZ'),
        pvRho = cms.string('pvRho'),
        type1_pfMETEt = cms.string('type1_pfMETEt'),
        type1_pfMETPhi = cms.string('type1_pfMETPhi'),
        Flag_BadPFMuonFilterPass = cms.string('? hasUserFloat("Flag_BadPFMuonFilterPass") ? '
                'userFloat("Flag_BadPFMuonFilterPass") : 100'),
        Flag_BadChargedCandidateFilterPass = cms.string('? hasUserFloat("Flag_BadChargedCandidateFilterPass") ? '
                'userFloat("Flag_BadChargedCandidateFilterPass") : 100'),
        ),
    vFloats = cms.PSet(
        jetPt = cms.vstring('jetPt'),
        jetEta = cms.vstring('jetEta'),
        jetPhi = cms.vstring('jetPhi'),
        jetCSVv2 = cms.vstring('jetCSVv2'),
        jetCMVAv2 = cms.vstring('jetCMVAv2'),
        ),
    vInts = cms.PSet(
        jetPUID = cms.vstring('jetPUID'),
        jetHadronFlavor = cms.vstring('jetHadronFlavor'),
        ),
    bools = cms.PSet(
        pvIsValid = cms.string('pvIsValid'),
        pvIdFake = cms.string('pvIsFake'),
        ),
    uints = cms.PSet(
        lumi = cms.string('lumi'),
        run = cms.string('run'),
        nvtx = cms.string('nvtx'),
        nJets = cms.string('nJets'),
        ),
    ulls = cms.PSet(
        evt = cms.string('evt'),
        ),
    )

lheScaleWeightBranches = cms.PSet(
    vFloats = cms.PSet(
        scaleWeights = cms.vstring('lheWeights::0,9'),
        ),
    floats = cms.PSet(
        minScaleWeight = cms.string('minLHEWeight::0,9'),
        maxScaleWeight = cms.string('maxLHEWeight::0,9'),
        ),
    )

lheScaleAndPDFWeightBranches = cms.PSet(
    vFloats = cms.PSet(
        scaleWeights = cms.vstring('lheWeights::0,9'),
        pdfWeights = cms.vstring('lheWeights::9,111'),
        ),
    floats = cms.PSet(
        minScaleWeight = cms.string('minLHEWeight::0,9'),
        maxScaleWeight = cms.string('maxLHEWeight::0,9'),
        ),
    )

lheAllWeightBranches = cms.PSet(
    vFloats = cms.PSet(
        scaleWeights = cms.vstring('lheWeights::0,9'),
        pdfWeights = cms.vstring('lheWeights::9,9999'),
        ),
    floats = cms.PSet(
        minScaleWeight = cms.string('minLHEWeight::0,9'),
        maxScaleWeight = cms.string('maxLHEWeight::0,9'),
        ),
    )

# gen information branches for regular ntuple
eventGenBranches = cms.PSet(
    floats = cms.PSet(
        genWeight = cms.string('genWeight'),
        nTruePU = cms.string('nTruePU'),
        ),
    )

# event branches for gen ntuple
genNtupleEventBranches = cms.PSet(
    floats = cms.PSet(
        genWeight = cms.string('genWeight'),
        ),
    vFloats = cms.PSet(
        jetPt = cms.vstring('genJetPt'),
        jetEta = cms.vstring('genJetEta'),
        jetPhi = cms.vstring('genJetPhi'),
        ),
    uints = cms.PSet(
        lumi = cms.string('lumi'),
        run = cms.string('run'),
        nJets = cms.string('nGenJets'),
        ),
    ulls = cms.PSet(
        evt = cms.string('evt'),
        ),
    )

jetSystematicBranches = cms.PSet(
    vFloats = cms.PSet(
        jetPt_jesUp = cms.vstring('jetPt::jesUp'),
        jetPt_jesDown = cms.vstring('jetPt::jesDown'),
        jetPt_jerUp = cms.vstring('jetPt::jerUp'),
        jetPt_jerDown = cms.vstring('jetPt::jerDown'),
        jetEta_jesUp = cms.vstring('jetEta::jesUp'),
        jetEta_jesDown = cms.vstring('jetEta::jesDown'),
        jetEta_jerUp = cms.vstring('jetEta::jerUp'),
        jetEta_jerDown = cms.vstring('jetEta::jerDown'),
        ),
    vInts = cms.PSet(
        jetPUID_jesUp = cms.vstring('jetPUID::jesUp'),
        jetPUID_jesDown = cms.vstring('jetPUID::jesDown'),
        jetPUID_jerUp = cms.vstring('jetPUID::jerUp'),
        jetPUID_jerDown = cms.vstring('jetPUID::jerDown'),
        ),
    uints = cms.PSet(
        nJets_jesUp = cms.string('nJets::jesUp'),
        nJets_jesDown = cms.string('nJets::jesDown'),
        nJets_jerUp = cms.string('nJets::jerUp'),
        nJets_jerDown = cms.string('nJets::jerDown'),
        ),
    floats = cms.PSet(
        type1_pfMETEt_UncTool = cms.string('type1_pfMETEt::fromUncertaintyTool'),
        type1_pfMETPhi_UncTool = cms.string('type1_pfMETPhi::fromUncertaintyTool'),
        type1_pfMETEt_jesUp_old = cms.string('type1_pfMETEt_jesUp'),
        type1_pfMETEt_jesUp = cms.string('type1_pfMETEt_jesUp::fromUncertaintyTool'),
        type1_pfMETEt_jesDown_old = cms.string('type1_pfMETEt_jesDown'),
        type1_pfMETEt_jesDown = cms.string('type1_pfMETEt_jesDown::fromUncertaintyTool'),
        type1_pfMETEt_jerUp_old = cms.string('type1_pfMETEt_jerUp'),
        type1_pfMETEt_jerUp = cms.string('type1_pfMETEt_jerUp::fromUncertaintyTool'),
        type1_pfMETEt_jerDown_old = cms.string('type1_pfMETEt_jerDown'),
        type1_pfMETEt_jerDown = cms.string('type1_pfMETEt_jerDown::fromUncertaintyTool'),
        ),
    )

# gen-level initial state info for reco ntuple
genInitialStateBranches = cms.PSet(
    floats = cms.PSet(
        GenMass = cms.string('genInitialStateMass'),
        GenPt = cms.string('genInitialStatePt'),
        GenEta = cms.string('genInitialStateEta'),
        GenPhi = cms.string('genInitialStatePhi'),
        ),
    )

dressedGenCompositeStateBranches = cms.PSet(
    floats = cms.PSet(
        UndressedMass = cms.string('undressedMass'),
        UndressedPt = cms.string('undressedPt'),
        UndressedEta = cms.string('undressedEta'),
        UndressedPhi = cms.string('undressedPhi'),
        ),
    )
