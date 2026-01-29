/* Chest in waterfall room that contains a spell scroll
 * Arman June 2018
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"

void
create_container()
{
    set_name("coffer");
    set_adj("invisible");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(1241241);

    set_pick(10);

    add_prop(OBJ_I_VALUE,120);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);
    add_prop(OBJ_I_INVIS, 1);

    add_item("lock", "The lock looks of very basic make. You imagine " +
        "it wouldn't take much effort to pick the lock with the most " +
        "rudimentary tools.\n");
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the coffer.\n");
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
    return "invisible coffer";
}

string
long_descr()
{
    return "This is a small and very rudimentary coffer, usually used " +
        "by children to store toys and trinkets. Surprisingly, it is " +
        "covered with runes of invisibility cover it, making it " +
        "impossible to see without magical assistance. It has a lock.\n";
}
