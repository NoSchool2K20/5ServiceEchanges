#!/bin/sh

setup_git() {
  git config --global user.email "travis@travis-ci.org"
  git config --global user.name "Travis CI"
}

upload_files() {
  git remote add clever https://$CLEVER_TOKEN:$CLEVER_SECRET@push-par-clevercloud-customers.services.clever-cloud.com/$CLEVER_APP_ID.git
  git push -u clever master 
}

setup_git
upload_files