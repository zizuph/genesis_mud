inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* A valuable herb known as redeye */


void
create_herb()
{
    set_name("weed");
    add_adj("bright-red");
    add_adj("sticky");
    set_short("bright-red sticky weed");

    set_id_long("This weed is known as bloodweed because of its bright "+
    "red color, and sticky film along its blades. It is poisonous to "+
    "eat.\n");

    set_unid_long("This is a strange weed indeed. Its blades are of "+
    "a bright red color, and they are covered with a sticky liquid. It "+
    "looks very much like blood.\n");

    set_herb_name("bloodweed");
    set_amount(2);
    set_decay_time(1000);
    set_id_diff(25);
    set_find_diff(6);
    set_herb_value(80);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"hp",-100);
}
