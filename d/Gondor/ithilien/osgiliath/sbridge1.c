#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";
inherit "/d/Gondor/ithilien/forest/room_tells";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public int     check_allow();

static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("south of the Morgulduin bridge by Osgiliath");
    set_long("A foul smell clouds your thoughts as you near the bridge "+
        "crossing the Morgulduin. The stone bridge looks ancient, but still "+
        "unscathed, leading northwest across the reeking stream towards "+
        "the ruins of Osgiliath. South of here, and stretching out east is "+
        "the southern forest of Ithilien.\n");
    add_item("bridge", "The bridge is made of stone, and seems ancient. " +
        "It is still whole, but orcs have scribbled crude paintings and foul " +
	"words in the tongue of Mordor, so it's not nice to look at. Below " +
        "the bridge, the Morgulduin stream flows, dark reeking fumes rising " +
        "from it.\n");
    add_item( ({"water","morgulduin","river","stream"}), 
        "The Morgulduin is flowing towards the Anduin under the bridge. " +
        "From the reeking water dark fumes are rising, giving off foul " +
        "smells that are clouding your thoughts.\n");

    add_exit(ITH_DIR + "osgiliath/bank",     "west",                0, 2);
    add_exit(ITH_DIR + "osgiliath/sbridge2", "northwest", check_allow, 2);

    reset_room();

    add_orc_camp_tells();

}

public int
check_allow()
{
    object stopper;

    if (query_friend_or_foe(TP) == -1)
        return 0;
    if (stopper = present("_stopping_npc",TO)) 
    {
	if (CAN_SEE_IN_ROOM(stopper) && CAN_SEE(stopper,TP) &&
	    (stopper->query_skill(SS_AWARENESS) > TP->query_skill(SS_SNEAK)/3)) 
	{
	    write(CAP(LANG_ADDART(stopper->query_race_name())) + 
		  " stops you from crossing the bridge.\n");
	    return 1;
	}
	write("You sneak past the " + stopper->query_race_name() + "!\n");
    }
    write(BS("You walk across the stone bridge, trying not to breathe " +
	     "in the fumes from the stream beneath.\n"));
    return 0;
}

static varargs object
clone_npc(object npc, string file, mixed path)
{
    if (!objectp(npc))
    {
	npc = ::clone_npc(npc, file, path);
	npc->add_name("_stopping_npc");
    }
    return npc;
}

public void
reset_room()
{
    clone_npcs(Orc, NPC_DIR + "std_mordor_orc", -1.0);
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
