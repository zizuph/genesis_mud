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
+"There is a white rock here.\n"
);

  add_item(({"white rock", "rock"}), "It is very large and has an eye inscribed on it.\n");
   add_item("eye", "It is red with a yellow slit.\n");
add_item("trees", "They are mostly decayed and lifeless, though some remain still that\n"
  +"have not perished.\n");
  add_prop(ROOM_I_LIGHT, -1);
add_exit(PATH + "forest2", "southwest", 0);
}
