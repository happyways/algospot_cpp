#!/bin/bash

if [ $# -ge 1 ]
then
  mkdir "$1"
  cp ./.make_exam/Makefile "./$1"
  cp ./.make_exam/main.cc "./$1"
  cp ./.make_exam/sample1.txt "./$1"
  cp ./.make_exam/sample2.txt "./$1"
  cp ./.make_exam/answer1.txt "./$1"
  cp ./.make_exam/answer2.txt "./$1"
else
  echo "---------사용법---------"
  echo "$0 {문제 이름}"
  echo "cd {문제 이름}"
  echo "sample1.txt, answer1.txt에 예제, 답 작성"
  echo "make 후 make test1"
  echo "------------------------"
fi
