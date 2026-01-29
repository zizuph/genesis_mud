 /* Bee Balm.
 * This herb will refresh the tired body when inhale it.
 * Coded by Marisol (08/11/98) to be used in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

inherit "/std/herb";

#include <herb.h>
#include <macros.h>


void
create_herb()
{
    set_name("flower");
    add_adj("scarlet");
    set_herb_name("bee balm");
    set_short("scarlet flower");
    set_pshort("scarlet flowers");
    add_name("herb");
    add_pname("herbs");
    set_unid_long("A tubular scarlet flower.\n");
    set_id_long("A Bee Balm. This sweetly aromatic plant has "+
        "bright scarlet flowers with a very sweet smelling leaves. "+
        "As the name suggestes, the flower attracts bees because "+
        "its fragance and nectar. When inhale, you feel "+
        "refresh and full of life.\n");

    set_ingest_verb("inhale");
    set_find_diff(8);
    set_id_diff(50);
    set_effect(HERB_HEALING, "fatigue", 50);
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
