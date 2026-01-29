/*
 * IGARD_QUEST_OBJ + orc_clue.c
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
    set_name("toy");
    add_name("_igard_orc_clue");
    add_name("doll");
    set_pname("toys");
    set_short("small broken toy");
    set_pshort("small broken toys");
    set_adj(({"small"}));
    add_adj(({"broken"}));
    set_long("This toy looks much like a child's doll, although "
        + "what child would want to play with a doll that looks like "
        + "an orc is uncertain.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE,   50);
    add_prop(OBJ_I_WEIGHT,  250);
    add_prop(OBJ_I_VOLUME,  250);
}
