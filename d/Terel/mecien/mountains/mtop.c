inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/mountains/"

create_room(){

set_short("Mountain Top");
set_long(
"Here, atop the icy mountain, the wind blows strong, clouds\n"
+"hang in the sky and lightning flashes through. A large stone\n"
+"is set into the ice here. A strange stone structure stands\n"
+"in seeming ruin to the north of here.\n"
);

add_item("ice", "It is everywhere.\n");
add_item("sky", "It is filled with clouds, lightning and mist.\n");
add_item("clouds", "They seem to wrap the mountain it their glory.\n");
add_item("stone", "It is round and set into the ice. There is some\n"
  + "engravings upon it.\n");
add_item(({"structure", "ruin", "stone structure", "shrine"}),
    "It is a bit to the north of here, on the edge of the mountain.\n");

add_cmd_item(({"stone", "engravings", "engraving"}), "read",
     "@@read");

add_prop("_can_summon_the_air", 1);
add_exit(PATH + "istairs2", "down", 0);
add_exit(PATH + "ishrine", "north", 0);

}

read(){

if(this_player()->query_skill(SS_LANGUAGE) > 10){
    write("The Wind has Glory in the ways of the Wise\n");
    write("The Clouds deliver all that is good to the Just\n");
    write("The Sky brings forth light to show Truth\n");
  return 1;
}

write("You cannot understand them, the words are obscure.\n");
return 1;

}

