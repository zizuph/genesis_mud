/* File:          /d/Khalakhor/ship/macdunn/pier1.c
 * Creator:       Teth
 * Date:          September 6, 1997
 * Modifications: Teth, December 8, 1997, added cross.
 *                Teth, December 9, 1997, added birds.
 * Purpose:       This is one of the pier rooms.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/cross.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

object crux, bird1, bird2;

public int *
query_local_coords()
{
    return ({9, 10});
}

public void
reset_pier()
{
    if (!crux)
    {
        crux = clone_object(MACDUNN_DIR + "cross");
        crux->move(this_object(), 1);
    }
    if (!bird1)
    {
        bird1 = clone_object(COM_WILDLIFE + "gull");
        bird1->set_restrain_path(MACDUNN_DIR);
        bird1->move(this_object(), 1);        
    }
    if (!bird2)
    {
        bird2 = clone_object(COM_WILDLIFE + "gull");
        bird2->set_restrain_path(MACDUNN_DIR);
        bird2->move(this_object(), 1);
    }
}

public void
create_pier()
{
    add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
        "into cala fasgadh","into the ocean","into ocean","into the water",
        "into water","harbour","cala fasgadh","water","off the pier",
        "off pier"}),({"jump","dive"}),"Jumping off the " +
      "pier here would land you in the sharp rocks below! " +
      "Suicide is not an option here!\n");
    add_item(({"rocks","sharp rocks"}),"The sharp rocks below " +
      "would slice and kill anyone who jumped onto them.\n");

    add_exit("/d/Khalakhor/se_speir/port/room/road_9_9", "north");
    add_exit(MACDUNN_DIR + "pier3", "south",0,0);

    reset_pier();
}


