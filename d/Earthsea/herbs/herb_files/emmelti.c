/* A emmelti. This sea fern when eat it will restore
 * your fatigue. It is found in all the beaches in Earthsea.
 * Coded by Marisol (11/25/97)
 * Copyright (c) Marisol Ramos 1997*/

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("sea fern");
    add_name("fern");
    add_adj("green");
    set_herb_name("emmelti");
    set_short("green sea fern");
    set_pshort("green sea ferns");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A ribbony sea fern.\n");
    set_id_long("An emmelti! This sea fern is sought by fishermen "+
      "for its healing properties. They sell it in the market "+
      "places of the Archipelago for healalls and witches. "+
      "This sea fern, contrary to the common variety, is spongy "+
      "and easy to chew. The common variety is hard and is "+
      "mostly used for jewelry.\n");

    set_ingest_verb("chew");
    set_find_diff(8);
    set_id_diff(20);
    set_effect(HERB_HEALING, "fatigue", 40);
    set_herb_value(450);
    set_decay_time(5000);
    set_dryable();
}
