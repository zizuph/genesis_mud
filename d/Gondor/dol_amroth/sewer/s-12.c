/* -*- Mode: C -*-
 * Sewer s-12.c
 */
#include "../defs.h"

inherit DOL_STD+"inside";

#include <macros.h>
#include <ss_types.h>

int TableSearch;

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

    write("There is no obvious exit north.\n");
    return 1;
}

string
table_desc()
{
    string r;

    r = "Description of table. ";

    if (TableSearch == 1)
	r += "Table not searched.";
    else r += "Table searched";

    r += "\n";

    return r;
}

void
create_inside()
{
    set_short("a secret basement");
    set_long("Gee, a secret basement. How could you beleave that? " +
	     "The room is sparesly furnished and only a dim light " +
	     "comes from a candle light on the table.\n");

    add_item( ({ "walls", "wall" }), "The walls here are damp, as if moist gets into the " +
	     "room.\n");
    add_item("table", &table_desc());

    add_prop(OBJ_I_SEARCH_TIME, 7);
    add_prop(OBJ_S_SEARCH_FUN, "search_wall");

    add_exit(DOL_TRADE + "houses/s-12", "up", 0, 1);
    add_exit(DOL_SEWER + "s-11", "north", &secret_found(), 2, 
	     &secret_seen());

    reset_room();
}

void
reset_room()
{
    TableSearch = 1;
}

public string
search_wall(object tp, string str)
{
    object o;

    if (str != "wall" &&str != "walls" && str != "walls for door" && 
	str != "here for door" && str != "wall for door" && str != "table")
	return "Your search reveals nothing.\n";

    if (str == "table" && TableSearch == 1)
    {
	o = clone_object(DOL_OBJ + "quest/evidence");
	o->move(this_player());
	say(QCTNAME(this_player()) + " finds something on the table.\n");
	TableSearch = 0;
	return "Among the papers on the table you find some letters and " +
	    "scetches you think can be used as evidence. You put them " +
	    "in an envilop to give them to the harbourmaster.\n";
    }

    if (this_player()->query_prop(DOL_I_FOUND_SEWER_DOOR) == 1)
        return "Your search reveals nothing.\n";

    if (this_player()->query_skill(SS_AWARENESS) > 25 &&
	CAN_SEE_IN_ROOM(this_player()) )
    {
	this_player()->add_prop(DOL_I_FOUND_SEWER_DOOR, 1);
	return "You see find a hidden door leading north.\n";
    }

    return "Your search reveals nothing.\n";
}

