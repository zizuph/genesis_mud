#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("onion");
    set_adj(({"little", "green", }));
    set_short("little green onion");
    set_pshort("little green onions");
    set_herb_name("green onion");
    set_id_long(BSN("This green onion is a member of the Cepa "
      + "species of the genus Allium in the lily family (Liliaceae). "
      + "The Dunland "
      + "green onion is both mild tasting and nutritious. The green "
      + "onion is said to have been here when the first Men arrived "
      + "ages ago."));
    set_unid_long("This looks like an ordinary green onion.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "fatigue", 3);
    set_id_diff(10);
    set_find_diff(1);
    set_decay_time(5400);
    set_herb_value(96);
    set_amount(64);
    add_prop(OBJ_I_WEIGHT, 64);
    add_prop(OBJ_I_VOLUME, 60);
    set_dryable();
}

