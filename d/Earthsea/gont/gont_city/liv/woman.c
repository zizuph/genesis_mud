/* 
 * woman--citizen of Gont Port, Amelia, 5/10/98
 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/width_height";

#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "defs.h"

#define DRESS "/d/Earthsea/gont/gont_city/arm/dress"
#define DAGGER "/d/Earthsea/gont/gont_city/wep/c_dagger"

public void
create_earthsea_monster()
{
    set_name("meia");
    add_name("woman");
    set_adj(({"tanned", "golden-haired"}));
    set_race_name("human");
    set_gender(G_FEMALE);
    set_height("tall");
    set_width("normal");
    set_stats(({ 60 + random(20), 55 + random(30),
        69 + random(30), 30, 30, 80 }));
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 90);
    set_skill(SS_WEP_KNIFE, 90);
    set_appearance_offset(-55);
    add_equipment(({ DAGGER, DRESS }));
    set_random_move(50);
    set_restrain_path(STREET);
    set_chat_time(120);
    set_act_time(120);
    add_chat("I hope I can get to the beach while the sun "+
        "is still shining!");
    add_act("emote smiles, showing a cute dimple in her cheek.");
    (MONEY_MAKE_SC(random(10)))->move(this_object());
}
