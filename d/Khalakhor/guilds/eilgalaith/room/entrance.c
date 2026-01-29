/**********************************************************************
 * - entrance.c                                                     - *
 * - Eil_Galaith Entrance                                           - *
 * - Created by Damaris 08/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 * - Typos fixed by Tapakah 6/2021                                  - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <stdproperties.h>

#include "/d/Khalakhor/sys/basic.h"

inherit GUILD_ROOM;
public int
block_exit()
{
	write("You may not go this way, at this time.\n");
	return 1;
}

public int
members_only()
{
	if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())
	{
		/* Is a member, pass through as normal */
		return 0;
	}
	write("A magical force prevents you from entering.\n"+
	"You are not a member of Eil-Galaith!\n");
	return 1;
}

void
create_guild_room()
{
	set_short("Sanctuary Tower Entrance Hall");
	set_long("   This is the entrance hall of Sanctuary Tower "+
	"the home of Eil-Galaith. The hall is quite large and an "+
	"unknown light source fills this hall in a warm inviting "+
	"light. There are paintings that fill the walls and in "+
	"the center of the room is a statue. A plaque "+
	"has been placed at the foot of the statue.\n");
	add_item(({"room", "area", "entrance", "hall"}), query_long);
	add_item(({"painting", "paintings"}),
	"Paintings line the walls in this room. They are quite beautiful "+
	"and noble in appearance. There are a total of eight paintings "+
	"and you should be able to look a bit closer at each one.\n");
	add_item(({"first painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of an "+
	"elven youth playing in the Great Forests with an elven nymph "+
	"watching over his shoulder.\n");
	add_item(({"second painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of a "+
	"noble elven lord casting his eyes towards the north. His elven "+
	"features are etched with concern as his crimson and gold cloak "+
	"flutters in the wind.\n");
	add_item(({"third painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of a "+
	"young elven mother holding an elven infant in her arms while "+
	"rushing to find shelter as a battle rages around her.\n");
	add_item(({"fourth painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of an "+
	"elder elven gentleman sitting near a fire and many elves are "+
	"gathered around him. It is most obvious with his hands spread "+
	"open he is telling a great story to many eager listeners.\n");
	add_item(({"fifth painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of "+
	"humans and dwarfs taking up arms along side many elves and "+
	"rushing through a battle scorched earth.\n");
	add_item(({"sixth painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of "+
	"three members of the Wise joined together in a circle and "+
	"raising their hands upward towards the sky.\n");
	add_item(({"seventh painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of "+
	"two male elves and a female elf sitting together by a "+
	"fire in the Great Forest. They appear to be joined in deep "+
	"conversation and an aura of light surrounds them "+
	"mysteriously.\n");
	add_item(({"eighth painting"}),
	"The painting is quite beautiful. You can tell right away the "+
	"finest elven artist has crafted it. The smooth brush strokes "+
	"are subtle yet prominent. The scene in this painting is of "+
	"many dwarven craftsmen and a few members of the Wise standing "+
	"proudly outside of a most spectacular tower.\n");
	add_item(({"statue"}),
	"The statue is made from pure white marble and it is the figure "+
	"of a noble elf carrying a scroll in his hand and is looking off "+
	"into the distance. At the foot of the statue is a plaque, which "+
	"you may read.\n");
	add_item(({"scroll"}),
	"The scroll is part of the statue and is unreadable.\n");
	add_item(({"plaque"}),
	"Welcome to the Sanctuary Tower.\n\n"+
	"We are pleased that you have found your way here.\n "+
	"You will find scrolls in adjoining rooms.\n "+
	"You are invited to read as much as you like.\n\n "+
	"Eil-Galaith.\n");
	add_cmd_item("plaque", "read", "Welcome to the Sanctuary "+
	"Tower.\n\nWe are pleased that you have found your way here.\n "+
	"You will find scrolls in adjoining rooms.\n "+
	"You are invited to read as much as you like.\n\nEil-Galaith.\n");
	
        add_prop(ROOM_I_INSIDE, 1);
        add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
        add_prop(ROOM_M_NO_ATTACK, 1);
	add_exit("start", "north", members_only);
	add_exit("/d/Khalakhor/inisi/galaith/room/isl0105", "south");
	add_exit("join", "east");
	add_exit("library", "west");
	add_exit("post", "up");
	add_fail("auto", "A wall stops you.\n");    
}
