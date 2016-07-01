#!/usr/bin/bash


pushd $CMSSW_BASE/src

if [ ! -d ./RecoEgamma ]; then
    echo "Setting up electron ID code"
    git clone https://github.com/Werbellin/RecoEgamma_8X RecoEgamma
else
    echo "RecoEgamma repository already initialized"
fi

if [ "$1" == "ZZ" ]; then
    bash ./UWVV/recipe/setupZZ.sh
fi

popd
