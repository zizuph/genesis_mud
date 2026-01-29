/*  -*- LPC -*-  */

/*
 * maul.c - Bolg's Maul.
 *
 * This is a giant Maul of Shield and Armour-slaying. It is a
 * black alloyed spiked mace/hammer that strikes as a war
 * mattock, and delivers crush criticals, twice normal concussion
 * hits. (x3 if Bolg wields it two-handed)
 *
 *
 *
 * Note further that since war hammers are not properly
 * captured in Genesis, it was decided that polearm was most
 * appropriate, due to the immense weight and impaling nature
 * of this weapon.  Dunstable, 7/95
 *   Added keepable functionality "/lib/keep"  -Igneous Dec 13th 1996
 *   Made the maul #include "hit_msgs.h" to take care of the hit msgs
 *   -Igneous 1/97
 *   Lowered the stat needed to wield this weapon -Igneous June 11th 97
 *
 *   After looking over the weapon it seemed that it was doing triple damage
 *   In certain occasions. THe header says it does 2X damage so I corrected it.
 *   Igneous June 11th 1997
 *
 *   Fixed a small typo. Toby 2007-04-23
 *   Fixed damage so it actually does x3 as intended (x4 had been happening)
 *     - Gorboth (June 2008)
 * 
 * Navarre October 30th 2010. Added CAN_SEE check to the 'change grip' wielding.
 * You can still wield it in dark rooms, but if the halberd has set_no_show, 
 * and/or set_no_show_composite, it cannot be wielded. Some holsters and 
 * scabbards set that on the weapon to hide it, and the 'special' way to 
 * wield the weapon circumvent setting it back to normal, so it ends up
 * being 'the player is wielding something'.
 *
 * Carnak June 20th 2017.
 * - Made the weapon polearm/club based on skill, requested by Varian.
 *
 * Carnak September 8th 2017.
 * - Added a prop to allow for altering the weapon to a hoopak.
 *
 * Carnak September 13th 2017.
 * - Recoded the weapon, keeping its original stats. This is to clean up
 *   the code and remove a bug ogres experienced when wielding the weapon.
 *   Let us hope the code is more readable from now on.
 */

#include "/d/Shire/moria/wep/defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <options.h>

inherit "/std/weapon";
inherit "/lib/keep";

inherit "/d/Shire/moria/lib/hit_msg";

/* Kender prop, allow alter ability to change the descriptions of the weapon */
#define OBJ_I_CONVERT_HOOPAK "_obj_i_convert_hoopak"

#define LEFT_HAND   ({                                      \
    "left hand", "lefthanded", "left-handed", "left"        \
})
#define RIGHT_HAND  ({                                      \
    "right hand", "righthanded", "right-handed", "right"    \
})
#define ANY_HAND ({                                         \
    "any hand", "whatever hand", "free hand", "one-handed", \
    "any free hand", "any", "one handed", "one hand", "one" \
})
#define BOTH_HANDS ({                                       \
    "both hands", "using both hands", "both", "two-handed", \
    "twohanded"                                             \
})

#ifdef DROP_LOG
/*
 * Function name: log_drop
 * Description:   Logs when the NPC Ashburz drops the item.
 * Returns:       (int) 0 finished logging
 */
int
log_drop()
{
    if (TP->query_real_name() == "ashburz" && TP->query_hp() != 0)
    {
        setuid();
        seteuid(getuid());
        write_file(DROP_LOG, ctime(time()) + " " + TP->query_name() +
        " drops " + HIS_HER(TP) + " " + short() + " with " +
        COMPOSITE_WORDS(FILTER_PLAYERS(INV(ENV(TP)))->query_name()) +
        " present.\n");
    }
    
    return 0;
} /* log_drop */
#endif

/*
 * Function name: create_weapon
 * Description  : Create the launch_weapon. As this function is declared
 *                nomask you must use the function launch_create_weapon 
 *                to actually construct it. This function does some basic
 *                initializing.
 */
