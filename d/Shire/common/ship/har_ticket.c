#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the harlond line");
    add_adj("new");
    add_adj("silver");
    set_long("It looks like a ticket to the ship that sails between Harlond " +
        "and Mithlond. The ticket is silver and diamond shaped.\n");
    add_prop(OBJ_I_VALUE, "@@value_of_ticket@@");
}

int
value_of_ticket()
{
    if (this_player()->query_average_stat() < 20)
	return 0;
    else
	return 20;
}