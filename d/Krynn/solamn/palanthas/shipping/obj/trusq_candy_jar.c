/* Mortis 02.2006
 *
 * Jar hidden in Trusq merchant house kitchen.  Dispenses
 * twenty gumdrops.
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"

void
stock_up_on_candy()
{
	object candy;

	candy = clone_object(SHIP + "obj/trusq_gumdrop");
	candy->set_heap_size(20);
	candy->move(TO);
}

void
create_container()
{
    set_name("jar");
	set_adj("candy");
    set_short("candy jar");
    set_pshort("candy jars");
    set_long("A small, clear jar for safely storing candies.\n");
    add_prop(CONT_I_WEIGHT,     100);
    add_prop(CONT_I_MAX_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME,     200);
    add_prop(CONT_I_MAX_VOLUME, 2000);
    add_prop(CONT_I_CLOSED, 0);
	add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_NO_SELL, 1);

	set_alarm(1.0, 0.0, "stock_up_on_candy");
}
