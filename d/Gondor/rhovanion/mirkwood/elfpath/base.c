/*
 * /d/Gondor/rhovanion/mirkwood/elfpath/base.c
 *
 * Base room for the elf path in Mirkwood.
 *
 */
 
#include "../defs.h"

inherit MIRKWOOD_STD_DIR + "room";
inherit MIRKWOOD_LIB_DIR + "movement";

#include <macros.h>
#include "descriptions.c"
#include "items.c"

void create_mirkwood_elfpath_room()
{
    set_short("You are wandering somewhere " + VBFC("location_desc") + 
        " of the legendary Mirkwood forest");
	add_location_long();
    add_tree_long(); 
    add_emo_long();  
    setup_mirkwood_herbs();

    
    set_add_all_rooms();
    set_movement_difficulty(70); 
}

nomask void create_mirkwood_room()
{
    create_mirkwood_elfpath_room();
}