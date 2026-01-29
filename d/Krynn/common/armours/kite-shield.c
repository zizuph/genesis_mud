/* kite-shield.c
 *
 * This shield provides more protection for mounted warriors, but
 * when used while fighting on foor, it may slam the enemy, hurting him.
 *
 * Blizzard, 7-06-2003
 *
 * Cotillion, 2004-10-13
 * - Fixed ::got_hit call.
 * - Removed leg protection (shields are too good)
 */

/*
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * It has slowly been raised over the years to become better for specific people
 * as well as having the AC raised. That is not acceptable.
 *
 * - There used to be a check in the code that gives leg protection if the wearer 
 *   belongs to a small race. Goblins were conveniently left out, which makes no sense. 
 *   The leg protection has been removed by Cotillion.
 *   The shield was still offering additional protection for hobbit, dwarf and gnome on 
 *   the head, but again, not goblins. I have removed this special check, and let the
 *   shield give that head and body protection for everyone.
 *
 * - The shield gave 47 Ac to dwarves and hobbits, I have removed that.
 *   Shields are too good, so I have lowered the AC from 39 to 30, and removed the Extra
 *   AC for the races that got special treatment.
 *
 * - I left the special feature of mounted people get additional ac from it, since
 *   kite shields are known to be used by riders.
 *   The extra AC for riders are set to 5.
 *
 * - The damage the shield gives was dependant on strength a lone. I added it to depend on
 *   dexterity as well.
 *
 * - Fixed a few typos. Bracing instead of Barcing. 
 * Louie Jan 2006 - Changed from MAGIC_DT to BLUDGEON
 *
 * -- Added special check to make sure the hit_me returns an array.
 *    I got runtime errors in my log files for it not being an array.
 *    It shouldn't happen, but since the logs showed otherwise I added this special case.
 *    -- Navarre October 2006
 *
 * Navarre Feb 2007, removed A_HEAD slot. Changed to use /sys/formulas.h for weight.
 *
 * Navarre August 2008, added A_LEGS, as our project with changing shields globally failed, and was addressed by a change to the combat system instead.
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

int      ready_to_bash  = 1;   // States if we can bash or not. 
int      subloc_present = 0;   // We do not have a subloc at start
object   wearer;
string   *sublocs;

#define  AR_CLASS      35
#define  MOUNTED_AC    40
#define  SUBLOC        "wearing_shield_subloc"

public void
create_armour()
{
    set_name("shield");
    add_name("kite-shield");
    add_name("_special_kite_shield_");
    set_adj("kite");
    add_adj("blackened");
    set_short("blackened kite-shield");
    set_ac(AR_CLASS);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("@@long_desc@@");

    add_item(({ "plates", "steel plates" }),
        "The steel conical plates, that have their tips directed " +
        "towards the boss of the shield. are to increase its durability. " +
        "They have dark, or rather blackened colour.\n");
    add_item(({ "straps", "strap" }),
        "The main large strap is used for slinging the shield when " +
        "marching over long distances or when fighting with a two " +
        "handed weapon. The two smaller straps are for the shield arm " +
        "when using single-handed weapons like swords.\n"); 
    add_item(({ "large strap", "main strap", "long strap" }),
        "The shield has a long strap across the diagonal of the shield " +
        "which allows the shield to be slung upside-down over the " +
        "warrior's back so it does not get it the way if he is carrying " +
        "it in peacetime.\n");
    add_item(({ "edge", "edges", "binding", "binds" }),
        "The binding is nailed in place around the shield to hold the " +
        "planks of wood that make up the shield together.\n");
    add_item( "boss",
        "Used to guard the handgrip of shield, the boss is a metal dish " +
        "riveted over a hole inside which the shield-hand sits.\n");
        
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_WEIGHT,  F_WEIGHT_DEFAULT_ARMOUR(30, A_SHIELD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) + random(500));
    
    set_af(TO);
    set_keep(1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "This kite shield seems to be magically enchanted.", 10,
            "It is more suitable for protecting a mounted warrior, but it is " +
            "also useful while fighting on foot.", 40,
            "This shield may be used not only for protection, but also for " +
            "bashing your enemies.\n", 70 }) );
    add_prop(OBJ_S_WIZINFO, "This shield is more suitable for protecting " +
        "a mounted warrior and that is why such will receive additional " +
        "AC (it is 40 for mounted warriors). However, those who wear the " +
        "shield while fighting on foot may use it for bashing their " +
        "opponents.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }) );
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_STEAL, VBFC_ME("subloc_check") );
}

public string
long_desc()
{
    if ( TP->query_skill(SS_MOUNTED_COMBAT) > 10 )
    {
        return "This kite shield is approximately four feet long and has " +
            "about thirty inches at the round top, tapering to a rounded " +
            "point at the bottom. It was made of the solid oaken wood, " +
            "reinforced by a few steel plates. It has two straps for the " +
            "wearer's arm to go through. This is helpful especially for a " +
            "mounted warrior, so he can hold both of the horse's reins in " +
            "his left hand while keeping the shield hugged in tight and " +
            "braced against the left leg, while his right arm is busy with " +
            "a sword or javelin. The edge of the shield is carefully bound. " +
            "This binding is nailed in place around the shield to hold the " +
            "planks of wood that make it up together. It provides a " +
            "non-splintered, padded edge that would not cut into the leg " +
            "of the cantering knight, or slap against the flanks of his " +
            "steed and spur into an unexpected gallop. The shield is also " +
            "useful while fighting on foot as it covers quite a big part of " +
            "the wearer's body. There is a long strap across the diagonal of " +
            "the shield.\n";
    }
    else
    {
        return "This kite shield is approximately four feet long and has " +
            "about thirty inches at the round top, tapering to a rounded " +
            "point at the bottom. It was made of the solid oaken wood, " +
            "reinforced by a few steel plates and reaches nearly from the " +
            "chin to the toe of the user. It must be fastened to the " +
            "forearm and the shield hand must firmly grip it at all times. " +
            "The edge of the shield is carefully bound. This binding is " +
            "nailed in place around the shield to hold the planks of wood " +
            "that make it up together. There is a long strap across the " +
            "diagonal of the shield.\n"; 
    }
}

/* Function name: subloc_check
 * Description  : Check if the player has the shield slung over the back
 * Returns      : 1     - if it slung
 */
