 /*
  * ithilgil.c
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
    set_adj(({"handful", "of", "white", "star-shaped", "small"}));
    set_herb_name("ithilgil");
    set_short("handful of white star-shaped flowers");
    set_pshort("handfuls of white star-shaped flowers");
    set_ingest_verb("eat");
    set_unid_long(BSN("These small star-shaped flowers are pale white like "+
      "the moon, and a weak but sweet fragrance surrounds them."));
    set_id_long(BSN("These are the flowers known among the Elves as Ithilgil, "+
      "which means 'Moon-star'. "+
      "The flowers look like small white stars, and seem "+
      "to shimmer with a pale light when the moon is visible. "+
      "A rare sight, this flower clings to rocks and crags in "+
      "forests, glinting like small white stars in the shadows of night. "+
      "The Ithilgil is known for a mild calming effect when eaten."));

    set_effect(HERB_SPECIAL, "panic", 12);
    set_id_diff(42);
    set_find_diff(3);
    set_decay_time(4800);
    set_herb_value(48);
    set_dryable();
}

void
special_effect()
{
    if ((effects[1] != "panic") || (TP->query_panic() <= 0))
    {
        write("You do not feel any effect.\n");
        return;
    }

    TP->add_panic(-(effects[2]/2 + random(effects[2])));
    TP->catch_msg("You feel more calm and relaxed, and less panicky.\n");
}

