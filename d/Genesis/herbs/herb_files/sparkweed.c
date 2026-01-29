/* A sparkweed. This herb will give some magic
 * resistance if eat it. It is found all over 
 * Earthsea. Coded by Marisol (11/11/97)
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_pname("flowers");
    add_adj("yellow-red");
    set_herb_name("sparkweed");
    set_short("yellow-red flower");
    set_pshort("yellow-red flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A flower with flame-like petals.\n");
    set_id_long("A sparkweed! This weed when blooming has beautiful "+
      "flame-like petals that when blown by the wind look like "+
      "fiery sparks igniting the sky. It is said by the wise that "+
      "these plants 'grow where the wind dropped the ashes of "+
      "burning Ilien, when Ereth-Akbe defended the Inward Islands "+
      "from the Firelord.' It is rumored, that this mighty wizard "+
      "and warrior used this flower to protect himself against "+
      "this enemy.\n");

    set_ingest_verb("eat");
    set_find_diff(8);
    set_id_diff(15);
    set_effect(HERB_ENHANCING, "fire", 30);
    set_herb_value(1500);
    set_decay_time(5000);
}

string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
}
void
int_recover(string arg)

{
    init_herb_recover(arg);
}
