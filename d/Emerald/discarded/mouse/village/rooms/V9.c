/* room coded by Elizabeth Cook/Mouse, January 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"
  

void create_room()  {
     set_short("Festiwycke Square");
     set_long("   The road has widened into a brick-laid square. This is "+
          "heart of the village of Festiwycke. An austere looking building "+
          "lies to the east. There is a bronze plaque attached to its "+
          "facade. A large yellow building stands to the west. Festiwycke "+
          "Road continues north. There is a well in the center of the "+ 
          "square. Many people are milling about.\n");
      
     add_exit(ROOT+"village/rooms/V13","north");
     add_exit(ROOT+"village/rooms/V8","south");
     add_exit(ROOT+"village/rooms/V11","west");
     add_exit("/d/Underground/yozhik/village/rooms/brbank","east");          

}

  


