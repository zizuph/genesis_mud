/*
 *  The Tower of the Society of the Morgul Mages
 *
 *  A room on the fourth level of the tower.
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";
 
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
 
//	Prototypes
public void reset_room();

public void
create_morgul_tower_room()
{
    set_level(4);
    set_room_type("dark chamber");
    set_extra_long("A window is set into "
      + "the south wall. Next to the doorway there is a steel-plated "
      + "footlocker and a large wooden chest is standing "
      + "at the western wall of the chamber.");

    add_prop(ROOM_I_LIGHT,1);

    add_exit(MAGES_DIR + "tower/tower_4c", "north", 0, 0);

    add_roof();
    add_walls();
    add_floor();

    add_item("window", BSN("Looking out of the window, you see the "
      + "cliffs that rise south of the Morgul vale. They almost seem "
      + "to be close enough to touch."));

    reset_room();
    add_prop(ROOM_I_NO_CLEANUP, 1); // For droproom purposes
}
 
public int 
check_time(string str)
{
    int     hour, day, month, year;
    string  time, shour;
    object  clock;

    clock = find_object(CLOCK);
    time = (string)clock->query_time_of_day();
    hour = (int)clock->query_hour();
    if (hour == 12)
        shour = "noon";
    else if (hour == 0)
        shour = "midnight";
    else
    {
        if (hour > 12)
            hour -= 12;
        shour = hour + " o'clock in the " + time;
    }
    day = (int)clock->query_day();
    month = (int)clock->query_month();
    year = (int)clock->query_year();
    write(BSN("You look through the window and think that it is about "+
    shour+" of day "+day+", month "+ month+" in the year "+year+"."));
    say(QCTNAME(TP)+" looks through the window, trying to decide "+
        "what time it is.\n",TP);
    return 1;
}
 
string
tod()
{
    object clock = find_object(CLOCK);
    string time  = (string)clock->query_time_of_day();
    return time;
}
 
public int
enter_window(string str)
{
    if (str == "window" || str == "the window")
    {
        NF("No, you would hurt yourself!\n");
        return 0;
    }
    NF("Enter what?\n");
    return 0;
}
 
public void 
init()
{
    add_action(enter_window, "enter");
    ::init();
}

public void
reset_room()
{
    object  chest, footlocker;

    if (!objectp(present("chest", this_object())))
    {
        chest = clone_object(MAGES_DIR + "obj/chest");
        chest->move(this_object());
    }

    if (!objectp(present("footlocker", this_object())))
    {
        footlocker = clone_object(MAGES_DIR + "obj/footlocker");
        footlocker->move(this_object());
    }

}

