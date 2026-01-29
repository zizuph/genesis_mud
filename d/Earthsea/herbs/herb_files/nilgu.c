/* A nilgu. This sea herb is used for healing.
 * It is found in all the beaches in Earthsea.
 * Coded by Marisol (11/25/97)
 * Copyright (c) Marisol Ramos 1997*/

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("seaweed");
    add_adj("brown");
    set_herb_name("nilgu");
    set_short("brown seaweed");
    set_pshort("brown seaweeds");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A great brown-leaved seaweed.\n");
    set_id_long("A nilgu! This seaweed looks like a fringed fern. "+
        "It usually grows from eighty to a hundred feet long. "+
        "But you only found a small piece of it drifted by the "+
        "tide. Fishermen use it when they hurt themselves during the "+
        "long hours fishing in the sea.\n");

    set_ingest_verb("eat");
    set_find_diff(4);
    set_id_diff(10);
    set_effect(HERB_HEALING, "hp", 15);
    set_herb_value(75);
    set_decay_time(5000);
    set_dryable();
}
