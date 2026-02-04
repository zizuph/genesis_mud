inherit "/std/room";
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/frost/local.h"

create_room(){
set_short("Ice Fortress");
set_long(break_string(
"A tall and desolate corridor. Wind whips through here, chilling " +
"and merciless. The ice on the walls is chipped." +
"\n", 70));

add_item("ice", "It covers the walls and ceiling, a bit chipped.\n");
add_item("ceiling", "Made of huge stone blocks, now coated with ice." +
         "Huge icicles hang from it.\n");
add_item("icicles", "The must be very huge! But too high to reach.\n");
add_item("floor", "Slick with ice.\n");
add_item("walls", "Huge stone blocks, coated with ice.\n");

INSIDE;
add_exit(PATH + "r4","northeast", 0);
add_exit(PATH + "r2","southwest", 0);

}
