/*
 * File : flame_glaive.c
 *
 * The lethal flame-bladed glaive is wielded by boss NPCs over Krynn.
 * Its stat may change, depending on the wielder's skill. It also has 
 * a powerful special that may stun the enemy. It may be wielded only
 * by tall races.
 *
 * Blizzard, 26.06.2003
 * Modified by Louie 2005-07- removing paralyze unless wielded by
 * an NPC.
 *
 * Navarre, August 31st 2006, removing small/tall race restriction. 
 * Carnak, June 6th 2017, allowed for hoopak conversion. 
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

#define  BASE_HIT     37
#define  BASE_PEN     43

object   wielder;

create_weapon()
{
    set_name(({"polearm", "glaive"}));
    set_short("lethal flame-bladed glaive");
    set_adj( ({"lethal", "flame-bladed" }) );
    set_long("This lightweight weapon consists of a long, broad knife-like " +
        "blade attached to a staff, made of some dark unrecognizable " +
        "wood. The wavy blade is edged on the convex side for slashing " +
        "and pointed at the tip for thrusts. It is also backed with " +
        "two smaller, claw-like blades, which are crooked towards the " +
        "grip. As you look at this strange weapon, it reminds you of a " +
        "flame, where the staff is an extension of the longest, central " +
        "flame-tongue. The glaive radiates an aura of intense power, " +
        "and may be lethal in the hands of a skilled fighter.\n");

    set_hit(BASE_HIT);
    set_pen(BASE_PEN);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);
    set_keep(1);

    /* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
    
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(OBJ_S_WIZINFO, "This is quite strage and powerful weapon. It " +
        "may be wielded only by a skilled person (SS_WEP_POLEARM >= 30); " +
        "if the skill is higher than 55, hit and pen will be slightly " +
        "increased; if the skill is higher than 85 it will be increased " +
        "even more (by maximum value 10). The glaive has also a special " +
        "which - if hits the arms, adds attack_delay to the enemy, but if " +
        "it hits the legs - makes him unable to move for a short time " +
        "(5 + random(5) seconds)).\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "This glaive can not be wielded by unskilled people and those who " +
        "know how to use it, will benefit from it.\n", 30,
        "The more skilled the wielder is, the more lethal, in his hands, the " +
        "glaive is.\n", 50,
        "If you manage to cut your opponent's legs or arms, he may find " +
        "it difficult to continue the fight against you.\n", 75 }) );
        
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, 2000 + random(300));
}

public mixed
wield(object ob)
{
    int    skill_bonus;
    string how;

    wielder = TP;
    
    if ( wielder->query_skill(SS_WEP_POLEARM) >= 55 )
    {
        skill_bonus = ( wielder->query_skill(SS_WEP_POLEARM) / 10 );

        if ( wielder->query_skill(SS_WEP_POLEARM) > 85 )
        {
            set_hit(BASE_HIT + skill_bonus);
            set_pen(BASE_PEN + skill_bonus);
            wielder->update_weapon(TO);
            how = "skillfully";
        }
        else
        {
            set_hit(BASE_HIT + (skill_bonus / 2));
            set_pen(BASE_PEN + (skill_bonus / 2));
            wielder->update_weapon(TO);
            how = "deftly";
        }
           
        write("You grasp the staff of the " + short() + " in both your " +
            "hands and spin it " + how + ", testing its balance.\n");
        say(QCTNAME(wielder) + " grasps the staff of the " + short() + 
            " in both " + HIS(wielder) + " hands and spins it " + how + 
            ", testing its balance.\n");
            
        return 1;
    }
    
    if ( wielder->query_skill(SS_WEP_POLEARM) < 30 )
    {
        say(QCTNAME(wielder) + " grasps the staff of the " + short() +
            ", but as " + HE(wielder) + " tries to spin it, the weapon " +
            "almost falls out of his hands. " + capitalize(PRONOUN(wielder)) +
            " decides not to use it.\n");
        return "You grasp the staff of the " + short() + " but as you try to " +
            "spin it, the weapon almost falls out of your hands. You decide " +
            "not to use it.\n";
        
    }
    
    return 0;
}
    
public int
unwield(object ob)
{
    set_hit(BASE_HIT);
    set_pen(BASE_PEN);
    
    query_wielded()->update_weapon(TO);
    
    return 0;
}
  
public mixed
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    string what, how;
    int    time, weapon_skill, damage, attacktype;
    object wound, me;
    mixed  hitres;
      
    weapon_skill = wielder->query_skill(SS_WEP_POLEARM);
    me = query_wielded();
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if ( !random(18 - (weapon_skill / 10)) )
    {
        time       = 5 + random(5);
        attacktype = random(6);
        
        switch (attacktype)
        {
            case 0:
                what = "legs";
            break;
            case 1:
                what = "arms";
            break;
            default:
                what = hdesc;
            break;
        }
        
        damage = ((weapon_skill + wielder->query_stat(SS_STR)) / 2 );
        damage += ( wielder->query_prop(LIVE_I_QUICKNESS) > 100 ? 100 :
            wielder->query_prop(LIVE_I_QUICKNESS) );
        damage -= (enemy->query_stat(SS_DEX) / 2);
        
        damage  = ((damage > 0) ? damage : 0 );

        if ( weapon_skill > 80 )
        {
            how = "skillfully";
            damage += 150;
        }
        else
        {
            how = "deftly";
            damage += 75;
        }
  
  /* Damage capped. 2.01.2004 - Blizzard.
   */        
        damage = MIN(450, damage);
        
        wielder->catch_msg("You twirl your " + short() + " " + how + " and " +
            "then lash out, striking the " + what + " of " + QTNAME(enemy) +
            " with a series of quick cuts.\n");
        enemy->catch_msg(QCTNAME(wielder) + " twirls " + HIS(wielder) + " " +
            short() + " " + how + " and then lashes out, striking your " + 
            what + " with a series of quick cuts.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " twirls " + HIS(wielder) + 
            " " + short() + " " + how + " and then lashes out, striking the " +
            what + " of " + QTNAME(enemy) + " with a series of quick cuts.\n",
            enemy);
        
        hitres = enemy->hit_me(damage, W_SLASH, me, -1);
        
        if ( !wielder->query_npc() )
        {                   /* if the player has mana we will drain some... */
            if ( wielder->query_mana() > 6 ) 
                wielder->add_mana(-7);
            else            /* if not, we will make him more tired */
                wielder->add_fatigue(-(wielder->query_max_fatigue() / 12));
        }
        
        if ( enemy->query_hp() <= 0 )
        {
            wielder->catch_msg(QCTNAME(enemy) + " tumbles to the ground.\n");
            enemy->catch_msg("Your " + what + 
                ((what == "body") ? " is" : " are") + " completely numb " +
                "and you tumble to the ground.\n");
            wielder->tell_watcher(QCTNAME(enemy) + " tumbles to the ground.\n",
                enemy);
            enemy->do_die(wielder);

            return 1;
        }

        if ( what == "arms" )
        {
            wielder->catch_msg(QCTNAME(enemy) + " winces in pain.\n");
            enemy->catch_msg("You wince in pain.\n");
            wielder->tell_watcher(QCTNAME(enemy) + " winces in pain.\n", 
                enemy);
            enemy->add_attack_delay(time, 1);  // Add attacked delay...
        }
    
