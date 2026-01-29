#pragma save_binary

inherit "/std/container.c";
#include <money.h>
#include <stdproperties.h>

string
short()
{
    if (present("torch"))
	return "torch in its stand";
    else
	return "torch stand";
}

create_container()
{
    set_name("stand");
    set_adj("torch");
    set_long("This is a torch stand mounted on the wall.\n");
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 11000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(OBJ_I_NO_GET, 1);
}