public string
subloc_check()
{
    if ( subloc_present )
        return "You can not steal the " + short() + ", while it is slung " +
            "over someone's back.\n";
}

public void
ready_again()
{
    ready_to_bash = 1;   
}

public int
query_ready()
{
    return ready_to_bash;
}

public int
got_hit(int hid, int phurt, object attacker, int dt, int dam)
{
    int      penet, time;
    string   str;
    mixed    hitres;

    ::got_hit(hid, phurt, attacker, dt, dam);
    
    wearer = TO->query_worn();
    
    /* Works only if we dodge the attack */
    if ( dt != 0 )
        return 0;
        
    /* And if the enemy aims for our body or left arm */        
    if ( hid != A_BODY && hid != A_L_ARM && hid != A_LEGS)
        return 0;

    /* Not ready yet */
    if ( ready_to_bash == 0 )
        return 0;
        
    /* The special will not work while the wearer is mounted... */
    if ( wearer->query_steed() )
        return 0;
        
    /* ...but it will not work if the attacker is mounted, either. */   
    if ( attacker->query_steed() )
        return 0;
      
    penet  = 100 + (wearer->query_stat(SS_STR) + wearer->query_stat(SS_DEX))/2;
    hitres = attacker->hit_me(penet, W_BLUDGEON, wearer, -1);
    
    if(typeof(hitres) != T_ARRAY)
    {
      return 0;
    }
    if (hitres[0] < 0)
        hitres[0] = 0;
    
    switch ( hitres[0] )
    {
    case 0..5:
        str = "weakly";
        break;
    case 6..50:
        str = "hard";
        break;
    default:
        str = "powerfully";
        break;
    }
    
    wearer->catch_msg("As " + QTNAME(attacker) + " catches you off " +
        "guard and prepares for the attack, you raise your " + short() + 
        " and slam it " + str + " into " + HIS(attacker) +
        " body, sending " + HIM(attacker) + " staggering backwards.\n");
    attacker->catch_msg("You catch " + QTNAME(wearer) + " off guard " +
        "and prepare to take adventage of that, but suddenly " + 
        HE(wearer) + " raises " + HIS(wearer) + " " + short() +
        " and slams it " + str + " into your body, sending you " +
        "staggering backwards.\n");
    wearer->tell_watcher("As " + QTNAME(attacker) + " catches " +
        QTNAME(wearer) + " off guard and prepares for the attack, " +
        HE(wearer) + " raises " + HIS(wearer) + " " + short() +
        " and slams it " + str + " into the body of " + 
        QTNAME(attacker) + ", sending " + HIM(attacker) + 
        " staggering backwards.\n", attacker);
            
    if ( attacker->query_hp() <= 0 )
    {
        wearer->catch_msg(QCTNAME(attacker) + " collapses to the ground.\n");
        attacker->catch_msg("You collapse to the ground.\n");
        wearer->tell_watcher(QCTNAME(attacker) + " collapses to the " +
            "ground.\n");
                
        attacker->do_die(wearer);
    }
            
    ready_to_bash = 0;
    time = 35 + random(10);
    
    set_alarm(itof(time), 0.0, &ready_again());
            
    return 1;    

}

