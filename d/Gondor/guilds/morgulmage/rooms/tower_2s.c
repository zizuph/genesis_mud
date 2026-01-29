/*
 *  The Tower of the Society of the Morgul Mages
 *
 *  A room on the second level of the tower.
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";
 
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
 
public void
create_morgul_tower_room()
{
    set_level(2);
    set_room_type("dark chamber");
    set_extra_long("The chamber is empty. A window is set into "
        + "the south wall, and the doorway leads north to the dark "
        + "staircase.");

    add_prop(ROOM_I_LIGHT,1);

    add_exit(TOWER_DIR + "tower_2c", "north", 0, 0);

    add_roof();
    add_walls();
    add_floor();
    add_item(({"staircase", "dark staircase"}), 
        "The staircase lies beyond the doorway to the north.");

    add_item(({"window", "cleft", "city wall", "wall", "face",
          "mountain face", "narrow cleft"}),   
        
          "Looking out of the window, you see the cliffs that rise south "
        + "of the Morgul vale. Below the window is the top of the city "
        + "wall, and beyond the walls is only a narrow cleft separating "
        + "the walls from the steep mountain face.");
}
 
public int 
check_time(string str)
{
    int     day,
            year;
    string  month_s;

    if (strlen(str))
    {
        NFN(CAP(query_verb()) + " what?");
        return 0;
    }

    day     = clock->query_day();
    year    = clock->query_year();
    month_s = clock->query_month_s();

    write("You look through the window to study the sky. "
      + "It is about " + qstime() + " on the " 
      + LANG_WORD(day) + " of the month of " + month_s
      + " in the year " + year + ".");
    say(QCTNAME(TP)+" looks through the window, trying to decide "+
        "what time it is.\n",TP);
    return 1;
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