/*
        if ( what == "legs" )            // ...but if we hit the legs, we make
*/
        if ( what == "legs" && wielder->query_npc() )
        {                                // enemy unable to move for a while.
            seteuid(getuid());
            wound = present("Legs_Wound", enemy);

            if ( wound )
            {
                wound->remove_object();
                wound = clone_object(KROBJECT + "legs_wound");
            }
            else
            {
                wound = clone_object(KROBJECT + "legs_wound");
            }
        
            wound->move(enemy, 1);
        }
    
        return 1;
    }

 /* Hit emotes borrowed from bladed silver staff, with slight modifications. */

    switch(phurt)
    {
    case -2:
    case -1:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You spin the " + short() + " around your " +
	      "body, the blade causing a high pitched whine as it " +
	      "cuts a path through the air.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg(QCTNAME(wielder) + " spins the " + short() + 
	      " around " + POSSESSIVE(wielder) + " body, the blade making a " +
	      "high pitched whine as it cuts a path through the " +
	      "air.\n");
	wielder->tell_watcher_miss(QCTNAME(wielder) + " spins the " + short() + 
	  " around " + POSSESSIVE(wielder) + " body, the blade making a " +
	  "high pitched whine as it cuts a path through " +
	  "the air.\n", enemy);
	break;

    case 0:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You narrowly miss the " + hdesc + " of " + 
	      QTNAME(enemy) + " as you swing your " + short() + 
	      " around your body.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg("You narrowly avoid the blade of the " + 
	      short() + " as "+ QTNAME(wielder) + " swings it " +
	      "at your " + hdesc + ".\n");
	wielder->tell_watcher_miss(QCTNAME(wielder) + " narrowly misses the " + 
	  hdesc + " of " + QTNAME(enemy) + " with " + POSSESSIVE(wielder) +
	  " " + short() + ".\n", enemy);
	break;

    case 1..5:
	wielder->catch_msg("You spin your " + short() + " in a deadly arc, " +
	  "tearing a shallow wound into the " + hdesc + " of " + 
	  QTNAME(enemy) + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " spins " + HIS(wielder) + " " +
	  short() + " in a deadly arc, tearing a shallow wound into your " +
	  hdesc + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " spins " + HIS(wielder) + 
	  " " + short() + " in a deadly arc, tearing a shallow wound into " +
	  "the " + hdesc + " of " + QTNAME(enemy) + ".\n", enemy);
	break;

    case 6..10:
	wielder->catch_msg("Twirling your " + short() + " about your body, " +
	  "you suddenly bring it down in a vicious stroke, " +
	  "striking the " + hdesc + " of " + QTNAME(enemy) +
	  " painfully.\n");
	enemy->catch_msg("Twirling " + POSSESSIVE(wielder) + " " + short() +
	  " about " + POSSESSIVE(wielder) + " body, " + QTNAME(wielder) +
	  " suddenly brings it down upon your "+ hdesc + " painfully.\n");
	wielder->tell_watcher("Twirling " + POSSESSIVE(wielder) + " " + 
	  short() + " about " + POSSESSIVE(wielder)+ " body, " + 
	  QTNAME(wielder) + " suddenly brings it down in a vicious stroke, " +
	  "striking the " + hdesc + " of " + QTNAME(enemy) + " painfully.\n",
	  enemy);
	break;

    case 11..19:
	wielder->catch_msg("You lash out unexpectedly at " + QTNAME(enemy) +
	  ", driving a blade deep into " + POSSESSIVE(enemy) + " " +
	  hdesc + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " lashes out unexpectedly at you "+
	  "with " + POSSESSIVE(wielder) + " " + short() + ", driving a " +
	  "blade deep into your " + hdesc + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " lashes out unexpectedly at " +
	  QTNAME(enemy) + " with " + POSSESSIVE(wielder) + " " + short() +
	  ", driving a blade deep into " + QTNAME(enemy) + "'s " +
	  hdesc + ".\n", enemy);
	break;

    case 20..29:
	wielder->catch_msg("You swing the " + short() + " towards " + 
	  QTNAME(enemy) + ", slashing deeply into " + POSSESSIVE(enemy) + 
	  " " + hdesc + ".\n");
	enemy->catch_msg(QCTNAME(wielder) + " swings the " + short() + 
	  " towards you with deadly accuracy, slashing deeply into your " +
	  hdesc + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " swings the " + short() + 
	  " towards " + QTNAME(enemy) + " with deadly accuracy, slashing " +
	  "deeply into " + POSSESSIVE(enemy) + " " + hdesc + ".\n",enemy);
	break;

    case 30..49:
	wielder->catch_msg(QCTNAME(enemy) + " staggers as you bring the " +
	  short() + " crashing down upon " + POSSESSIVE(enemy) + " " + hdesc +
	  ".\n");
	enemy->catch_msg("You stagger as " + QTNAME(wielder) + " brings the "+
	  short() + " crashing down upon your " + hdesc + ".\n");
	wielder->tell_watcher(QCTNAME(enemy) + " staggers as " + 
	  QTNAME(wielder) + " brings the " + short() + " crashing down upon " +
	  POSSESSIVE(enemy) + " " + hdesc + ".\n", enemy);
	break;

    case 50..75:
	wielder->catch_msg("With perfect timing, you twirl the " + short() +
	  " around your head, cutting to the bone the " +
	  hdesc + " of " + QTNAME(enemy) + " on the downstroke.\n");
	enemy->catch_msg(QCTNAME(wielder) + " twirls the " + short() + 
	  " around " + POSSESSIVE(wielder) + " head, cutting all the way to " +
	  "the bone of your " + hdesc + " on the downstroke.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " twirls the bladed staff " +
	  "around " + POSSESSIVE(wielder) + " head, bringing it down upon " +
	  "the " + hdesc + " of " + QTNAME(enemy) + " with perfect timing, " +
	  "and cutting to the bone.\n", enemy);
	break;

    case 76..99:
	wielder->catch_msg("Spinning your " + short() + " around you, you "+
	  "lunge at " + QTNAME(enemy) + " tearing into " +
	  POSSESSIVE(enemy) + " " + hdesc + " with the blade, then " +
	  "suddenly twirl, bringing it around " +
	  "in a wide arch, nearly slicing clean through " +
	  POSSESSIVE(enemy) + " " + hdesc + ".\n");
	enemy->catch_msg(QTNAME(wielder) + " lunged at you, tearing into " +
	  "your " + hdesc + " with the blades, then suddenly " +
	  PRONOUN(wielder) + " twirls, bringing it " +
	  "around in a wide arch, and nearly slicing clean " +
	  "through your " + hdesc + ".\n");
	wielder->tell_watcher(QCTNAME(wielder) + " lunges at " + 
	  QTNAME(enemy) + " tearing into " + POSSESSIVE(enemy) + " " + hdesc + 
	  " with one blade. " + capitalize(PRONOUN(wielder)) + 
	  " then suddenly twirls, bringing the other blade around in a " +
	  "wide arch, and nearly slicing through the " + hdesc + " of " +
	  HIS(wielder) + " enemy.\n", enemy);
	break;

    default:
	wielder->catch_msg("You feel victory upon you. Slowly twirling, you " +
	  "spin blade after blade into " + QTNAME(enemy) + "'s " +
	  "shattered body. Your macabre dance of death " +
	  "ends, and with a final spin you slice into " +
	  POSSESSIVE(enemy) + " exposed neck.\n");
	enemy->catch_msg(QCTNAME(wielder) + " begins to slowly twirl, and " +
	  "blade after blade slices into you in this macabre " +
	  "dance of death. With a last spin, the blade tears " +
	  "through your neck, leaving you stunned, as your " +
	  "lifeblood drains from you.\n");
	wielder->tell_watcher(QCTNAME(wielder) + " begins to slowly twirl " +
	  "in a horrific but beautiful dance of death, sending " +
	  "blade after blade " +
	  "of the " + short() + " tearing into " + QTNAME(enemy) +
	  "'s body. With a final spin, the blade slashes " +
	  "through " + POSSESSIVE(enemy) + " throat, and " +
	  PRONOUN(enemy) + " stands there stunned, as the " +
	  "remaining blood pours from " + POSSESSIVE(enemy) +
	  " many wounds.\n", enemy);
	break;

    }

    return 1;

    
}