void
create_weapon()
{
    set_name("maul");
    add_name("mace");
    add_name("hammer");
    add_name("_bolgs_maul");
    set_adj(({"giant", "alloy", "spiked", "bolg's", "black"}));

    set_short("giant black maul");

    set_long("Ashburz's Maul.\n"
    + "This is a giant black alloy spiked mace/hammer, which belonged to "
    + "Ashburz the Large, Son of Burzuruk, Captain of the Red-Claws of Moria "
    + "and male uruk champion. It is said that Ashburz the Large managed to "
    + "wield the maul in one hand, but it also said that he liked to use it "
    + "two-handed. You might try this trick by changing the grip of this "
    + "weapon.\n");

    set_hit(35);
    set_pen(45);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hands(W_BOTH);
    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);

    set_wf(TO);
    
/* Kender prop, allow alter ability to change the descriptions of the weapon */
    add_prop(OBJ_I_CONVERT_HOOPAK, 1);
    
    add_prop(OBJ_I_VOLUME, 12200);
    add_prop(OBJ_I_WEIGHT, 16600); /* 16.6 kg */
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_BUY, 1);

//  Old logging for the maul drop.
#ifdef DROP_LOG
    add_prop(OBJ_M_NO_DROP, log_drop);
#endif

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({60, "enchantment", 50, "armour-slaying"}));
    add_prop(MAGIC_AM_ID_INFO, ({
        "It is enchanted.\n", 15,
        "This maul has a heavy enchantment of black magic on it.\n", 30,
        "It is very powerful magic indeed, capable of damaging " +
        "the toughest of armours.\n", 50
    }));
      
    add_prop(OBJ_S_WIZINFO, ""
    + "This giant maul is essentially a club or polearm depending on the one "
    + "who wields it, with sharp spikes extending from it. It has been "
    + "enchanted by the Balrog's magic to enable Ashburz, his Uruk Champion to "
    + "defend the Mines from any silly dwarves wanting to reclaim their former "
    + "kingdom.\n");
    
    set_keep();
} /* create_weapons */


/*
 * Function name: query_hands
 * Description  : Find out the hands that we can use for this weapon.
 * Returns      : int - the hands.
 */
int
query_hands()
{
    /* Ensures that the special acts like a two handed for ogres */
    if (this_object()->query_prop("_aod_wield_prop") &&
        calling_function() == "did_hit")
        return W_BOTH;
    
    return ::query_hands();
} /* query_hands */


/*
 * Function name: set_hands
 * Description  : Set how the weapon should be wielded, W_ANYH, W_BOTH, ...
 *                When the lock has been set, no changes are allowed anymore.
 * Arguments    : int which - the hands.
 */
void
set_hands(int which)
{
    /* Ensures the item stays one handed for ogres. */
    if (this_object()->query_prop("_aod_wield_prop") && which != W_ANYH &&
        calling_function() != "leave_inv")
        return;
    
    return ::set_hands(which);
} /* set_hands */


/*
 * Function name: change_to
 * Description:   Handles the actual change of the grip, unwields and rewields
 *                the weapon if already wielded.
 * Returns:       (int)  1 successful
 */
int
change_to(int hands)
{
    mixed res;

    if (query_wielded() && query_hands() != hands)
        unwield_me();

    set_hands(hands);
    res = wield_me();

    if (stringp(res))
        return notify_fail(res);
    
    return 1;
} /* change_to */


/*
 * Function name: do_change
 * Description:   Changes wielded hand requirement for the weapon.
 * Returns:       (int)  1 successful change
 *                (int)  0 failed to change
 */
int
do_change(string hand)
{
    if (member_array(hand, LEFT_HAND) > -1)
        return change_to(W_LEFT);
    else if (member_array(hand, RIGHT_HAND) > -1)
        return change_to(W_RIGHT);
    else if (member_array(hand, ANY_HAND) > -1)
        return change_to(W_ANYH);
    else if (member_array(hand, BOTH_HANDS) > -1)
        return change_to(W_BOTH);
    else
        return 0;
} /* do_change */


/*
 * Function name: test_change
 * Description:   Tests if the do_change function exists in object ob.
 * Returns:       (int)  1 function exists
 *                (int)  0 no such function
 */
int
test_change(object ob)
{
    return stringp(function_exists("do_change", ob));
} /* test_change */


