/*
 *  IGARD_PLAIN_PATHS + "nw_dome1.c"
 *
 *  Experimental path on the plain of Isengard.
 *
 *  Last modified by Alto, 22 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

#define CLIMBING_THE_DOME    "_climbing_the_dome"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "plain_funcs.c";

public void        create_gondor();
public string      long_desc();
public int         climb_dome();
public int         exit_room();
public int         check_dome();

static object  Troop;
int distance = 6;

public void
create_gondor()
{
    set_short("Before a large dome of stone");
    set_long(&long_desc());

    sky_add_items();
    outside_add_items();
    plain_add_items();
    add_plain_tells();
    path_add_items();
    dome_add_items();

    add_item(({"room", "area", "surroundings", "area", "place",
        "landscape"}), long_desc);

    add_exit(IGARD_PLAIN_PATHS  + "nw_path1f.c", "north", check_dome, 2, 0);

    add_prop(ROOM_I_INSIDE, 0);

    add_cmd_item(({"dome", "the dome", "up dome", "up the dome"}), 
            "climb", &exit_room());

    reset_room();
}


string
long_desc()
{
    return "You stand before a large dome of stone rising upon the "
      + "plain of Isengard like a festering boil." + sky_desc()
      + plain_tower_desc(distance)
      + "Great gouts of steam and unwholesome vapours belch from "
      + "a great copper pipe at its top. Leading away from the dome is "
      + "a small gravel path.\n";
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
     sky_add_items();
     start_room_tells();

}


public void
reset_room()
{
    if (!objectp(Troop))
    {
        Troop = clone_object(IGARD_NPC + "igard_orc4_rider.c");
        Troop->set_restrain_path(IGARD_PLAIN_PATHS);
        Troop->arm_me();
        Troop->move_living("down", TO);
        Troop->add_warg();
        Troop->add_3_orcs(3);
    }
}


int
climb_dome()
{
    actor = TP;

    TP->add_prop(CLIMBING_THE_DOME, 1);

    set_alarm(0.0, 0.0, &write("You look about for a handhold on the "
        + "dome. Pieces of it crumble away beneath your grip as you "
        + "begin to climb it.\n"));
    set_alarm(1.0, 0.0, &write("You almost lose your footing!\n"));
    set_alarm(2.0, 0.0, &write("Almost there ...\n"));
    set_alarm(3.0, 0.0, &write("You reach the top and fall into the "
        + "copper pipe!\n"));

    tell_room(environment(actor), QCTNAME(actor) + " begins to scramble "
        + "up the side of the dome.\n", 
        ({actor}));

    return 1;
}


int
move_player()
{
    say(QCTNAME(TP) + " reaches the top and falls into the copper "
        + "pipe!\n");
    tell_room(IGARD_DEEP_PRISON + "entry_stair1", QCNAME(TP) 
        + " tumbles down from above, landing on the floor with a loud "
        + "splat.\n");

    TP->move_living("M", IGARD_DEEP_PRISON + "entry_stair1", 1, 0);
    TP->remove_prop(CLIMBING_THE_DOME);

    return 1;
}


int
check_dome()
{
    if (TP->query_prop(CLIMBING_THE_DOME))
    {
        write("You are climbing the dome! You would probably fall and "
            + "break your neck if you tried to back out now.\n");
        return 1;
    }

    return 0;
}


int
exit_room()
{
        climb_dome();
        set_alarm(4.0, 0.0, &move_player());        
        return 1;

}

