/**********************************************************************
 * - pier10.c                                                       - *
 * - Ship from Pelagar docs here.                                   - *
 * - Orginial code By Teth 09/6/1997 - Faerie used to docked here.  - *
 * - Modified by Damaris@Genesis 01/2006                            - *
 * - Prepared a teaser for Mariners landfall - Tapakah, 10/2021     - *
 **********************************************************************/

#pragma strict_types

#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";

object sign;
object bird;

int *
query_local_coords ()
{
  return ({8, 15});
}

void
add_stuff ()
{
	seteuid(getuid(this_object()));
	if (!sign) {
		sign = clone_object("/d/Khalakhor/ship/macdunn/psign");
		sign->move(this_object());
	}
}

string
extra_long ()
{
  add_item(({"crates", "boxes", "materials", "construction materials"}),
           "You read a label saying <MARINERS OF GENESIS> on some.\n");
  return
    "You notice some crates and construction materials have been piled "+
    "up along the side of the pier.\n";
}

void
create_pier ()
{
	add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
                 "into cala fasgadh","into the ocean","into ocean",
                 "into the water", "into water","harbour","cala fasgadh",
                 "water","off the pier", "off pier"}),
               ({"jump","dive"}), go_tide1);
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MACDUNN_DIR + "pier11", "east",0,0);
  
  bird = clone_object(COM_WILDLIFE + "gull");
  bird->set_restrain_path(MACDUNN_DIR);
  bird->move(this_object(), 1);
  
  add_stuff();
}
