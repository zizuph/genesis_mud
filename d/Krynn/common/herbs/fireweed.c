/* Fireweed by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"purple", "showy"}));
    set_herb_name("fireweed");
    set_short("showy purple flower");
    set_pshort("showy purple flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a showy purple flower. It was probably " +
        "picked from a disturbed area near forest or prairie."));
    set_id_long(BSN("This is the flower of fireweed, an herb found " +
        "in temperate areas near disturbance. Fireweed (Epilobium " +
        "angustifolium) is given this name since it is frequently found " +
        "near areas that have been recently burned. Its roots don't " +
        "seem to be too affected by fire, perhaps that is true for the " +
        "rest of the plant as well. Every part of the plant is edible, " + 
        "particularly in the spring time."));
    set_herb_value(1232);
    set_id_diff(16);
    set_find_diff(8);
    set_effect(HERB_ENHANCING,"fire",25);
    add_effect(HERB_HEALING,"fatigue",1);
    set_decay_time(7200);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
