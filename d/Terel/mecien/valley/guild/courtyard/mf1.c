/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/courtyard/garden_room";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){

  ::create_room();
set_short("Inner Forest");
set_long(
"All about rising up, tall cears and redwoods. Gentle in their most\n"
+"magnificent size, they cover this place with their gracious and\n"
+"solemn mantle of living colour. The air is calm, whispering only\n"
+"in the slightest, as if prayers of the dead echoing from within.\n"
);

add_item("trees", "They are tall cedars and redwoods, they reach high into the sky and\n"
  + "they keep out most light.\n");
add_item("cedars", "An aromatic coniferous tree, its bark reddish.\n");
add_item("redwoods", "Beautiful noble trees, huge and ancient. They are coniferous.\n");

  add_exit(PATH + "hill", "northwest", 0);
  add_exit(PATH + "rf2", "east", 0);
}

