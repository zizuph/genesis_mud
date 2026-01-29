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
    set_short("in a storage tent");
    set_long(long_func);

    add_item(({"wall","walls","flap","tent"}),"The entire tent, " +
      "walls, and open flap are all made of canvas.\n");
    add_item(({"box","boxes"}),"The boxes here are stacked about " +
	     "the room and are sealed shut.\n");
    add_exit(CAMP_ROOM_DIR + "fort5.c","north");

add_prop(ROOM_I_INSIDE, 1);
    reset_room();

}


public string
long_func()
{
    string time = tod(),
    longtxt,
    moon;


    longtxt = "This tent is used to store materials which may be of use " +
"to the camp at a later date.  " +
    "Aside from the tent flap leading out and the boxes which take up " +
    "most of the space, there is little of interest here.  ";

    return BSN(longtxt);     

}

public void
reset_room()
{
    
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












