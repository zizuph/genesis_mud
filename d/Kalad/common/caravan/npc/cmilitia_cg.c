/*
   Modified by Zignur 2017-09-14
   
 */

#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/d/Kalad/lib/arm_me";
inherit "/d/Kalad/lib/assist";

string
random_extra()
{
    return ({
      "reginald", "reginald", "reginald",
      "boris", "boris", "boris", "boris",
      "anth",
      "james",
      "charles",
      "norwood",
      "febbo",
      "amrocar",
      "andian",
      "ulf",
      "gorbel",
      "brit",
      "daniel",
      "wilhelm",
      "obbo",
      "tandel",
      "ardindel",
      "mitus",
      "linus",
      "landil",
      "kathin",
      "baern",
      "sehkmaa",
      "joseph",
      "dav",
      "pieter",
      "mikel",
      "glen",
      "erik",
      "fellir", })[random(35)];
}

void
create_kalad_monster()
{
    string extra;

    extra = random_extra();

    set_name(extra);
    add_name("militiaman");
    add_pname("militiamen");
    set_race_name("human");
    set_adj("watchful");
    set_long("This ordinary-looking man is carefully scanning his "+
      "surroundings, alert to any possible danger. The patch sewed onto his "+
      "right arm of two crossed swords indicates he is a member of the Kabal "+
      "city militia.\n");
    
    /* New stats changed by Zignur 2017-09-14 */
    set_stats(({65, 65, 65, 65, 65, 65}));
    set_alignment(250);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_act_time(3);
    add_act("hmm");
    add_act("say Greetings traveller.");
    add_act("say Welcome to Kabal, our wonderful city.");
    add_act("emote carefully scans his surroundings.");
    set_cact_time(3);
    add_cact("say You will cease this senseless act now!");
    add_cact("say The city guards will kill you for this!");
    set_title("the Militiaman");
    add_speak("You're a bit too curious for your own good.\n");
    set_knight_prestige(-3);

    // I am a Kabal citizen
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    // I do funny stuff when a Kabal citizen is attacked
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    // Add some equipment
    equip(({
    CVAN + "arm/cmscale",
    CVAN + "wep/cmsword",
      }));
      
    command("wield all");
    command("wear all");

    MONEY_MAKE_SC(random(30)+5)->move(TO, 1);
    
    /* Added because of their special attack by Zignur 2017-09-13 */
    set_exp_factor(120);
}

// I don't assist, but make a lot of noise in stead.
void
assist(object friend, object attacker)
{
    if (!CAN_SEE_IN_ROOM(this_object()))
    return;

    command("shout No fighting in the streets, " +
      attacker->query_nonmet_name() + "!");
    command("swear");
    command("say You'll be sorry you did this, " +
      attacker->query_nonmet_name() + "!");
    command("in");
    command("emote warns of attackers at the gate.");
    command("emote sweats profusely.");
    command("say I'll just wait here while the guards take care of those "+
      "pesky attackers.");
    command("grin .");
}

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;

    if(random(100) > 85)
    {
    if(query_combat_object()->cb_tohit(-1, 40 + random(20), ob) < 1)
       return 0;

    if(!sizeof(query_weapon(-1)))
       return 0;

    hitres = ob->hit_me(random(90)+50, W_BLUDGEON, TO, -1);
    phurt = " with hardly any effect";
    switch(hitres[0])
    {
    case 1..20:
        phurt = "";
        break;
    case 21..40:
        phurt = " with a thud";
        break;
    case 41..60:
        phurt = " with a loud thud";
        break;
    case 61..80:
        phurt = " with a loud crack";
        break;
    default:
        phurt = " with a bone crushing sound";
    }

    tell_object(ob, query_The_name(ob)+" slams his foot into your "+
     "chest"+phurt+"!\n");
    tell_watcher(QCTNAME(TO)+" slams his foot into "+QTNAME(ob)+"'s "+
      "chest"+phurt+"!\n", ob);

    if(ob->query_hp() <= 0)
        ob->do_die(TO);
    return 1;

    }
    return 1;
}
