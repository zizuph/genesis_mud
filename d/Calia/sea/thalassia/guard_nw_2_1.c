
/* 	Thalassian Guard Barracks

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

#define NUM 3
#define THIS this_object()

inherit "/d/Calia/std/water_room";
object this, *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object("/d/Calia/sea/creatures/br_triton");
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
    set_short("Lookout tower");
    set_long("You are in a small room that serves as the "+
        "lookout tower for this guard tower. There is a "+
        "small opening in the wall that appears to look "+
        "down outside the tower itself. North you see a "+
        "set of stairs leading back down to the first floor "+
        "of the tower. There is a room to the west that "+
        "appears to have beds in it.\n");
    add_item(({"opening","small opening"}),
        "This small opening looks down onto the road below. "+
        "If you were to examine the small slit or the road below, "+
        "you could most likely see if anyone was there.\n");
    add_item(({"below","slit","small slit","road",
        "road below"}),"@@exa_below@@");
    add_item("stairs","The stairs are in the room to the "+
        "north and lead down to the first floor of the "+
        "tower.\n");
    add_item(({"bed","beds"}),"The chamber to the west seems "+
        "to have beds in it, probably used as a sleeping "+
        "area for those who stand guard in this tower.\n");

    add_swim_exit(THAL+"guard_nw_2_3","north",0,1);
    add_swim_exit(THAL+"guard_nw_2_2","west",0,1);
    this = THIS;
    set_alarm(1.0, 0.0, reset_room);

    // Do not remove the next line, it is to load the path room
    // to make sure the check for players works and doesn't runtime
    "/d/Calia/sea/thalassia/path4"->teleledningsanka();
}

string
exa_below()
{
    object below = find_object("/d/Calia/sea/thalassia/path4");
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
    else results = "You do not see anyone on the below.";

    return "Far below you see the road leading into Thalassia.\n" + 
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