/*
 * Function name: change_grip
 * Description:   Parses the change command to verify success.
 * Returns:       (int)  1 successful parse
 *                (int)  0 failed parse
 */
int
change_grip(string arg)
{
    mixed *obs;
    string handedness;

    notify_fail("Eh? The syntax is: 'change grip on <weapon> to "
    + "<handedness>'\n");
    if (!strlen(arg))
        return 0;

    if (parse_command(arg, all_inventory(this_player()),
                      "[the] [grip] [on] [of] [the] %i [to] [using] [the] %s",
                      obs, handedness) && CAN_SEE(this_player(), this_object()))
    {
      obs = NORMAL_ACCESS(obs, "test_change", this_object());
      
      if (!sizeof(obs))
          return 0;
      
      if (sizeof(obs) > 1)
      {
          notify_fail("Eh? Try one weapon at a time.\n");
          return 0;
      }
      
      return obs[0]->do_change(handedness);
    }

    if (parse_command(arg, ({}), "[the] [grip] [to] [using] [the] %s",
        handedness) && CAN_SEE(this_player(), this_object()))
        return do_change(handedness);
    
    return 0;
} /* change_grip */


/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init()
{
    ::init();
    add_action(change_grip, "change");
} /* init */


/*
 * Function name: query_usable
 * Description:   Check if the wielder is strong enough to wield this weapon.
 * Returns:       (int)  1 success
 *                (int)  0 failure
 */
int
query_usable(object who)
{
    if (who->query_race() == "uruk")
        return 1;
    else if (query_hands() == W_BOTH)
        return (STR(who) > 100);
    else
        return (STR(who) > 140 && DEX(who) > 110);
} /* query_usable */


/*
 * Function name: wield
 * Description:   Wield a weapon
 * Arguments:     The weapon to wield
 * Returns:       string - error message (weapon not wielded)
 *                1 - successs (weapon wielded)
 */
int
wield(object to)
{
    string how;
    object cmbt;

    if (!query_usable(this_player()))
    {
        write("You are not strong enough to wield this weapon.\n");
        return -1;
    }

    switch(query_attack_id())
    {
        case W_BOTH:
        how = "two-handed";
            break;
        case W_LEFT:
        how = "left-handed";
            break;
        case W_RIGHT:
        how = "right-handed";
            break;
    }
    
    write("With a great deal of effort, you manage to wield the " + short()
    + " " + how + ".\n");
    say(QCTNAME(this_player()) + " manages to wield the " + short() + " "
    + how + ".\n");
    
    /* Carnak: Added a check for skills to change to club */
    if ((TP->query_skill(W_CLUB) > TP->query_skill(W_POLEARM)) &&
        TP->query_skill(W_CLUB) > 50)
    {
        write("The " + short() + " rests comfortably in your grip, " +
        "usable as a club in your skillful hands.\n");
        set_wt(W_CLUB);
    }
    else
    {
        /* Redundant set_wt, but always good to be cautious */
        set_wt(W_POLEARM);
    }
    
    /* Updates the combat object, so it uses the correct skill */
    if (objectp(cmbt = this_player()->query_combat_object()))
        cmbt->cb_update_weapon(this_object());
    
    return 1;
} /* wield */


/*
 * Function name: unwield
 * Description  : This function might be called when someone tries to unwield
 *                this weapon. In a launch weapon unwield causes the weapon to
 *                be unloaded as well.
 *
 * Arguments    : object obj - the weapon to stop wielding.
 * Returns      : int  0 - the weapon can be unwielded normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - do not unwield the weapon, print default messages.
 *                string - do not unwield the weapon, use this fail message.
 */
public mixed
unwield(object to)
{
    /* Carnak: Returned the weapon to a polearm */
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    return 0;
} /* unwield */


/*
 * Function name: protects_hid
 * Description:   Checks the object which hid it protects and if the id
 *                is a match.
 * Returns:       (int)  1 armour slot matches id
 *                (int)  0 armour slot does not match
 */
int
protects_hid(object what, int id)
{
    return (member_array(id, what->query_protects()) > -1);
} /* protects_hid */


