inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/hforest/"

create_room(){
set_short("Haunted Forest");
set_long(
"This is the depths of a cold and dismal forest. Almost everything\n"
+"here is either dead or dying. The trees are black and lifeless.\n"
+"The wind is cold like winters bleak hand, arising to take the\n"
+"souls of those foolish to trespass in this morbid place.\n"
);

add_item("trees", "They are mostly decayed and lifeless, though some remain still that\n"
  +"have not perished.\n");
  add_prop(ROOM_I_LIGHT, -1);
add_exit(PATH + "mound", "east", 0);
add_exit(PATH + "forest6", "southwest", 0);
add_exit(PATH + "pine1", "northwest", 0);
add_exit(PATH + "pine2", "north", 0);
}
