
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"



public void create_gondor();
public void reset_room();

object Orc1, Orc2, Orc3, Orc4;


public string long_func();

public void clone_npc(object npc, string npc_file);

public void
create_gondor()
{
    set_short("between two large trees in Ithilien");
    set_long(long_func);


    add_exit("xroads", "west");
    add_exit("o_room2","east");

    reset_room();

}



public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;

	longtxt = "You are standing in the forest " +
	"of Ithilien. " +
	"A clearing stretches out to the west and east. ";
    return BSN(longtxt);
}


public void
reset_room()
{

	if (!objectp(Orc1))
	{
	    Orc1 = ::clone_npc(Orc1, CAMP_NPC_DIR + "ithil_uruk");
	    Orc1->set_monster_home(CAMP_ROOM_DIR + "fort1");
	}
	if (!objectp(Orc2))
	{
	    Orc2 = ::clone_npc(Orc2, CAMP_NPC_DIR + "ithil_uruk");
	    Orc2->set_monster_home(CAMP_ROOM_DIR + "fort1");
	}
	if (!objectp(Orc3))
	{
	    Orc3 = ::clone_npc(Orc3, CAMP_NPC_DIR + "ithil_uruk");
	    Orc3->set_monster_home(CAMP_ROOM_DIR + "fort1");
	}
	if (!objectp(Orc4))
	{
	    Orc4 = ::clone_npc(Orc4, CAMP_NPC_DIR + "ithil_uruk");
	    Orc4->set_monster_home(CAMP_ROOM_DIR + "fort1");
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

