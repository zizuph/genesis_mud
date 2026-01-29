/* -*- Mode: C -*-
 *
 * other/store/void.c
 *
 * Skippern 20(c)01
 *
 * A store room.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";

#include <stdproperties.h>

/* Global variables */

/* Prototypes */
public void     enter_inv(object ob, object from);

void
create_inside()
{
    set_short("store room for w-12");
    set_long("this is the store room of the shop in w-12\n\n");

    add_exit(DOL_TRADE + "houses/w-12", "in", 0, 1);
}

void 
move_armour(object ob)
{
    ob->move(DOL_OTHER + "store/d-07");
}

void 
move_weapon(object ob)
{
    ob->move(DOL_OTHER + "store/f-06");
}

void
move_clothes(object ob)
{
    ob->move(DOL_OTHER + "store/a-05");
}

void
move_suply(object ob)
{
    ob->move(DOL_OTHER + "store/i-06");
}

void
move_gems(object ob)
{
    ob->move(DOL_OTHER + "store/r-12");
}

void
move_potion(object ob)
{
    ob->move(DOL_OTHER + "store/s-13");
}

void 
move_other(object ob)
{
    ob->move(DOL_OTHER + "store/o-11");
}

public void
enter_inv(object ob, object from)
{
    if (function_exists("create_living", ob))
        return;

    if (ob->query_prop(OBJ_I_NO_GET))
	ob->remove_object();

    // find the type of object and move it to the right store room
    if (function_exists("create_weapon", ob))
    {
	set_alarm(8.0, 0.0, &move_weapon(ob));
	return;
    }
    if (function_exists("create_armour", ob))
    {
	set_alarm(6.0, 0.0, &move_armour(ob));
	return;
    }
    if (function_exists("set_looseness", ob))
    {
	set_alarm(2.0, 0.0, &move_clothes(ob));
	return;
    }
    if (function_exists("create_food", ob) || 
	function_exists("create_drink", ob))
    {
	set_alarm(10.0, 0.0, &move_suply(ob));
	return;
    }
    if (function_exists("create_gem", ob))
    {
	set_alarm(35.0, 0.0, &move_gems(ob));
	return;
    }
    if (function_exists("create_potion", ob))
    {
	set_alarm(15.0, 0.0, &move_potion(ob));
	return;
    }
    // else:
    set_alarm(7.0, 0.0, &move_other(ob));
}

