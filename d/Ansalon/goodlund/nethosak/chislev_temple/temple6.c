/*
 *  temple6.c
 *
 *  This is a room for the druid temple in Mithas.
 *
 *  Created by Carnak, January 2016
 */

#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_IN;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#include "./local.h"


create_mithas_room()
{
    set_short("An overgrown hallway");
    set_long("@@long_desc");
    
    add_exit(TDIR +"temple3", "south", 0);
    add_exit(TDIR +"temple9", "north", 0);
    
    add_item(({"floor","ground","weeds","grass","rocks","dirt",
	"lush grass","smooth rocks"}),
    "The floor is tiled with smooth rocks and covered in dirt, "+
    "the grass has begun growing more wildly compared to the "+
    "southern parts of the temple.\n");
    
    add_item(({"ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");

    add_item(({"stones","blocks","granite blocks","granite stones"}),
    "The stones are square gray granite blocks which have "+
    "been worn down by time and harsh weather.\n");

    add_item(({"walls","roots","moss","fungi","patches","cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability. The moss and fungi are growing in "+
    "more frequent patches as the corridor inches northwards.\n");
	 
    add_item(({"wooden roof","roof","hatch","ceiling"}),
    "The wooden roof appears to be in good condition. A hatch "+
    "in the roof has been propped open, allowing light to "+
    "spread throughout the temple during the day.\n");

    add_item(({"hallway","corridor"}),
    "The hallway extends north and southwards, in the northern "+
    "regions of the hallway, the ruin have begun to collapse. "+
    "The ruins have more vegetation growth the farther north "+
    "you travel.\n");

    add_item(({"decorations","decor"}),
    "In the far southern corner of the hallway, a large floor "+
    "mounted candelabra has been placed to evenly spread "+
    "the light throughout the temple.\n");

    add_item(({"candelabras","candelabra"}),
    "You should move closer if you are interested in the decor.\n");

    add_item(({"collapse","wall"}),
    "The corridor wall shows signs of collapse towards the "+
    "north, where nature has forced its way into the temple.\n");

}

string
long_desc()
{ 
    return tod_desc()+ "" +season_desc()+
    "The vegetation is becoming more prevalent as the corridor "+
    "inches northwards, moss and fungi is creeping up to cover "+
    "parts of the walls while lush grass has taken root in the "+
    "dirt, inbetween the rock tiles. The corridor wall shows "+
    "signs of collapse towards the north, where nature has "+
    "forced its way into the temple.\n";
}
