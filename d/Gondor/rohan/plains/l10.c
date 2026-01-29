#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

#define RHARD   20

static object  Uruk,
              *Orcs = allocate(4 + random(3));

public void
create_plain()
{
    set_geo("flat");
    set_wet("damp");
    set_grass("thick, dark green and spicy");
    set_land("the West Emnet");
    set_where("east");
    set_special(1);
    set_river_name("Entwash");
    set_rhard(RHARD);
    set_rwhere("north and east");
    add_exit("NotOpen/m10","north", drown, RHARD);
    add_exit("NotOpen/l11","east",  drown, RHARD);
    add_exit("k10","south",     0,     5);
    add_exit("l09","west",      0,     5);

    reset_room();
    set_drink_from( ({"entwash","river","stream"}) );
}

public varargs object
clone_npc(object npc, string file, mixed restrain_path, function setup)
{
    if (!objectp(npc))
    {
	if (!restrain_path)
	{
	    restrain_path = ({ (ROH_DIR + "plains") });
	}
	/* call clone_npc in ~gondor/std/room so we don't set random_move */
	npc = ::clone_npc(npc, file, restrain_path, setup);
	if (objectp(Uruk) && (npc != Uruk))
	{
            Uruk->team_join(npc);
	}
    }
    return npc;
}

public void
reset_room()
{
    ::reset_room();
    Uruk = clone_npc(Uruk, ROH_DIR + "npc/wemneturuk");
    set_alarm(1.0, 0.0, &clone_npcs(Orcs, NPC_DIR + "std_orc", 2.0));
    set_alarm(30.0, 0.0, &Uruk->set_random_move(15));
}

