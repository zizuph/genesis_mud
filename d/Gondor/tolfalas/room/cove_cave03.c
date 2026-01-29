/*
 * /d/Gondor/tolfalas/room/cove_cave03.c
 *
 *  Toby - 28 Aug 2006
 *
 *  The cave in the secret cove on Tolfalas
 *  'home' for the rowboat of the Black Numenorean
 *
 *  Modification log:
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
inherit "/d/Gondor/tolfalas/lib/room_funcs.c";


public void
create_gondor()
{
   set_short("inside a cave on the island of Tolfalas");
   set_long("You are inside a vast cave where every sound seems to become " +
            "enhanced. The walls glimmer softly from the many torches lit " +
            "giving the cave its luminous light level. The ceiling reaching " +
            "up a few meters and the opposite wall quite a few paces ahead. " +
            "Along the wall in this western part of the cave stand sturdy " +
            "tables. There is also a tall table with chairs placed around it. " +
            "On top of the table stand pots and plates, as if left from a " +
            "recent meal.\n");

   /* make it harder to sneak due to echoes and constant light.
      10 is normal value.  */
   add_prop(ROOM_I_HIDE, 40);

   add_exit(TOLFALAS_DIR + "room/cove_cave02", "northeast", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave05", "east", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave04", "southeast", 0, 2);

   add_item(({"table","sturdy table","tall table","tall sturdy table"}), 
         "It is a rather sturdy tall table with chairs placed all around it. Atop of it " +
         "stand pots and plates as if recently left from a dining. It is placed a good " +
         "part away from the wall, moreto the center of the cave.\n");
   add_item(({"tables","sturdy tables"}), 
         "The sturdy tables look well used and there are some boxes and smaller " +
         "crates resting on top of them and below.\n");
   add_item(({"box","boxes","crate","crates","small crate","smaller crates","small crates"}), 
         "There is nothing special about them.\n");
   add_item(({"chair","chairs","sturdy chair","sturdy chairs"}), 
         "There is nothing special about the chairs. They are just plain, quite sturdy, " +
         "chairs with a low back.\n");
   add_item(({"pot","pots","plate","plates"}), 
         "The pots and plates have been emptied of all food. The plates show traces of " +
         "food as do the pots, they are obviously not cleaned yet.\n");

   cave_add_items();

   add_cave_tells();
   set_tell_time(300);
}


