 /*
  * niphredil.c
  *
  * modified from tuo.c by Elessar
  * Elessar, Nov 1994
* Renamed by Varian, it was put into the game outside
* of Lorien and needs to be removed. January 2021
  *
  * This herb can be found in Lorien, only!
  *
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
    set_name("flowers");
    add_name("flower");
    set_adj(({"handful", "of", "white", "slender-stalked", "slender",
              "pale", "green", "palest"}));
    set_herb_name("niphredil");
    set_short("handful of white and pale green slender-stalked flowers");
    set_pshort("handfuls of white and pale green flowers");
    set_ingest_verb("eat");
    set_unid_long(BSN("These flowers have slender stalks, and are white "
      + "and palest green. They almost seem to glimmer by themselves, "
      + "and a sweet refreshing fragrance surrounds them."));
    set_id_long(BSN("These are the flowers known among the Elves as "
      + "Niphredil, which means 'Pale-star'. The name is very fitting, "
      + "for the Niphredil is white and palest green, and blossoms in "
      + "starlight. The flower seems to reflect the starlight, making "
      + "it seem to glimmer in the twilight, nodding on its slender stalk. "
      + "They are not known to grow anywhere outside Lothlorien. "
      + "The Niphredil is known for a mild refreshing effect when eaten."));

    set_effect(HERB_HEALING, "mana", 2);

    set_id_diff(41);
    set_find_diff(3);
    set_decay_time(7200);
    set_herb_value(48);
    set_dryable();
}

