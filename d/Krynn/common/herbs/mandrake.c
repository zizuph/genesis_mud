/* Mandrake by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("root");
    set_adj(({"twisted", "gnarly"}));
    set_herb_name("mandrake");
    set_short("twisted gnarly root");
    set_pshort("twisted gnarly roots");
    set_pname(({"roots", "herbs", }));
    set_ingest_verb("chew");
    set_unid_long(BSN("This is a twisted gnarly root. It was " +
        "probably picked from an herb in a dark forest or swamp."));
    set_id_long(BSN("This is a root of mandrake, an herb found " +
        "in dark forests and swamps. Mandrake is a mystical herb that " + 
        "is rumoured to have magical properties, when the root is " + 
        "chewed. The root is consistently in the shape of a humanoid, " +
        "hence the name. It blooms black flowers, and its leaves are " +
        "said to be fatally poisonous."));
    set_herb_value(516);
    set_id_diff(62);
    set_find_diff(10);
    set_decay_time(2000);
    set_effect(HERB_SPECIAL,"",0);
    set_amount(2);
}

void
special_effect()
{
    object shadow;

    shadow = clone_object(KRHERB + "skill_enhance");
    shadow->set_enhance_effect(SS_ELEMENT_DEATH,"cast death spells",5);
    shadow->move(this_player(),1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
