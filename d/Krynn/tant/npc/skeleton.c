/*
 * Skeleton by Teth Jan 18 97
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

    set_name("skeleton");
    set_race_name("skeleton");
    set_short("vicious skeleton");
    set_long("This is a vicious skeleton, that obviously hates all life " +
        "and obviously intends to rob you of yours! The bones of the " +
        "skeleton seem more delicate than a human's bones.\n");
    set_adj("vicious");
    set_gender(G_NEUTER);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_UNDEAD, 2);
    set_alarm(1.0,0.0,"arm_me");
    set_m_in("stalks in");
    set_m_out("stalks");
    set_aggressive(1);

    set_stats(({30,10,20,5,5,10}));
    set_skill(SS_DEFENCE,        10);
    set_skill(SS_WEP_SWORD,      20);

    set_alignment(-100);
    set_knight_prestige(2);

    set_random_move(50);
    set_restrain_path(TROOM);
    set_monster_home(TROOM + "sewer16");
   
    set_act_time(4);
    add_act("emote cackles voicelessly.");
    add_act("emote stares at you with hatred.");
    add_act("emote stalks about with hesitant movements.");
    add_act("emote glares at you evilly.");
    add_act("emote appraises its sword with undead eyes.");
}

public void
arm_me()
{
    clone_object(TWEP + "sk_sword")->move(TO);
    clone_object(KRARMOUR + "sk_ring")->move(TO);
    clone_object(KRARMOUR + "sk_helmet")->move(TO);
    clone_object(KRARMOUR + "sk_elfmail")->move(TO);
    command("wear all");
    command("wield all");
}

