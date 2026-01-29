/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

/* 
 * This file contains handy definitions and macros used 
 * throughout the dwarven code. 
 */

#include <stdproperties.h>

#define NF(message)	notify_fail(message)
#define TP		this_player()
#define ETP		environment(this_player())
#define TI		this_interactive()
#define TO		this_object()
#define ETO		environment(this_object())
#define BS(message)	break_string(message, 75)
#define E(x)            environment(x)

#define I add_prop(ROOM_I_INSIDE,1)

#define D_DIR		"/d/Genesis/start/dwarf/"
#define D_OBJ		D_DIR + "obj/"
#define D_MON		D_DIR + "monster/"
#define D_L1		D_DIR + "level_1/"
#define D_L2		D_DIR + "level_2/"

#define LVL3            D_DIR +"lvl3/"
#define LVL1            D_DIR +"lvl1/"
#define LVL2            D_DIR +"lvl2/"

#define ANTHANDLER (D_MON+"anthandler.c")

/* a property for the ants */

#define ANTSCENT  "_an_ant_walked_from_"
