/*
 * /d/Gondor/tolfalas/room/cove03.c
 *
 *  Toby - 28 Aug 2006
 *
 *  Northern outcropping in the secret cove on Tolfalas
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

public string long_desc();

public void
create_gondor()
{
   set_short("before a sheer cliff on the island of Tolfalas, in the Bay of Belfalas");
   set_long(&long_desc());

   add_prop(ROOM_I_NO_CLEANUP,1);

   add_exit(TOLFALAS_DIR + "room/cove04", "southwest", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove02", "east", 0, 2);

   cove_add_items();
   sky_add_items();
   beach_add_items();

   add_beach_tells();
   add_cove_tells();
   set_tell_time(300);

   clone_object(TOLFALAS_DIR + "obj/cove_door_outside.c")->move(TO);

   reset_room();
}

string
long_desc()
{
   return "You stand alongside a sheer cliff that runs in a general " +
          "northeast to southwest direction. It is as if the cliff has been " +
          "cut with a knife from above. A few meters up there are " +
          "grass growing on top of the cliff but hanging over the edge. " +
          "You can also make out the foliage of some trees leaning precariously " +
          "out over the edge." + sky_desc() + " "; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}
