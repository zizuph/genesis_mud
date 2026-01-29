/*
 * /d/Gondor/tolfalas/room/pier.c
 *
 *  Pier for ship from Tolfalas island to the river Poros
 *  Other side is /d/Gondor/ithilien/poros/pier2
 *  Captain's name is Feldon
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
   set_short("a newly built pier on Tolfalas island, in the Bay of Belfalas");
   set_long(BSN("You are on a newly constructed pier in a quiet bay on the island of Tolfalas."));
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_exit(TOLFALAS_DIR + "room/beach1", "west", 0, 2);
   add_item(({"pier","piers","water","river"}), BSN(
         "The pier you are standing on seems in perfect condition. "+
         "The ocean water is clear and blue and quite calm. The beach is covered in large rocks making passage impossible."));
   reset_room();
}

