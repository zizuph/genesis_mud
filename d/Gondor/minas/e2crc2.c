/*
 *  Last modified by Alto, 09 June 2001
 *      Added room tells and revised descriptions
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";
inherit "/d/Gondor/minas/lib/street_funcs.c";

#include <filter_funs.h>
#include "/d/Gondor/std/tell.c"

#include "/d/Gondor/defs.h"

#define OPEN_HOUR 4
#define CLOSE_HOUR 10

static int     Om_Aid = 0;

private string
read_sign()
{
    return
        "The sign above the shop door reads:\n\n"+
        "              - Minas Tirith General Store -\n"+ 
        "    open from "+OPEN_HOUR+" in the morning to "+CLOSE_HOUR+" in the evening.\n"+
        "    We have the equipment you need for your journeys!\n";
}

public void
create_street()
{
    set_circle("Second");
    set_streetname("Main Street");
    set_streettype("broad street");
    set_areaname("eastern");
    set_wealth(1);
    set_activity(1);
    add_exit(MINAS_DIR + "e1crc2","south");
    add_exit(MINAS_DIR + "tcrc2","north");
    add_exit(MINAS_DIR + "rooms/mtshop", "west", "@@checktime");

    add_item(({"shop","sign","door"}), read_sign());
    add_cmd_item(({"shop","sign","door"}), "read", read_sign());

    set_extraline("The street continues north into a tunnel through the "+
        "huge mountain-pier, and south along the Second Circle. "+
        "Above the wall to the west you see the top of the White Tower "+
        "stretching tall towards the sky. There is a shop to the west, with a sign above the door. ");
    add_item("tower","You can only see the upper parts of the White Tower from here,\n"+
        "the rest is obscured by the Third Wall to the west. The tower looks\n"+
        "magnificent standing there, with silvery white walls.\n");
    add_item("wall","The Third Wall lies to the west, protecting the inner parts of\n"+
        "the town.\n");

    /* These items are similar in all streets on all levels */

    add_street_items();

    set_tell_time(150);

    /* These tells are common to all streets */

    add_street_tells();

    /* These tells are unique to this circle */

    reset_room();

}

public int 
checktime(int silent = 0)
{
    object clock = find_object(CLOCK);
    string time  = clock->query_hour();

    if ((time >= OPEN_HOUR) && (time < (CLOSE_HOUR+12)))
        return 0;
    if (!silent)
        write("The shop is closed, as it is "+clock->query_time_of_day()+". Come back later.\n");
    return 1;
}

public void 
open_msg()
{
    if (!sizeof(FILTER_LIVE(all_inventory(TO))))
        return;

    if (!checktime(1))
    {
        tell_room(TO, "A slender young human opens the shop door.\n");
        return;
    }

    if (!Om_Aid || !sizeof(get_alarm(Om_Aid)))
        Om_Aid = set_alarm(30.0, 0.0, open_msg);
}

public void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob || !living(ob))
        return;

    if (checktime(1))
        open_msg();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!ob || !living(ob))
        return;

    if(interactive(ob))
        start_room_tells();

    if (Om_Aid)
    {
        remove_alarm(Om_Aid);
        Om_Aid = 0;
    }
}
            


