/* Chicory by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"short", "sharp"}));
    set_herb_name("chicory");
    set_short("sharp short leaf");
    set_pshort("sharp short leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a sharp short leaf. It was probably " +
        "picked from somewhere near open plains or much sunlight."));
    set_id_long(BSN("This is the leaf of chicory, a herb found " +
        "in temperate open areas. Chicory (Cichorium intybus) is a " +
        "herb that develops purple blossoms. It is deep-rooted, " +
        "efficiently tapping underground water. Chicory is said to " +
        "help fight tiredness and stimulate action."));
    set_herb_value(188);
    set_id_diff(25);
    set_find_diff(5);
    set_effect(HERB_HEALING,"fatigue",35);
    set_decay_time(8000);
    set_dryable();
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
