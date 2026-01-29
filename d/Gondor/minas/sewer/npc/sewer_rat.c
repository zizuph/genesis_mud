/*
 *  /d/Gondor/minas/sewer/npc/sewer_rat.c
 *
 *  This is a nasty little rat who's bretheren inhabit these sewers.
 *  It was necessary to create a file for him to make use of the
 *  clone_npcs function defined in /d/Gondor/std/room.c
 *
 *  Copyright (c) August 1999 by Cooper Sherry (Gorboth)
 *      based on code created by Christian Markus (Olorin)
 */

#pragma strict_types
inherit NPC_DIR + "rat";

#include "/d/Gondor/defs.h"

/* prototypes */
