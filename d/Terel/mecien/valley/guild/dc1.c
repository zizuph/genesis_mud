inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"
create_room(){

set_short("Dark Cavern");
set_long(
"A craggy dark cavern, roughly hewn.\n");

add_prop(ROOM_I_LIGHT, 0);
add_exit(PATH + "dc2", "west", 0);
add_exit(PATH + "ss3", "east", 0);


}
