/*
 * Lamia herb, better known as Self-heal in the real world.
 * Finwe, March 2003
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
    set_name("lamia");
    add_name("leaf");
    set_adj(({"long","green", "rough"}));
    set_short("long rough leaf");
    set_herb_name("lamia");
    set_id_long("This sprawling green plant with sandpapery leaves " +
        "is called Lamia. It blooms in the summer with copper-purple " +
        "flowers on spikes in early summer. It is rumoured to heal when " +
        "the leaves are chewed.\n");
    set_unid_long("This is a long rough leaf.\n");
    set_ingest_verb("chew");
    set_id_diff(35);
    set_find_diff(2);
    set_effect(HERB_HEALING,"hp",5);
    set_decay_time(2500);
    set_herb_value(700);
    set_dryable();
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
