 /*
  * fennel.c
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
    set_name("leaves");
    add_name(({"leaf", "spice", "_spice"}));
    add_name("ringurth_ingr2");
    set_adj(({"handful", "of", "threadlike", "fine"}));
    set_herb_name("fennel");
    set_short("handful of fine threadlike leaves");
    set_pshort("handfuls of fine threadlike leaves");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a handful of fine threadlike leaves. "
      + "They probably were picked from a small plant."));
    set_id_long(BSN("This is a handful of fennel leaves. Fennel "
      + "(Foeniculum vulgare) is a plant of the parsley family, "
      + "native to southern climates. It grows erect to three to five "
      + "feet, and on greyish smooth stems it bears fine threadlike "
      + "leaves and many umbels of yellow flowers in clusters. The "
      + "highly flavoured leaves and seeds are used to flavour dishes."));

    set_effect(HERB_HEALING,"fatigue",1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(36);
    set_dryable();
}
