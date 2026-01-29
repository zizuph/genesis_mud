/* Cabinet in Kurinost elven tower ruins
 * Arman June 2018
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_container()
{
    set_name("chest");
    set_adj("large");
    add_adj("wooden");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(1241242);

    set_pick(20);

    add_prop(OBJ_I_VALUE,120);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    set_no_show_composite(1);

    add_item("lock", "The lock looks quite basic.\n");
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the large wooden chest.\n");
	return;
    }
    ::enter_inv(obj,from);
}

void
leave_inv(object obj, object to)
{
    if (E(TP)->query_dragon_present())
    {
	write("You cannot take anything from the chest, the " +
            "ancient green dragon is in the way!\n");
	return;
    }

    ::leave_inv(obj,to);
}

/*
 * Function name: query_no_pick
 * Description  : Returns whether the lock on the container can be picked.
 * Returns      : 1 - lock on container is not pickable
 *                0 - lock on container is pickable
 */
public int
query_no_pick()
{
    if (E(TP)->query_dragon_present())
    {
	write("You cannot pick the lock, the " +
            "ancient green dragon is in the way!\n");
	return 1;
    }

    return 0;
}

string
short_descr()
{
    return "large wooden chest";
}

string
long_descr()
{
    return "This is a large but crudely crafted wooden chest, banded " +
        "with black iron. It is likely the inept work of hobgoblin " +
        "minion, providing a basic storage option for the treasures " +
        "the dragon has obtained in the invasion of Silvanesti.\n";
}
