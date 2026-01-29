/*
 * /d/Gondor/tolfalas/room/cove05.c
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
   set_short("in a cove of the island Tolfalas, in the Bay of Belfalas");
   set_long(&long_desc());

   add_exit(TOLFALAS_DIR + "room/cove04", "north", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove06", "east", 0, 2);

   cove_add_items();
   sky_add_items();
   beach_add_items();

   add_beach_tells();
   add_cove_tells();
   set_tell_time(300);
}

string
long_desc()
{
   return "On your west side a steep rocky hillside rise quite abrubptly " +
          "into a sheer cliff. The cliff, almost as if cut with a knife " +
          "from above, continues northward. East of here the hillside " +
          "subdues into jutting pieces of rock, as studs, sticking up " +
          "through the water surface. There is another of these " +
          "outcroppings a little way to the northeast. North of here " +
          "a docking place have been cut out of the cliff." + sky_desc() + "\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}
