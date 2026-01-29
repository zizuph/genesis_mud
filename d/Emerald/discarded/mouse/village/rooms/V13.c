/* room coded by Elizabeth Cook/Mouse, January 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"


void create_room()  {
     set_short("North of the square");
     set_long("   Elegant brick homes flank Festiwycke Road to the east "+
          "and west. This thoroughfare north of the square is perhaps the "+
          "best maintained section of road in the district, no doubt owing "+
          "to the influentiality of the residents here. The way continues "+
          "to be laid in brick from the square, and great care has been "+
          "taken to make it as even as possible. The road north "+
          "appears to lead away from the business district, and yet there "+
          "is considerable traffic in that direction.\n"); 
      
     add_exit(ROOT+"village/rooms/V15","north");
     add_exit(ROOT+"village/rooms/V9","south");
     add_exit(ROOT+"village/rooms/V12","west");
     add_exit(ROOT+"village/rooms/V14","east");
               

}

  

