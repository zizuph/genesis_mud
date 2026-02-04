inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("City Hall");
set_long(
"This massive hall is made from pine, its arched doorways and\n"
+"floor of bright oak. Pictures cover the walls, as do tapestries\n"
+"and shields. A set of stairs leads up into the tower, in a spiral\n"
+"that goes up to the bell. A large desk stands here, upon it a\n"
+"old register.\n"
);

add_cmd_item("register", "sign", "@@sign");
add_cmd_item("register", "read", "@@readr");
add_item("register", "It is an old dusty book.\n");
add_item("tower", "It stretched upwards, a spiral staircase follows\n"
  + "its ascent. A bell is at the top.\n");
add_item("bell", "At the top of the tower. It looks bronze.\n");
add_item("pictures", "They are former alderman and leaders of the city.\n");
add_item("shields", "They bear emblems of the nobles of the city.\n");
add_item("stairs", "They lead up into the tower in a spiral.\n");
add_item("tapestries", "They are simply decorative.\n");

add_exit(PATH + "street7", "south", 0);
add_exit(PATH + "tower", "up", "@@closed");

clone_object(PATH + "board")->move(this_object());

}

sign(){

}

read(){
 write("You look through the register.\n");
return 1;
}

closed(){
write("It is closed.\n");
return 1;
}

