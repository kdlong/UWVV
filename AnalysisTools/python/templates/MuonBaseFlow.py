from UWVV.AnalysisTools.AnalysisFlowBase import AnalysisFlowBase

import FWCore.ParameterSet.Config as cms


class MuonBaseFlow(AnalysisFlowBase):
    def __init__(self, *args, **kwargs):
        super(MuonBaseFlow, self).__init__(*args, **kwargs)

    def makeAnalysisStep(self, stepName, **inputs):
        step = super(MuonBaseFlow, self).makeAnalysisStep(stepName, **inputs)
        
        if stepName == 'preselection':
            step.addBasicSelector('m', 'pt > 5 && (isGlobalMuon || isTrackerMuon)')
        elif stepName == 'embedding':
            self.addMuonPOGIDs(step)

        return step

    def addMuonPOGIDs(self, step):
        '''
        Add Muon POG IDs as UserInts

        '''
        embedMuId = cms.EDProducer(
                "MuonIdEmbedder",
                src = step.getObjTag('m'),
                vertexSrc = step.getObjTag('v')
            )
        step.addModule("muonIDembedding", embedMuId, 'm')

