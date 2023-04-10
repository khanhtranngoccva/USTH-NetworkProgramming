#!/bin/bash

search () {
  if [[ -z "$1" ]] || [[ -z "$2" ]]
  then
    1>&2 echo Missing arguments.
    return 1
  fi
  w3m "$1" -X -dump | grep "$2";
  return $?
}

search "$1" "$2"
