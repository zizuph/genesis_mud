/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define PATH "/d/Terel/mecien/valley/guild/"
#define TP this_player()
#define TO this_object()

object ob1;

reset_room(arg){
if(!ob1){
ob1=clone_object(PATH + "acolyte");
ob1->move(TO);
}
}

create_room(){

set_short("Vestibule");
set_long(
"This dark stone hall, round and vaulted, is the landing for a small\n"
+"staircase that descends to the center of this chamber. It is also a\n"
+"vestibule for a much larger hall that opens to the west, through a tall\n"
+"bronze archway. A bronze lamp hangs on each side of the arch.\n"
);

  add_item("archway", "It is a bronze archway, leading into a large stone\n"
  + "hall, on which writing has been inscribed.\n");
add_cmd_item(({"archway", "writing", "inscription"}), "read",
  "Collegium Mystici In Vitae et Veritas\n");
add_item(({"lamp", "lamps", "bronze lamp", "bronze lamps"}),
  "They are brightly polished lamps of bronze in the shape of small\n"
 +"dragons, the flame burning from their mouths.\n");
add_item("staircase", "It leads upwards, it is made of dark stone.\n");
add_exit(PATH + "foyer", "up", 0);
add_exit(PATH + "academy", "west", 0);

reset_room();
}

