inherit "/std/room";
#include <stdproperties.h>

object *ravens_arr;

reset_room(){

  while(sizeof(ravens_arr) < 3)
   ravens();
}

ravens() {
  object ob;
   ob=clone_object("/d/Terel/mecien/valley/guild/raven");
  ob->move_living("xx", this_object());
  
  if (!ravens_arr)
       ravens_arr = ({ ob });
  else
      ravens_arr += ({ ob });
}

create_room(){
set_short("Hilltop");
set_long(
"This is a small hill, rising just a bit over the forest. It stands\n"
+"like an advent, a symbol of spring. All about grass growing up with\n"
+"wondrous life. In the middle of the hill grows a small tree.\n"
+"The mountains rise up to the west and north.  A set of stairs has\n"
+"been cut into the mountains, it leads up to the west where only the\n"
+"clouds can be seen dancing upon the mountain steppes.\n"
);
add_item(({"tree","small tree"}),
"Although it is alive, it is barren. It stands here like an enigma.\n");

add_exit("/d/Terel/mecien/valley/path5", "north", 0);
add_exit("/d/Terel/mecien/valley/guild/stair1", "west", 0);
reset_room();
}