/*
 * Function name: breakable_armour
 * Description:   Checks the armours likely to break value
 * Returns:       (int)  1 if breakable
 *                (int)  0 if unbreakable
 */
int
breakable_armour(object what)
{
    return (what->query_likely_break() > 0);
} /* breakable_armour */


/*
 * Function name: break_armour
 * Description:   Displays description and handles breaking of items and adding
 *                of armour condition to degrade its state.
 * Returns:       (int)  1 always a success
 */
int
break_armour(object ob)
{
    object  wielder = query_wielded(),
            enemy   = ob->query_worn();
    int     condition;
    
    wielder->catch_msg("Your " + short() + " hits " + QTNAME(enemy) + "'s "
    + QSHORT(ob)+ " with shattering force!\n");
    enemy->catch_msg(QCTNAME(wielder) + "'s " + short() + " hits your "
    + QSHORT(ob) + " with shattering force!\n");
    wielder->tell_watcher(QCTNAME(wielder) + "'s " + short() + " hits "
    + QCTNAME(enemy) + "'s " + QSHORT(ob)+ " with shattering force!\n", enemy);

    if ((wielder->query_race() == "uruk" && !random(5)) || !random(10))
    {
        wielder->tell_watcher(CAP(LANG_THESHORT(ob)) + " breaks into several "
        + "pieces and seems useless.\n");
        ob->remove_broken(1);
        return 1;
    }
    
    condition = (wielder->query_race() == "uruk" ? 6 : random(2) + 1);
    ob->set_condition(ob->query_condition() + condition);
    return 1;
} /* break_armour */


/*
 * Function name: break_random_armour
 * Description:   Selects a random armour protecting the hid slot, the function
 *                switches the difficulty of breaking an item based on enchanted
 *                items.
 * Returns:       (int) -1 means no armour
 *                (int)  0 means failure to break
 *                (int)  1 means broken armour
 */
int
break_random_armour(object enemy, int dam, int hid)
{
    object *arms, ob;
    mixed   magic_arr;
    int     ench;
    
    foreach(object armour: enemy->query_armour(-1))
    {
        if (!pointerp(arms))
            arms = ({});
        
        if (protects_hid(armour, hid) && breakable_armour(armour))
            arms += ({ armour });
    }
    
    if (dam < 100)
        return 0;

    if (!sizeof(arms))
        return -1;
    
    ob = one_of_list(arms);
    
    if (ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        magic_arr = ob->query_prop(MAGIC_AM_MAGIC);

        ench = member_array("enchantment", magic_arr);
        if ((ench >- 1 && random(magic_arr[ench-1]) < dam / 100) ||
            (random(ob->query_ac()) < dam / 20))
            return break_armour(ob);
    }
    else
    {
        if (random(ob->query_ac()) < dam / 5)
            return break_armour(ob);
    }

    return 0;
} /* break_random_armour */


/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat messages
 *                to all relevant parties. If the weapon chooses not to handle
 *                combat messages then a default message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
        int dt, int phit, int dam, int hid)
{
    object  wielder = query_wielded();
    int     break_status;

    if (!dt)
        dt = W_BLUDGEON;

    if (!query_usable(wielder))
    {
        wielder->catch_msg("You fumble and drop your weapon!\n");
        wielder->tell_watcher(QCTNAME(wielder) + " fumbles and drop "
        + HIS_HER(wielder) + " weapon!\n");
        
        wielder->command("$drop _bolgs_maul");
        return 0;
    }

    if (query_hands() == W_BOTH)
    {
        break_status = break_random_armour(enemy, dam, hid);
        
        switch(break_status)
        {
            case 1:
            produce_msg(enemy, hdesc, phurt, dt);
                break;
            
            case -1:
            enemy->heal_hp(-dam * (wielder->query_race() == "uruk" ? 2 : 1));
            phurt += phurt;
            
            default:
            produce_msg(enemy, hdesc, min(phurt, 100), dt);
                break;
        }
    }
    else
    {
        produce_msg(enemy, hdesc, phurt, dt);
    }
    
    return 1;
} /* did_hit */
