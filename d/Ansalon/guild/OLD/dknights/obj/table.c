/*
 * File Name        : table.c
 * By               : Elmore.
 * Inspiration from : The Dragonarmy racks by Milan
 * Date             : Nov. 2000.
 * Description      : This is the table in the droproom.
 *
 */

inherit "/std/container";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"

void
create_rack()
{
}

void
create_container()
{
    set_name("table");
    set_adj("large");
    add_adj("oakwood");
    set_long("This is a large oakwood table, that has been "+
        "reinforced with tempered steel.\n");

    add_prop(OBJ_I_VALUE,       0);
    add_prop(CONT_I_ATTACH,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(OBJ_M_NO_GET,      1);
    add_prop(CONT_I_WEIGHT,     10000);
    add_prop(CONT_I_VOLUME,     7500);
    add_prop(CONT_I_MAX_WEIGHT, 900000);
    add_prop(CONT_I_MAX_VOLUME, 900000);

    create_rack();
}

public int
prevent_enter(object ob)
{
    if (living(ob))
        return 1;
    return 0;
}


