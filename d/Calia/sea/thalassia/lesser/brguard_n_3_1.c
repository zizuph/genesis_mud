
/* 	Bridge Guard Tower in the Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <ss_types.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define NUM 2
#define THIS this_object()
#define ROOM_SOUTH "/d/Calia/sea/thalassia/lesser/lesser20"
#define ROOM_NORTH "/d/Calia/sea/thalassia/major/major29"

inherit "/d/Calia/std/water_room";
object this, *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/tin_triton");
    guard[i]->equip_me();
    guard[i]->move(this);
    tell_room(this, QCTNAME(guard[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

void
create_water_room()
{
    set_short("Bridge lookout tower");
    set_long("You are at the top of the tower crowning "+
        "the bridge between these two sections of the city. "+
        "Heading down below you is a spiral staircase made "+
        "from white marble. There are two windows in this "+
        "tower, one looking north and the other looking to "+
        "the south. This tower is used to monitor those "+
        "people who are entering and exiting this section "+
        "of the city.\n");
    add_item(({"stairs","spiral stairs","spiral staircase"}),
        "The spiral staircase is made from white marble "+
        "blocks and leads down to the room below.\n");
    add_item(({"window","windows","two windows"}),"These "+
        "two windows overlook the road leading into different "+
        "parts of the city. One is looking north and the other "+
        "is looking south. You could probably examine each one "+
        "seperately.\n");
    add_item(({"north road","north","north window"}),
        "@@exa_north@@");
    add_item(({"south road","south","south window"}),
        "@@exa_south@@");
    add_swim_exit(THALL+"brguard_n_2_1","down",0,1);
    this = THIS;
    set_alarm(1.0, 0.0, reset_room);

    // Do not remove the next lines, it is to load the viewable rooms
    // to make sure the check for players works and doesn't runtime
    ROOM_SOUTH->teleledningsanka();
    ROOM_NORTH->teleledningsanka();
}

string
exa_south()
{
    object below = find_object(ROOM_SOUTH);
    object *below_live_objects = FILTER_LIVE(all_inventory(below));
    object *too_small_to_see = ({});

    int perception = (50 - TP->query_skill(SS_AWARENESS)) * 1000;
    int m;
    int n;
    string results = "";

    if (below->query_prop(ROOM_I_LIGHT) > 0
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        m = sizeof(below_live_objects);
        for (n=0; n < m; n +=1)
        {
            if (below_live_objects[n]->query_prop(OBJ_I_VOLUME) <= perception)
                too_small_to_see += ({below_live_objects[n]});
            }
        below_live_objects -= too_small_to_see;
    }
    if (sizeof(below_live_objects))
        results = "On the road below you see "+
        COMPOSITE_ALL_LIVE(below_live_objects)+".";
    else results = "You do not see anyone on the road below.";

    return "Through the window and far below you see the "+
        "road leading into the Lesser Zone.\n" + 
        results + "\n";
}

string
exa_north()
{
    object below = find_object(ROOM_NORTH);
    object *below_live_objects = FILTER_LIVE(all_inventory(below));
    object *too_small_to_see = ({});

    int perception = (50 - TP->query_skill(SS_AWARENESS)) * 1000;
    int m;
    int n;
    string results = "";

    if (below->query_prop(ROOM_I_LIGHT) > 0
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        m = sizeof(below_live_objects);
        for (n=0; n < m; n +=1)
        {
            if (below_live_objects[n]->query_prop(OBJ_I_VOLUME) <= perception)
                too_small_to_see += ({below_live_objects[n]});
            }
        below_live_objects -= too_small_to_see;
    }
    if (sizeof(below_live_objects))
        results = "On the road below you see "+
        COMPOSITE_ALL_LIVE(below_live_objects)+".";
    else results = "You do not see anyone on the road below.";

    return "Through the window and far below you see the "+
        "road leading into the Major Zone.\n" + 
        results + "\n";
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (guard[i])
            return 1;

    remove_object();
}
