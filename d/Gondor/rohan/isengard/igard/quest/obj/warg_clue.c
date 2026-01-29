/*
 * IGARD_QUEST_OBJ + warg_clue.c
 *
 * Clue to visit orc dens.
 *
 * Last modified by Alto, 04 December 2001
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../../igard_defs.h"

public void
create_object()
{
    set_name("wisp");
    add_name("_igard_warg_clue");
    add_name("fur");
    set_pname("wisps");
    set_short("wisp of fur");
    set_pshort("wisps of fur");
    set_long("A small wisp of fur that looks and feels so soft that "
        + "it must have come from a puppy. How puppy fur would find its "
        + "way into the cold fortress of Isengard is uncertain.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE,   50);
    add_prop(OBJ_I_WEIGHT,  250);
    add_prop(OBJ_I_VOLUME,  250);
}
