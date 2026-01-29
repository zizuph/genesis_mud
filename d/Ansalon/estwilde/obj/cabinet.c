inherit "/d/Ansalon/estwilde/obj/std_receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"


void
create_container()
{
    set_name("cabinet");
    set_adj("wooden");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(0);
    /*No set key, so I have set the key value to 0 */
    set_no_pick();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_VOLUME, 7500);
    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
    add_prop(CONT_I_CLOSED, 0);
}


void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the cabinet.\n");
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
    return "wooden cabinet";
}

string
long_descr()
{
    return "This wooden cabinet has been lovingly carved " +
    "by the sure hands of a dwarven craftsman. It stands to " +
    "the side of the storeroom, and is used to store odds " +
    "and ends in it.\n";
}
