 /*
  * chervil.c
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
    add_name(({"leaf", "spice", "_stew_spice", "dramalgos_ingr1"}));
    set_adj(({"handful", "of", "fine", "small"}));
    set_herb_name("chervil");
    set_short("handful of small fine leaves");
    set_pshort("handfuls of small fine leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of small fine leaves. They "
    + "probably were picked from a small herb."));
    set_id_long(BSN("This is a handful of chervil leaves. Chervil "
    + "(Anthriscus cerefolium) is a small fine-leaved annual plant "
    + "of the parsley family. The aromatic leaves are used to flavour "
    + "dishes. In Gondor and Ithilien, many a recipe of old requires "
    + "chervil for preparing stews."));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(84);
    set_dryable();
}

