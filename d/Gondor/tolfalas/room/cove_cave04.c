/*
 * /d/Gondor/tolfalas/room/cove_cave04.c
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
            "This is the southern part of the cave and along the wall stand " +
            "sturdy working tables. In the southmost part, almost as a corner " +
            "but yet not, stand a big anvil, with a cold furnace next to it, " +
            "complete with bellow and water barrel. Smoke, should the furnace " +
            "be lit, would be lead out by the metal pipe jutting out of the " +
            "wall above it.\n");
 
   /* make it harder to sneak due to echoes and constant light.
      10 is normal value.  */
   add_prop(ROOM_I_HIDE, 40);

   add_exit(TOLFALAS_DIR + "room/cove_cave03", "northwest", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave05", "north", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave01", "northeast", 0, 2);

   add_item(({"table","sturdy table","tables","sturdy tables"}), 
         "The sturdy tables look well used and there are some boxes and smaller " +
         "crates resting on top of them and below.\n");
   add_item(({"box","boxes","crate","crates","small crate","smaller crates","small crates"}), 
         "There is nothing special about them.\n");
   add_item(({"anvil","big anvil","large anvil"}), 
         "It looks like a quite regular anvil the smiths of the realms use.\n");
   add_item(({"furnace","cold furnace"}), 
         "The smiths furnace rests cold next to the large anvil.\n");
   add_item(({"bellow"}), 
         "There is nothing out of the ordinary with the bellow. It is used to blow air " +
         "onto the furnace that now rests cold.\n");
   add_item(({"barrel","water barrel"}), 
         "The water barrel is empty of water.\n");
   add_item(({"pipe","metal pipe"}), 
         "The pipe, used to lead out smoke when the smith is at work, connects into the " +
         "wall and dissapears.\n");


   cave_add_items();

   add_cave_tells();
   set_tell_time(300);
}


