// file name:        port4.c
// creator(s):       Ilyian
// revision history: Denis, Sep'96: Changes due to the port inheritance recode.
//                   Lilith Sep 2021: Updated wall desc for Shrine quest. 
// purpose:
// note:
// bug(s):   
// to-do:

# pragma strict_types
# include "port.h"
#include "/sys/cmdparse.h"
inherit PORT_ROOM;
inherit "/d/Avenir/inherit/sair_wall";
	
static void create_port_room()
{
   
    set_short("Above a warehouse");
    set_long("On a roof built into the southern cavern wall, " +
             "with the choppy dark sea below you. The mist is "+
			 "especially heavy here, obscuring your vision, "+
			 "but you can just make out that the building "+
			 "beneath you is a warehouse.\n");

    IN
	
	add_exit(PORT+"port6", "down");
    
	add_rift_no_see_item();
    add_wall_item();
    add_ceiling_in_item();
    add_no_swim_cmditems();
	
    add_sair_wall();
    set_sair_dest(({LEDGE+"ledge3", PORT +"port5"}));
	
}

void init()
{
    sair_init();
    ::init();
}

