/*
 * /d/Gondor/tolfalas/room/cove_cave01.c
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
   set_long("You are inside a vast cave where every sound seems to become " +
            "enhanced. The walls glimmer softly from the many torches lit " +
            "giving the cave its luminous light level. The ceiling reaching " +
            "up a few meters and the opposite wall quite a few paces ahead. " +
            "Along the wall in this eastern part of the cave stand sturdy " +
            "tables. ");

   /* make it harder to sneak due to echoes and constant light.
      10 is normal value.  */
   add_prop(ROOM_I_HIDE, 40);

   add_exit(TOLFALAS_DIR + "room/cove_cave02", "northwest", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave05", "west", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_cave04", "southwest", 0, 2);

   add_item(({"table","sturdy table","tables","sturdy tables"}), 
         "The sturdy tables look well used and there are some boxes and smaller " +
         "crates resting on top of them and below.\n");
   add_item(({"box","boxes","crate","crates","small crate","smaller crates","small crates"}), 
         "There is nothing special about them.\n");

   cave_add_items();

   clone_object(TOLFALAS_DIR + "obj/cove_door_inside.c")->move(TO);

   add_cave_tells();
   set_tell_time(300);
}




