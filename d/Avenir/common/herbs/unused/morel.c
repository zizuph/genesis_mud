// file name:   ~Avenir/common/herbs/morel
// creator(s):   Cirion, March 1007
// last update:
// purpose:      Healing mushroom found in the Union's garden
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

    set_herb_name("morel");

    set_id_long("This is a wide, dark-grey mushroom with a thin hood "
        + "that droops down over the stalk. The Morel is "
        + "known for its potent healing effects, but is often confused "
        + "with the deadly False Morel.\n");

    set_unid_long("This is a wide, dark-grey mushroom with a thin hood "
        + "that droops down over the stalk.\n");

    set_ingest_verb("eat");

    set_id_diff(50);
    set_find_diff(3);

    set_decay_time(100);

    set_effect(HERB_HEALING, "hp", 20); 
    set_herb_value(100);

    set_dryable();

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 15);

}


