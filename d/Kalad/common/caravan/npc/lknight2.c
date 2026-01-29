/*
* Added a new weapon to Thanar knights, with the permission of Valen.
* Dargoth, 2004.09.10. 20:13
*
*  Modified by Zignur 2017-09-20
*  Mirandus 2018-02-13 -  Added some actions indicating that he disagrees 
*  with the new stance of the Thanar Order which allows for it to make 
*  sense for him to remain below. He still wishes to carry out what 
*  he believes are the true plans of Thanar.
*/
#include "default.h"
#include <macros.h>
	
inherit "/d/Kalad/std/monster";
inherit "/lib/unique";

#define GNATSLAYER (WEP + "gnatslayer")
#define MAX_GNATS 5
#define CHANCE_GNAT 50
#define SWORD (WEP + "lksword")
	
void create_kalad_monster()
{
    set_name("knight");
    add_name("killer knight");
    set_race_name("human");
    set_adj("impressive");
    add_adj("murderous");
    set_short("killer knight of Thanar");
    set_long("An impressive-looking individual whose countenance "+
      "indicates one practiced in not only the art of combat, but the art "+
      "of tortuous murder. His crazed eyes betray a look of barely "+
      "contained insanity.\n");
    /* New stats changed by Zignur 2017-09-20 */  
    set_stats(({110, 110, 110, 110, 110, 110}));
    
    set_alignment(-875);
    
    /* New skills changed by Zignur 2017-09-20*/
    set_skill(SS_WEP_CLUB, 80);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_AWARENESS, 90); 
    
    set_act_time(6);
    add_act("emote sneers in contempt at the thought of the lesser non-human races.");
    add_act("emote makes a crude joke involving a gnome and a cow.");
    add_act("glare all");
    add_act("say Only the faithful of Thanar may pass me.");
    add_act("say I can't wait till the war starts, then I get to murder "+
      "and pillage to my heart's content!");
    add_act("laugh insanely");
    add_act("say The leadership has sold out. I shall make them pay.");
    add_act("grin menacingly all");
    add_act("say Those damn fools. They've cowed to the pressure.");
    add_act("say I will never agree to return to the Cathedral.");
    add_act("say The Chosen Priest has made a mistake.");
    set_cact_time(3);
    add_cact("say I will slay you quickly, that you may meet whatever "+
      "pitiful god it is that you worship!");
    add_cact("emote sings out a battlecry to Thanar!");
    add_cact("snarl all");
    add_cact("emote makes a repulsive joke involving you and a two-humped camel.");
    add_cact("growl devil all");
    add_speak("You may  pass...\n");
    set_knight_prestige(875);
    set_default_answer("The killer knight of Thanar says: What?!?\n");
    MONEY_MAKE_GC(random(5))->move(TO, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    /* XP Adjustment, because of their special Zignur 2017-09-20 */
    set_exp_factor(120);    
}

void
init_living()
{
    ::init_living();
}

void arm_me()
{
    object wep, arm;
    setuid();
    seteuid(getuid(TO));
    
    arm = clone_object(ARM + "lkhelm");
    arm->move(TO);
    arm = clone_object(ARM + "lkchain");
    arm->move(TO);
    command("wear all");
    
    wep = clone_unique(GNATSLAYER, MAX_GNATS, SWORD , 1, CHANCE_GNAT);
    if (MASTER_OB(wep) != GNATSLAYER)
        add_act("emote pledges anew his blade to the cause of Thanar.");
    else
    {
        add_act("emote brandishes his "+wep->short()+".");
        add_act("say Ah, those wizards are of some use, after all!");
        add_cact("emote jabs his "+wep->short()+
        " towards you, attempting a false move.");
        add_prop(LIVE_I_QUICKNESS,150);
    }
    wep->move(TO);
    command("wield all");
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
    command("shout Death to the demihumans!!!");
    command("kill " + OB_NAME(ob));
    }
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;
    if (random(10))
    return 0;
    hitresult = enemy->hit_me(200 + random(300), W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
    how == "";
    if (hitresult[0] > 10)
    how = " hard";
    if (hitresult[0] > 20)
    how = " very hard";
    me->catch_msg("You bodyslam your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is bodyslammed"+
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " bodyslams you!\n"+
      "You are bodyslammed" + how + ".\n");
    tell_watcher(QCTNAME(me) + " bodyslams " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is bodyslammed"+
      how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
    enemy->do_die(me);
    return 1;
}


