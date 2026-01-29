/*
 * Columbine
 * Finwe, March 2003
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
    set_name("chives");
    add_name("leaf");
    set_adj(({"slender","green"}));
    set_short("bunch of slender green leaves");
    set_pshort("bunches of slender green leaves");
    set_herb_name("chives");
    set_id_long("This is a bunch of chives. The leaves resemble tall " +
        "grass shoot, are narrow and hollow inside. They are not as strong " +
        "as its cousin, the onion, but still tasty. The plant grows in " +
        "moist ground, and when flowering, has small pom-pom shaped flowers.\n");
    set_unid_long("This is a bunch of slender green leaves.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(1);
    set_effect(HERB_HEALING,"hp",3);
    set_decay_time(1800);
    set_herb_value(200);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
