/*
 * /d/Gondor/tolfalas/room/beach1.c
 *
 *  Palmer - 12 Aug 2006
 *  
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"



public void
create_gondor()
{
   set_short("a sandy beach on Tolfalas island, in the Bay of Belfalas");
   set_long(BSN("You are on a sandy beach on the island of Tolfalas. "+
         "The beach is quite narrow. Cliffs of black rocks impede your way into the island."));
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_exit(TOLFALAS_DIR + "room/beach25", "southwest", 0, 2);
   add_exit(TOLFALAS_DIR + "room/beach27", "north", 0, 2);
   add_item(({"rock","rocks","black rocks"}), BSN(
         "The cliff is composed of black rocks."));
   reset_room();
}

