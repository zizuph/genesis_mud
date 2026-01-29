 /*
  * dill.c
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
  add_name(({"leaf", "spice", "_spice"}));
  set_adj(({"handful", "of", "green", "feathery"}));
  set_herb_name("dill");
  set_short("handful of feathery leaves");
  set_pshort("handfuls of feathery leaves");
  set_ingest_verb("eat");
  set_unid_long("This is a handful of feathery leaves.\n");
  set_id_long(BSN("This is a handful of dill leaves. Dill (Anethum "
    + "graveolens) is a quick-growing annual herb of the parsley family. "
    + "The plant prefers warm climates, growing to three feet with "
    + "feathery leaves and small yellow flowers in broad umbels. Both "
    + "the leaves and the fruits are used to flavour dishes."));

  set_effect(HERB_HEALING, "fatigue", 1);
  set_id_diff(10);
  set_find_diff(2);
  set_decay_time(5400);
  set_herb_value(24);
  set_dryable();
}
