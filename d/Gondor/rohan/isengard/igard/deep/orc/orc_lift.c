/*
 *  IGARD_DEEP_WARG + "orc_lift.c"
 *
 *  Lift out of the orc dens.
 *
 *  Last modified by Alto, 24 November 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

inherit IGARD_LIB + "igard_funcs.c";
inherit IGARD_LIB + "orcden_funcs.c";

public void        create_gondor();

public string      long_func();
public int         start_escalator();
public int         move_escalator();
public int         exit_escalator();

object             actor;

public void
create_gondor()
{
    set_short("A clattering lift");
    set_long(long_func);

    underground_add_items();

    add_item(({"lift", "room", "surroundings", 
        "device", "contraption"}), long_func);

    add_item(({"platform", "wooden platform", "broad platform", "floor"}),
        "The floor of the lift is made of wood and seems rather flimsy. "
        + "Hopefully you will not fall through it and hurtle to your death "
        + "somewhere far below.\n");
    add_item(({"wood"}), "The platform is made of it. It does not look all "
        + "that sturdy.\n");
    add_item(({"shaft", "wide shaft"}), "The shaft extends far upward and "
        + "out of sight.\n");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}


public string
long_func()
{
    string  longtxt;

    longtxt = 
        "You are standing on a broad wooden platform. The platform is "
        + "part of a great moving lift which moves you higher and higher "
        + "up the broad shaft surrounding you.\n"; 

    return longtxt;
}


int
move_escalator()
{
    actor = TP;

    set_alarm(0.0, 0.0, &write("The lift suddenly lurches upward, "
        + "causing you to stumble in attempt to catch your balance.\n"));
    set_alarm(5.0, 0.0, &write("The lift groans loudly.\n"));
    set_alarm(10.0, 0.0, &write("The platform stops suddenly!\n"));
    set_alarm(15.0, 0.0, &write("You almost fall down as the "
        + "platform suddenly lurches into action again.\n"));
    set_alarm(20.0, 0.0, &write("Something squeals and clanks.\n"));
    set_alarm(25.0, 0.0, &write("The lift finally crashes into the "
        + "open air.\n"));

    return 1;

}


int
exit_escalator()
{
    actor = TP;

    write("You lurch over the copper pipe and tumble down the dome.\n");
    tell_room(environment(actor), QCTNAME(actor) + " stumbles out of "
        + "sight.\n", 
        ({actor}));
    tell_room(IGARD_PLAIN_PATHS + "ne_dome1.c", QCTNAME(TP) + " lurches over "
        + "the copper pipe and tumbles down the dome.\n");

    TP->move_living("M", IGARD_PLAIN_PATHS + "ne_dome1.c", 1, 0);

    return 1;
}


int
start_escalator()
{
    move_escalator();
    set_alarm(26.0, 0.0, &exit_escalator());        
    return 1;
}



public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_escalator();
}


