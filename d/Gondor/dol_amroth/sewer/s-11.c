/* -*- Mode: C -*-
 * Sewer k-07.c
 */
#include "../defs.h"

inherit DOL_STD+"sewer";

#include <macros.h>
#include <ss_types.h>

int
secret_seen()
{
    if (this_player()->query_prop(DOL_I_FOUND_SEWER_DOOR) == 1)
        return 0;

    return 1;
}

int
secret_found()
{
    if (this_player()->query_prop(DOL_I_FOUND_SEWER_DOOR) == 1)
	return 0;

    write("There is no obvious exit south.\n");
    return 1;
}

void
create_sewer()
{
    add_prop(OBJ_I_SEARCH_TIME, 7);
    add_prop(OBJ_S_SEARCH_FUN, "search_wall");

    add_exit(DOL_SEWER + "r-10", "northwest", 0, 2);
    add_exit(DOL_SEWER + "t-12", "southeast", 0, 2);
    add_exit(DOL_SEWER + "s-12", "south", &secret_found(), 2, 
	     &secret_seen());
}

public string
search_wall(object tp, string str)
{
    if (str != "walls" && str != "wall" && str != "wall for door" &&
	str != "walls for door" && str != "here for door")
	return "Your search reveals nothing.\n";

    if (this_player()->query_prop(DOL_I_FOUND_SEWER_DOOR) == 1)
	return "Your search reveals nothing.\n";

    if (this_player()->query_skill(SS_AWARENESS) > 32 &&
	CAN_SEE_IN_ROOM(this_player()) )
    {
	this_player()->add_prop(DOL_I_FOUND_SEWER_DOOR, 1);
	return "You see find a hidden door leading south.\n";
    }

    return "Your search reveals nothing.\n";
}

