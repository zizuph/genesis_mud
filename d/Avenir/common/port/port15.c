// file name:        port14.c
// creator(s):       Ilyian
// revision history:
//		     Denis, Sep'96: Changes due to the port inheritance recode.
//           Lilith 21 Feb 2014: Tweaked room desc
//           Lilith, Sep 2021: Added fishing prop.
//           Lilith Sep 2021: Updated wall desc for Shrine quest.
// purpose:
// note:             EARTHSEA SHIP DOCKS HERE
// The line to Gont disabled - Tapakah, 05/2009
//
#pragma strict_types

#include "/d/Avenir/common/port/port.h"

inherit PORT_ROOM;
inherit "/d/Avenir/inherit/sair_wall";

public string
exa_block(void)
{ 
    return "A scene has been carved into the fragrant cedar, "+
           "showing a fiery red-scaled dragon, its wings spread "+
           "protectively over a small boat whose large sail is "+ 
	   "speckled with silver stars.\nThe base has been "+ 
           "inscribed with the words:\n"+
           "    The Sea Witch no longer sails to the port of Gont.\n";
} 

public void
create_port_room(void)
{
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");

    set_short("Northern ledge in Sybarus Port cavern");
    set_long("You are on a wide ledge between the cavern wall to " +
             "the north and the churning waters of the lake of the "+
			 "Sybarus rift to the south. " +
             "Mist seems to cling everywhere, glossing everything with a "+
             "thin layer of moisture. The sounds of water thundering "+
             "through the Rift seems to hammer your flesh, making your "+
             "footing unsteady. The ledge extends a little further to "+
             "the west, and continues east toward the ship berths and "+
			 "the Port of Sybarus."+
/*			 
	     "A carved cedar post marks this as a former berth "+
	     "for ships hailing from Earthsea. "+
 */
			 "\n");
    IN
    LIGHT

    add_exit("port14", "east");
    add_exit("port16", "west"); 

    add_rift_item();
    add_wall_item();
    add_no_swim_cmditems();
/*
    add_item(({"sign", "post", "cedar", "base"}), "@@exa_block@@");
    add_cmd_item(({"sign","base", "post"}), "read", "@@exa_block@@");
 */
 
 	add_sair_wall();
	set_sair_dest(({PORT +"port6", LEDGE+"ledge2"}));
    
}

void init()
{
    sair_init();
    ::init();
}
