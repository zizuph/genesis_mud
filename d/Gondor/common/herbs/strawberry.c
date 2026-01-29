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
    set_name("berry");
    set_short("large red berry");
    set_pshort("large red berries");
    set_adj(({"large", "red"}));
    set_herb_name("strawberry");
    // genus changed from Rubus to Fragaria, following a mail by Teth.
    // Olorin, 29-Aug-1997
    set_id_long(BSN("This large red strawberry is a member of the "+
    "genus Fragaria. "+
    "It is believed that the strawberry originated in Beleriand. "+
    "It still grows abundantly on the western shores or Middle Earth. "+
    "It is widely cultivated and grows in many formerly settled places "+
    "now reverted to the wilds. "+
    "This strawberry has a mild nutrative and healing effect."));
    set_unid_long("This large red berry looks like an ordinary berry.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "hp", 2);
    set_id_diff(20);
    set_find_diff(3);
    set_decay_time(5400);
    set_herb_value(24);
    set_amount(6);
    add_prop(OBJ_I_WEIGHT, 60);
    add_prop(OBJ_I_VOLUME, 60);
}

