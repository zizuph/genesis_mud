/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

object monster;

reset_room(arg){

if(!monster){
monster=clone_object(PATH + "mystic1");
monster->move(this_object());
}
}
create_room(){

set_short("Hallway");
set_long("This darkened stone stands silent, almost in a\n"
  + "morbid decay. The walls of thin slate-like pieces\n"
  + "stacked atop each other, like bricks. The walls are\n"
  + "are somewhat brittle, bits breaking off.\n");

add_my_desc("An alabaster arch leads north.\n");

add_exit(PATH + "foyer", "north", 0);
add_exit(PATH + "n_hall2", "south", 0);


add_item("arch", "It is an old alabaster arch, very simple.\n");

reset_room();
}
