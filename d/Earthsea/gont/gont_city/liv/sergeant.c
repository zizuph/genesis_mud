/* 
* sergeant in Gont Port/leader of guards
*
* Coded by Porta, Dec 97
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "basic_guard.h"

public void
create_earthsea_monster()
{
    set_name("sergeant");
    set_living_name("_sergeant_gp_");
    set_short("tough sergeant");
    set_adj("tough");
    add_adj("ramrod");
    set_long("This is a sergeant in the mercenary "+
        "army of the Lord of Gont. " + capitalize(query_pronoun()) +
        " stands ramrod straight as if always at attention.\n");
    set_gender(random(1));
    set_random_move(10);
    set_stats(({ 100 + random(20), 110 + random(35),
        110 + random(20), 20, 20, 90 }));
    set_skill(SS_WEP_SWORD, 75 + random(30));
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_PARRY, 65);
    set_skill(SS_BLIND_COMBAT, 85);
    set_skill(SS_AWARENESS, 90);
    set_restrain_path(STREET);
    set_m_in("marches in");
    set_m_out("marches away");
    set_chat_time(250);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_act_time(250);
    add_chat("Lazy slackers! I won't tolerate lack of discipline!");
    add_act("emote inspects you up and down and frowns slightly.");
    (MONEY_MAKE_GC(random(5)))->move(this_object());
    add_equipment(({ SWORDTWO, BOOTS, HELM, CLOAK, RINGMAIL }));
}

public void
attacked_by(object player)
{
    object *other_guards = query_team_others();
    int i;

    if(sizeof(other_guards))
    {
        other_guards[0]->command("shout Attack!! Sound the alarm!");
        command("shout Guards! To me!!");
        for(i = 0; i < sizeof(other_guards); i++)
        {
            other_guards[i]->command("kill " +
            lower_case(player->query_real_name()));
        }
    }
}
