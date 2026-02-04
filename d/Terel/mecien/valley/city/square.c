inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

#define PATH "/d/Terel/mecien/valley/city/"

create_room(){

set_short("Square");
set_long(
"Paved with cobblestone, this dismal square opens wide with its\n"
+"haunting skyline filled with shadowed builings, clouded in a mist\n"
+"and visited by sudden drafts. A large fountain is centered in\n"
+"the midts of the square, a steady stream of water issues\n"
+"forth from its top.\n"
);

   add_cmd_item("water", "drink", "@@fdrink");
  add_item("cobblestone", "It covers the street nicely.\n");
add_item("buildings", "They line the many streets.\n");
add_item("fountain", "It is huge stone fountains.\n");
add_item("water", "It does not look too clean.\n");
add_exit(PATH + "street3", "south", 0);
add_exit(PATH + "street4", "north", 0);
add_exit(PATH + "street7", "west", 0);
add_exit(PATH + "street11", "east", 0);
add_prop(OBJ_I_CONTAIN_WATER, 1);

}

fdrink(string str){
  TP->catch_msg("Other than being a bit dirty, it tastes fine.\n");
   tell_room(ENV(TP), QCTNAME(TP) + " drinks from the fountain.\n", TP);
return 1;
}

