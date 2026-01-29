/* A moly. This herb will give some magic
  * resistance if eat it. It is found
  * all over Earthsea. Coded by Marisol (11/10/97)
  * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("bulb");
    add_adj("lilac");
    set_herb_name("moly");
    set_short("lilac bulb");
    set_pshort("lilac bulbs");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A garlic-like plant with lilac flowers "+
    "and a bulb of the same color.\n");
    set_id_long("A moly! This is a wild and garlic-like plant of the "+
        "lily family. It magic properties are highly prized by witches, "+
        "sorceress and wizards alike. If you fear against magic "+
        "attacks this may protect you.\n");

    set_ingest_verb("eat");
    set_find_diff(8);
    set_id_diff(12);
    set_effect(HERB_ENHANCING, "magic", 15);
    set_herb_value(890);
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
