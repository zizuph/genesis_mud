inherit "/std/room";
#include <ss_types.h>

create_room(){
  set_short("Path End");
  set_long("A small path ends here and fades away into the\n" +
          "deep foliage. The path leads west.\n");
add_cmd_item("foliage", "enter", "@@enter");
add_item("foliage", "It is very thick, but perhaps passable.\n");
  add_exit("/d/Terel/mecien/valley/path3", "west", 0);
}

enter(){
if((this_player()->query_stat(SS_DEX))>random(100)){
this_player()->move_living("into the foliage", "/d/Terel/mecien/valley/bp");
 return 1;
}
write("You were repelled by the thick foliage.\n");
return 1;
}

