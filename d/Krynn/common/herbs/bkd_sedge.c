/* Beaked Sedge by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"elongated", "slender"}));
    set_herb_name("beaked sedge");
    set_short("elongated slender leaf");
    set_pshort("elongated slender leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an elongated slender leaf. It was " +
        "probably picked from a grass-like herb in a moist meadow."));
    set_id_long(BSN("This is a leaf of beaked sedge, an herb found " +
        "in temperate moist meadows. Sedges (Carex spp.) are herbs " + 
        "that grows from 2 cm to 80 cm high. This particular sedge " +
        "is called the beaked sedge due to the encasing perigynia " +
        "which covers the seed. The leaf feels gritty, as if it contained " +
        "sand. Most likely, it would not be a good idea to eat it."));
    set_effect(HERB_HEALING,"hp",-20);
    set_herb_value(12);
    set_id_diff(28);
    set_find_diff(5);
    set_decay_time(10000);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
