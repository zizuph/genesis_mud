 /* Apothecary's rose. A nicely fragant and healthful rose.
 * Its medicinal use are many but for Emerald, will help to
 * resist poisoning but not cure it.
 * Coded by Marisol (08/11/98), Copyright (c) Marisol Ramos 1998*/

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("rose");
    add_adj("crimson");
    set_herb_name("apothecary's rose");
    set_short("crimson rose");
    set_pshort("crimson roses");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A crimson rose from a rose shrub.\n");
    set_id_long("An apothecary's rose! It has beautiful blooms with "+
        "intense fragance, semi-double flowers with crimson petals "+
        "with a golden center. It is said that its aroma can help "+
        "withstand noxious poisons for a little time. "+
        "It is a very important herb for a healer.\n");

    set_ingest_verb("smell");
    set_find_diff(10);
    set_id_diff(55);
    set_effect(HERB_ENHANCING, "poison", 30);
    set_herb_value(900);
    set_decay_time(5000);
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
