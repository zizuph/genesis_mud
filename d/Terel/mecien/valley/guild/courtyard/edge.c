/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/courtyard/garden_room";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){

  ::create_room();
set_short("Forest Edge");
set_long(
"Rising up here, a small forest of grand trees, redwoods. They abide\n"
+"here upon the edge of this stately garden like sentinels of some other\n"
+"land, knowing and ominous. The hedges diminish here and blend into the\n"
+"forest, disappearing in the solemnity of the darker woods.\n"
);

add_item("forest", "It is a small forest, dark and ominous.\n");
add_item("hedges", "They are evergreens, they fade into the forest.\n");
add_item("trees", "They are tall redwoods, they reach high into the sky and\n"
  + "they keep out most light.\n");
add_item("redwoods", "Beautiful noble trees, huge and ancient. They are coniferous.\n");

  add_exit(PATH + "rf1", "north", 0);
  add_exit(PATH + "g5", "southwest", 0);
}

