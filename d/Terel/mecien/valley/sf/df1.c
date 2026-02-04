inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/sf/"
#define TP this_player()

create_room(){

set_short("Dead Forest");
set_long(
"The forest here is dead and lifeless, as if some strange disease\n"
+ "cast itself down here or the very power of spring was halted. The buds\n"
+"of spring are shrivelled and dried to the branches.\n"
+"There is a small house here.\n"
);

add_item("trees", "They are mostly dead, some still have a bit of life though.\n");
add_item("buds", "The spring buds have died too.\n");

  add_cmd_item("house", "enter", "@@enter");
add_item("house", "It is a small stone house. Its door is oak. It\n" +
  "has a small window.\n");
add_item("door", "It is oak. A few claw marks are upon it.\n");
add_item("window", "It is too dirty to see through.\n");
  add_exit(PATH + "df", "west", 0);
   add_exit(PATH + "df2", "east", 0);
}
enter(){
tell_room(environment(this_player()), QCTNAME(this_player()) +
   " enters the stone house.\n", TP);
this_player()->catch_msg("You enter the house.\n");
this_player()->move_living("X", PATH + "house");
return 1;
}


