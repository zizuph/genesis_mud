 /*
  * marjoram.c
  *
  * modified from tuo.c by Elessar
  * Olorin, April 1993
  */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("umbel");
    add_name(({"spice", "_spice"}));
    set_adj(({"flowery", "broad"}));
    set_herb_name("marjoram");
    set_short("broad flowery umbel");
    set_pshort("broad flowery umbels");
    set_ingest_verb("eat");
    set_unid_long("This is a broad flowery umbel. It probably was picked from a small herb.\n");
    set_id_long(BSN("This is a broad flowery umbel of marjoram. Marjoram "
      + "(Majoram hortensis) is a small annual herb of the mint family "
      + "with broad flowery umbels growing in Mediterranean climate. "
      + "The aromatic leaves and umbels are used to flavour dishes."));
    set_herb_value(20);
    set_id_diff(10);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue",1);
    set_decay_time(5000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }