 /*
  * savory.c
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
    set_name("leaves");
    add_name(({"leaf", "spice", "_rabbit_spice", "handful of leaves"}));
    set_adj(({"handful", "of", "aromatic", "stiff", "small"}));
    set_herb_name("savory");
    set_short("handful of small stiff aromatic leaves");
    set_pshort("handfuls of small stiff aromatic leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of small, stiff aromatic "
      + "leaves. They probably were picked from a small shrub."));
    set_id_long(BSN("This is a handful of savory leaves. Savory "
      + "(Satureia hortensis) is a hardy annual shrub of the mint "
      + "family that grows in Mediterranean climate to about one "
      + "foot. The aromatic leaves are used as spice and are said "
      + "to give quick relief from bee sting. In Gondor and Ithilien "
      + "many a recipe of old requires savory leaves for preparing "
      + "rabbit meat."));

    set_effect(HERB_CURING, "bee", 50);
    set_id_diff(15);
    set_find_diff(3);
    set_decay_time(7200);
    set_herb_value(36);
    set_dryable();
}

