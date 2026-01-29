
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>
#include <composite.h>
#include "../local.h"

inherit DARGAARD_OUT;

int gate_is_open;
object other_room  = DROOM + "eastguard";
object other_room2 = DROOM + "entrance";

void
reset_dargaard_room()
{

}

void
create_dargaard_room()
{
   set_short("Inside Dargaard Keep, before an iron gate"); 
   set_long("@@room_descr");

   INSIDE;

    add_item(({"lever","small lever", "iron lever"}), "The lever is "+ 
             "attached to the wall, next to the gate. A complicated "+ 
             "system of wires connects the lever with the gate.\n"); 

    add_item(({"gate","huge gate", "iron gate"}), "The gate is made "+
             "out of blackened iron, twisted into a strange pattern. Two iron chains "+ 
             "connect the gate with the top of the stone wall. It must be impossible "+
             "to lift the gate, but there might be another way of opening it. A "+
             "complicated system of wires connects the gate with the lever next "+
             "to the wall.\n"); 

    add_item(({"yard","courtyard"}), "The courtyard continues in the northern "+ 
              "direction. Bones and debris fills the ground.\n"); 

    add_item(({"bones","debris"}), "Human bones lies scattered all over the "+ 
              "the ground.\n"+ 
              "You find nothing interesting among them.\n"); 

   add_exit(DROOM + "court7", "northwest", 0);
   add_exit(DROOM + "court8", "northeast", 0);
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
      tell_room(TO, "With a deep rumbling sound the black gate closes.\n");
      remove_exit("south");
      other_room->gate_closes();
      other_room2->gate_closes();
      gate_closes();
      return 1;
   }

   tell_room(TO, "With a deep rumbling sound the black gate opens.\n");
   add_exit(DROOM + "entrance", "south", 0);
   other_room->gate_opens();
   other_room2->gate_opens();
   gate_opens();
   return 1;
}

int
do_open(string what)
{
   if((what == "gate") || (what == "gates"))
   {
      write("You are too weak to open the gate.\n");
      return 1;
   }
   
   return 0;
}



string
room_descr()
{
   if(gate_is_open == 1)
      return tod_descr()+ "" +season_descr()+ " You in the courtyard "+ 
             "in Dargaard Keep. Before you to the south, a huge black "+ 
             "iron gate has been opened allowing you access to the "+ 
             "Dargaard Mountains. Vague screams can be heard inside the "+ 
             "Keep beyond the courtyard to the north. The courtyard "+ 
             "continues to the northeast and northwest.\n"+ 
             "A small iron lever is here.\n"; 

   return tod_descr()+ "" +season_descr()+ " You in the courtyard "+ 
             "in Dargaard Keep. Before you to the south, a huge black "+ 
             "iron gate stands blocking your way out of the Keep. Vague "+ 
             "screams can be heard inside the Keep beyond the courtyard "+ 
             "to the north. The courtyard continues to the northeast and "+ 
             "northwest.\n"+ 
             "A small iron lever is here.\n"; 
}
