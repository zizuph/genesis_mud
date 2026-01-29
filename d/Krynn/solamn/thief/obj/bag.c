/* Created by Aridor, sometime in 1994
 *
 * this is a normal sized bag which can be tied around the
 * body so that it won't be sold or dropped accidentally.
 */

inherit "/std/receptacle";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>

void
create_bag()
{
    set_name("bag");
    set_short("bag");
    set_pshort("bags");
    set_long("It's a normal bag. It's not very large, but " +
	     "you could still put several items into it.\n");
    add_prop(CONT_I_WEIGHT,     500);
    add_prop(CONT_I_MAX_WEIGHT, 15000);
    add_prop(CONT_I_VOLUME,     300);
    add_prop(CONT_I_MAX_VOLUME, 20000);
    add_prop(CONT_I_CLOSED,     1);
    add_prop(OBJ_I_VALUE,       150);
    set_keep(1);
}


nomask void
create_container()
{
    create_bag();
}


void
init_recover(string arg)
{
    init_keep_recover(arg);
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}
