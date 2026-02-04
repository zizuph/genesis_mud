/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "std/room";
#include <macros.h>
#include <stdproperties.h>
#define TP this_player()


#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
   set_short("Lower Hall");
   set_long(
   "Dark and crytic, this ancient halls spans out in its bleak\n"
+"and somber stone. A breeze of cool air runs through here, like a\n"
+"mysterious portent. The floor is damp and painted with silvery stars.\n"
+"A dark stone staircase leads up.\n"
   );
add_item("floor",
   "The floor is painted with a design of silvery stars.\n");
add_item("stars", "They are very silvery.\n");
   
   add_exit(PATH + "d_hall1", "west", 0);
    add_exit(PATH + "entry", "up", 0);
   
}


leave_inv(object ob, object to){
::leave_inv(ob, to);
if(MASTER_OB(to)=="/d/Terel/mecien/valley/guild/entry"){
tell_room(to, "A secret passage opens in one of the stone pillars.\n", TP);
write("You climb the stairs and exit through a secret door.\n");
}
}

