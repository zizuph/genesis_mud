/* room coded by Elizabeth Cook/Mouse, March 1997 */

inherit "std/room";
#include <stdproperties.h> 
#include "../../mouse.h"   

void create_room()  {
     set_short("The Silver Needle");
     set_long("   The seamstress shop is cluttered with an incredible "+
           "array of colorful fabrics and sewing notions of all kinds. "+
           "The sewing mistress sits at one table, adding some intricate "+
           "needleworking to a garment. One of her assistants sits nearby, "+
           "adorning another piece with exquisite beading. Two other "+
           "young assistants work at a second table, one girl cutting "+
           "a pattern from a length of fabric and the other sewing simple "+
           "seams.\n");


     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,2);

     add_exit(ROOT+"village/rooms/cottent","northwest");
   
     clone_object(ROOT+"village/mons/swmistress.c")->move(TO);   
        
}
 
void reset_room()
{
  if(!present("seamstress"))
      clone_object(ROOT+"village/mons/swmistress.c")->move(TO);
}
