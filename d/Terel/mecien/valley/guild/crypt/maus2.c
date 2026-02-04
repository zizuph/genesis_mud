/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include "defs.h"
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/crypt"
#define TP this_player()


create_room(){
object door;

set_short("Ancient Mausoleum");
set_long(
"This is the foyer of some ancient mausoleum. The walls are fine cut " +
"stone, gray in color. The floor is inscribed with words. A curtain of blue " +
"leads west, separating this chamber with what seems to be the main hall.\n"
);
add_cmd_item("floor", "read", "The walk from life to death is but one step.\n");
add_item("floor", "It is stone and inscribed with some words.\n");
add_item("curtain", "It is bright blue and forms a barrier between this chamber and the next.\n");
  add_item("ceiling", "It is vaulted, very dark and inscrived with symbols.\n");
  add_item(({"runes", "symbols"}), "They are runes and symbols of the dead.\n");

   add_exit(PATH+ "/maus3", "west", "@@check");

door=clone_object(PATH + "/mdoor2");
door->move(this_object());

}

check(){
  if(TP->query_skill(130005) < 500){
  TP->catch_msg("The ancient song of death arises in your ears and you fear to go within!\n");
  say(QCTNAME(TP) + " reaches for the curtain and is gripped with fear.\n");
  return 1;
   }

}

