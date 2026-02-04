/*  house5a.c 
    Tomas 11/19/1999
*/

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/include/Terel.h"

object citizen = 0;

public void
create_room()
{
  
  INSIDE;
  set_short("bedroom");
  set_long("The bedroom is moderately decorated. Several " +
     "pieces of furniture can be seen about the room. A painting " +
     "hangs from the wall.\n");

  add_item(({"furniture","bed","chair","dresser"}),
     "An average bed, chair and dresser. Stuff " +
     "you'd likely find in a bedroom.\n");

  add_item(("painting"),"It looks like a family " +
     "portrait done by some childs fingers in " +
     "various colors.\n");
  
  add_exit(CALATHIN_DIR + "houses/house5.c","south",0,1);

       
   reset_room();
}


void
reset_room()
{    
  
    if(!citizen)
    {
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
       citizen->move(TO);
   
    }
}
