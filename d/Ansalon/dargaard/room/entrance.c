
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

void
reset_dargaard_room()
{

}

void
create_dargaard_room()
{
    set_short("At an iron gate before Dargaard Keep"); 
   set_long("@@room_descr");

    add_exit(DROOM + "eastguard","east",0); 
    add_exit(DROOM + "westguard","west",0); 
    add_exit(DROOM + "road6","down",0); 

    add_item(({"road", "path"}), 
      "A few bones lies scattered on the path.\n"); 

    add_item(({"gate", "iron gate", "massive gate"}), 
      "The gate is made out of blackened iron, twisted into a strange pattern. Two iron chains "+ 
      "connect the gate with the top of the stone wall. It must be impossible to lift the gate, but "+ 
      "there might be another way of opening it.\n"); 

    add_item(({"footprints", "prints"}), 
      "Judging by the size of the footprints you think that it may come from humans or dwarves. "+ 
      "A large group of people must have entered the Keep a few days ago, but you are only "+ 
      "able to find a few footprints leading out of there again.\n"); 
  
    gate_is_open = 0;
    reset_dargaard_room();
}


void
init()
{
   ::init();
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


void
gate_opens()
{
   tell_room(TO, "With a deep rumbling sound the black gate opens.\n");

   add_exit(DROOM + "court0", "north", 0);
   gate_is_open = 1;
}


void
gate_closes()
{
   tell_room(TO, "With a deep rumbling sound the black gate closes.\n");

   remove_exit("north");
   gate_is_open = 0;
}


string
room_descr()
{
   if(gate_is_open == 1)
      return tod_descr()+ "" +season_descr()+ "You stand before "+ 
             "the massive iron gate leading to Dargaard Keep. The road "+ 
             "is filled with different footprints most of them leading into the Keep "+ 
             "but only few ones leading out of it. To the east and west lies two small "+ 
             "guardrooms. A steep path downwards takes you away from Dargaard Keep.\n"+ 
             "The massive iron gate is open.\n"; 

   return tod_descr()+ "" +season_descr()+ "You stand before "+ 
          "the massive iron gate leading to Dargaard Keep. The road "+ 
          "is filled with different footprints most of them leading into the Keep "+ 
          "but only few ones leading out of it. To the east and west lies two small "+ 
          "guardrooms. A steep path downwards takes you away from Dargaard Keep.\n"+
          "The massive iron gate is closed.\n"; 
}

