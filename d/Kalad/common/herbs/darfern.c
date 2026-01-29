inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

void
create_herb()
{
    set_name("leaf");
    add_adj("black");
    add_adj("feathery");
    set_short("black feathery leaf");
    set_id_long("This is a common leaf found in Raumdor. It comes from "+
    "a small plant black fern that occasionaly sprouts them. Known "+
    "as darfern, it really has no use except to tickle with.\n");

    set_unid_long("A nice, little leaf that is very light and feathery.\n");

    set_herb_name("darfern");
    set_amount(1);
    set_decay_time(2500);
    set_id_diff(15);
    set_find_diff(3);
    set_herb_value(6);
}

