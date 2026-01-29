 /*
  * elanor.c
  *
  * modified from tuo.c by Elessar
  * Elessar, Nov 1994
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
  set_adj(({"handful", "of", "yellow", "golden", "star-shaped", "small"}));
  set_herb_name("elanor");
  set_short("handful of yellow star-shaped flowers");
  set_pshort("handfuls of yellow star-shaped flowers");
  set_ingest_verb("eat");
  set_unid_long(BSN("These small star-shaped flowers are golden like "+
    "the sun, and a sweet refreshing fragrance surrounds them."));
  set_id_long(BSN("These are the flowers known among the Elves as Elanor, "+
    "which means 'Elf-sun'. "+
    "The small star-shaped flowers have the colour of the sun, and seem "+
    "to keep the sunlight in them even after the darkness has come. "+
    "They are not known to grow anywhere outside Lothlorien. "+
    "The Elanor is known for a mild refreshing effect when eaten."));

    set_effect(HERB_HEALING, "fatigue", 5);
    set_id_diff(35);
    set_find_diff(2);
    set_decay_time(3600);
    set_herb_value(36);
    set_dryable();
}
