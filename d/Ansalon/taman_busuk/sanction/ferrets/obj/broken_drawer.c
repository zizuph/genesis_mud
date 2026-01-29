
/*
 *broken_drawer.c
 *Used in a ferret quest to find the 'missing' dead ferrets.
 *However, this isn't an item for the quest.
 *
 *Ares July 2004
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("drawer");
    add_name("_quest_drawer_");
    set_adj("broken");

    set_short("broken drawer");
    set_pshort("broken drawers");
    set_long("This is a broken drawer, it's in several pieces.  \n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);

}

