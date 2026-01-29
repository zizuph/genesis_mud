/*
 * /d/Gondor/tolfalas/room/beach1.c
 *
 *  Palmer - 12 Aug 2006
 *  
 */
#pragma strict_types

//inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/tolfalas/lib/room_funcs.c";


public void
create_gondor()
{
   set_short("a sandy beach on Tolfalas island, in the Bay of Belfalas");
   set_long(BSN("You are on a sandy beach on the island of Tolfalas. "+
         "The beach is quite narrow. Cliffs of black rocks impede your way into the island. To the east is a newly constructed pier."));
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_exit(TOLFALAS_DIR + "room/pier", "east", 0, 2);
   add_exit(TOLFALAS_DIR + "room/beach2", "north", 0, 2);
   add_exit(TOLFALAS_DIR + "room/beach28", "south", 0, 2);
   add_item(({"pier","piers","water"}), BSN(
         "The pier you are standing on seems in perfect condition. "+
         "The ocean water is clear and blue and quite calm. The beach leads to a cliff composed of large rocks making passage to the inner island impossible."));
   add_item(({"rock","rocks","black rocks"}), BSN(
         "The cliff is composed of black rocks."));
   reset_room();
}

