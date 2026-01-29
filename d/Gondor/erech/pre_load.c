/*
 * pre_load.c
 * By Skippern
 * December 2000
 *
 */
#pragma strict_types
#pragma save_pinary

#include "erech.h"

inherit "/std/room.c";
inherit "/lib/unique.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_room();

/* Global variables */
object ob;

/*
 * Function name:    create_room()
 * Definition   :    Creates the room.
 */
public void
create_room()
{
    set_short("Preload room");
    set_long("This is just a room for pre loading.\n");    
  
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(E_FIELD + "G4.c", "field", 0,0,1);

    ob = clone_object(E_NPC + "hermit");
    ob->move_living("field", E_FIELD+"G4", this_object());

    reset_room();
}

void
reset_room()
{
    ob=clone_unique(E_NPC + "hermit.c", 1);
    ob->move_living("field", E_FIELD+"G4.c", this_object());
}
