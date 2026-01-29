/* room coded by Elizabeth Cook/Mouse, March 1997 */

inherit "std/room";
#include <stdproperties.h>
#include "../../mouse.h"  

void create_room()  {
     set_short("The Golden Loom");
     set_long("   The front room of the weaver's shop is quite large, "+
          "allowing ample space for two looms operated by the mistress "+
          "and her first assistant. Shelves of woolen yarn in a rainbow "+
          "of colors line the walls, within reach of the busy weavers. "+
          "At the far western end of the room, next to the door to the "+
          "back workroom, a young woman adeptly spins wool into yarn on "+
          "a spinning wheel. An even younger girl sits on a stool beside "+
          "her, quietly carding a heap of wool.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);

     add_exit(ROOT+"village/rooms/cottent","northeast");
     add_exit(ROOT+"village/rooms/bkwk","west");
   
     clone_object(ROOT+"village/mons/wvmistress.c")->move(TO);
        
}
 
void reset_room()
{
  if(!present("weaver"))
     clone_object(ROOT+"village/mons/wvmistress.c")->move(TO);
}
