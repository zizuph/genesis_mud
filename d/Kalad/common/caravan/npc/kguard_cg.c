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
    int i;

    set_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj(({"vigilant"}));
    set_long("He is a tall, dark-haired man whose job is to insure that "+
      "order is maintained in the great city of Kabal. Oftentimes he fails, "+
      "making him ever more cruel to those that defy him.\n");

    /* New stats changed by Zignur 2017-09-14 */ 
    set_stats(({90, 90, 90, 90, 90, 90}));
    set_alignment(333);
    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 30);
    /* New skills changed by Zignur 2017-09-14 */
    set_skill(SS_BLIND_COMBAT,50);
    set_act_time(6);
    add_act("peer all");
    add_act("say Beware.");
    add_act("emote scratches his chin in thought.");
    add_act("emote adjusts his armour.");
    set_cact_time(3);
    add_cact("shout Fellow guardsmen, come to my aid!");
    add_cact("say You will die for this cowardly attack, you miserable cur.");
    add_cact("scream");
    add_cact("say Filthy savage!!");
    add_cact("say Scum, I'll make you wish you'd never been born.");
    add_speak("Do not cause trouble here, you will be sorry if you do.\n");
    set_knight_prestige(-3);
    set_default_answer("The guardsman of Kabal says: What?\n");
    add_ask(({"captain"}), "The guardsman of Kabal says: That would be Hahmal.\n");

    // I assist Kabal citizens in combat
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    // I'm a Kabal guard and citizen
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN | KABAL_GUARD);

     /* Use Equp instead changed by Zignur 2017-09-14*/
    equip(({
    CVAN + "wep/" + ({"gmace", "gsword", "gaxe"})[random(3)],
    CVAN + "arm/gchain",
    CVAN + "arm/ghelm",
    CVAN + "wep/gdagger",
      }));    
    command("wield all");
    command("wear all");
    
    MONEY_MAKE_GC(random(4)+1)->move(TO, 1);
    MONEY_MAKE_SC(random(6)+2)->move(TO, 1);
    
    /* Added because of special changed by Zignur 2017-09-14 */
    set_exp_factor(120);
}

void
assist_hook(object friend, object enemy)
{
    command("say Villanous retch! Die!");
    command("spit " + OB_NAME(enemy));
}

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;

    if(random(100) > 75)
    {
    if(query_combat_object()->cb_tohit(-1, 60 + random(25), ob) < 1)
        return 0;

    if(!sizeof(query_weapon(-1)))
        return 0;

    hitres = ob->hit_me(random(150)+100, W_BLUDGEON, TO, -1);
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
    return 0;
}
