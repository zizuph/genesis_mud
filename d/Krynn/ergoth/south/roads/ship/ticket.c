#include "local.h"
#include <stdproperties.h>

inherit "/std/object";

void create_object()
{
    set_name("ticket");
    add_name(TICKETNAME);
    set_adj(({"small", "stamped"}));
    set_long("This is small piece of paper stamped with the image of a short,"
        + " three-masted ship.\n");
    add_prop(OBJ_I_VALUE, PRICE / 2);
}

