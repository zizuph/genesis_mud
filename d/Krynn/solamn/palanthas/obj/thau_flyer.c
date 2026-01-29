#pragma strict_types
// file name:	thau_fluer.c	
// creator(s): 	Zizuph Sep 2021
// purpose:	to educate visitors on stat respecs

#include "../local.h"

inherit "/std/scroll";

#define FILEPATH  OBJ + "thau_flyer.txt"

#include <macros.h>
#include <stdproperties.h>

public void
create_scroll(void)
{
    set_name("_transform_parchment");
    add_name(({"parchment", "piece of parchment"}));
    add_adj(({"piece"}));
    set_long("This parchment contains various details about how the " +
        "spell of transformation will affect you.\n");
    set_short("piece of parchment");
    set_pshort("pieces of parchment");
    set_file(FILEPATH);
    add_prop(OBJ_I_NO_SELL, "This parchment has no market value.\n");
}

public void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if (!from)
	return;

    if (inv->query_prop(ROOM_I_IS))
    {
	set_alarm(0.5, 0.0, &remove_object(this_object()));
	tell_room(inv, "The "+ short() +" takes wing on a "+
	  "breeze and floats away.\n");
    }
}
