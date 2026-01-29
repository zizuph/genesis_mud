
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>
#include <composite.h>
#include "../local.h"

inherit DARGAARD_OUT;

int gate_is_open;
object other_room  = DROOM + "court0";
object other_room2 = DROOM + "entrance";
object skeleton1, skeleton2, skeleton3; 

void 
reset_dargaard_room() 
{ 
   if(!objectp(skeleton1)) 
   { 
      skeleton1 = clone_object(DNPC + "skeletonguard"); 
      skeleton1->move(TO); 
   } 
   if(!objectp(skeleton2)) 
   { 
      skeleton2 = clone_object(DNPC + "skeletonguard"); 
      skeleton2->move(TO); 
   } 
   if(!objectp(skeleton3)) 
   { 
      skeleton3 = clone_object(DNPC + "skeletonguard"); 
      skeleton3->move(TO); 
   } 
} 


void
create_dargaard_room()
{
    set_short("Western guardroom in Dargaard Keep"); 
    set_long("You are in the western guardroom in Dargaard Keep. "+ 
             "In the center of the room lies a broken table and a "+ 
             "bunch of rotten wood that might once have been a "+ 
             "couple of chairs. A rusty weapon rack has been placed "+ 
             "next to the western wall, however the weapons from it "+ 
             "have been removed years ago. Water is dripping down "+ 
             "from above from the half-collapsed ceiling. The exit "+ 
             "to the east takes you back to the main gate.\n"); 

    add_exit(DROOM + "entrance","east",0); 

    add_item(({"ceiling", "collapsed ceiling"}), "The ceiling here has begun "+ 
        "to collaps, allowing water from above to fill the room.\n"); 

    add_item(({"wood", "chairs", "table", "debris"}), "The wooden remains "+ 
        "of a table and a couple of chairs fill the center of the room. The wood "+ 
        "is filled with fungi and drenched with water from the leaky ceiling.\n"); 

    add_item(({"rack", "weapon rack"}), "The rusty weapon rack is empty.\n"); 

    reset_dargaard_room();
}

