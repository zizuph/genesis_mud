

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

create_room(){

set_short("Icy Chasm");
set_long(
"The wind howls through the bottom of this icy chasm. All about\n"
+"long icicles hang from the chasm walls. The chasm narrows to\n"
+"north and widens to the southwest.\n"
);

add_item("icicles", "They hang from the chasm walls.\n");
add_item("walls", "They are icy and its impossible to climb them.\n");
add_exit("/d/Terel/mountains/chasm4", "north", 0);
add_exit("/d/Terel/mountains/chasm2", "southwest", 0);

}

