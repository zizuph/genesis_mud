/* File:          /d/Khalakhor/ship/macdunn/pier3.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is one of the pier rooms.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

object bird1,bird2;

public int *
query_local_coords()
{
    return ({9, 11});
}

public void
reset_pier()
{
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
        "off pier"}),({"jump","dive"}),"@@go_tide2");

    add_exit(MACDUNN_DIR + "pier2", "west",0,0);
    add_exit(MACDUNN_DIR + "pier1", "north",0,0);
    add_exit(MACDUNN_DIR + "pier4", "east",0,0);
    add_exit(MACDUNN_DIR + "pier5", "south",0,0);

    reset_pier();
}
