// file name:        port5.c
// creator(s):       Ilyian
// updates: Denis, Sep'96: Changes due to the port inheritance recode.
//           Lilith, Sep 2021: Added shrine to Sair for a little quest.
//              Sair is the goddess of walls, and the maker and remover 
//              of obstacles. Fire Opals are sacred to Sair and the 
//              only known offering that she accepts.
// purpose:
// note:
// bug(s):   
// to-do:

# pragma strict_types
# include "port.h"
#include "/sys/cmdparse.h"
inherit PORT_ROOM;

object shrine;
	
static void create_port_room()
{
   
    set_short("Shrine to Sair");
    set_long("High on a ledge along the southern cavern wall, " +
             "with the choppy dark sea spreading out to the north "+
			 "as far as the eye can see. The mist is especially "+
			 "heavy here, obscuring your view of the distance, "+
			 "but you can just make out the roof of a warehouse "+
			 "below.\nA glowing orange octagonal column.\n");
    IN
	
    
	add_rift_no_see_item();
    add_wall_item();
    add_ceiling_in_item();
    add_no_swim_cmditems();
		
	add_exit(PORT+"port4", "down");

	if (!shrine)
	{
		shrine = clone_object(PORT +"obj/sair_altar");
        shrine->move(TO, 1);
	}
}


