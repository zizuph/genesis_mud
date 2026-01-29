/* 
* Standard guard for Gont Port
*
* Coded by Porta, Dec 97
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/width_height";

#include "basic_guard.h"
#include <ss_types.h>
#include <money.h>

public void
create_earthsea_monster()
{
    set_name("vorn");
    add_name("vorn skahrn");
    set_living_name("_captain_gp_");
    set_adj(({"stern", "grey-haired"}));
    add_name("captain");
    add_name("skahrn");
    set_height("very tall");
    set_width("lean");
    set_title("Skahrn, Captain of the Guard");
    set_long("This is the captain of the mercenary guard who "+
        "serves the Lord of Gont. He appears very stern.\n");
    set_race_name("human");
    set_stats(({ 120, 140, 130, 80, 65, 120 }));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 95);
    add_chat("If you have no news, then don't waste my time!");
    add_chat("We will eliminate the troublemakers in this town.");
    add_act("emote looks very stern.");
    add_chat("Law and order, that's what we are here for.");
    (MONEY_MAKE_GC(random(5)))->move(this_object());
    add_equipment(({SWORDTWO, BOOTS, HELM, CLOAK, RINGMAIL }));
}
