inherit "std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/mountains/"


create_room(){
set_short("Dark Passage");
set_long(
"A roughly hewn passage in stone, completely bare.\n");

add_prop(ROOM_I_LIGHT, 0);
add_exit(PATH + "dpas2", "west", -12);
add_exit(PATH + "archcham", "north", 0);

}
