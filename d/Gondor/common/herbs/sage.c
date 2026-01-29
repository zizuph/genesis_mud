 /*
  * sage.c
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
    set_name("flowers");
    add_name(({"flower", "spice", "_spice"}));
    set_adj(({"handful", "of", "two-lipped", "tubular", "aromatic"}));
    set_herb_name("sage");
    set_short("handful of tubular two-lipped flowers");
    set_pshort("handfuls of tubular two-lipped flowers");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of aromatic tubular two-lipped "
      + "flowers. They probably were picked from a small herb."));
    set_id_long(BSN("This is a handful of sage flowers. Sage (Salvia "
      + "officinalis) is a low shrub of the mint family growing in "
      + "Mediterranean climate with aromatic tubular two-lipped "
      + "flowers. The flowers are used to flavour dishes."));

    set_effect(HERB_HEALING,"fatigue",1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(36);
    set_dryable();
}

