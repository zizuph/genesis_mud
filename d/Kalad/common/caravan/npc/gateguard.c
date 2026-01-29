/*
   Modified by Zignur 2017-09-14
   
 */
 
#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/assist";
inherit "/d/Kalad/lib/arm_me";

void
create_kalad_monster()
{
    set_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("elite");
    add_adj("kabal");

    set_short("elite guardsman of Kabal");
    set_pshort("elite guardsmen of Kabal");
    set_long("A tall, dark-haired man of indeterminate age. Just from "+
      "gazing at his stance you can clearly tell he is an individual that "+
      "is well-trained in the art of combat. His duty is to stand guard "+
      "at the Caravan Gate and make sure nothing is amiss, and if trouble "+
      "occurs he will do his utmost to end that threat to the city.\n");
    
    /* New stats changed by Zignur 2017-09-14 */ 
    set_stats(({130, 130, 130, 130, 130, 130}));
    
    set_alignment(125);
    /* New skills changed by Zignur 2017-09-14 */
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_AWARENESS, 50);

    set_act_time(20);
    add_act("emote peers at you suspiciously.");
    add_act("say Don't start any trouble here.");
    add_act("emote stares resolutely around the area.");
    add_act("emote adjusts his keen awl pike.");

    set_cact_time(9);
    add_cact("shout To the most skilled warrior goes this battle!");
    add_cact("say I shall savour ridding Kabal of filth such as you.");
    add_cact("say You shall meet death at my hands!");
    add_cact("say Filthy animal! I will impale your worthless corpse upon my pike!!");
    add_cact("grin");
    add_cact("say You'll regret the day you attacked me!");
    add_speak("My duty is to protect the Caravan Gate from potential "+
      "troublemakers.\n");

    set_knight_prestige(-3);

    set_default_answer("The elite guardsman says: What? Do not come here disturbing me " +
      "with your stupid questions. I have better things to do.\n" +
      "The elite guardsman grumbles.\n");
    add_ask(({"captain"}), "The elite guardsman says: That would be Hahmal.\n");

    // Set the friends we should assist
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);
    // Actively watch my friends.
    set_watch_friends(1);

    // Add some equipment
    equip(({
    CVAN + "arm/egbanded",
    CVAN + "arm/eghelm",
    CVAN + "arm/eggreaves",
    CVAN + "arm/eggaunt",
    CVAN + "wep/egpolearm",
      }));
    command("wield all");
    command("wear all");
      
    MONEY_MAKE_GC(random(3))->move(TO, 1);
    
    /* Added because of special changed by Zignur 2017-09-14 */
    set_exp_factor(120);
}

// Do something when we assist
void
assist_hook(object friend, object enemy)
{
    command("shout Attackers at the Caravan Gate!!!");
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;
    if(random(6))
    return 0;
    hitresult = enemy->hit_me(100 + random(200), W_IMPALE, me, -1);
    how = " with barely a scratch";

    if(hitresult[0] > 0)
    how == "";
    if(hitresult[0] > 5)
    how = " with a glancing blow";
    if(hitresult[0] > 10)
    how = " with a firm blow";
    if(hitresult[0] > 15)
    how = " with a painful blow";
    if(hitresult[0] > 20)
    how = " with a savage blow";
    if(hitresult[0] > 25)
    how = " with a devastating blow";
    if(hitresult[0] > 30)
    how = " with a blow that rips through your flesh";
    me->catch_msg("You attempt to impale your foe on your keen awl pike!\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " attempts to impale you!\n"+
      "You are hit" + how + ".\n");
    tell_watcher(QCTNAME(me) + " attempts to impale " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
    if(enemy->query_hp() <= 0)
    enemy->do_die(me);
    return 1;
}
