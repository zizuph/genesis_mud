/*
 * Brigand by Teth Jan 18 97
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "../local.h"
inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

void
create_krynn_monster()
{

    set_name("brigand");
    set_race_name("human");
    set_short("menacing brigand");
    set_long("This is a menacing brigand. He obviously means to do you " +
        "no good. Perhaps you shouldn't meddle with him.\n");
    set_adj("menacing");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_alarm(1.0,0.0,"arm_me");
    set_m_in("saunters in");
    set_m_out("saunters");

    set_stats(({15,15,15,5,5,15}));
    set_skill(SS_DEFENCE,        10);
    set_skill(SS_WEP_SWORD,      20);

    set_alignment(-50);
    set_knight_prestige(2);

    set_random_move(50);
    set_restrain_path(TROOM);
    set_monster_home(TROOM + "road6");
   
    set_act_time(4);
    add_act("emote glares at you suspiciously.");
    add_act("emote preens himself.");
    add_act("emote snarls: You're a useless piece of crud! Worse than the " +
        "stuff flowing out of the sewers of Tantallon!"); 
    add_act("emote laughs at you exuberantly.");
}

public void
arm_me()
{
    clone_object(TWEP + "brig_sword")->move(TO);
    clone_object(KRARMOUR + "brig_shield")->move(TO);
    clone_object(TOBJ + "brig_food")->move(TO);
    command("wear all");
    command("wield all");
}

