/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/d/Terel/mecien/valley/guild/courtyard/garden_room";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"

create_room(){

  ::create_room();
set_short("Redwood Forest");
set_long(
"Tall and glorious, these redwoods grow up and form a small forest\n"
+"of their own. Unwavering in their majestic antiquity, they form a \n"
+"solemn sanctuary to the living world. The air is calm and a reverent\n"
+"silence hangs upon this place like an ancient vow.\n"
);

add_my_desc("\nA large stone juts up from the forest floor, like a table.\n");

add_item(({"table", "stone", "stone table"}), 
  "It is a large stone that erupts from the forest floor and has\n"
+"been carved to look like some kind of table. It is ancient\n"
+"looking and some insrciption is upon it.\n");
add_cmd_item(({"table", "inscription", "stone"}),
 "read", "For the Stars are Her Mantle, the Moon Her Crown\n");
add_item("trees", "They are tall redwoods, they reach high into the sky and\n"
  + "they keep out most light.\n");
add_item("redwoods", "Beautiful noble trees, huge and ancient. They are coniferous.\n");

  add_exit(PATH + "rf1", "west", 0);
}

