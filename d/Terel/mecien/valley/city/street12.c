inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/city/"
#define TO this_object()
#define EN environment

create_room(){
   
   set_short("Street");
   set_long(
      "Lonely in the fog, this part of the street rolls out into a dark " +
      "residential area. Tall houses line the streets." +
      "\n");
   
   add_item("fog", "It seems at home here.\n");
   add_item("street", "It is cobblestone.\n");
   add_item("homes", "They are tall houses that line the streets, closed to the public.\n");
   
   add_exit(PATH + "street11", "southwest", 0);
   
}

