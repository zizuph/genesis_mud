/*  /d/Ravenloft/droptables/fos_drops/no_drop.c
 *
 *
 *  Nerull, 2016
 *
 */

inherit "/std/object";
#include "../loot_chest_defs.h";
#include <stdproperties.h>
#include <macros.h>


void
do_destroy()
{
    remove_object();
	return;
}


void
create_object()
{
    set_name("_no_drop");

    set_long("\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_INVIS, 100);

    // Questitem properties.
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP, 1);

    set_alarm(0.0, 0.0, &do_destroy());
}

string
query_recover()
{
    return 0;
}
