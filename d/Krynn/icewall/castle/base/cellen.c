#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
set_short("Prison cell");
set_long(BS("You are in a prison cell. In the corner of the room is "
	+"a brittle skeleton. The roof looks unsafe and may fall "
	+"at the slightest move.",70));

add_item("skeleton",
"The skeleton disintegrates at your touch.\n");
add_item("cell",
"The cell doors seem to be unlocked.\n");

add_exit(BASE + "prisonn","west",0);
}
