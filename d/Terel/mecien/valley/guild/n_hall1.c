/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Hallway");
set_long("This darkened stone hallway is fashioned of an unusual\n"
  +"black and gray stone, it is almost like slate. The walls\n"
  +"pieced together like bricks, but in thin scale-like sections\n"
   +"set atop one another. It seems ancient and almost a crude\n"
   +"make, though very strong.\n");

add_exit(PATH + "n_hall2", "north", 0);
add_exit(PATH + "hall", "south", 0);


}
