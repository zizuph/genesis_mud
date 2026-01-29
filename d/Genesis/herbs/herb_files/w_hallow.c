/* A white hallow blossom. A forest and meadow flower
 * prized for its healing properties by healers. Flower
 * could be found in Gont and maybe other islands in Earthsea
 * Coded by Marisol (11/4/97)
 * This flower if eat it or use in a potion will heal hp.
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("blossom");
    add_adj("white");
    set_pname(({"blossoms", "flowers", "blooms"}));
    add_pname("white hallows");
    set_herb_name("white hallow");
    set_short("white blossom");
    set_pshort("white blooms");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A white blossom.\n");
    set_id_long("This is a white hallow blossom. This blossom is "+
      "rare and highly prized for its healing properties by "+
      "healalls and witches. It is found near creeks in the meadows "+
      "and forests of Gont and maybe in some other islands in "+
      "Earthsea.\n");

    set_ingest_verb("eat");
    set_find_diff(7);
    set_id_diff(10);
    set_effect(HERB_HEALING, "hp", 50);
    set_herb_value(800);
    set_decay_time(2000);
    set_dryable();
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
