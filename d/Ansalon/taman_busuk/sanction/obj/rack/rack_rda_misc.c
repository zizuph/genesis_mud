#include "../../local.h"
#include <wa_types.h>

inherit SOBJ + "rack/new_rack";

/*
 * Function name:   create_rack
 * Description:     Basic rack constructor.
 */
void
create_rack()
{
    ::create_rack();
    
    add_adj(({"miscellaneous", "misc"}));
    add_name("rack_misc");
    set_short("miscellaneous rack");
} /* create_rack */