/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"


create_room(){
  object lat;
   
   set_short("Foyer");
   set_long("Shadowy and abyssmal, a blackened slate staircase\n"
      +"rises and descends here. Its steps clear and polished, glossy\n"
      +"black like volcanic rock. The walls are carved in\n"
      +"relief, depicting strange haunted faces.\n");
   add_my_desc("An alabaster arch leads south.\n");
   add_item(({"arch", "alabastar arch"}),
        "It is smooth alabastar and is carved with stars.\n");
   add_exit(PATH + "n_hall3", "south", 0);
   add_exit(PATH + "u_hall1", "up");
   add_exit(PATH + "vesti", "down", 0);
   
   
   lat = clone_object(PATH + "courtyard/lat2");
   lat->move(this_object());
   lat->set_key(50999);
}

