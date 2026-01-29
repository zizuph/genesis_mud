 /* A marsh mallow plant. When eat it, will increase the 
 * healing process. Coded by Marisol (08/10/98)
 * Copyright (c) Marisol Ramos 1998 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_adj("pale pink");
    set_herb_name("marsh mallow");
    set_short("pale pink flower");
    set_pshort("pale pink flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A charming pale pink flower.\n");
    set_id_long("A marsh mallow plant. This plant has charming "+
        "pale pink, saucer-shaped flowers. It is very common in "+
        "marshes lands, mainly near the sea, but it can be found "+
        "in any kind of wet land. The whole plant, both flowers and "+
        "root is mighty medicinal.\n");

    set_ingest_verb("eat");
    set_find_diff(6);
    set_id_diff(20);
    set_effect(HERB_HEALING, "hp", 30);
    set_herb_value(100);
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
