/*
 *  Base code from /d/Gondor/common/wep/h_poleaxe.c
 *  Varian - 2016
 *
 * Cotillion - 2017-09-05
 * - Added null checks in try_hit to prevent runtimes
 */ 

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

#define IS_STUN "_stunned_from_poleaxe"
#define WEP ({"warhammer"})
#define ADJ ({ "massive"})
#define ADJ2 ({"mithril"})

void
create_weapon()
{
    string wep = one_of_list(WEP);
    string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2); 

    set_name(({wep}));
    add_name(({"club"}));
    set_short(adj+" "+adj2+" "+wep);
    set_adj(({adj}));
    add_adj(({adj2}));
    set_long("The "+adj+" "+adj2+" "+wep+" is extremely heavy, and " +
        "looks as if it would be absolutely deadly in the hand of a " +
        "trained soldier. Markings on the haft of the "+wep+" indicate that " +
        "this weapon belongs to the army of Gondor.\n");

    add_prop(OBJ_M_NO_BUY, 1); 
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }) );
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,({"It takes a bit of skill to use this" +
        " "+wep+" to its fullest. ",1,
        "When it is used to its fullest extent it makes deadly hits from " +
        "time to time. Its solid weight crushing the wielders opponent. ",25,
        "Sometimes the club might even stun an oponent. ",65,
        "\n",1}));
    set_default_weapon((40 + random(5)), (40 + random(10)), 
        W_CLUB, W_BLUDGEON, W_BOTH, 0);
    set_wf(this_object());

    add_prop(OBJ_I_WEIGHT, 2700);
    add_prop(OBJ_I_VOLUME, 2700);
    add_prop(OBJ_I_VALUE, 2500);
}

void reset_stun(object target)
{
	target->remove_prop(IS_STUN);
}

