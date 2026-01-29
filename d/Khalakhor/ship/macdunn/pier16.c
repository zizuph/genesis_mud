/* File:          /d/Khalakhor/ship/macdunn/pier16.c
 * Creator:       Damaris
 * Date:          03/2001
 * Modifications:
 * Purpose:       This is one of the piers.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 *                /d/Khalakhor/ship/macdunn/crate.c
 * Comments:
 * Ported to the new ship system by Tapakah, 04/2009
 */

#pragma save_binary
#pragma strict_types

#include "local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";

object crate;

public int *
query_local_coords()
{
    return ({9, 17});
}

public void
create_pier()
{
  add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
                 "into cala fasgadh","into the ocean","into ocean","into the water",
                 "into water","harbour","cala fasgadh","water","off the pier",
                 "off pier"}),({"jump","dive"}),"@@go_tide2");
  
  add_exit(MACDUNN_DIR + "pier15", "west",0,0);
  
  add_pier_entry(MASTER_OB(TO), "Port Macdunn", "Cabotage to Tabor Sogh");
  initialize_pier();
}
