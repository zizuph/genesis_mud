/* 
* corporal/ leader of patrol in Gont Port
*
* Coded by Porta, Dec 97
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include "basic_guard.h"
#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>

private int attacked = 0;

public void
create_earthsea_monster()
{
    set_name("corporal");
    set_living_name("_corporal_gp_");
    add_adj("young");
    set_short("young corporal");
    set_long("This is a corporal in the mercenary "+
        "army of the Lord of Gont. " + capitalize(query_pronoun()) +
        " looks like he is hoping for his next promotion.\n");
    set_gender(random(1));
    set_random_move(10);
    set_stats(({ 60 + random(30), 60 + random(30),
        60 + random(30), 20, 20, 90 }));
    set_skill(SS_WEP_SWORD, 65);
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_PARRY, 65);
    set_skill(SS_BLIND_COMBAT, 85);
    set_skill(SS_AWARENESS, 90);
    set_restrain_path(STREET);
    set_m_in("marches in");
    set_m_out("marches away");
    set_chat_time(180);
    set_act_time(180);
    add_chat("The sergeant doesn't tolerate lack of discipline.");
    (MONEY_MAKE_GC(random(5)))->move(this_object());
    add_equipment(({SWORDTWO, BOOTS, HELM, CLOAK, RINGMAIL }));
    add_prop(LIVE_I_NEVERKNOWN, 1);
}

public int
attacked_by(object player)
{
    object *other_guards;
    int i;

    if(attacked)
        return 1;

    command("shout Guards! To me!!");
    other_guards = query_team_others();
    attacked = 1;

    if(sizeof(other_guards))
    {
        other_guards[0]->command("shout Attack!! Sound the alarm!");

        for(i = 0; i < sizeof(other_guards); i++)
        {
            other_guards[i]->command("kill " +
                lower_case(player->query_real_name()));
        }
    }

    return 1;
}
