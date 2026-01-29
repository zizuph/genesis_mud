/*
 *  Edit Ckrik 11/2003
 *    Added to long desc note about fire hazard.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include "defs.h"

public void
create_herb() 
{
    set_name(({"berry","herb","handful",}));
    set_pname("handfuls");
    set_short("handful of small purple berries");
    set_pshort("handfuls of small purple berries"); 
    set_adj(({"purple", "small"}));
    set_herb_name("skunk berries");
    add_name("_es_skunkberry_");
    set_pname(({"handfuls of skunk berries", "herbs"}));
    set_unid_long("A handful of small purple berries.\n"); 
    set_id_long("Skunk berries, or "+
        "Flatulentia maxima. The small purple berries of " +
        "this plant have medicinal value, but have unfortunate " +
        "side effects in susceptible individuals. It has been " +
        "rumoured that consumption of these berries is a " +
        "potential fire hazard. Use with caution.\n");
    set_ingest_verb("eat");
    set_find_diff(3);
    set_id_diff(30);
    set_effect(HERB_SPECIAL, "", 25);
    set_herb_value((4 * 25) + (25 * 25)/5);
    set_decay_time(5000);
}

public void
special_effect()
{
    object tp = this_player(), to = this_object(), poison;
    write("As you eat the purple berries, a terrible bitter taste " +
        "fills your mouth.\n");
    tp->command("gag");
    setuid();
    seteuid(getuid(to));
    poison = clone_object(SKUNK_POISON);
    poison->move(tp, 1);
}
