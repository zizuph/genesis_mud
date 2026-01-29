/* Manor's Garden black rose
 * Coded by Marisol (10/27/97)
 * This flower if smell it will make you ill.
 * For use in the Manor's Garden in Re Albi
 * Copyright (c) Marisol Ramos 1997 */

/* Modified by Marisol for the castle_garden in Emerald. (07/7/98)*/

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#define EBONY_POISON "/d/Emerald/herbs/eb_rose_poison.c"

int EFFECT, CC;

void
create_herb()
{
    set_name("rose");
    add_adj("ebony");
    set_herb_name("dark apollyon");
    set_short("black rose");
    set_pshort("black roses");
    add_name("flower");
    add_pname("flowers");
    set_unid_long("A unusual-smelling ebony rose from a rosebush.\n");
    set_id_long("A Dark Apollyon rose. This rose is "+
        "very rare. It is rumored that followers of Val-Shoreil "+
        "use it as an offering to him. Also that its smell can affect "+
        "people in peculiar ways. It is also rumored that the "+
        "previous lord of Talbarion cultivated these flowers for "+
        "his nefarious spells.\n");

    EFFECT = 2;
    CC = (6 * EFFECT) + (EFFECT * EFFECT)/4;

    set_ingest_verb("smell");
    set_find_diff(5);
    set_id_diff(11);
    set_effect(HERB_SPECIAL, "", EFFECT);
    set_herb_value(CC);
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

void
special_effect()
{
    object tp = this_player();
    object to = this_object();
    object poison;

    tp->catch_msg("As you smell the ebony rose, "+
    "you see in the corner of your eyes something suspicious.\n");
    tp->command("peer susp");
    setuid();
    seteuid(getuid(to));
    poison = clone_object(EBONY_POISON);
    poison->move(tp);
}
