/*
 * /d/Gondor/tolfalas/room/cove_cave05.c
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
inherit "/d/Gondor/tolfalas/lib/room_funcs.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"


public void
create_gondor()
{
   set_short("inside a cave on the island of Tolfalas");
   set_long("You in the middle of a vast cave where every sound seems to become " +
            "enhanced. The ceiling reach quite a few meters up. Where you stand " +
            "there are some crates and boxes stacked in a seeminly disorderly " +
            "way, almost as if thrown and scattered about.\n");
   
   /* make it harder to sneak due to echoes and constant light.
      10 is normal value.  */
   add_prop(ROOM_I_HIDE, 40);

   add_exit(TOLFALAS_DIR + "room/cove_cave01", "east", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave04", "south", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave03", "west", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave02", "north", 0, 2);

   add_item(({"box","boxes","crate","crates","small crate","smaller crates","small crates"}), 
         "There is nothing special about them.\n");

   cave_add_items();

   add_cave_tells();
   set_tell_time(300);
}


