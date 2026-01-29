// infidel-slayer        /d/Avenir/common/obj/falcata.c
// creator(s):           Lilith, Aug 2001
// based upon:           /d/Genesis/genesis/doc/examples/weapons/elf_slayer
// purpose:              To be wielded by undead army on the Necronisi
// note:                 This is a magical infidel-slaying sword.
//                       It is most effective against enemies of Sybarus,
//                       namely, ogres, dark elves, and infidels.
//                       It is cloned by the wights on the Isle of the dead.
//            Drawbacks: Wielder cannot be > 50% intoxicated, thus player
//                       health regens more slowly.
//         Requirements: It checks for STR, DIS & SWORD; has intox limits. 
//                       These checks are bypassed for UNDEAD, for whom
//                       the sword has a particular affinty.
//                       Takes 50 fatigue when wielded.
//                       It cannot be wielded by Enemies of Sybarus.
//              Effects: MAGIC_DT against Infidels. Checks for resistance to 
//                       element DEATH.
//     Associated files: /d/Avenir/common/city/obj/wep/intox_shadow.c
//                       To monitor use of alcohol.
/*
 * Revisions:
 * 	Lilith, Oct 2004: Added likely break etc
 * 	Lucius, Aug 2017: Removed ENEMY checks.
 *  Lilith, Sep 2021: Updated intox ck to 50% of max intox
 *  Lilith, Feb 2022: Made a magic enhancer level 46. ok'd by Arman.
 *                    Added prop for npcs to bypass wield tests.
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#include "/d/Avenir/include/macros.h"
#include "/d/Avenir/include/deities.h"
#include "/d/Avenir/include/relation.h"


#define TP		    this_player()
#define CLONE_LOG	"/d/Avenir/log/misc/falcata"
#define SHADOW		"/d/Avenir/common/city/obj/wep/intox_shadow"
#define OK_NPC      "_i_am_npc_falcata_wielder"
object  sword_shadow;

/* 
 *  Long desc of the sword
 */
string 
my_long()
{
    return "It is the faint greenish-yellow glow of the "+
           "recurved blade of this sword that first draws "+
           "the eye to it. "+
           "Forward-curved and widened, rather than "+
           "tapering, at the tip, the weight is in the "+
           "upper third of the blade, where most of the impact "+
           "occurs. "+
           "A double fuller runs separately "+
           "from the hilt, joining the blade approximately "+ 
           "three quarters of the way down. The forward-sloping "+
           "convex causes the flesh of the target to pull "+
           "the blade inward, making for a deeper, deadlier cut. "+
           "The hilt is made of bronze, and cast as an elf "+
           "with its hands around the neck of an ogre, thus "+
           "enclosing the grip. "+ 
           "This sword is noticeably without pommel or guard, "+
           "additions that would simply detract from the elegant "+
           "functionality of this weapon.  It is intended to be "+
           "a blade-heavy weapon, and thus there are no pinions "+
           "or other additions to act as a counter-balance. "+
           "\n   There is an illusory grace to the falcata at rest, "+ 
           "but in action it is a cleaver, separating spirit from "+
           "flesh with sinister economy.\n";
}

void
create_weapon()
{
    set_name("sword");
    add_name(({ "falcata", "falcatta" }));
    set_adj(({"ogre-slaying","infidel-slaying","recurved","sybarun"}));
    set_short("sybarun falcata");
    set_long(my_long);
    // only one magical avenirian sword wielded at a time.
    set_default_weapon(50, 42, W_SWORD, W_SLASH | W_IMPALE, W_LEFT);
    set_wf(this_object());
    set_magic_spellpower(46);
 
    /* Designate this as a magic weapon */
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    /* Allow for identification of the magical properties */
    add_prop(MAGIC_AM_ID_INFO, ({ 
      "The sword seems magically enchanted.\n", 10,
      "It causes extra damage to Enemies of Sybarus.\n", 20,
	  "It also acts as a magic enhancer.\n", 30 }));

    /* Indicate the level and type of magic */
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));

    /* Let wizards know what the sword does */
    add_prop(OBJ_S_WIZINFO, "This sword will do MAGIC_DT to  "+
        "Infidels, ogres, dark-elves, and the like. Wielder must "+
		"have high enough STR, DIS, and SWORD, as well as 50 fatigue. "+
		"The player cannot be >50% intoxicated or an Enemy of Sybarus "+
		"in order to wield.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 42) + 1000);

    // Lets try to combat extended uptimes.
    // Lilith Oct 2004
    set_likely_break(2);
    set_likely_dull(3);
    set_likely_corr(4);    

    add_item(({"hilt", "bronze hilt", "elf", "ogre head"}),
           "The hilt is made of bronze, and cast as an elf "+
           "with its hands around the neck of an ogre, thus "+
           "enclosing the grip. The shoulder and knees of the "+
           "elf's body are designed to provide "+
           "excellent purchase for the fingers on otherwise "+
           "slippery-smooth metal.\n");

    add_item(({"fuller", "double fuller" }),
           "A double fuller runs separately "+
           "from the hilt, joining the blade approximately "+ 
           "three quarters of the way down.\n");

    seteuid(getuid(this_object()));
    SCROLLING_LOG(CLONE_LOG, " falcata was cloned.");

}

