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

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (this_player()->query_wiz_level()) {
        dump_array(({ "enter_inv", ob, from }));
    }
}

void
leave_inv(object ob, object from)
{
    ::leave_inv(ob, from);

    if (this_player()->query_wiz_level()) {
        dump_array(({ "leave_inv", ob, from }));
    }
}


