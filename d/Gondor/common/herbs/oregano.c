 /*
  * oregano.c
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
    add_name(({"leaf","spice","_spice"}));
    add_name("dramalgos_ingr1");
    set_adj(({"handful", "of", "stalked", "ovate"}));
    set_herb_name("oregano");
    set_short("handful of stalked ovate leaves");
    set_pshort("handfuls of stalked ovate leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a handful of stalked, broadly ovate leaves with toothed margins.\n");
    set_id_long(BSN("This is a handful of oregano leaves. Oregano (Origanum "
      + "vulgare) is an annual herb of the mint family growing in temperate "
      + "climate. It has clusters or short spikes of purplish flowers and "
      + "stalked, broadly ovate leaves with toothed margins. The pungent plant "
      + "is much used for seasoning. In trade it is offered in packaged bits of "
      + "stems, leaves, and flowers, or as cut, dried plants."));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(72);
    set_dryable();
}

