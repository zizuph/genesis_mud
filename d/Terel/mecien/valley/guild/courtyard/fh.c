/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

reset_room(arg){
}

create_room(){

object obj1;

set_short("Ancient Hall");
set_long(
"Wondrous in its archaic patterns, this cavernous hall looks like\n"
+"a royal chamber, its ceiling draped with glimmering stalactites\n"
+"streaked with silver, the walls imbedded with shining minerals and\n"
+"fancy stones. A mysterious and ancient majesty seems to emanate from\n"
+"the very stone itself, a pale glow illuminating everything.\n"
);

add_my_desc("\nA set of stairs winds upwards into darkness.\n\n");

obj1=clone_object("/d/Terel/mecien/valley/guild/eyisti");
obj1->move(this_object());

   add_item("walls", "They are coated with minerals and ornamentals stones.\n");
   add_item("minerals", "There are many kinds, all layered in the stone.\n");
  add_item("stones", "They are semi-precious stones, existing naturally\n"
   +"here amoungst the minerals and deep stone.\n");
   add_item("stairs", "They are cut into the stone and lead up.\n");
  add_item("ceiling", "It is covered with stalactites.\n");
   add_item("stalactites", "They hang from the ceiling and seems to contain\n"
   +"streaks of silver and other minerals.\n");


set_noshow_obvious(1);
add_exit(PATH + "hill", "up", 0);

}

