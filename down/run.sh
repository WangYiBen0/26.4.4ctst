#!/usr/bin/env bash

if [[ $# == 1 ]]; then
  echo "checking $1, input $1.in, output $1.out, expected $1.ans"
elif [[ $# == 2 ]]; then
  echo "checking $1, input $2.in, output $2.out, expected $2.ans"
  cp $2.in $1.in
  cp $2.ans $1.ans
else
  echo "invalid arg"
fi

time ./$1

diff $1.out $1.ans -Z

if [[ $? != 0 ]]; then
  echo "DIFF"
  exit 1
fi
