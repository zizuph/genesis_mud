/**********************************************************************
 * - delivery.c                                                     - *
 * - This is a delivery shop in Port Macdunn.                       - *
 * - Created by Damaris@Genesis 11/2005                             - *
 **********************************************************************/
#pragma strict_types

#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Genesis/delivery/delivery.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Genesis/delivery/office";
public int *
query_local_coords()
{
    return ({11, 8});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}
void
reset_room()
{
    reset_office();
}

string
query_sign()
{
    return("\n"+
	"          *--------------------*` - - `*--------------------*\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          | `                                             ` |\n"+
	"          | `         Port Madunn Delivery Office         ` |\n"+
	"          | `       *`---------------------------`*       ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     * To get a packet to deliver            ` |\n"+
	"          | `       <ask for a delivery tour>             ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     * Deliver packet at destination         ` |\n"+
	"          | `       <deliver packet>                      ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     * To return packet to this office       ` |\n"+
	"          | `       <return packet>                       ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          *--------------------*` - - `*--------------------*\n");
}

void
create_khalakhor_room()
{
	set_short("Port Macdunn Delivery Office");
	set_long("   This single room building isn't very large but "+
	"is spacious enough to hold two long tables, which contain "+
	"packages and packets of different shapes and sizes. There "+
	"are paintings along the walls of far off lands and there is "+
	"a huge sign posted on the back wall with bold print.\n");
	add_item(({"area", "office", "room", "delivery office"}), query_long);
	add_item(({"sign", "huge sign"}), query_sign);
	add_cmd_item(({"sign","huge sign"}),
	 (({"read"})), query_sign);	
	add_item(({"ceiling", "roof"}),
	"The ceiling is only a thatched roof, so it isn't too much "+
	"to look at.\n");
	add_item(({"floor", "flooring", "ground"}),
	"The floor is made of wooden boards.\n");
	add_item(({"boards", "wooden board", "wooden boards", "board"}),
	"The boards are made of wood and set together side by side "+
	"making a floor.\n");
	add_item(({"wall", "walls"}),
	"The walls are cream coloured with paintings on them, with "+
	"the far wall having a huge signed posted.\n");
	add_item(({"painting", "paintings"}),
	"There are lovely paintings on the walls of far off places.\n");
	add_exit("road_11_9", "south");
        set_office("Port Macdunn Delivery Office",10);
        reset_room();
}
void
init()
{    
	init_office();
	::init();
}


