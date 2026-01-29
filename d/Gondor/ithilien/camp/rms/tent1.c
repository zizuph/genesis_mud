//
//  A normal tent.
//
//  Coded by:  Morbeche, Nov 19th 1999
//
//                                      Copyright @Morbeche Nov 8th 1999
//
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <formulas.h>

object Orc1, Orc2;

public void create_gondor();
public void reset_room();

public string long_func();

public void clone_npc(object npc, string npc_file);

int rq_stage_stored = rq_stage();

public int
query_being_built()
{

    if (rq_stage_stored < RQ_GANDALF_IN_BAGEND)
    {
	return 0;
    }
    if ((rq_stage_stored >= RQ_GANDALF_IN_BAGEND) &&
      (rq_stage_stored < RQ_OSGILIATH_ATTACK))
    {
	return 1;
    }

    return 2;
}

public void
create_gondor()
{
    set_short("in a barracks tent");
    set_long(long_func);

    add_item(({"wall","walls","flap","tent"}),"The entire tent, " +
      "walls, and open flap are all made of canvas.\n");
    add_item(({"row","bed","beds"}),"The beds here are very simple " +
      "and do not look very comfortable.\n");
    add_item("table","The table is made of wood, and has nothing " +
      "on it.\n");   

add_prop(ROOM_I_INSIDE, 1);
    add_exit(CAMP_ROOM_DIR + "fort3.c","south");

    reset_room();

}


public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;


    longtxt = "This tent is quite bare, consisting of only a row " +
    "of beds and a table.  Leaving out the flap will lead back into " +
    "the camp.  ";

    return BSN(longtxt);     

}

public void
reset_room()
{
    if (rq_stage_stored < RQ_OSGILIATH_ATTACK)
    {
	if (!objectp(Orc1))
	{
	    Orc1 = ::clone_npc(Orc1, NPC_DIR + "i_ranger");
	}
	if (!objectp(Orc2))
	{
	    Orc2 = ::clone_npc(Orc2, NPC_DIR + "i_ranger");
	}
    }
    if (rq_stage_stored >= RQ_OSGILIATH_ATTACK)
    {
	if (!objectp(Orc1))
	{
	    Orc1 = ::clone_npc(Orc1, MORGUL_DIR + "npc/ithil_orc");
	}
	if (!objectp(Orc2))
	{
	    Orc2 = ::clone_npc(Orc2, MORGUL_DIR + "npc/ithil_orc");
	}                                                       

    }
}

public object
clone_npc(object npc, string npc_file)
{

    if (objectp(npc))
	return npc;

    npc = clone_object(npc_file);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}












