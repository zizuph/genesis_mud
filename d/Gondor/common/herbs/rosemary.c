 /*
  * rosemary.c
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
    set_name("flowers");
    add_name(({"flower", "spice"}));
    add_name("_spice");
    set_adj(({"handful", "of", "blue", "pale", "small"}));
    set_herb_name("rosemary");
    set_short("handful of small pale blue flowers");
    set_pshort("handfuls of small pale blue flowers");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of small, pale blue flowers. "
      + "They probably were picked from a small herb."));
    set_id_long(BSN("This is a handful of rosemary flowers. Rosemary "
      + "(Rosmarinus officinalis) is a hardy aromatic shrub of the "
      + "mint family, prefering Mediterranean climate. It grows to a "
      + "height of two to six feet, and bears clusters of small, pale "
      + "blue flowers and numerous quarter inch long leaves. The leaves "
      + "and flowers yield a fragant, volatile oil and are used as spice."));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(24);
    set_dryable();
}

