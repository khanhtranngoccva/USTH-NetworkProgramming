#!/bin/bash

w3m "$0" -x -dump | grep "$1"