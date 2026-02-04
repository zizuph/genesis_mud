/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"


create_room(){
   object lat;
   
   set_short("Portico");
   set_long(
   "Its white stone luminous, this ancient portico outstretches\n"
 + "from the shrine and enters into a vibrant courtyard. The portico\n"
 + "is long and gracious, its elegant pillars and arched roof honor\n"
 + "its beautiful stone walkway. Though a bit cragged with age, its\n"
 + "grand architecture is still a marvel.\n"
);

  add_item("roof", "Its made of white stone. It forms a long arched\n"
  + "covering for the walkway.\n");
   add_item("courtyard", "The portico leads north into the courtyard.\n");
   add_item("shrine", "A silver lattice leads into the great shrine.\n");
  add_item("walkway", "This is the main part of the portico, it leads\n"
  + "from the shrine into the courtyard.\n");
 add_item("pillars", "The line the portico on both sides, made of elegant\n"
  + "white stone.\n");
  add_exit(PATH + "/courtyard/g1", "north", 0);
  lat = clone_object(PATH + "courtyard/lat1");
  lat->move(this_object());
   
}

