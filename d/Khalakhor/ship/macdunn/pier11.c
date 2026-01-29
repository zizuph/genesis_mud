/* File:          /d/Khalakhor/ship/macdunn/pier11.c
 * Creator:       Teth
 * Date:          November 28, 1997
 * Modifications:
 * Purpose:       This is one of the piers.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 *                /d/Khalakhor/ship/macdunn/crate.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";
#include "local.h"
#include <stdproperties.h>

object crate;

public int *
query_local_coords()
{
    return ({9, 15});
}

public void
create_pier()
{
    add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
        "into cala fasgadh","into the ocean","into ocean","into the water",
        "into water","harbour","cala fasgadh","water","off the pier",
        "off pier"}),({"jump","dive"}),"@@go_tide2");

    add_exit(MACDUNN_DIR + "pier10", "west",0,0);
    add_exit(MACDUNN_DIR + "pier9", "north",0,0);
    add_exit(MACDUNN_DIR + "pier12", "east",0,0);
    add_exit(MACDUNN_DIR + "pier13", "south",0,0);

    crate = clone_object(MACDUNN_DIR + "crate");
    crate->move(this_object(), 1);
}
