/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

init(){
   add_action("swim", "swim");
   add_action("bathe", "bathe");
    add_action("bathe", "clean");
   add_action("dive", "dive");
  ::init();
}
swim(){
write("You swim about in the shallow waters of the bath.\n");
say(QCTNAME(this_player()) + " swims about in the bath waters.\n");
return 1;
}
bathe(){
write("You clean yourself in the purifying waters of the bath.\n");
say(QCTNAME(this_player()) + " bathes within the water.\n");
this_player()->add_prop("purified", 1);
return 1;
}
dive(){
write("The water is too shallow.\n");
return 1;
}

create_room(){
  set_short("Bath");
   set_long("Luminous and sparkling, this hallowed resevoir rests\n"
    + "enclosed within the low vaulted bath hall. The ceiling is\n"
    + "made of a soft white stone, the walls and floor of a\n"
    + "pale greenish onyx. Long vertical fistula channel water\n"
    + "in from the outside, the water colder but slowly warms.\n");
  add_exit("/d/Terel/mecien/valley/guild/antechamber", "out", 0);
}
