 /*
  * simbelmyne.c
  *
  * Olorin, July 1995
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
    set_adj(({"small", "white", }));
    set_herb_name("simbelmyne");
    add_name("evermind");
    set_short("small white flower");
    set_pshort("small white flowers");
    set_ingest_verb("eat");
    set_unid_long("A small white flower, blossoming like a star.\n");
    set_id_long(BSN("This small white flower is called Simbelmyne or "
      + "Evermind. It grows among grass and blossoms in all seasons "
      + "of the year. It is said that they grow where dead men rest."));

    set_effect(HERB_HEALING, "mana", 2);

    set_id_diff(30);
    set_find_diff(1);
    set_decay_time(7200);
    set_herb_value(72);
    set_dryable();
}

