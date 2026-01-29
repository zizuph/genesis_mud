/*
 * scroll.c
 *
 * Scroll provided to new members of the Blademasters for some
 * initial information.
 *
 * Khail - Mar 4/97
 */
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <cmdparse.h>

inherit "/std/object";

public void
create_object()
{
    set_name("scroll");
    set_adj("small");
    add_adj("dark");
    set_short("small dark scroll");
    set_long("A small dark scroll of parchment, upon it is a " +
        "small drawing of a chain and a thistle. It contains a " +
        "great deal of writing you can read.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public int
do_read(string str)
{
    object *arr;

    NF("Read what?\n");
    if (!str || !strlen(str))
        return 0;

    arr = FIND_STR_IN_OBJECT(str, TP);

    if (!sizeof(arr) || sizeof(arr) > 1)
        return 0;
    
    if (arr[0] != TO)
        return 0;

    if (!IS_BLADEMASTER(TP))
    {
        write("The words have no meaning to you.\n");
        return 1;
    }

    seteuid(getuid());
    TP->more(read_file(DOCS + "blademaster_join"));
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
}
