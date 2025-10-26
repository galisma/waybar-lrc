#!/usr/bin/env bash
set -xe
watchexec -r -c -w src -w test make run
