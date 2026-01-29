/*
 * /d/Gondor/tolfalas/room/beach1.c
 *
 *  Palmer - 12 Aug 2006
 *
 *  Toby - 18 Sept 2006: Modifed to support callouts and 
 *                       the description changed to support
 *                       the slope described in the cove.
 *  
 */
#pragma save_binary
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
   set_short("a sandy beach on Tolfalas island, in the Bay of Belfalas");
   set_long(&long_desc());

   //add_exit(TOLFALAS_DIR + "room/beach23", "west", 0, 2);
   add_exit(TOLFALAS_DIR + "room/beach25", "northeast", 0, 2);

   add_item(({"slope","steep slope","steep rocky slope"}), 
              "The slope rise rather quickly into black cliffs that impede " +
              "further travel around the island to the west.\n");

   beach_add_items();
   sky_add_items();
   add_beach_tells();
   set_tell_time(300);

   reset_room();
}


string
long_desc()
{
    return "On a rocky beach on Tolfalas Island, in the Bay of Belfalas." +
        sky_desc() + " The shoreline is rather narrow and to the west it " +
           "changes into a steep rocky slope and cliffs beyond impeding " +
           "your way further around the island.\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}
