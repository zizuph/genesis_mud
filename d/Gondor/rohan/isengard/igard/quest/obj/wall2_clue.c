/*
 * IGARD_QUEST_OBJ + wall2_clue.c
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

#define COLOUR       "green"
#define CONDITION    "dull"
#define METAL        "silver"
#define WEAVE        "loose"
#define CLEANLINESS  "clean"


public void
create_object()
{
    set_name("scrap");
    add_name("_igard_wall2_clue");
    add_name("fabric");
    set_pname("scraps");
    set_short("torn scrap of fabric");
    set_pshort("torn scraps of fabric");
    set_adj(({"torn"}));
    set_long("A small scrap of fabric. It is made from " + COLOUR
        + " cotton that is quite " + CONDITION + ". The fabric is "
        + "woven through with " + METAL + " thread, and as you examine "
        + "the thread you notice that the weave is extremely " + WEAVE
        + ". The fabric is also rather " + CLEANLINESS + ".\n");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE,   50);
    add_prop(OBJ_I_WEIGHT,  250);
    add_prop(OBJ_I_VOLUME,  250);
}
