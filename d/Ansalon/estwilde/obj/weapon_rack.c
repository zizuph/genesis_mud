inherit "/d/Ansalon/estwilde/obj/std_rack";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"


void
create_container()
{
    set_name("rack");
    set_adj("weapon");
    set_short("@@short_descr");
    set_long("@@long_descr");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,0);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_MAX_WEIGHT, 90000000);
    add_prop(CONT_I_MAX_VOLUME, 90000000);
}


void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the rack.\n");
	return;
    }
    ::enter_inv(obj,from);
}


void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}


string
short_descr()
{
    return "weapon rack";
}

string
long_descr()
{
    return "This large rack, skillfully crafted " +
    "from a dark wood native to these areas, " +
    "is used by the clan warriors to store their " +
    "weapons for later use.\n";
}
