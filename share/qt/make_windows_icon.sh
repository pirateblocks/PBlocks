#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/PirateBlocks.ico

convert ../../src/qt/res/icons/PirateBlocks-16.png ../../src/qt/res/icons/PirateBlocks-32.png ../../src/qt/res/icons/PirateBlocks-48.png ${ICON_DST}
