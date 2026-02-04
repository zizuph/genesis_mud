/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Hall of the Stars");
set_long(
"This circular hall, of cold dark stone, stands like a vigil\n" +
"to the heavens themselves. Painted across the floor is a bright\n" +
"four-pointed silvery star, its edges rippled with fire. The walls and\n" +
"ceiling are covered with smaller stars and constellations.\n" +
"\nA black chair rests at the far side of the hall.\n"
+ "A spiral of stairs leads up and down.\n"
);

add_item("star", "It is a painted silver star that coverd the floor.\n");
add_item("stars", "They are painted upon the walls and ceiling.\n");
add_item("constellations", "Painted on the walls and ceiling," +
  "apparently to match\ndifferent parts of the world.\n");
add_item("chair", "It is made of black wood. It looks ancient and arcane.\n");

  add_exit(PATH + "chancery", "down", 0);
  add_exit(PATH + "skypoint", "up", 0);
  set_noshow_obvious(1);
}

