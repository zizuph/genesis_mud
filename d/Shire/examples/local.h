/*
 *  Local defines for this directory and it's sub directories
 *
 */

//  Include the Shire defines
#include "/d/Shire/sys/defs.h"

//  Define the root directory
#define EXAMPLE_DIR  "/d/Shire/examples/"

//  Now we define the directories for all types of objects (npcs, weapons, etc)
#define EXAMPLE_ARM  EXAMPLE_DIR + "arm/"
#define EXAMPLE_WEP  EXAMPLE_DIR + "wep/"
#define EXAMPLE_OBJ  EXAMPLE_DIR + "obj/"
#define EXAMPLE_NPC  EXAMPLE_DIR + "npc/"

// Now we define the directories in which all the rooms are contained
#define EXAMPLE_FOREST  EXAMPLE_DIR + "forest/"
#define EXAMPLE_ROAD    EXAMPLE_DIR + "road/"
#define EXAMPLE_TOWN    EXAMPLE_DIR + "town/"

// Now we define the base file (must be full pathname)
#define FOREST_BASE     "/d/Shire/examples/std/forest_base.c"
#define TOWN_BASE       "/d/Shire/examples/std/town_base.c"
#define ROAD_BASE       "/d/Shire/examples/std/road_base.c"

/*  Ok the reason we set things up this way is because it makes
 *  all the files easier to read and easier for you to set up your
 *  project.  Also it makes this whole directory "portable" If you
 *  should ever want to move this whole area to another root directory 
 *  You only have to change a few lines in these defines not every
 *  single file in all your subdirectories.
 *  -Igneous-
 */
