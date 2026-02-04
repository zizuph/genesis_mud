inherit "/std/room";
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/frost/local.h"

object ogre;

reset_room(){
 int n;
 if(!ogre){
  ogre = clone_object("/d/Terel/mecien/mountains/ogre");
  ogre->move(TO);
  ogre->set_aggressive(1);
}
 if(!present("giant")) {
     n = 3;
     call_out("giants", 1, n);
     }
}

giants(n) {
  object ob;
  ob=clone_object(PATH + "mon/fg1");
  ob->move_living("X", this_object());
  n--;
  if (n > 0)
   call_out("goblins", 0, n);

}

create_room(){
set_short("Ice Fortress");
set_long(break_string(
"A large icy hall. A massive stone table rests here, slicked over " +
"with a pane of ice." +
"\n", 70));

add_item("table", "It is a massive stone table, crude and icy.\n");
add_item("ice", "It covers the walls and ceiling.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice." +
         "Huge icicles hang from it.\n");
add_item("icicles", "The must be very huge! But too high to reach.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");


INSIDE;
add_exit(PATH + "r5","north", 0);
add_exit(PATH + "r3","southwest", 0);
add_exit(PATH + "main1", "west", 0);
reset_room();
}
