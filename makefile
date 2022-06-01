#!/bin/bash

HALIDE_DISTRIB_PATH := ${HOME}/Applications/Halide/Halide-14.0.0/build/install/

#"Adams2019" "Mullapudi2016" "Li2018"
AUTOSCHEDULER := Mullapudi2016
#"libautoschedule_adams2019" "libautoschedule_mullapudi2016" "libautoschedule_li2018"
LIB_AUTOSCHEDULER := $(HALIDE_DISTRIB_PATH)/lib/libautoschedule_mullapudi2016.so

TARGET := arm-64-android-armv81a
GEN_FOLDER := build_android/gen_files/
GENERATOR_BIN := build/bin/

FiltersManual :=  
FiltersAuto := halide_gaussian_blur

FiltersManual := $(foreach n, $(FiltersManual), ${GEN_FOLDER}/$(n).a)
FiltersAuto := $(foreach n, $(FiltersAuto), ${GEN_FOLDER}/$(n).a)

all: $(FiltersManual) $(FiltersAuto)

# manual
$(FiltersManual): $(GEN_FOLDER)/%.a : ${GENERATOR_BIN}/%.generator
	@echo -- $(subst .a, , $(notdir $@))
	@$< -g $(subst .a, , $(notdir $@)) -o $(GEN_FOLDER) target=$(TARGET) 

# auto
$(FiltersAuto): $(GEN_FOLDER)/%.a : ${GENERATOR_BIN}/%.generator
	@echo -- $(subst .a, , $(notdir $@))
	@$< -g $(subst .a, , $(notdir $@)) -o $(GEN_FOLDER) target=$(TARGET) auto_schedule=true -p $(LIB_AUTOSCHEDULER) -s $(AUTOSCHEDULER)