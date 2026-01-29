/* Sarr */
#include "defs.h"
inherit "/std/object";


void
create_object()
{
    set_name(({"horn", QUEST_HORN_NAME}));
    set_adj("bloody");
    add_adj("demon");
    set_short("bloody demon horn");
    set_long("This looks like a horn from a large beast. It is black "+
    "and is covered with red blood. It looks like it was torn from "+
    "some creature.\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_WEIGHT,100);
}

