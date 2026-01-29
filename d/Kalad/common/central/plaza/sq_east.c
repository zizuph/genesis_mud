/*
ROOM: East corner of Town Square
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   hear_bell = 3;
   
   set_short("The east corner of Town Square");
   set_long(                    
      "This is the east corner of Town Square. To the west you "+
      "see the massive city monument, and to the southeast you see the "+
      "beautiful Library of Mathegus, probably the only good-looking "+
      "building in the entire town square.\n"+
      "    When you glance northeastwards, you find yourself staring "+
      "at the house of the Firebrigade.\n"
   );
   
   add_prop(ROOM_NO_TIME_DESC, 1);
   
   add_exit(CENTRAL(library/entrance),"southeast",0,-1,-1);
   add_exit(CENTRAL(plaza/fb_rm11), "northeast",0,-1,-1);
   add_exit(CENTRAL(plaza/sq_mon), "west");
   add_exit(CENTRAL(plaza/sq_north), "northwest");
   add_exit(CENTRAL(plaza/sq_south), "southwest");
   add_item("firebrigade",
      "This building looks like it hasn't seen water in years. Its all "+
      "dusted down, and has few marks off use. But maybe things are different inside?\n");
   add_item("library", 
      "This is the famous library founded by the sage Mathegus. Many "+
      "volumes written by the wisest sages stand on its shelves.\n"
   );
}
