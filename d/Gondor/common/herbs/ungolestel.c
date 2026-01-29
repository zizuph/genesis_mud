#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("moss");
    add_name(({"_herb_for_spider_cleanse", "_cleanse_spell_herb_"}));
    add_name("gosta_ingr1");
    add_name("patch");
    set_short("brown patch of moss");
    set_pshort("brown patches of moss");
    set_adj(({"brown", "soft"}));
    set_herb_name("ungolestel");
    set_unid_long("This is a soft brown patch of moss.\n");
    set_id_long(BSN("This is a patch of the Ungolestel moss, "
      + "brown of colour and soft to the touch. This moss can "
      + "cure spider-poison."));

    set_ingest_verb("eat");

    set_effect(HERB_CURING, "spider", 100);
    set_id_diff(29);
    set_find_diff(5);
    set_decay_time(7200);
    set_herb_value(360);
}