void un_stun(object target, object attacker)
{
    if (objectp(target))
    {
        target->remove_stun();
        target->catch_msg("You've recovered your senses.\n");
        tell_room(ENV(target), QCTNAME(target) + " seems to have recovered " +
            HIS_HER(target) + " senses.\n", target, target);
        set_alarm(30.0, 0.0, &reset_stun(target));
	}
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    object me;
    string me_text, target_text, watch_text;

    me = query_wielded();
    
    if (!objectp(me) || !objectp(enemy))
        return 1;


    skill = me->query_skill(SS_WEP_CLUB);
    stat = me->query_stat(SS_STR);
    skill_e = enemy->query_skill(SS_PARRY);
    stat_e = enemy->query_stat(SS_DEX);
    
    if (TP->query_skill(SS_WEP_CLUB) < 50)  //Special hit wont work unless you have the skill
        return 1;

    // We want to cap the stat at around 100 if the stats get too
    // high (above 110)
    if (stat > 90)
        stat = 70 + random(20);
    if (stat_e > 90)
        stat_e = 70 + random(20);

    if ((random(80) < (skill/2)) && (random(skill + stat) > random(skill_e + stat_e)))
    {
        if(random(4))
        {
            if(!enemy->query_prop(IS_STUN))
     	    {
                enemy->add_stun();
                enemy->add_prop(IS_STUN, 1);

                set_alarm(10.0, 0.0, &un_stun(enemy, me));
                me->catch_msg("Mustering all your strength, you swing your " + 
                    short() + " at " + QTNAME(enemy) + ", whacking " + 
                    HIM_HER(enemy) + " soundly on the head.\n" + 
                    capitalize(HE_SHE(enemy)) + " looks dazed.\n");

                enemy->catch_msg(QCTNAME(me) + " swings " + HIS_HER(me) + " " +
                    short() + " at you, hitting you soundly on the head.\n" +
                    "You feel dazed.\n");

                me->tell_watcher(QCTNAME(me) + " swings " + HIS_HER(me) + " " + 
                    short() + " at " + QTNAME(enemy) + ", whacking " + 
                    HIM_HER(enemy) + " soundly on the head.\n" + 
                    capitalize(HE_SHE(enemy)) + " looks dazed.\n");

                return 1;
            }
        }
	
    pen = F_PENMOD(40+random(stat/4), skill);
    hitresult = enemy->hit_me(pen, W_BLUDGEON, me, -1);
    perf = hitresult[2] * 100 / pen;
   
    me_text = "You fumble with your " + short() + ", barely hitting " +
        QTNAME(enemy) + ".\n";
    target_text = " fumbles with " + HIS_HER(me) + " " + short() +
        ", barely hitting you.\n";
    watch_text = "fumbles with " + HIS_HER(me) + " " + short() +
        ", barely hitting " + QTNAME(enemy) + ".\n";
    if (perf > 15)
    {
        me_text = "You make a bold attempt to strike " + QTNAME(enemy) +
            " with your " + short() + ", but only manage a glancing blow.\n";
        target_text = " makes a bold attempt to strike you with his " +
            short() + ", but only manages a glancing blow.\n";
        watch_text = " makes a bold attempt to strike " + QTNAME(enemy) +
            " with his " + short() + ", but only manages a glancing blow.\n";
    }
    if (perf > 30)
    {
        me_text = "You study " + QTNAME(enemy) + " momentarily, then " +
            "suddenly strike out with your " + short() + ", smashing at " +
            "their unguarded flank.\n";
        target_text = " studies you momentarily, then suddenly strikes out " +
            "with " + HIS_HER(me) + " " + short() + ", smashing past your " +
            "guard with a heavy blow.\n";
        watch_text = " studies " + QTNAME(enemy) + " momentarily, then " +
            "suddenly strikes out with " + HIS_HER(me) + " " + short() + 
            ", smashing past their guard to strike their unprotected " +
            "flank.\n";
    }
    if (perf > 45)
    {
        me_text = "With dizzying speed, you spin your " + short() +
            " overhead, then bring it down on " + QTNAME(enemy) +
            " in a thunderous blow!\n";
        target_text = " spins " + HIS_HER(me) + " " + short() +
            " overhead with dizzying speed, then brings it down on you " +
            "in a thunderous blow!\n";
        watch_text = " spins " + HIS_HER(me) + " " + short() + " overhead " +
            "with dizzying speed, then brings it down on " + QTNAME(enemy) +
            " in a thunderous blow!\n";
    }
    if (perf > 60)
    {
        me_text = "Your enemy is completely caught off guard as bring your " +
            short() + " around in a crushing blow!\n";
        target_text = " catches you off guard, bringing " + HIS_HER(me) + " " +
            short() + " around in a crushing blow!\n";
        watch_text = " catches " + QTNAME(enemy) + " off guard, bringing " +
            HIS_HER(me) + " " + short() + " around in a crushing blow!\n";
    }
    if (perf > 75)
    {
        me_text = "Bringing your " + short() + " up in a savage upswing, " +
            "you pummel " + QTNAME(enemy) + " with a deadly blow!\n";
        target_text = " brings " + HIS_HER(me) + " " + short() + " up in a " +
            "savage upswing, pummeling you with a deadly blow!\n";
        watch_text = " brings " + HIS_HER(me) + " " + short() + " up in a " +
            "savage upswing, pummeling" + QTNAME(enemy) + " with a " +
            "deadly blow!\n";
    }
    
    if (enemy->query_hp() <= 0)
    {
        me->catch_msg(QCTNAME(enemy) + " convulses violently as you smash " +
            HIM_HER(enemy) + " in the head with your " + short() + "!\n" +
            capitalize(HE_SHE(enemy)) + " collapses to the ground, " +
            "crushed into a bloody pulp.\n");
        enemy->catch_msg("You start to shudder and convulse violently as " +
            QTNAME(me) + " smashes your head with " + HIS_HER(me) + " " +
            short() + "!\nYou lose consciousness and pass into death " +
            "as your head is crushed into a bloody pulp.\n");
        me->tell_watcher(QCTNAME(enemy) + " convulses violently as " +
            QTNAME(me) + " smashes " + HIM_HER(enemy) + " in the head with " +
            HIS_HER(me) + " " + short() + "!\n" + QCTNAME(enemy) +
            " collapses to the ground, their head crushed into a bloody " +
            "pulp.\n");
	
        enemy->do_die(me);
        return 0;
    }
    
    me->catch_msg(me_text);
    enemy->catch_msg(QCTNAME(me) + target_text);
    me->tell_watcher(QCTNAME(me) + watch_text,({me,enemy}));
    
    }
    return 1; /* Try hit */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}
