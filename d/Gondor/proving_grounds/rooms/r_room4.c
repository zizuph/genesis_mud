
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"



public void create_gondor();
public void reset_room();

object *Rangers = allocate(4);
object Orc1, Orc2, Orc3, Orc4;


public string long_func();

public void clone_npc(object npc, string npc_file);

public void
create_gondor()
{
    set_short("in a forest in Ithilien");
    set_long(long_func);


    add_exit("xroads", "east");
    add_exit("r_room3", "west");

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

	if (!objectp(Rangers))
	{
	    set_alarm(2.0, 0.0, &clone_npcs(Rangers,
		NPC_DIR + "i_ranger", 1.0));
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

