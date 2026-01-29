#pragma strict_types

inherit "/std/object";

#include "zigg.h"
#include <macros.h>
#include <stdproperties.h>

/*
 *  This gets the time from the avenir_time object and returns the
 *  get_time_text string.
 */
public string
tell_time(void)
{
    return AVTIME->get_time_text();
}

/*
 * This notifies us of the change of hours once every hour.
 */
public int
avenir_event(int year, int week, int day, int hour)
{
    /* This will tell the time every hour. */
    tell_room(environment(this_object()),
	"The clepsydra indicates that it is currently the " +
	tell_time() + ".\n");

    /* Needed to keep registered. */
    return 1;
}

static void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("clepsydra");
    set_pname("clepsydrae");
    add_name(({"clock", "water clock", "fountain"}));
    set_adj(({"water", "glass"}));
    set_short("bronze and glass clepsydra");
    set_long("It is a bronze and glass clepsydra, or water clock.\n"+
        "Clepsydrae are devices which use the flow of water "+
        "to measure the passage of time.\n   Doubling as an "+
        "intricate and appealing fountain, this clepsydra "+
        "is fed by hidden water channels carved throughout the "+
        "stonework of the Ziggurat. Water flows through a pipe "+
        "and empties into a bronze basin with three openings "+
        "near the bottom. The three streams of water arcing "+
        "from the basin then fill coloured glass recepticles of "+
        "varying sizes, each of which indicate Hour, day, and "+
        "Wei.\n   The clepsydra indicates that it is currently the "+
        "@@tell_time@@.\n");

    add_item(({"basin", "bronze basin", "openings"}),
        "It is a broad, oval basin made of bronze. There are three "+
        "differently-sized openings near the base, each of which "+
        "projects a crystalline rope of water.\n");
    add_item(({"water", "stream", "streams", "rope"}),
        "The water is beautifully clear, and it sparkles like "+
        "crystals as it cascades from the basin.\n");
    add_item(({"glass", "tubes", "recepticles", "coloured glass",
        "coloured glass recepticles"}),
        "Three recepticles with bands of coloured glass, each "+
        "recording a different aspect of the sybarite year.\n");

    add_prop(OBJ_M_NO_GET, "It is far too heavy.\n");
    set_no_show_composite(1);

    if (IS_CLONE)
	AVTIME->add_event(TO);
}
