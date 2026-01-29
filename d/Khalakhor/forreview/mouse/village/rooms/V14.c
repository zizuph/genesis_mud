/* room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"
  

void create_room()  {
     set_short("In the yard of a brick home");
     set_long("   A lush green lawn stretches before a simple, yet "+
          "elegant, brick house. A variety of fragrant flowers have "+
          "been artfully arranged in beds skirting the edges of the "+
          "lawn. Trees have been strategically placed around the house "+
          "to provide a maximum of shade against the hot summer sun.\n");
      
     add_exit(ROOT+"village/rooms/V13","west");
     clone_object(ROOT+"village/mons/crybaby.c")->move(TO);
}

void reset_room()
{
  if(!present("boy"))
      clone_object(ROOT+"village/mons/crybaby.c")->move(TO);
}
  


