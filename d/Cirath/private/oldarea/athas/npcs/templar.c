/* templar.c: Generic Athasian Templar. Serpine, 12/5/95. */
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include "defs.h"
 
#define TDESC ({"cruel", "sadistic", "pale-faced", "bureucratic", "arrogant", "condescending"})[random(6)]
#define TWEAP ({"swrd_obs", "qrtrstff", "axe_hevy", "swrd_nrw"})[random(4)]
#define TBARM ({"body_std", "body_hid", "body_scl"})[random(3)]
#define TLARM ({"legs_lth", "legs_wod", "legs_hid"})[random(3)]
#define TAARM ({"arms_lth", "arms_wod", "arms_hid"})[random(3)]
 
void
create_monster ()
{
    ::create_monster();
    set_name("_genericus_");
    add_name("templar");
    add_prop (LIVE_I_NEVERKNOWN, 1);
    set_race_name("templar");
    set_adj(TDESC);
    set_gender(random(2));
    set_long("This is a Templar, sworn to defend "+HIS_HER(TO)+" city to the death, "
            +"and out to make a profit while at it if possible. This "
            +"Templar is special, being on so secret a mission that "
            +HIS_HER(TO)+" origin must be kept hidden.\n");
   
    set_stats(({ 95, 85, 115, 55, 55, 50 }));
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_KNIFE, 75);
    set_skill(SS_BLIND_COMBAT, 25);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 45);
    set_skill(SS_UNARM_COMBAT, 60);
    set_alignment(-(random(500)));
   
    set_act_time(3);
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
    clone_object(ATH_WEAPON+TWEAP)->move(TO);
    clone_object(ATH_ARMOUR+TBARM)->move(TO);
    clone_object(ATH_ARMOUR+TLARM)->move(TO);
    clone_object(ATH_ARMOUR+TAARM)->move(TO);
    clone_object(ATH_ARMOUR+"robe_sim")->move(TO);
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
    spell=clone_object(ATH_ITEMS+"temphold");
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
