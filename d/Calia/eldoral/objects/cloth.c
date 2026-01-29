/*
 * cloth.c
 * 
 * This object is a piece of 'evidence' in the 'Seer and the Lord Quest'
 * in Eldoral. It loads in any one of a number of randomly determined
 * rooms, which is reset when the quest does.
 *
 * Khail, Jan 3/96          
 */
#pragma strict_types

#include "defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("cloth",1);
    set_pname("cloths");
    set_pshort("small rotted cloths");
    add_name("fabric");
    add_name(ELDORAL_CLOTH_NAME);
    set_adj("small");
    add_adj("rotted");
    set_long("This small, rotted scrap of cloth appears to have " +
        "once been a rich shade of red and purple, but it has " +
        "seen a lot of years it seems, as it has rotted away to " +
        "little more than a handful of threads barely holding " +
        "themselves together.\n");

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 100);
}
