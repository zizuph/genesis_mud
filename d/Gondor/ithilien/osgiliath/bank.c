/*
 *	/d/Gondor/ithilien/osgiliath/bank.c
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("on the east bank of the river Anduin");
    set_long("You are standing on the east riverbank of the Anduin river. "+
    "A foul-smelling river flows past to the north of here, its steaming "+
    "dark water merging with Anduin just to the northwest. A bridge "+
    "from the old days crosses the Morgulduin to the east, leading into "+
    "the ruined city of Osgiliath. The ruins are beyond the stream "+
    "to the north. Green ilexes and tall oaks grow in thickets to "+
    "the southeast, marking the edge of the southern forests of "+
    "Ithilien. Far beyond the great river Anduin, you spot a large "+
    "circular stone wall.\n");
    add_item("buildings","One of the ruined buildings looks almost like a palace,\n"+
    "or a fortress of some sort.\n");
    add_item("bridge","It is an old bridge of stone, built in the ancient days when\n"+
    "the Morgulduin was called the Ithilduin and was still a stream with\n"+
    "fresh clear water from the sources in the Imlad Ithil. Now the bridge\n"+
    "is even more an advantage, for you would not like the thought of\n"+
    "attempting to wade across the Morgulduin, with its bewitched water.\n");
    add_item(({"stream","morgulduin"}),
        "The Morgulduin comes running from the dark mountains you can see\n"+
    "looming in the horizon east. It runs out of the Morgul valley, and\n"+
    "passes close to Minas Morgul on its way. The stench from its black\n"+
    "water disgusts you, and makes you feel sick.\n");
    add_item("wall","The great circular wall you see across the river, is the Rammas\n"+
    "Echor. The wall is built to defend Minas Tirith against the\n"+
    "feared onslaught of the Menace of the East.\n");
    add_item("ruins","The ruins are old; from the days when Gondor was still a mighty\n"+
    "nation. Now the armies of the Shadow have forced the people to abandon\n"+
    "the city on the river, and the city has crumbled.\n");
    add_item(({"ilex","ilexes","oak","oaks","thickets","forest","forests",
	       "tree","trees"}), BS(
    "To the southeast, you can see impenetrable thickets of underbrush " +
    "consisting mainly of green ilexes growing between the stems " +
    "of tall oaks. Further away the thickets change into a dense " +
    "forest, the northern spurs of the forests of Southern Ithilien. \n"));

    add_exit(ITH_DIR + "osgiliath/sbridge1", "east",  0, 2);
    add_exit(ITH_DIR + "osgiliath/bank1",    "south", 0, 2);

    add_orc_camp_tells();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
