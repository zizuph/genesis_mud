inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>


void
create_herb()
{
    set_name("berry");
    add_adj("orange");
    set_short("orange berry");

    set_id_long("This is a tiny berry that is bright orange in color. "+
    "It is known as lore. It is a very rare herb, only found in forests "+
    "and jungles. When eaten, it is said to give you more "+
    "knowledge, thus the name lore.\n");

    set_unid_long("This a tiny orange berry, much like a blueberry.\n");

    set_herb_name("lore");
    set_amount(10);
    set_decay_time(1900);
    set_id_diff(35);
    set_find_diff(5);
    set_herb_value(1800);
    set_ingest_verb("eat");
    set_effect(HERB_ENHANCING,"int",20);
}
