inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* An herb that increases tracking skill by giving eater special */
/* senses. Strength is 40, Sarr */

void
create_herb()
{
    set_name("mushroom");
    add_adj("translucent");
    add_adj("soft");
    set_short("soft translucent mushroom");

    set_id_long("This is a very valuable herb known as blade. It is "+
    "very rare, and is said to only be found in the darkest of swamps "+
    "or forests, and only then can it be found at the darkest hour of "+
    "the night. Eating the herb is said to give you extra, powerful "+
    "senses that are vital to a hunter.\n");

    set_unid_long("This is a very odd looking mushroom. It is soft "+
    "and you can see tiny red flecks in its center.\n");

    set_herb_name("blade");
    set_amount(2);
    set_decay_time(1200);
    set_id_diff(60);
    set_find_diff(12);
    set_herb_value(3600);
    set_ingest_verb("eat");
    set_effect(HERB_SPECIAL,"",0);
}

void
special_effect()
{
    object ske;
    seteuid(getuid());
    ske = clone_object("/d/Kalad/common/herbs/kskill_enhance");
    ske->set_enhance_effect(SS_TRACKING,"track",20);
    ske->move(TP);
}