public int
query_ac(int hid)
{
    /* Let's check if the wearer is still mounted. */
    if ( wearer->query_steed() )
    {
        set_ac(MOUNTED_AC);
        wearer->update_armour(TO);

        return ::query_ac();
    }
    else
        return ::query_ac();       
}

public mixed
wear(object ob)
{
    object shield, *armours = ({ });
    int    i, size;
        
    wearer = TP;

    armours = wearer->query_armour(-1);
    
    if ( sizeof(armours) )
    {
        size = sizeof(armours);
        
        for ( i = 0; i < size; i++)
        {
            shield = armours[i];
           
            /* The player can wear _only_ one such shield at a time. */   
            if ( shield->id("_special_kite_shield_") )
                return "You can wear only one " + short() + " at a time.\n";
        }
    }    
        
    if ( subloc_present )
    {
        wearer->remove_subloc(SUBLOC, TO);
        subloc_present = 0;
        
        if ( wearer->query_steed() )
        {
            wearer->catch_msg("You remove the " + short() + 
                " from your back and wear on your shoulder, " +
                "bracing it against your leg.\n");
            say(QCTNAME(TP) + " removes the " + short() + 
                " from " + HIS(wearer) + " back and wears on " +
                HIS(wearer) + " shoulder, bracing it " +
                "against " + HIS(wearer) + " leg.\n");
        
            set_ac(MOUNTED_AC);
            wearer->update_armour(TO);
        
            return 1;
        }

        wearer->catch_msg("You remove the " + short() + " from your back " +
            "and fasten it to your forearm.\n");
        say(QCTNAME(wearer) + " removes the " + short() + " from " +
            HIS(wearer) + " back and fastens it to " + HIS(wearer) + 
            " forearm.\n");
        return 1;
    }
         
    if ( wearer->query_steed() )
    {
        wearer->catch_msg("You wear the " + short() + ", bracing it " +
            "against your leg.\n");
        say(QCTNAME(TP) + " wears the " + short() + ", bracing it " +
            "against " + HIS(TP) + " leg.\n");
        
        set_ac(MOUNTED_AC);
        wearer->update_armour(TO);
        
        return 1;
    }
    
    return 0;
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    
    if ( carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) )
        return "";
    
    if ( for_obj == carrier )
        str = "You carry the " + short() + " slung upside-down over " +
            "your back.\n";
    else
        str = capitalize(PRONOUN(carrier)) + " carries the " + short() +
            " slung upside-down over " + HIS(carrier) + " back.\n";
    
    return str;
}

public mixed
remove(object ob)
{
    set_this_player(query_worn());
    
    set_ac(AR_CLASS);
    query_worn()->update_armour(TO);
 
    TP->add_subloc(SUBLOC, TO);
    subloc_present = 1;
    
    if ( TP->query_npc() )
        return 0;
        
    wearer->catch_msg("You remove the " + short() + " and sling " +
        "it upside-down over your back.\n");
    say(QCTNAME(TP) + " removes the " + short() + " and slings " +
        "it upside-down over " + HIS(TP) + " back.\n");

    return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    sublocs = from->query_sublocs();
    
    if ( member_array(SUBLOC, sublocs) == -1 )
        return;
        
    if ( interactive(from) && subloc_present )
    {
        from->remove_subloc(SUBLOC, TO);
        subloc_present = 0;
 
        wearer->catch_msg("You remove the " + short() + " from your back.\n");
        say(QCTNAME(from) + " removes the " + short() + " from " +
            HIS(from) + " back.\n");
 
        return;
    }
 
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }));
}

