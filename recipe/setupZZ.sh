#!/usr/bin/bash


pushd $CMSSW_BASE/src

echo "Setting up ZZ matrix element stuff"
git clone https://github.com/cms-analysis/HiggsAnalysis-ZZMatrixElement.git ZZMatrixElement
pushd ZZMatrixElement
git checkout -b from-master master
popd

popd
