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
    
    add_adj(({"large", "wooden"}));
    add_name("ho_rack");
    set_short("large wooden rack");
    set_long("This is a large rack, made from a blackwood pine native to this "
    + "area. It has been specially designed to hold various items.\n");
} /* create_rack */
