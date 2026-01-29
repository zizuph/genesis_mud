/*
 *  IGARD_PLAIN_PATHS + "sw_dome2.c"
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

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "plain_funcs.c";

#define CLIMBING_THE_DOME    "_climbing_the_dome"

public void        create_gondor();
public string      long_desc();
public int         climb_dome();
public int         exit_room();
public int         check_dome();

static object  Troop;
int distance = 3;

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

    add_exit(IGARD_PLAIN_PATHS  + "sw_path2h.c", "south", check_dome, 2, 0);

    add_cmd_item(({"dome", "the dome", "up dome", "up the dome"}), 
            "climb", &exit_room());

    add_prop(ROOM_I_INSIDE, 0);

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

    if (!SFI1 && !SFI2 && !SFI3)
    {
        set_alarm(0.0, 0.0, &write("You look about for a handhold on the "
            + "dome. You can't seem to find any and decide not to bother "
            + "climbing the dome.\n"));
        return 1;
    }

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
    if (!SFI1 && !SFI2 && !SFI3)
    {
        return 1;
    }

    if (!SFI3)
    {
        say(QCTNAME(TP) + " reaches the top and falls into the copper "
            + "pipe! Suddenly, " + HE_SHE(TP) + " rockets out of the dome "
            + "and sails away high into the air and over the ringwall.\n");
        write("Apparently this was the wrong place. A huge gout of steam "
            + "erupts from below, sending you reeling high into the air.\n");
        TP->move_living("M", IGARD_ROOM + "catapult_room", 1, 0);
        TP->remove_prop(CLIMBING_THE_DOME);
        TP->add_prop(FURNACE_KILLED_ME, 1);
        return 1;
    }

    tell_room(IGARD_QUEST + "entry3_stair", QCNAME(TP) 
            + " tumbles down from above, landing on the floor with a loud "
            + "splat.\n");
    TP->move_living("M", IGARD_QUEST + "entry3_stair", 1, 0);
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



