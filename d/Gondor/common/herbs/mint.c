 /*
  * mint.c
  *
  * modified from tuo.c by Elessar
  * Olorin, April 1993
  * last mod: increased fatigue restoring power
  *           and price, ingredient to morgul spell faugoroth
  *           Olorin, 16-jun-94
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
    set_name("leaves");
    add_name(({"leaf", "spice", "_spice"}));
    add_name("faugoroth_ingr1");
    set_adj(({"handful", "of", "narrow", "sharply", "toothed"}));
    set_herb_name("mint");
    set_short("handful of narrow sharply toothed leaves");
    set_pshort("handfuls of narrow sharply toothed leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a handful of narrow sharply toothed "
      + "fragrant leaves.\n");
    set_id_long(BSN("This is a handful of mint leaves. Mint (Mentha "
      + "piperita) is a fragrant, square-stemmed perennial herb of the "
      + "mint family growing in north temperate zones. It grows to a "
      + "height of one to three feet. The smooth branchy stems bear "
      + "narrow, sharply toothed leaves that are dotted with minute oil "
      + "glands. The purplish and occasionally white flowers grow in "
      + "dense clusters. Leaves, stem, and roots contain aromatic oils, "
      + "the leaves are used to flavour dishes, eating the leaves is "
      + "said to have a slightly refreshing effect."));

    set_effect(HERB_HEALING, "fatigue", 10);

    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(84);

    set_dryable();
}

