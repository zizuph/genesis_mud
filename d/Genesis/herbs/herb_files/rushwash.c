/* A bunch of rushwash. This herb when eat it
 * will make you feel less tired. It is found all
 * over Earthsea. Coded by Marisol (11/12/97)
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("leaves");
    add_adj("bunch of");
    set_herb_name("rushwash");
    set_short("bunch of leaves");
    set_pshort("bunch of leaves");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A bunch of fragant green leaves.\n");
    set_id_long("A bunch of fresh rushwash! This herb is highly "+
        "prized in all the islands of the Archipelago. The dry "+
        "leaves are used to brew a delicious tea. The fresh herbs "+
        "are good when you feel down and tired after a long day "+
        "at the sea.\n");

    set_ingest_verb("eat");
    set_find_diff(3);
    set_id_diff(6);
    set_effect(HERB_HEALING, "fatigue", 10);
    set_herb_value(38);
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
