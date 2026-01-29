#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("flower");
    set_short("sweet-smelling golden flower");
    set_pshort("sweet-smelling bunch of golden flowers");
    set_herb_name("lissuin");
    set_adj(({"sweet-smelling", "golden", }));
    set_id_long(BSN("These golden flowers are called lissuin. Once "
      + "the Eldar gave the sweet-smelling blossoms as gifts to the "
      + "Numenoreans. Now they are rare indeed."));
    set_unid_long(BSN("This golden flower smells wonderful. You want "
      + "to inhale the intoxicating sweet perfume!"));
    set_ingest_verb("inhale");

    set_effect(HERB_HEALING, "fatigue", 30);
    set_id_diff(45);
    set_find_diff(9);
    set_decay_time(1800);
    set_herb_value(432);
    set_dryable();
}