/*
 * did_hit() is called whenever the weapon is used.  We redefine it
 * to do extra damage when we hit an ogre, dark elf or infidel.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    string Name = QCTNAME(wielder);
    string name = QTNAME(wielder);
    string names = LANG_POSS(name);
    string enem = QTNAME(enemy);
    string his = wielder->query_possessive();
    string sword = short();
    int resistance;

    /* did_hit() is called even when the weapon misses, so we need
     * to check if phurt < 0 before we do any special damage.  If
     * phurt < 0, then it was a missed attack.
     */
    if (phurt < 0)
    {
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    /* We only want to do the special damage if the target is 
     * infidel, ogre, or dark elf, 1 in 5 attacks.
     */

    if ((enemy->query_race() == "ogre" || 
         enemy->query_race() == "dark elf" ||
         IS_INFIDEL(enemy)) && !random(5))

    {
        wielder->catch_msg("Your "+ sword +" "+
            "twists in your hand. It glows a sickly greenish-yellow "+
            "as it penetrates deep into "+ enem +"'s flesh.\n"); 
        enemy->catch_msg(Name +"'s "+ sword +" glows a sickly greenish-"+
            "yellow as it penetrates your flesh.\n");
        wielder->tell_watcher(Name +"'s "+ sword +" glows a sickly greenish-"+
            "yellow as it penetrates "+ enem +"'s flesh.\n", enemy);

        /* Check the target's magic resistance */
        resistance = spell_resist_basic(this_object(), enemy, 
            SS_ELEMENT_DEATH, TASK_DIFFICULT);

        /* Do the extra damage, taking the magic resistance into account */
        enemy->hit_me(200 * (100 - resistance) / 100, MAGIC_DT,
            wielder, -1);

        /* Kill the target, if appropriate */
        if (enemy->query_hp() <= 0)
        {
            wielder->catch_msg("You quench your "+ sword +" "+
                "in "+ enem +"'s flesh.\n"); 
            enemy->catch_msg(Name +" quenches "+ his +" "+ sword +
                "your flesh, feeding it with your spirit.\n");
            wielder->tell_watcher(Name +" quenches "+ his +" "+ sword +
                "in "+ enem +"'s flesh.\n", enemy);
            enemy->do_die(wielder);
        }
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
    
/*
 * Function     : wield
 * Description  : Wield a weapon
 * Arguments    : Object what - The weapon to wield
 * Returns      : string - error message (weapon not wielded)
 *                1 - success (weapon wielded)
 */
mixed 
wield(object what)
{
    int go, tox_max;

    /* Is it broken? If so, dont wield */
    if (query_prop(OBJ_I_BROKEN))
        return "It is broken in such a way that you cannot wield it.\n";

    if (this_player()->query_prop(OK_NPC))
		return 1;
	
    /* I'm an infidel/enemy of Sybarus, the sword doesn't like me,
       because the sword is made to kill people like me. */
    if (IS_INFIDEL(this_player()))
    {
        this_player()->heal_hp(-50);
        return "The "+ short() +" twists out of your grasp and "+
               "lands on your foot, causing you great pain.\n";
    }

    /* Does player have more than 50% alcohol level? If so, don't wield */  
    tox_max = TP->intoxicated_max() / 2;	
    if (TP->query_intoxicated() > (tox_max) && 
	    (!TP->query_prop(I_DRANK_WITH_SYBARUN_GOD)))
        return "You are too intoxicated to wield the "+
               "blade-heavy "+ short() +". You might "+
               "hurt yourself with it.\n";

    /* Lets set some stat and skill requirements to wield */
    go = TP->query_stat(SS_STR) / 3;          /* Mortal: 100/3 = 33 */
    go += TP->query_skill(SS_WEP_SWORD) / 3;  /* Mortal: 100/3 = 33 */
    go += TP->query_stat(SS_DIS) / 3;         /* Mortal: 100/3 = 33 */
                                              /* random(100) < 50 fails */
    if ((random(go) < 50) && (!TP->query_prop(LIVE_I_UNDEAD)))
    {
        TP->add_fatigue(-20);    
        return "You try to wield the "+ short() +", but its weight "+
               "is too much strain on your wrist.\n";
    }

    /* If undead the requirements are bypassed */
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        TP->catch_tell("You feel an affinity toward the "+ 
            short() +".\n");
    }
        
    /* All checks have passed, proceed with wielding */
    TP->add_fatigue(-50);
    TP->catch_tell("You grip the "+ short() +" and balance the "+
       "weight of its blade with the strength of your wrist.\n");
    say(QCTNAME(TP)+" grips the "+ short() +".\n");

    SCROLLING_LOG(CLONE_LOG, capitalize(TP->query_real_name()) +
            " wielded a falcata.");

    (sword_shadow = clone_object(SHADOW))->shadow_me(TP);
    sword_shadow->set_sword(this_object());

    return 1;
}

/* 
 * Function    : unwield
 * Description : Unwield a weapon
 * Arguments   : object wep - the weapon to unwield
 */
mixed 
unwield(object wep)
{
    sword_shadow->remove_shadow();
    return 0;
}

void appraise_object(int num)
{
   ::appraise_object(num);
   write(item_spellpower_desc());
}
 
string stat_object() 
{
     return ::stat_object() + stat_object_spellpower();
}

 