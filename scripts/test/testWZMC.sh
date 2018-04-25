#!/bin/bash
#igprof -d -mp -z -o igprof.mp.gz 
cmsRun UWVV/Ntuplizer/test/ntuplize_cfg.py \
    inputFiles=/store/data/Run2016G/DoubleEG/MINIAOD/03Feb2017-v1/100000/5CE70F7B-90EA-E611-BEC9-002590E39D8A.root \
    datasetName=WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8 \
    outputFile=testMC_DoubleEG.root \
    channels=wz \
    isMC=1 \
    eCalib=1 \
    muCalib=0 \
    lheWeights=3 \
    globalTag=80X_mcRun2_asymptotic_2016_TrancheIV_v8 \
    $1
#    inputFiles=/store/mc/RunIISummer16MiniAODv2/WZTo3LNu_3Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/100000/14CC20E6-A1CF-E611-8950-0025905A6094.root \
#    datasetName=/WZTo3LNu_3Jets_MLL-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM \
