/*
 * Columbine
 * Finwe, March 2003
 */

#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb.c";

create_herb()
{
    set_name("columbine");
    add_name("leaf");
    set_adj(({"emerald","green"}));
    set_short("emerald green leaf");
    set_herb_name("columbine");
    set_id_long("This is a branching leaf from the Columbine plant. The " +
        "plant grows in moist areas, occasionally in woods and copses, " +
        "and in open clearings. The flowers are either blue or white, and " +
        "turned upside down on a curved stem. The leaves become smaller the " +
        "further up the stem, and are emerald green colored.\n");
    set_unid_long("This is a emerald green leaf.\n");
    set_ingest_verb("eat");
    set_id_diff(35);
    set_find_diff(2);
    set_effect(HERB_HEALING,"hp",-15);
    set_decay_time(1800);
    set_herb_value(350);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
