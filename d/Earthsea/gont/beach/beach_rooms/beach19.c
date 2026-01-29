/*
 * Beach in Gont
 * By Finwe
 * April 1997
 */

#pragma strict_types 
#pragma no_clone

#include "default.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANDY;

public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");

    add_my_desc("This bar of sandy beach reaches out to the water. " +
      "In the next cove, you can spot a couple of longships. "+
      "There seems to be some activity to the northeast.\n");

    add_item (({"beach", "sandy beach"}),
      "The beach is warm and very inviting. The sun shines down "+
      "on the white sand warming it throughout the day.\n");
    add_item (({"ship", "ships"}),
      "The ships do not look like the ships the locals sail.\n");
    add_item("northeast",
      "You can see camp fires to the northeast.\n");

    add_exit(KARG_LANDING_DIR + "karg_landing01", "northeast");
    add_exit("beach18", "northwest");
}
