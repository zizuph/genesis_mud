inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/frost/local.h"

create_room(){

object d1, d2;

set_short("Ice Fortress");
set_long(break_string(
"A huge corridor in the fortress, it leads north deeper in and south to " +
"the gates. Massive icicles hang from the ceiling." +
"\n", 70));
add_item("ice", "It covers the walls and ceiling.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice." +
         "Huge icicles hang from it.\n");
add_item("icicles", "The must be very huge! But too high to reach.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");

   add_exit(PATH + "r2", "north", 0);

INSIDE;

d1 = clone_object(PATH + "d1a");
d1->move(TO);
d2 = clone_object(PATH + "d2a");
d2->move(TO);

}



