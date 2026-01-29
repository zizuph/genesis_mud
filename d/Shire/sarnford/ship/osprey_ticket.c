#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the osprey");
    add_adj("brown");
    add_adj("paper");
    set_long("This is a ticket for 'The Osprey', a ship which travels " +
        "a regular route between the Grey Havens and Sarn Ford.\n");
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