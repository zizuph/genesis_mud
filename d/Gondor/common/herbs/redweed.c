/* 
 * This herb is required to cast the rest-spell of the Rangers.
 * It will not have any other use.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("weed");
    add_name("_rest_spell_herb_");
    set_adj("red");
    set_herb_name("redweed");
    set_short("red weed");
    set_pshort("red weeds");
    set_unid_long("This is a red weed. You don't know what it's for.\n");
    set_id_long(BSN("This is the Redweed, known in Gondor for its "
      + "fatigue-relieving magic powers. Unfortunately the power "
      + "cannot be used except with the Ranger-spell Rest. Eating "
      + "the weed will not have any effect."));

    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "fatigue", 0);
    set_id_diff(11);
    set_find_diff(2);
    set_herb_value(390);
    set_decay_time(2100);
    set_dryable();
}

