/* -*- Mode: C -*-
 *
 * other/store/w-12.c
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

public void
enter_inv(object ob, object from)
{
    if (function_exists("create_living", ob))
	return;

    ob->move(DOL_OTHER + "store/void");
}
