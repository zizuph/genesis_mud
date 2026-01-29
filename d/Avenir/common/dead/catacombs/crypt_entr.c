// file name: crypt_entr
// creator:       Ilyian (Oct 15, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch 
//                Lilith, July 2021: Added gate functionality.
//                Lilith, Sep 2021: added statserv logging, updated short.
// purpose:     Entrance to the underground crypts
// note:        Most of the code for these rooms is in
//              crypt_base.c - see that file for info on these rooms.
//             Chatelaine is cloned here by the crypt_placer.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"
#include <macros.h>
#include <stdproperties.h>

#define OTHER_SIDE   (CRYPT +"crypt_out")
#define CHATELAINE   MON +"chatelaine.c"  /* Cloned by the placer */

int door_closed;
public int query_closed() {    return door_closed;    }

int test_gate();


public void
reset_domain_room()
{
	door_closed = 1;
	set_searched(0);  ::reset_domain_room();

}

void
create_crypt_room()
{
    acat("93","south");
    
	add_exit(CRYPT + "crypt_out","north", "@@go_north");
	
    set_short("Catacombs entrance.\nAn imposing iron gate");

    set_long("This is the entrance to the Catacombs of Sybarus. " 
	      +"A long tunnel slants south down into a frightful "
          +"blackness. The walls seem to be made from "
          +"glistening limestone, and the floor is covered "
          +"with a thick white mist, similar to the fog "
          +"that lies on the moors, but whiter. Some light "
          +"filters in from the north.\n"
		  +"There is an imposing iron gate to the north.\n");

    add_prop(ROOM_I_LIGHT, 1);

    add_item(({"gate", "iron gate", "imposing gate",  
       "imposing iron gate", "north gate"}),
       "This imposing iron gate has the trefoil seal of "
	   +"Sybarus emblazoned on it. It has an unusual "
	   +"lock.\n");
	add_item(({"lock", "unusual lock", "locking mechanism"}),
	    "The opening in this lock is for a skull-shaped "
		+"key.\n");
    add_cmd_item(({"gate", "iron gate", "imposing gate",  
         "imposing iron gate", "north gate", "on gate", "on iron gate"}), 
        ({"knock", "bang"}), "Your banging probably woke the dead.\n"
		+"You might try asking the spirit to open it, instead.\n");
	add_cmd_item(({"gate", "iron gate", "imposing gate",  
        "imposing iron gate", "north gate"}), 
        ({"unlock", "open"}), "You have no way of unlocking or opening "
		+"the gate. You might try asking the gatekeeper to open it -- or "
		+"find a different way out, if there is one...\n");
    add_item(({"wall","walls","limestone", "moisture"}),
	   "The walls of the "
      +"catacombs are made from soft and porous limestone "
      +"that glistens with moisture. Recesses filled with "
	  +"bodies have have been cut into the stone, stretching "
	  +"upwards into the darkness, row upon row.\n");
	add_item(({"ceiling"}),"The ceiling is farther up than you "
      +"can see. It is obscured from sight.\n");
    add_item(({"floor","ground"}),"The floor is uneven, "
      +"dark, and damp, making footing treacherous.\n");
    add_item(({"mist","fog"}),"A thin white mist moves along "
      +"the ground, making the floor wet and slippery.\n");
	add_item(({"dark","darkness","black","blackness","gloom"}),
      "Darkness is, by its nature, invisible.\n");
    add_item(({"wind","breeze","air"}),"The breeze moving along "
      +"the ground feels cold and damp around your ankles.\n");


    add_prop(ROOM_S_DARK_MSG, "The darkness around is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is thick "
      +"and oppressive. You feel it weigh upon your "
      +"soul.\n");		

   reset_domain_room();
}

int
go_north()
{
    if (!OTHER_SIDE)
		OTHER_SIDE->load_me();
    if(!OTHER_SIDE->query_closed())
    {
        write("You pass through the open imposing iron gate.\n");
		STATSERV_LOG_EVENT("crypt", "Left Crypt via gate");
        return 0;
    }
		
    write("The imposing iron gate is closed.\n");
    say(QCTNAME(TP)+ " tries to go north through the imposing iron gate "
	    +"but cannot.\n");

    return 1;
}


public int
test_gate()
{
    object gatekeeper;

    gatekeeper = find_object("/d/Avenir/comon/dead/mon/chatelaine");	

    if(!OTHER_SIDE->query_closed())
    {
        gatekeeper->command("say The gate is already open.");
        return 0;
    }
    gatekeeper->command("emote opens the imposing iron gate.");
    (OTHER_SIDE)->open_door();
    set_alarm(8.0, -1.0, "close_door");
    return 1;
}

public void
close_door()
{
    (OTHER_SIDE)->close_door();	
	door_closed = 1;
    return;
}
