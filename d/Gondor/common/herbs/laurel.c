 /*
  * laurel.c
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
    set_name("leaf");
    add_name(({"spice", "_stew_spice"}));
    set_adj(({"green", "dark", "stiff"}));
    set_herb_name("laurel");
    set_short("stiff dark green leaf");
    set_pshort("stiff dark green leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a stiff, dark green leaf. It was probably picked from a tree.\n");
    set_id_long(BSN("This is a laurel leaf. Laurel (Laurus nobilis), "
      + "also called Sweet Bay, is an evergreen tree, native to "
      + "Mediterranean climates, growing to 60 feet, with stiff leaves, "
      + "small yellowish flowers, and purple berries. The leaves of the "
      + "bay tree are used to flavour dishes. In Gondor and Ithilien, "
      + "many a recipe of old requires laurel for preparing stews."));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(24);
    set_dryable();
}

