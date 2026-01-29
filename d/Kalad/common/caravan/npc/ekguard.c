/*
 *  Modified by Zignur 2017-09-22
 */

#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("soldier");
    set_race_name("human");
    set_adj("elite");
    add_adj("kabal");
    set_short("elite kabal soldier");
    set_long("An elite member of the already elite military of the city-state of Kabal, "+
      "his stern, unforgiving features are no doubt due to the horrendous "+
      "acts of brutality and violence he's seen, as well as committed.\n");
    
    /* New stats changed by Zignur 2017-09-22 */
    set_stats(({133, 133, 133, 133, 133, 133}));
    
    set_alignment(100);
    
    /* New skills changed by Zignur 2017-09-22 */
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_BLIND_COMBAT, 50);
    
    set_act_time(6);
    add_act("emote peers at you suspiciously.");
    add_act("say Don't start any trouble here.");
    add_act("emote stares resolutely around the area.");
    add_act(({"assist grumbar", "assist goliath", "assist guard"}));
    add_act("say You'll be sorry if you cause any commotion here.");
    set_cact_time(1);
    add_cact("say Damn you to the Nine Hells!!!");
    add_cact("say I'll enjoy watching you die!");
    add_cact("say Death to you!");
    add_cact("emote grins savagely.");
    add_cact("laugh evil all");
    add_speak("You'd better not start any trouble here.\n");
    set_knight_prestige(-1);
    set_default_answer("What?\n");
    add_ask(({"captain"}), "That would be Hahmal.\n");
    add_ask(({"military", "army"}), "You could never join, so why bother asking!?!\n");
}

void
arm_me()
{
    /* Use equip instead changed by Zignur 2017-09-22 */
    equip(({
      ARM + "egbanded",
      ARM + "egbanded",
      ARM + "egshield",
      ARM + "eggreaves",
      ARM + "eggaunt",
      WEP + "egsword",
      }));
      
    command ("wear all");     
    command("wield all");
    
    MONEY_MAKE_GC(random(6))->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
    command("say Die troublemaker!");
    command("kill " + OB_NAME(ob));
    }
}
