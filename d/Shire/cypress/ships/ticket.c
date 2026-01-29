#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the Grey Havens-Cypress");
    add_adj("torn");
    set_long("This is a ticket for the ship that runs between " +
        "Grey Havens and Cypress.\n");
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