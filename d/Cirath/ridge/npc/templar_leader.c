/* The templar who leads a patrol on the roads outside of the Tyr's
   city gates. Based heavily upon Serpine's generic templar.c .
   Dethraine, March 1998. Code (c) Damian Horton.
*/ 

#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include "defs.h"

#define TDESC ({"cruel", "sadistic", "pale-faced", "bureucratic", "arrogant", "condescending"})[random(6)]
#define TWEAP ({"axe_hevy", "swrd_nrw"})[random(2)]
#define TBARM ({"body_std", "body_hid", "body_scl"})[random(3)]
#define TLARM ({"legs_lth", "legs_wod", "legs_hid"})[random(3)]
#define TAARM ({"arms_lth", "arms_wod", "arms_hid"})[random(3)]
 
void
create_monster ()
{
    set_name("templar");
    add_prop (LIVE_I_NEVERKNOWN, 1);
    set_race_name("human");
    set_adj(TDESC);
    set_gender(random(2));
    set_long("This templar leads a patrol of guards in the service of "+
        "Kalak. It is "+HIS_HER(TO)+" job to keep order in the "+
        "agricultural fields which feed the city of Tyr.\n");
    set_appearance_offset((-50)+random(100));

    set_stats(({82+random(12),80+random(12),78+random(12),
        76+random(12),80+random(12),78+random(12)}));

    set_skill(SS_WEP_SWORD, 62+random(10));
    set_skill(SS_WEP_AXE, 62+random(10));
    set_skill(SS_BLIND_COMBAT, 15+random(10));
    set_skill(SS_DEFENCE, 62+random(10));
    set_skill(SS_PARRY, 56+random(10));
    set_skill(SS_UNARM_COMBAT, 45+random(10));
    set_alignment(-(random(500)));
    set_exp_factor(150);   

    set_act_time(5);
    add_act("east");
    add_act("west");
    add_act("emote ponders throwing you into the slave pits.");
    add_act("emote prays.");
    add_act("say Don't cause me any trouble.");
 
    set_cact_time(3);
    add_cact("say You will feel the power of my master!");
    add_cact("emote gazes at you with glowing eyes.");
    add_cact("emote reaches out with an outstretched hand.");
}
 
void
arm_me()
{
    clone_object(TYR_WEP+TWEAP)->move(TO);
    clone_object(TYR_ARM+TBARM)->move(TO);
    clone_object(TYR_ARM+TLARM)->move(TO);
    clone_object(TYR_ARM+TAARM)->move(TO);
    clone_object(TYR_ARM+"robe_sim")->move(TO);
    command("wield all");
    command("wear all");
}
 
/* **************** The Templar Casts! ******************** */
int
special_attack(object enemy)
{
    object spell, me;
    mixed* hitresult; 
    string how;
    int strength, power_this_time;
 
    me=this_object();
    strength=(me->query_base_stat(SS_WIS));
 
    power_this_time=(random(strength));
 
    if(random(10)) return 0;
 
    if(power_this_time < 75)
    {
        hitresult = enemy->hit_me((2*power_this_time), W_BLUDGEON, me, -1);
        how = "unimpressed";
        if (hitresult[0] > 0) how = "shaken";
        if (hitresult[0] > 15) how = "slightly drained";
        if (hitresult[0] > 30) how = "moderately drained";
        if (hitresult[0] > 50) how = "greatly drained";
        if (hitresult[0] > 75) how = "horribly drained";
 
        enemy->catch_msg(QCTNAME(me) + " touches you with "+
                         HIS_HER(me) + " outstreched palm.\n");
        enemy->catch_msg("You feel " + how + ".\n");
 
        tell_watcher(QCTNAME(me)+" touches "+QCTNAME(enemy)+
                     " with " + HIS_HER(me) + " outstretched palm.\n",
                     me, enemy);
 
        if(enemy->query_hp() <= 0) enemy->do_die(me);
 
        return 1;
    }
 
    if (present("_templar_hold_", enemy)) return 0;
    spell=clone_object(TYR_OBJ+"temphold");
    spell->set_remove_time(random(strength+1));
    spell->move(enemy);
    enemy->catch_msg(QCTNAME(me) + " touches you with " + HIS_HER(me)
         +" hand. A sense of helplessness fills you as your "
         +"limbs stiffen.\n");
    tell_watcher(QCTNAME(me)+" touches "+QCTNAME(enemy)+" lightly, "
         +"apparently inducing some sort of paralysis.\n",
         me, enemy);
 
    return 1;
}
