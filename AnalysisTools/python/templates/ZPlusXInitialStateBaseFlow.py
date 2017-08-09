from UWVV.AnalysisTools.templates.ZPlusXBaseFlow import ZPlusXBaseFlow
from UWVV.Utilities.helpers import mapObjects, parseChannels

import FWCore.ParameterSet.Config as cms


class ZPlusXInitialStateBaseFlow(ZPlusXBaseFlow):
    def __init__(self, *args, **kwargs):
        super(ZPlusXInitialStateBaseFlow, self).__init__(*args, **kwargs)

    def makeAnalysisStep(self, stepName, **inputs):
        step = super(ZPlusXInitialStateBaseFlow, self).makeAnalysisStep(stepName, **inputs)

        if stepName == 'initialStateCreation':
            self.addZPlusXCreation(step)

        if stepName == 'initialStateEmbedding':
            self.addAlternatePairInfo(step)
            self.embedCleanedJets(step)

        return step


    def addZPlusXCreation(self, step):
        '''
        Add modules to combine Zs into 3l candidates
        '''
        for chan in parseChannels('zl'):
            mod = cms.EDProducer(
                'PATCandViewShallowCloneCombiner',
                decay = cms.string('{0} {1}'.format(step.getObjTagString('ee' if chan.count('e') > 1 else 'mm'),
                                                    step.getObjTagString('e' if chan.count('e') in [1,3] else 'm'))),
                cut = cms.string(""),
                checkCharge = cms.bool(False),
                setPdgId = cms.int32(25),
                )
            
            step.addModule(chan+'Producer', mod, chan)


    def addAlternatePairInfo(self, step):
        '''
        Add modules to embed alternate lepton pair (e.g. e1+m1) info.
        '''
        for chan in parseChannels('zl'):
            mod = cms.EDProducer(
                'AlternateDaughterInfoEmbedder',
                src = step.getObjTag(chan),
                names = cms.vstring(*mapObjects(chan)),
                fsrLabel = cms.string(""),#"fsr"),
                )
            step.addModule(chan+'AlternatePairs', mod, chan)

    def embedCleanedJets(self, step):
        '''
        Add modules to embed alternate lepton pair (e.g. e1+m1) info.
        '''
        for chan in parseChannels('zl'):
            try:
                mod = cms.EDProducer(
                    'CleanedJetCollectionEmbedder',
                    src = step.getObjTag(chan),
                    jetSrc = step.getObjTag('j'),
                    jesUpJetSrc = step.getObjTag('j_jesUp'),
                    jesDownJetSrc = step.getObjTag('j_jesDown'),
                    jerUpJetSrc = step.getObjTag('j_jerUp'),
                    jerDownJetSrc = step.getObjTag('j_jerDown'),
                )
            except KeyError:
                mod = cms.EDProducer(
                    'CleanedJetCollectionEmbedder',
                    src = step.getObjTag(chan),
                    jetSrc = step.getObjTag('j'),
                )
            step.addModule(chan+'CleanedJetsEmbed', mod, chan)
