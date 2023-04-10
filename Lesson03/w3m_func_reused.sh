#!/bin/bash

search () {
  if [[ -z "$1" ]] || [[ -z "$2" ]]
  then
    1>&2 echo Missing arguments.
    return 1
  fi
  echo "$1"
  w3m "$1" -X -dump | grep -i "$2";
  echo "______________"
  return $?
}

declare -a array=( "www.nytimes.com" "www.mirror.co.uk" "www.daily-sun.com" "www.washingtonpost.com" "www.chicagotribune.com" "www.theguardian.com/us" )
for variable in "${array[@]}"
do
  search "$variable" "$1"
done


