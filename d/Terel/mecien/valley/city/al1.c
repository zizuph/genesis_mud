inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Alley");
set_long(
"A dark alley running between many old and crumbling stone buildings,\n"
+"it twists and runs through the darkness seeking light. Water coats the\n"
+"way, dirty and stagnant.\n"
);

add_prop(ROOM_I_LIGHT, 0);

add_exit(PATH + "street8", "north", 0);

}

