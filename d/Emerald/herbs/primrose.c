 /* Evening primrose. Its smell will make you feel
 * slightly less tired. To be found in Emerald.
 * Coded by Marisol (08/11/98), Copyright (c) Marisol Ramos 1998*/

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_adj("yellow");
    set_herb_name("evening primrose");
    set_short("yellow flower");
    set_pshort("yellow flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A yellow and fragant flower from a bush.\n");
    set_id_long("An Evening primrose. A lovely bright yellow "+
        "flower. Its perfume is more sweet and fragant during the "+
        "evening.\n");

    set_ingest_verb("sniff");
    set_find_diff(3);
    set_id_diff(8);
    set_effect(HERB_HEALING, "fatigue", 10);
    set_herb_value(100);
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
