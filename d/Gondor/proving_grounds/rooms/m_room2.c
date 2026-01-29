
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"



public void create_gondor();
public void reset_room();

object *Mage = allocate(1);


public string long_func();

public void clone_npc(object npc, string npc_file);

public void
create_gondor()
{
    set_short("between two large trees in Ithilien");
    set_long(long_func);


    add_exit("m_room1", "north");
    add_exit("m_room3", "south");

    reset_room();

}



public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;

	longtxt = "You are standing in the forest of Ithilien.";
    return BSN(longtxt);
}


public void
reset_room()
{

	if (!objectp(Mage))
	{
	    set_alarm(2.0, 0.0, &clone_npcs(Mage,
		"/d/Gondor/common/guild2/newnpc/npc_mage", 1.0));
	}
}

public object
clone_npc(object npc, string npc_file)
{
    int     b = 35,
    rs = random(41);

    if (objectp(npc))
	return npc;

    npc = clone_object(npc_file);
    npc->default_config_npc(b + b + rs);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

