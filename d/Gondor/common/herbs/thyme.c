 /*
    * thyme.c
    *
    * modified from tuo.c by Elessar
    * Olorin, April 1993
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
    set_name("leaves");
    add_name(({"leaf", "spice"}));
    add_name("_spice");
    set_adj(({"handful", "of", "pungent", "narrow", "sessile"}));
    set_herb_name("thyme");
    set_short("handful of pungent narrow leaves");
    set_pshort("handfuls of pungent narrow leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of pungent narrow leaves. "
      + "They probably were picked from a small shrub."));
    set_id_long(BSN("This is a handful of thyme leaves. Thyme (Thymus "
      + "vulgaris) is a small perennial shrub of the mint family "
      + "growing in Mediterranean climate. It can reach a height of "
      + "eight inches. The slender whitish branches bear narrow, "
      + "sessile leaves in loose terminal or axillary clusters, giving "
      + "of a pungent, mintlike odour, and dense clusters of purple "
      + "flowers. The fresh or dried leaves are used as spice."));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(2400);
    set_herb_value(48);
    set_dryable();
}

