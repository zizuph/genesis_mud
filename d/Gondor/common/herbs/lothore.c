/* 
 * This herb is required to cast the heal-spell of the Rangers.
 * It will not have any other use.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("flower");
    add_name("_heal_spell_herb_");
    set_adj(({"red", "heart-shaped"}));
    set_herb_name("lothore");
    set_short("red heart-shaped flower");
    set_pshort("red heart-shaped flowers");
    set_unid_long(BSN("This is a small red flower shaped like a heart. "
      + "It has a refreshing smell, and is beautiful to look at. You "
      + "do not know what it is for."));
    set_id_long(BSN("This is the Lothore flower, known in Gondor for "
      + "its magical healing powers. Unfortunately the power cannot be "
      + "used except by the Ranger-spell Heal. Eating the flower will "
      + "not have any effect."));
    set_ingest_verb("eat");

    set_effect(HERB_HEALING,"hp",0);
    set_id_diff(13);
    set_find_diff(1);
    set_herb_value(600);
    set_decay_time(1500);
    set_dryable();
}

