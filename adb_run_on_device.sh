#!/bin/bash

set -e

DEVICE_PATH=/data/local/tmp/
adb shell mkdir -p ${DEVICE_PATH}

adb push build_android/bin/test2 ${DEVICE_PATH}
adb shell chmod +x ${DEVICE_PATH}/test2
adb shell ${DEVICE_PATH}/test2