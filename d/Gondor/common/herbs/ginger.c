 /*
  * ginger.c
  *
  * modified from tuo.c by Elessar
  *
  * Ingredient for Morgul spell ringurth
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
    set_name("root");
    add_name(({"rootstock", "spice", "_stew_spice"}));
    add_name("ringurth_ingr2");
    set_adj("tuberous");
    set_herb_name("ginger");
    set_short("tuberous rootstock");
    set_pshort("tuberous rootstocks");
    set_ingest_verb("eat");
    set_unid_long("This is a tuberous rootstock. Someone seems to have been digging here.\n");
    set_id_long(BSN("This is a ginger root. Ginger (Zingiber officinale) "
      + "is a perennial herb of the ginger family, native to tropical "
      + "climates. But it has been cultivated in Ithilien for centuries. "
      + "The herb grows three feet tall, bears grasslike leaves and "
      + "yellowish-purple flowers in dense spikes three inches long on "
      + "separate stems. The tuberous rootstock is used as spice, often "
      + "in stews."));

    set_effect(HERB_HEALING,"fatigue",1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(36);
    set_dryable();
}

