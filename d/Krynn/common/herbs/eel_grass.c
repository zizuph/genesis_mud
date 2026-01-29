/* Eel Grass by Teth, March 2,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_adj(({"green", "linear"}));
    set_herb_name("eel grass");
    set_short("linear green leaf");
    set_pshort("linear green leaves");
    set_pname(({"leaves", "herbs", }));
    set_ingest_verb("chew");
    set_unid_long(BSN("This is a linear green leaf. It was probably " +
        "picked from a salt marsh or near a beach."));
    set_id_long(BSN("This is the leaf of eel grass, an herb found " +
        "in salt marshes and near beaches. Eel grass (Zostera marina) " +
        "is a true flowering sea grass. It is always found " +
        "submerged. It has broader leaves than that of surf grass. " +
        "It has been suggested that chewing on the leaves has some " +
        "beneficial effect."));
    set_herb_value(1476);
    set_id_diff(45);
    set_find_diff(9);
    set_effect(HERB_SPECIAL,"",0);
    set_decay_time(2000);
}

void
special_effect()
{
    object  shadow;

    shadow = clone_object(KRHERB + "skill_enhance");
    shadow->set_enhance_effect(SS_SWIM,"swim",20);
    shadow->move(this_player(),1);
}


string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }




