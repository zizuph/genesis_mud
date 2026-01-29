/* -*- Mode: C -*-
 *
 * other/store/r-12.c
 *
 * Skippern 20(c)01
 *
 * A store room.
 */
#include "../../defs.h"

inherit DOL_STD + "inside";
inherit "/d/Gondor/common/lib/potion_storage";

#include <stdproperties.h>

/* Global variables */

void
create_inside()
{
    set_short("store room for r-12");
    set_long("this is the store room of the shop in o-11\n\n");

    add_exit(DOL_TRADE + "houses/r-12", "down", 0, 1);

    add_prop(ROOM_I_INSIDE, 1);

    set_save_file(DOL_OTHER+"store/r-12");
    create_potion_storage();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    enter_storage_inv(ob, from);
}
