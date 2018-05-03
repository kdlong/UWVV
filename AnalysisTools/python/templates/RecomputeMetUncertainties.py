from UWVV.AnalysisTools.AnalysisFlowBase import AnalysisFlowBase

import FWCore.ParameterSet.Config as cms

class RecomputeMetUncertainties(AnalysisFlowBase):
    def __init__(self, *args, **kwargs):
        if not hasattr(self, 'isMC'):
            self.isMC = kwargs.pop('isMC', True)
        super(RecomputeMetUncertainties, self).__init__(*args, **kwargs)

    def makeAnalysisStep(self, stepName, **inputs):
        step = super(RecomputeMetUncertainties, self).makeAnalysisStep(stepName, **inputs)

        if stepName == 'preliminary':
            # Recompute MET uncertainties with new JEC
            from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
            runMetCorAndUncFromMiniAOD(self.process,
                isData=not self.isMC,
            )
            
            step.addModule('fullPatMetSequence', self.process.fullPatMetSequence,
                'met_fromUncertaintyTool', met_fromUncertaintyTool = ':Ntuple')
        return step

