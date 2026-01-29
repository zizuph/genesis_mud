 /*
 * File name: /d/Genesis/start/human/sparkle/docks/defs.h
 *
 * Description: Standard definitions for the rooms in
 *              this directory.
 *
 * Copyright (C) by Jakob 2000-03-22
 *
 */

#include "../defs.h"

// Directory definitions

#define THIS_DIR         SPARKLE + "docks/"
#define NPC_DIR          THIS_DIR + "npc/"
#define OBJ_DIR          THIS_DIR + "obj/"

// General definitions
#define DIRT    add_item(({"filth", "dirt"}), "A characteristical " +
						  "scrouge in Westport.\n")
#define WAVES   add_item(({"waves" }),"The waves are wild and rough.\n")
#define ROCKS   add_item(({"stones", "rocks" }),"The waves have polished " +
						 "the rock to a smooth and even surface.\n")




