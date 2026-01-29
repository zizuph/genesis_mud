
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
    set_short("Eastern guardroom in Dargaard Keep"); 
    set_long("You are in the eastern guardroom in Dargaard Keep. In "+ 
             "the center of the room lies a broken table and a bunch "+ 
             "of rotten wood that might once have been a couple of "+ 
             "chairs. A rusty weapon rack has been placed next to "+ 
             "the eastern wall, however the weapons from it have "+ 
             "been removed years ago. The exit to the west takes you "+ 
             "back to the main gate.\n"+ 
             "A small iron lever is here.\n"); 

    add_exit(DROOM + "entrance","west",0); 

    add_item(({"wood", "chairs", "table", "debris"}), "The wooden remains "+ 
        "of a table and a couple of chairs fill the center of the room. The wood "+ 
        "is filled with fungi and drenched with water from the leaky ceiling.\n"); 

    add_item(({"lever", "small lever"}), "The lever is made out of iron and "+ 
        "it's connected to a complicated mechanism of wires. Perhaps this "+ 
        "might open or close the main gate.\n"); 

    add_item(({"ceiling", "collapsed ceiling"}), "The ceiling here has begun "+ 
        "to collaps, allowing water from above to fill the room.\n"); 

    add_item(({"rack", "weapon rack"}), "The rusty weapon rack is empty.\n"); 

    gate_is_open = 0;

    reset_dargaard_room();
}


void
init()
{
   add_action("turn_lever", "turn");
   add_action("turn_lever", "move");
   add_action("turn_lever", "pull");
   ::init();
}


void
gate_opens()
{
   gate_is_open = 1;
}


void
gate_closes()
{
   gate_is_open = 0;
}


int
turn_lever(string what)
{
   if (what != "lever")
   {
      NF("Turn what ?\n");
      return 0;
   }

   if (gate_is_open)
   {
      write("You turn the lever, and you hear the gate to the west close.\n");
      other_room->gate_closes();
      other_room2->gate_closes();
      gate_closes();
      return 1;
   }

   write("You turn the lever, and you hear the gate to the west open.\n");
   say(QCTNAME(TP) + " opens the gate to the west.\n");

   other_room->gate_opens();
   other_room2->gate_opens();
   gate_opens();
   return 1;
}

