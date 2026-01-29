inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>



void
create_herb()
{
    set_name("pumpkin");
    add_adj("small");
    add_adj("orange");
    set_short("small orange pumpkin");

    set_id_long("This is a commonly found squash known as a pumpkin. "+
    "It is easily distinguished by its orange color and large and round "+
    "shape.\n");

    set_unid_long("This is a commonly found squash known as a pumpkin. "+
    "it is easily distiguished by its orange color and large, round "+
    "shape.\n");

    set_herb_name("pumpkin");
    set_amount(50);
    set_decay_time(9000);
    set_id_diff(5);
    set_find_diff(1);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"fat",10);
}
