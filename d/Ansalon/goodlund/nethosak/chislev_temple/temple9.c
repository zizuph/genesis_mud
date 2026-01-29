/*
 *  temple9.c
 *
 *  This is a part of the chislev temple, the only thing
 *  of interest in here is the prevention of bouncing
 *  the druid.
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


public int      pass_tapestry();

create_mithas_room()
{
    set_short("A ruined hallway");
    set_long("@@long_desc");
    
    add_exit(TDIR +"temple6", "south", 0);
    add_exit("", "east", &pass_tapestry());

    add_item(({"floor","ground","grass","lush grass"}),
    "The floor is completely overgrown, showing no signs that "+
    "this area is indoors, moss and fungi grow in patches in "+
    "the lush grass.\n");
	 
    add_item(({"ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");

    add_item(({"stones","blocks","granite blocks","granite stones"}),
    "The stones are square gray granite blocks which have been "+
    "worn down by time and harsh weather, little remains visible "+
    "as most has been covered by the lush vegetation.\n");

    add_item(({"walls","roots","wall","cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability. The moss and fungi have nearly covered "+
    "the stone walls and crept up towards the ceiling.\n");
	 
    add_item(({"moss","fungi","vegetation","lush vegetation"}),
    "The moss and fungi have nearly covered the stone walls and "+
    "crept up towards the ceiling, a few patches can be seen "+
    "within the lush grass.\n");
	 
    add_item(({"roof","ceiling"}),
    "The ceiling here differs from the rest of the temple, "+
    "stones are apparent beneath the moss and roots, which "+
    "hints towards a second floor.\n");

    add_item(({"hallway"}),
    "The hallway comes to an abrupt end as the northern wall and "+
    "parts of the ceiling has collapsed, barely held up by a myriad "+
    "of roots. In the southern direction the vegetation is less "+
    "prevalent and the ruin becomes more apparent.\n");
	 
    add_item(({"door","wooden door"}),
    "The wooden door hangs on crooked hinges and is propped with "+
    "a stone to keep it from blowing inwards. The threshold on "+
    "the outside appears to be elevated, one would have to lift "+
    "the door to open it.\n");
	
    add_item(({"threshold"}), "The threshold on the other side of "+
	"the door appears to be elevated.\n");
	 
    add_cmd_item(({"door","wooden door"}),"lift", "@@lift_door");
    add_cmd_item(({"door","wooden door"}),"open", "@@pass_tapestry");
}

string
long_desc()
{ 
    return tod_desc()+ "" +season_desc()+
    "The hallway comes to an abrupt end as the northern wall and "+
    "parts of the ceiling has collapsed, barely held up by a myriad "+
    "of roots. This part of the temple has been completely swallowed "+
    "by nature, the vegetation wildly growing to cover the walls "+
    "and floor, even the ceiling has patches of moss. In the "+
    "eastern wall, a wooden door hangs on crooked hinges and "+
    "propped with a stone to keep it from blowing open.\n";
}

int
lift_door()
{
    mixed *druid = find_living("_chislev_druid", 1);
    
    if (sizeof(druid) && !druid[0]->query_relaxed_from_combat())
    {
        write("The surrounding vegetation rapidly grows and blocks your "+
        "attempt at reaching the door.\n");
        say(QCTNAME(TP) + " tries to reach the door but the surrounding "+
        "vegetation prevents "+HIM(TP)+".\n");
        return 1;
    }
    write("You lift the door, freeing it from the elevated "+
    "threshold on the other side, pushing it open.\n");
    say(QCTNAME(TP) + " opens the door and steps outside, closing it "+
    "behind "+HIM(TP)+".\n");
    
    TP->move_living("M",TDIR + "temple_clearing.c", 1, 0);
    
    write("You close the door behind you.\n");
    say(QCTNAME(TP) + " arrives from within the temple, closing the "+
    "door behind " + HIM(TP) + ".\n");
    return 1;
}

int
pass_tapestry()
{
    write("You attempt to open the door, but fail. The door appears "+
    "to be stuck.\n");
    say(QCTNAME(TP) + " tries to open the wooden door, but fails.\n");
    return 1;
}