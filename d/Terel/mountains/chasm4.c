

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

create_room(){

set_short("Icy Chasm");
set_long(
"The wind howls through the bottom of this icy chasm. All about\n"
+"long icicles hang from the chasm walls. A huge staircase has\n"
+"cut into the ice and it spirals up into the heights. A small\n"
+"pass leads north and south.\n"
);

add_item(({"stairs", "staircase"}), "They climb the mountain and "
   + "seem to lead to the clouds themselves.\n");
add_item("icicles", "They hang from the chasm walls.\n");
add_item("walls", "They are icy and its impossible to climb them.\n");
add_exit("/d/Terel/mountains/chasm5", "north", 0);
add_exit("/d/Terel/mountains/chasm3", "south", 0);
add_exit("/d/Terel/mountains/istairs1", "stairs", 0);

}

