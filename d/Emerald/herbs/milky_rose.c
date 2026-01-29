/* Manor's Garden white rose
 * Coded by Marisol (10/29/97)
 * This flower if smells it will clear your mind..
 * For use in the Manor's Garden in Re Albi
 * Copyright (c) Marisol Ramos 1997 */
/* Modified by Marisol (07/21/98) to be used of the garden in the 
 * castle near the village of Ovejuno in Emerald. */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("rose");
    add_adj("milky white");
    set_herb_name("moonlight beauty");
    set_short("milky white rose");
    set_pshort("milky white roses");
    add_name("flower");
    add_pname("flowers");
    set_unid_long("A honeyed-smelling white rose "+
    "from a rosebush.\n");
    set_id_long("A Moonlight Beauty rose. This enchanting rose is "+
        "like a piece of moonligh capture in the many petals of this "+
        "rose. It smells is sweet like honey, bringing a state of "+
        "well-being as the aroma enter your sense. This rose is "+
        "hard to cultivate and is only found in gardens under the "+
        "supervision of expert elvish gardener and sometimes some "+
        "gifted human in the lands of Emerald.\n");

    set_ingest_verb("smell");
    set_find_diff(10);
    set_id_diff(20);
    set_effect(HERB_HEALING, "mana", 50);
    set_herb_value(600);
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
