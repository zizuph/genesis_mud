
/*
 *old_paper.c
 *Used in a ferret quest to find the 'missing' dead ferrets.
 *
 *Ares July 2004
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("paper");
    add_name("_quest_old_paper_");
    set_adj("old");
    add_adj("wrinkled");

    set_short("old wrinkled paper");
    set_pshort("old wrinkled papers");
    set_long("This old paper is actually a long forgotten Death Certificate. "+
        "The name on the certicate reads: SKEDAR.  \n");

    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);


}

