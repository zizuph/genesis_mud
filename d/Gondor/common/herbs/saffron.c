 /*
  * saffron.c
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
    set_name("flower");
    add_name(({"spice", "_spice"}));
    set_adj("cup-shaped");
    set_herb_name("saffron");
    set_short("cup-shaped flower");
    set_pshort("cup-shaped flowers");
    set_ingest_verb("eat");
    set_unid_long("This is the cup-shaped flower of a crocus.\n");
    set_id_long(BSN("This is the cup-shaped flower of a saffron "
      + "crocus. The saffron crocus (Crocus sativus) is a plant of "
      + "the iris family. It grows in Mediterranean climate, "
      + "reaches up to six inches, and has a solid bulb, grasslike "
      + "leaves, and a cup-shaped flower. The flowers are used to "
      + "extract saffron, a spice."));

    set_effect(HERB_HEALING, "fatigue", 5);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(36);
    set_dryable();
}

