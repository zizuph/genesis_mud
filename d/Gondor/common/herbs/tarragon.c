 /*
  * tarragon.c
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
    add_name(({"leaf", "spice", "_rabbit_spice", "dramalgos_ingr1"}));
    set_adj(({"handful", "of", "bitter", "small"}));
    set_herb_name("tarragon");
    set_short("handful of small bitter leaves");
    set_pshort("handfuls of small bitter leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of small, bitter leaves. "
      + "They probably were picked from a small herb."));
    set_id_long(BSN(
        "This is a handful of tarragon leaves. Tarragon (Artemisia dracunculus) "
      + "is a perennial herb of the family Compositae that grows to a height of "
      + "two feet and prefers temperate climate. Its bitter, aromatic leaves "
      + "are used as spice and to extract oil of tarragon. In Gondor and Ithilien, "
      + "many a recipe of old requires tarragon for preparing rabbit meat."));

    set_effect(HERB_HEALING,"fatigue",1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(72);
    set_dryable();
}

