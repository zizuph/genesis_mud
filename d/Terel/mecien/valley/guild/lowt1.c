/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/"
create_room(){

set_short("Dark Tunnel");
set_long(
"This gothic tunnel, natural in appearance, seems to lead into\n"
+"a nothingness of darkness. The rock here is mottled, with green\n"
+"and black stone. Small stalactites of greenish stone protrude\n"
+"from the roof of the cavern.\n"
);

add_prop(ROOM_I_LIGHT, 0);

add_item("rock", "It is mottled green and blac, natural in appearance.\n");
add_item("roof", "It has sharp greenish stone stalactites that hang\n"
+"down from it.\n");
add_item("stalactites", "They seem secure. There is some kind of image\n"
+"carved into the midst of them.\n");
add_item("image", "It is a hand within a circle. The hand has some kind\n"
+"of writing upon it.\n");
add_item("writing", "It is arcane.\n");
add_cmd_item("writing", "read", "When we call to the earth, all things will change at our command!\n");

add_exit(PATH + "lowt2", "north", 0);
add_exit(PATH + "ss3", "south", 0);

}

