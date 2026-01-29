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
    set_short("little red berry");
    set_pshort("little red berries");
    set_adj(({"little", "red"}));
    set_herb_name("wild strawberry");
    // genus changed from Rubus to Fragaria, following a mail by Teth.
    // Olorin, 29-Aug-1997
    set_id_long(BSN("This little red strawberry is a member of the "+
        "genus Fragaria. "+
        "It is believed that the wild strawberry originated in Beleriand. "+
        "It still grows abundantly on the western shores of Middle Earth. "+
        "This strawberry has a mild nutrative and healing effect."));
    set_unid_long("This little red berry looks like an ordinary berry.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING,"hp", 5);

    set_id_diff(20);
    set_find_diff(5);
    set_decay_time(5400);
    set_herb_value(42);

    set_amount(5);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 48);
}
