 /* Selfheal. A plant with mauve spike of flowers. It will help
   * to heal fast when eat it. To be used in Emerald.
   * Coded by Marisol (08/11/98), Copyright (c) Marisol Ramos 1998*/

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flowers");
    add_adj("dense head of");
    set_herb_name("selfheal");
    set_short("dense head of flowers");
    set_pshort("dense heads of flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A full head of mauve flowers.\n");
    set_id_long("A selfheal. This herb is always in a dense "+
        "head of mauve flowers. It doesn't have any smell. As the name "+
        "indicates, selfheal increase the speed of recovery when "+
        "injured. It is a very handy herb to have around.\n");

    set_ingest_verb("eat");
    set_find_diff(3);
    set_id_diff(6);
    set_effect(HERB_HEALING, "hp", 20);
    set_herb_value(50);
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
