/*
 * Olorin, July 1994
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
    set_name("berry");
    set_adj("red");
    add_adj("small");
    set_herb_name("suranie");
    set_short("small red berry");
    set_pshort("small red berries");
    set_unid_long("This is a small red berry. You could probably eat it.\n");
    set_id_long("This is the Suranie, known in Gondor for its "
      + "mentally restoring virtues when it is eaten. It grows "
      + "typically in forest glades.\n");

    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "mana", 50);

    set_id_diff(50);
    set_find_diff(7);

    set_decay_time(1200);

    set_herb_value(1080);
}

