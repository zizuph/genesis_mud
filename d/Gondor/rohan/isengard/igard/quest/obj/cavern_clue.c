/*
 * IGARD_QUEST_OBJ + cavern_clue.c
 *
 * Clue to visit caverns to west of Isengard.
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
    set_name("flake");
    add_name("_igard_cavern_clue");
    add_name("stone");
    set_pname("flakes");
    set_short("jagged flake of stone");
    set_pshort("jagged flakes of stone");
    set_adj(({"jagged"}));
    set_long("A jagged flake of stone. It is speckled with strange "
        + "glimmering obsidian crystals.\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE,   50);
    add_prop(OBJ_I_WEIGHT,  250);
    add_prop(OBJ_I_VOLUME,  250);
}
