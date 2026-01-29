/* File:          /d/Khalakhor/ship/macdunn/pier8.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the pier for the Khalakhor to
 *                Sparkle ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 * Comments:
 * Ported to the new ship system by Tapakah, 05/2009
 */

#pragma save_binary
#pragma strict_types

#include "local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";

public int *
query_local_coords()
{
    return ({10, 13});
}

public void
create_pier()
{
    add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
        "into cala fasgadh","into the ocean","into ocean","into the water",
        "into water","harbour","cala fasgadh","water","off the pier",
        "off pier"}),({"jump","dive"}),"@@go_tide2");

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_exit(MACDUNN_DIR + "pier7", "west",0,0);
  add_pier_entry(MASTER_OB(TO), "Port Macdunn",
                 "Newbie Circle Line B");
  initialize_pier();
}

