

inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mountains/"

create_room(){
   
   set_short("Dark Hole");
   set_long(
 "Dark and crude, this bleak hole smells of sulfur and other\n"
+"nauseating fumes. A film of black greasy substance coats the\n"
+"rock here.\n"
);
   
  add_item(({"film", "black grease", "grease", "substance", "greasy substance"}),
  "It is disgusting and of an unknown origin.\n");
  add_item("rock", "It is coated with a black film.\n");

add_exit(PATH + "t2", "up", 0);
   
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 1);
   
}


