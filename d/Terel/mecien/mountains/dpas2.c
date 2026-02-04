inherit "std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/mountains/"


create_room(){
set_short("Dark Passage");
set_long(
"A roughly hewn passage in stone, completely bare.\n");

add_prop(ROOM_I_LIGHT, 0);
add_exit(PATH + "dpas1", "southwest", -12);
add_exit(PATH + "dpas3", "east", -12);

}
