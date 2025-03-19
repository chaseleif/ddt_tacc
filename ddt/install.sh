#! /usr/bin/env bash

# https://www.linaroforge.com/download-documentation

arch="linux-x86_64"
#arch="linux-aarch64"
#arch="macos-x86_64"
#arch="windows-x86_64"

# latest (too new)
version="24.1.2"
# stampede3 has 23.1.2
version="23.1.2"
# ls6 has 23.0.1
# frontera has 23.0.1, 20.0.2, 19.0.5
#version="23.0.4"

if [[ "$arch" =~ linux.* ]] ; then
  linaro="linaro-forge-$version-$arch"
else
  linaro="linaro-forge-client-$version-$arch"
fi

echo "$linaro"

url="https://downloads.linaroforge.com/$version/$linaro"

if [[ "$arch" =~ linux.* ]] ; then
  [ ! -f "$linaro.tar" ] && wget "$url.tar"
elif [[ "$arch" =~ macos.* ]] ; then
  [ ! -f "$linaro.dmg" ] && wget "$url.dmg"
else
  [ ! -f "$linaro.exe" ] && wget "$url.exe"
fi

if grep -q "$version" "$arch.md5" ; then
  if ! md5sum -c "$arch.md5" ; then
    echo "Checksum verification failed"
    exit 1
  fi
else
  echo "Unable to check checksum"
fi

if [[ ! "$arch" =~ linux.* ]] ; then
  echo -n "Use $linaro"
  if [[ "$arch" =~ macos.* ]] ; then
    echo -n ".dmg "
  else
    echo -n ".exe "
  fi
  echo "to complete installation"
  exit 0
fi

[ -d "$linaro" ] && rm -rf "$linaro"
tar -xf "$linaro.tar"

if [ -d install/ ] ; then 
  rm -rf install/*
else
  mkdir install
fi

cd "$linaro" || { echo "unable to cd to $linaro" ; exit 1 ; }

./textinstall.sh --accept-licence ../install

cd ../
rm -rf "${linaro:?}/" "$linaro.tar"

echo "add \"$(pwd)/install/bin\" to PATH to use ddt and map"

