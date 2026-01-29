/* Fireweed by Teth, Feb.18,96 */
/* Modified by Teth, Dec 28, 97 -> added check for fire spells */
/* Known bug: without a mudlib change, the long desc is set only 
 * once and does not change depending on the person's fire spells
 * skills. */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Krynn/common/defs.h"

public void
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
    set_id_long(query_id_long());
    set_herb_value(1232);
    set_id_diff(16);
    set_find_diff(8);
    set_effect(HERB_ENHANCING,"fire",25);
    add_effect(HERB_HEALING,"fatigue",1);
    set_decay_time(7200);
    set_amount(1);
}

public string
query_id_long()
{
    int fire_check = this_player()->query_skill(SS_ELEMENT_FIRE);
    string skilled = "";

    if (fire_check > 15)
    {
      skilled = " Your knowledge of fire gives you the ability " +
            "to recognize that eating fireweed will increase " +
            "one's resistance to fire.";
    } 

    return ("This is the flower of fireweed, an herb found " +
        "in temperate areas near disturbance. Fireweed (Epilobium " +
        "angustifolium) is given this name since it is frequently found " +
        "near areas that have been recently burned. Its roots are " +
        "rumoured not to be affected by fire, perhaps the rest of " +
        "the plant is as resistant. Every part of the plant is edible, " + 
        "particularly in the spring time." + skilled + "\n");
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }

