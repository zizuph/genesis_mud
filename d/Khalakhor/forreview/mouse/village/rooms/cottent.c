/* room coded by Elizabeth Cook/Mouse, March 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"  

void create_room()  {
     set_short("Between two cottages");
     set_long("   Just inside the low stone wall, you discover that the "+
          "gate opens onto a narrow path between two of the cottages. "+
          "The cottages appear to be especially well-maintained and "+
          "kept in a state of picture perfect beauty. Signs on the "+
          "buildings indicate that they are not merely homes. A delicate "+
          "fragrance of roses lingers in the air.\n");

     room_add_object(ROOT+"village/items/rosegate2.c");
   
     add_item(({"sign","signs"}),"Do you wish to examine the southeast "+
          "sign or the southwest sign?\n");
     add_item("southwest sign","It is a sign with some lettering you can "+
          "read.\n");
     add_item("southeast sign","It is a sign with letters on it, you might "+
          "try reading it.\n");
     add_cmd_item("southeast sign","read", " _______________________\n"+
                                           "|                       |\n"+
                                           "|   THE SILVER NEEDLE   |\n"+
                                           "|_______________________|\n");
     add_cmd_item("southwest sign","read"," _______________________\n"+
                                          "|                       |\n"+
                                          "|    THE GOLDEN LOOM    |\n"+
                                          "|_______________________|\n");
     add_exit(ROOT+"village/rooms/seam","southeast");
     add_exit(ROOT+"village/rooms/weaver","southwest");
      
}

