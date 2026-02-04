inherit "/std/room";
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/frost/local.h"

object wolf;

reset_room(){
 int n;
 if(!wolf){
  wolf = clone_object("/d/Terel/mecien/dwolf");
  wolf->move(TO);
  wolf->set_aggressive(1);
}
 if(!present("giant_guard")) {
     n = 2;
     call_out("guards", 1, n);
     }
}

guards(n) {
  object ob;
  ob=clone_object(PATH + "mon/fg2");
  ob->move_living("X", this_object());
  n--;
  if (n > 0)
   call_out("guards", 0, n);

}

create_room(){
set_short("Ice Fortress");
set_long(break_string(
"A small hall, filled with ice. Passages lead off from here, causing " +
"a great about of wind to whip through here." +
"\n", 70));

add_item("ice", "It covers the walls and ceiling.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice." +
         "Huge icicles hang from it.\n");
add_item("icicles", "The must be very huge! But too high to reach.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");


add_exit(PATH + "t1", "east", 0);
INSIDE;
add_exit(PATH + "r3","northeast", 0);
add_exit(PATH + "r1","south", 0);
reset_room();
}
