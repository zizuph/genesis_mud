// file name:   ~Avenir/common/herbs/false_morel
// creator(s):   Cirion, March 1007
// last update:
// purpose:      Poisoning mushroom found in the Union's garden
// note: 
// bug(s):
// to-do:

inherit "/std/herb";
#include <herb.h>
#include "/d/Avenir/common/common.h"

create_herb()
{
    set_name("mushroom");
    add_name("herb");
    add_pname("herbs");
    set_adj(({ "fat", "grey" }));
    set_short("fat grey mushroom");

    set_herb_name("false morel");

    set_id_long("This is a wide, dark-grey mushroom with a thin hood "
        + "that droops down over the stalk. This is the False Morel, "
        + "nearly identical to the healing Morel mushroom, but its "
        + "effects are deadly.\n");

    set_unid_long("This is a wide, dark-grey mushroom with a thin hood "
        + "that droops down over the stalk.\n");

    set_ingest_verb("eat");

    set_id_diff(50);
    set_find_diff(3);

    set_decay_time(100);

    set_effect(HERB_POISONING, "morel", 90);
    set_herb_value(15);

    set_dryable();

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 15);
}


