/*
 * /d/Gondor/tolfalas/room/cove06.c
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
   set_short("a rocky outcropping of a cove in the Sea of Belfalas");
   set_long(&long_desc());

   add_exit(TOLFALAS_DIR + "room/cove05", "west", 0, 2);

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
   return "This is a rocky outcropping of a cove in the Sea of Belfalas. " +
          "Looking west the cove lies protected of this outcropping and another " +
          "little a way north of here. The passage out to sea and into the cove " +
          "looks very narrow as if only a rowingboat could manage it." + sky_desc() +
          " The water, studded with sharp rocks, reach up almost to the knees " +
          "of a horse. It looks almost as it boil with strong undercurrents " +
          "making the water churn on the rocks.\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}


