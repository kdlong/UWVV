import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.Mixins import _ParameterTypeBase


_defaultEventParams = {
    'vtxSrc'             : 'offlineSlimmedPrimaryVertices',
    'eSrc'               : 'slimmedElectrons',
    'mSrc'               : 'slimmedMuons',
    'tSrc'               : 'slimmedTaus',
    'gSrc'               : 'slimmedPhotons',
    'jSrc'               : 'slimmedJets',
    'pfCandSrc'          : 'packedPFCandidates',
    'metSrc'             : 'slimmedMETs',
    'puSrc'              : 'slimmedAddPileupInfo',
    'genEventInfoSrc'    : 'generator',
    'lheEventInfoSrc'    : 'externalLHEProducer',
    'genParticleSrc'     : 'prunedGenParticles',
    'genJetSrc'          : 'slimmedGenJets',
    'initialStateSrc'    : '',
    'genInitialStateSrc' : '',
    }


def makeEventParams(flowOutputs, channel='', **newParams):
    '''
    Makes a PSet for event info contruction. Defaults above are always there
    unless overridden by something in the flowOutputs (assumed to be in the
    usual format from AnalysisFlowBase or newParams (which takes precedence).
    Anything that isn't already a CMS type is assumed to be an InputTag.
    Extra collections are indicated by a regular object string, then an
    identifier after an underscore, e.g. "j_jesUp" for a jet collection with
    the energy scale raised. These will be added as extra collections labeled
    with the identifier, e.g. you'd retrieve that jet collection from the
    EventInfo object with evt.jets("jesUp").
    '''
    params = _defaultEventParams.copy()

    objTypes = set(['e', 'm', 't', 'g', 'j'])
    extras = {ob:{} for ob in objTypes}
    extras['vtx'] = {}
    for fo, tag in flowOutputs.iteritems():
        if fo in objTypes:
            params[fo+'Src'] = tag
        elif fo.split('_')[0] in extras:
            obj = fo.split('_')[0]
            extras[obj][fo.replace(obj+'_', '', 1)] = tag
        elif fo == 'v':
            params['vtxSrc'] = tag
        elif fo.split('_')[0] == 'v':
            extras['vtx'][fo.replace('v_', '', 1)] = tag
        elif fo.split('_')[0] == channel and channel:
            params['initialStateSrc'] = tag
        elif fo.split('_')[0] == channel+'Gen' and channel:
            params['genInitialStateSrc'] = tag

    extraCollections = {}
    for obj, tags in extras.iteritems():
        tags = {n:cms.InputTag(t) for n,t in tags.iteritems()}
        if tags:
            extraCollections[obj+'Extra'] = cms.PSet(**tags)

    params.update(extraCollections)
    params.update(newParams)

    for p in params:
        if not isinstance(params[p], _ParameterTypeBase):
            params[p] = cms.InputTag(params[p])

    return cms.PSet(**params)


def makeGenEventParams(flowOutputs, **newParams):
    params = _defaultEventParams.copy()

    params['genJetSrc'] = flowOutputs['j']
    params['genParticleSrc'] = flowOutputs['pfCands']

    params.update(newParams)

    for p in params:
        if not isinstance(params[p], _ParameterTypeBase):
            params[p] = cms.InputTag(params[p])

    return cms.PSet(**params)
