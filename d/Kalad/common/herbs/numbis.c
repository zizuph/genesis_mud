inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>


void
create_herb()
{
    set_name("mushroom");
    add_adj("purple");
    set_short("purple mushroom");

    set_id_long("This is a tiny mushroom deep purple in color. It "+
    "has a thick stem and a wide head, and gives off a most unpleasant "+
    "odor. Yet, this is numbis, a rare and valuable herb said to be "+
    "strong in the powers of anti-poison. It is found only in the "+
    "dark forests of Raumdor.\n");

    set_unid_long("This a strange mushroom that is a deep purple in "+
    "color. You have never seen anything like it.\n");

    set_herb_name("numbis");
    set_amount(12);
    set_decay_time(2000);
    set_id_diff(40);
    set_find_diff(8);
    set_herb_value(2000);
    set_ingest_verb("eat");
    set_effect(HERB_ENHANCING,"poison",10);
}
