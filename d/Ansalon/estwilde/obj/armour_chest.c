/*
inherit "/std/receptacle";
*/
inherit "/d/Ansalon/estwilde/obj/std_receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"


void
create_container()
{
    set_name("chest");
    set_adj("large");
    set_adj("stone");
    set_short("@@short_descr");
    set_pshort("grand oak chests");
    set_long("@@long_descr");
    set_key(0);
    /*No set key, so I have set the key value to 0 */
    set_no_pick();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_WEIGHT, 250000);
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_MAX_WEIGHT, 90000000);
    add_prop(CONT_I_MAX_VOLUME, 90000000);
    add_prop(CONT_I_CLOSED, 0);
}


void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the chest.\n");
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
    return "large stone chest";
}

string
long_descr()
{
    return "This is a very large chest made of stone, " +
    "used to hold all the armours left behind by the " +
    "dwarven warriors of the Neidar clan for other " +
    "clan members to use.\n";
}
