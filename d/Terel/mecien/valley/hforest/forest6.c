inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/hforest/"

create_room(){
set_short("Haunted Forest");
set_long(
"This is the depths of a cold and dismal forest. Almost everything\n"
+"here is either dead or dying. The trees are black and lifeless.\n"
+ "A gigantic dead oak stands here.\n");

add_item("oak", "It is a gigantic dead oak tree, still standing,\n"
  + "but partly rotted and a huge hole has been made in it.\n");
add_item("hole", "It is a large hole in the dead oak. It must have been\n"
  +"made by some creature.\n");
add_item("trees", "They are mostly decayed and lifeless, though some remain still that\n"
  +"have not perished.\n");
  add_prop(ROOM_I_LIGHT, -1);
add_exit(PATH + "forest4", "northeast", 0);
add_exit(PATH + "forest5", "southeast", 0);
  add_cmd_item("hole", "enter", "@@enter");
}

enter(){
write("You enter the dark hole of the dead oak.\n");
this_player()->move_living("into the hole in the dead oak", PATH + "hole");
return 1;
}

