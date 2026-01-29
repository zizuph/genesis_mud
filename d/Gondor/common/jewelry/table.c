/*
 * /d/Gondor/common/jewelry/table.c
 *
 * A table to put a book on.
 *
 * Coded by Gwyneth, 08/27/02
 */
inherit "/std/container";

#include <macros.h>
#include "jewelry.h"

void
create_container()
{
    set_name("table");
    add_name("_chivalric_order_table_");
    set_adj("small");
    set_short("small table");
    set_long("The small table is just large enough for a book.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 500);
    add_prop(CONT_I_MAX_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(CONT_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_CLOSED, 0);
    add_prop(OBJ_M_NO_GET, "It's attached to the floor.\n");

    setuid();
    seteuid(getuid());
    clone_object(JEWELRY_DIR + "book")->move(this_object());
}

