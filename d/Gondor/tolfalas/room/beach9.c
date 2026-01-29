/*
 * /d/Gondor/tolfalas/room/beach1.c
 *
 *  Palmer - 12 Aug 2006
 *
 *
 *  Toby - 28 Aug 2006, removed BSN since I stumbled over it
 */

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
   set_long("You are on a sandy beach on the island of Tolfalas. "+
         "The beach is quite narrow. Cliffs of black rocks impede your "+
         "way into the island. A dark building is under construction on the cliff-top.");
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_exit(TOLFALAS_DIR + "room/beach8", "north", 0, 2);
   add_exit(TOLFALAS_DIR + "room/beach10", "south", 0, 2);
   add_exit("/d/Gondor/sea/sector_1_0_0/8_6_0", "west", 0, 2);
   add_item(({"building","dark building","cliff-top"}), 
         "The building looks almost complete. You can just make out workers at the base.");
   add_item(({"workers"}), 
         "The workers have dark skin and are possibly from Harad.");
   add_item(({"rock","rocks","black rocks","cliff"}), 
         "The cliff is composed of black rocks.");
   reset_room();
}

int
check_entry()
{
   
    if(!TP->query_wiz_level())
    {
        write("You can't make your way up the steep cliff.\nA Haradrim shouts from above, 'Go away!\n\nAn arrow wizzes by your head.\n\n");
        return 1;
    }
    return 0;
}

void
reset_room()
{
    object Troll;

    ::reset_room();
    if (!present("troll"))
        Troll = clone_npc(Troll, TOLFALAS_DIR + "npc/troll");
}

