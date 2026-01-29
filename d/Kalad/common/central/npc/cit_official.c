/*
Different workers in the Citadel.
    MADE BY: Korat
DATE: Feb 14 1995
*/
/* 2017-06-04 Malus: Removed name, set LIVE_I_NEVERKNOWN, fixed gender */ 
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
#include <stdproperties.h>

void
create_monster()
{
    ::create_monster();
    if (random(2))
        set_gender(G_FEMALE);

    switch(random(6))
    {
        case 0:
        set_adj("lazy");
        add_adj("accountant");
        set_alignment(50);
        set_knight_prestige(-1);
        break;
        case 1:
        set_adj("worksome");
        add_adj("cleric");
        set_alignment(200);
        set_knight_prestige(-1);
        break;
        case 2:
        set_adj("neglectful");
        add_adj("employee");
        set_alignment(50);
        set_knight_prestige(-1);
        break;
        case 3:
        set_adj("dedicated");
        add_adj("assistant");
        set_alignment(200);
        set_knight_prestige(-2);
        break;
        case 4:
        set_adj("laborous");
        add_adj("accountant");
        set_alignment(150);
        set_knight_prestige(-2);
        break;
        case 5:
        set_adj("plain");
        add_adj("worker");
        set_alignment(100);
        set_knight_prestige(-2);
        break;
        case 6:
        set_adj("silent");
        add_adj("archiver");
        set_alignment(150);
        set_knight_prestige(-2);
        break;
    }
    
    add_name("worker");
    set_race_name("human");
    set_long("This human is one of the employees of the High Lord, and is "+
        "supervised by the Master cleric.\n");
    set_stats(({40,30,45,40,50,20}));
    set_skill(SS_UNARM_COMBAT,40);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS,40);
    set_act_time(6);
    add_act(({"emote smiles at you.","say Greetings stranger."}));
    add_act(({"emote ponders work, work and work.","sigh"}));
    add_act(({"bow .","say Are you soon leaving?","smile hopefully"}));
    add_act(({"say He is a busy man, our Lord!",
                "smile proudly"}));
    set_cact_time(1);
    add_cact("say Why? What have I done to you?");
    add_cact("shout Heeeelp!");
    add_cact(({"scream","say Please stop this senseless act!"}));
    add_cact(({"say I am unarmed and unarmoured! This is unfair!","gasp"}));
    add_speak("I can't chat more...the Master cleric might see us.\n");
    set_default_answer("I am certain that your question is important, but "+
        "please ask someone else. I cannot help you.\n");
    add_ask(({"help","task","quest"}),"Ohh, very nice of you to ask, but "+
        "I have to do this by myself.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
}
void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/central/arm/cit_human_robe");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/central/arm/cit_human_sandal");
    arm -> move(TO);
    command("wear all");
    MONEY_MAKE_SC(random(20)+10)->move(TO,1);
}   
