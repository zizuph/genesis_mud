 /*
  * caraway.c
  *
  * modified from tuo.c by Elessar
  * Olorin, April 1993
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
    set_name("seeds");
    add_name(({"seed", "spice", "_spice"}));
    set_adj(({"handful", "of", "aromatic", "brown", "dark"}));
    set_herb_name("caraway");
    set_short("handful of small brown aromatic seeds");
    set_pshort("handfuls of small brown aromatic seeds");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of small brown aromatic seeds. "+
        "Perhaps they can be used as spice."));
    set_id_long(BSN("This is a handful of caraway seeds. Caraway "+
        "(Carum carvi) is a biennial plant of the parsley " +
        "family with finely divided leaves and slender stems, reaching "+
        "one to two feet of height. The umbels of white flowers contain "+
        "aromatic seeds, that are used to flavour dishes."));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(24);
    set_dryable();
}

