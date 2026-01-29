#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    add_name("_nightv_spell_ingr_");
    add_name("crabandir_ingr1");
    set_short("little red berry");
    set_pshort("little red berries");
    set_adj(({"little", "red", "holly", }));
    set_herb_name("holly berry");
    set_id_long(BSN("This red berry is a member of the Aquifolium species "
      + "of the genus Ilex. The holly has spiny, fleshy, evergreen leaves, "
      + "with red berries. The Elves consider it to be holy."));
    set_unid_long(BSN("This red berry looks like an ordinary berry. You do "
      + "not know what it is for."));
    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "fatigue", 2);

    set_id_diff(5);
    set_find_diff(2);

    set_decay_time(5400);
    set_herb_value(108);

    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,1);
}

