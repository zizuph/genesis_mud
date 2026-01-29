inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* A valuable herb known as redeye */


void
create_herb()
{
    set_name("bean");
    add_adj("white");
    add_adj("red-eyed");
    set_short("white red-eyed bean");

    set_id_long("This bean comes from a very strange plant found only "+
      "in the dark reaches of the Raumdor Forest of Shadows. It is "+
      "completely white except for the center, which is bright red. It "+
      "has a small healing effect when eaten. It is known as redeye.\n");

    set_unid_long("This is a small white bean with a very strange red "+
      "pit in the center.\n");

    set_herb_name("redeye");
    set_amount(2);
    set_decay_time(2000);
    set_id_diff(30);
    set_find_diff(5);
    set_herb_value(100);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"hp",10);
}
