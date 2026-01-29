
/* 	Bridge Guardhouse in Thalassia

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
#define ROOM_WEST "/d/Calia/sea/thalassia/grove/grove5"
#define ROOM_EAST "/d/Calia/sea/thalassia/citadel/citadel6"

inherit "/d/Calia/std/water_room";
object this, *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/ori_triton");
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
        "tower, one looking west and the other looking to "+
        "the east. This tower is used to monitor those "+
        "people who are entering and exiting this section "+
        "of the city.\n");
    add_item(({"stairs","spiral stairs","spiral staircase"}),
        "The spiral staircase is made from white marble "+
        "blocks and leads down to the room below.\n");
    add_item(({"window","windows","two windows"}),"These "+
        "two windows overlook the road leading into different "+
        "parts of the city. One is looking west and the other "+
        "is looking east. You could probably examine each one "+
        "seperately.\n");
    add_item(({"west road","west","west window"}),
        "@@exa_west@@");
    add_item(({"east road","east","east window"}),
        "@@exa_east@@");
    add_swim_exit(THALC+"brguard_w_2_1","down",0,1);
    this = THIS;
    set_alarm(1.0, 0.0, reset_room);

    // Do not remove the next lines, it is to load the viewable rooms
    // to make sure the check for players works and doesn't runtime
    ROOM_WEST->teleledningsanka();
    ROOM_EAST->teleledningsanka();
}

string
exa_west()
{
    object below = find_object(ROOM_WEST);
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
exa_east()
{
    object below = find_object(ROOM_EAST);
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
        "road leading into the Citadel.\n" + 
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


