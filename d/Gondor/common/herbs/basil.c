 /*
  * basil.c
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
    add_name(({"leaf", "spice", "_rabbit_spice"}));
    add_name("dramalgos_ingr1");
    set_adj(({"handful", "of", "green", "dark", "small"}));
    set_herb_name("basil");
    set_short("handful of small dark green leaves");
    set_pshort("handfuls of small dark green leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of small, dark green leaves. "
		      + "They probably were picked from a small herb."));
    set_id_long(BSN("This is a handful of basil leaves. Basil (Ocimum "
		    + "basilicum) is a small annual herb of the mint family growing "
		    + "in warm climate. It can reach a height of two feet and has tiny "
		    + "reddish-white or deep-purple flowers borne in branching spikes. "
		    + "The aromatic leaves are used to flavour dishes. In Gondor and "
		    + "Ithilien, many a recipe of old requires basil for preparing "
		    + "rabbit meat."));
    set_herb_value(72);
    set_id_diff(10);
    set_find_diff(2);
    set_effect(HERB_HEALING, "fatigue", 1);
    set_decay_time(5400);
    set_dryable();
}

