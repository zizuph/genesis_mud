/* room coded by Elizabeth Cook/Mouse, January 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"

void create_room()  {
     set_short("Festiwycke");
     set_long("   The forest thins as Festiwycke Road leads closer to the "+
          "center of the village. A cobblestone lane branches from the "+
          "main road, running southwest. Fragrant pink wild roses have "+
          "spread rampantly over the low stone walls that flank the road "+
          "on both sides. Quaint stone cottages covered with lush green "+
          "ivy stand behind the walls. More of Festiwycke lies to the "+
          "north. Southeast leads away from Festiwycke, toward the Briarwood "+
          "Forest.\n");
     add_item("road","A worn, dusty road that runs north and southeast.\n"); 
     
     add_exit(ROOT+"village/rooms/V9","north");
     add_exit(ROOT+"village/rooms/V7","southeast");
     add_exit(ROOT+"village/rooms/shopent","southwest");          

}

  
