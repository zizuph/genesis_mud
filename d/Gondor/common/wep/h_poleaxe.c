/*
 *Rare poleaxe wielded by haradrim
 *Altrus, July 2005
 *
 * Modified by Toby 2006-10-23:
 *    Looked for bug report: 'reveal the name of the person it hits'
 *    and updated the MAGIC_AM_ID_INFO to send a newline last.
 *
 *    2007-03-29, Toby: Fixed a typo
 *    2008-03-19, Gorboth: Added OBJ_AM_MAGIC prop and info.
 *    2008-06-18, Toby: Fixed typo collaspes and reworked the 
 *                      MAGIC_AM_ID_INFO a little.
 *    2008-10-11, Eowul: Removed keep support as OBJ_M_NO_BUY is set.
 *
 * Carnak: September 8th 2017.
 * - Added a prop to allow for altering the weapon to a hoopak.
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

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

void
create_weapon()
{
    set_name("poleaxe");
    add_name("polearm");
    set_short("sleek steel-bladed poleaxe");
    set_pshort("sleek steel-bladed poleaxes");
    set_adj(({"sleek", "steel-bladed"}));
    set_long("The steel blade of this polearm is long, curved, and honed to a razor-edge. It appears to be rivetted securely to a sleek wooden shaft. The shaft is bound with strips of leather to provide a good grip. The leather is old, sweat-stained, but still tightly bound.\n");
    add_prop(OBJ_I_WEIGHT, 3500 + random(1000));
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }) );
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,({"It takes a bit of skill to use this poleaxe to its fullest. ",1,
    "When it is used to its fullest extent it makes deadly hits from time to time. " +
    "Its razor-edge cutting deep into the wielders opponent. ",25,
    "Sometimes the poleaxe might even stun an oponent. ",65,
    "\n",1}));
    set_default_weapon((40 + random(5)), (40 + random(10)), W_POLEARM, W_SLASH | W_IMPALE, W_BOTH, 0);
    set_wf(this_object());
    
/* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
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
        tell_room(ENV(target), QCTNAME(target) + " seems to have recovered " + HIS_HER(target) + " senses.\n", target, target);
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
    skill = me->query_skill(SS_WEP_POLEARM);
    stat = me->query_stat(SS_STR);
    skill_e = enemy->query_skill(SS_PARRY);
    stat_e = enemy->query_stat(SS_DEX);
    
    if(TP->query_skill(SS_WEP_POLEARM) < 50)  //Special hit wont work unless you have the skill
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
                me->catch_msg("Mustering all your strength, you swing the haft of your " + short() + " at " + QTNAME(enemy) + ", whacking " + HIM_HER(enemy) + " soundly on the head.\n" + capitalize(HE_SHE(enemy)) + " looks dazed.\n");

                enemy->catch_msg(QCTNAME(me) + " swings the haft of " + HIS_HER(me) + " " + short() + " at you, hitting you soundly on the head.\nYou feel dazed.\n");

                me->tell_watcher(QCTNAME(me) + " swings the haft of " + HIS_HER(me) + " " + short() + " at " + QTNAME(enemy) + ", whacking " + HIM_HER(enemy) + " soundly on the head.\n" + capitalize(HE_SHE(enemy)) + " looks dazed.\n");

                return 1;
            }
        }
	
    pen = F_PENMOD(40+random(stat/4), skill);
    hitresult = enemy->hit_me(pen, W_SLASH, me, -1);
    perf = hitresult[2] * 100 / pen;
   
    me_text = "You fumble with your " + short() + ", barely hitting " + QTNAME(enemy) + ".\n";
    target_text = " fumbles with " + HIS_HER(me) + " " + short() + ", barely hitting you.\n";
    watch_text = "fumbles with " + HIS_HER(me) + " " + short() + ", barely hitting " + QTNAME(enemy) + ".\n";
    if (perf > 15)
    {
        me_text = "You make a bold attempt to strike " + QTNAME(enemy) + " with your " + short() + ", but only manage a grazing cut.\n";
        target_text = " makes a bold attempt to strike you with his " + short() + ", but only manages a grazing cut.\n";
        watch_text = " makes a bold attempt to strike " + QTNAME(enemy) + " with his " + short() + ", but only manages a grazing cut.\n";
    }
    if (perf > 30)
    {
        me_text = "You study " + QTNAME(enemy) + " momentarily, then suddenly strike out with your " + short() + ", slashing at an unguarded weak point.\n";
        target_text = " studies you momentarily, then suddenly strikes out with " + HIS_HER(me) + " " + short() + ", slashing at an unguarded weak point.\n";
        watch_text = " studies " + QTNAME(enemy) + " momentarily, then suddenly strikes out with " + HIS_HER(me) + " " + short() + ", slashing at an unguarded weak point.\n";
    }
    if (perf > 45)
    {
        me_text = "With dizzying speed, you spin your " + short() + " overhead, then bring it down on " + QTNAME(enemy) + " in a brutal slash!\n";
        target_text = " spins " + HIS_HER(me) + " " + short() + " overhead with dizzying speed, then brings it down on you in a brutal slash!\n";
        watch_text = " spins " + HIS_HER(me) + " " + short() + " overhead with dizzying speed, then brings it down on " + QTNAME(enemy) + " in a brutal slash!\n";
    }
    if (perf > 60)
    {
        me_text = "Your enemy is completely caught off guard as bring your " + short() + " around in a vicious swing, slicing deep!\n";
        target_text = " catches you off guard, bringing " + HIS_HER(me) + " " + short() + " around in a vicious swing, slicing deep into you!\n";
        watch_text = " catches " + QTNAME(enemy) + " off guard, bringing " + HIS_HER(me) + " " + short() + " around in a vicious swing, slicing deep!\n";
    }
    if (perf > 75)
    {
        me_text = "Bringing your " + short() + " up in a savage underswing, you nearly gut " + QTNAME(enemy) + "!\n";
        target_text = " brings " + HIS_HER(me) + " " + short() + " up in a savage underswing, nearly gutting you!\n";
        watch_text = " brings " + HIS_HER(me) + " " + short() + " up in a savage underswing, nearly gutting " + QTNAME(enemy) + "!\n";
    }
    
    if (enemy->query_hp() <= 0)
    {
        me->catch_msg(QCTNAME(enemy) + " convulses violently as you butcher " + HIM_HER(enemy) + " with your " + short() + "!\n" + capitalize(HE_SHE(enemy)) + " collapses to the ground, surrounded by the blood and gore of the slaughter.\n");

        enemy->catch_msg("You start to shudder and convulse violently as " + QTNAME(me) + " butchers you with " + HIS_HER(me) + " " + short() + "!\nYou can feel your blood and entrails as the leave your body, and you know for a certainty that you are going to die.\n");

        me->tell_watcher(QCTNAME(enemy) + " convulses violently as " + QTNAME(me) + " butchers " + HIM_HER(enemy) + " with " + HIS_HER(me) + " " + short() + ".!\n" + QCTNAME(enemy) + " collapses to the ground, surrounded by the blood and gore of the slaughter.\n");
	
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
