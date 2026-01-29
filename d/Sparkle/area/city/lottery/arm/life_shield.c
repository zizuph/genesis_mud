/*
 * Shield of Life
 *
 * This shield is a strong shield, with a one-time use magical property.
 * If worn by an individual who takes a death blow, the shield will
 * immediately break. Upon breaking, however, it will restore a certain
 * amount of health back to the user, keeping them from death. This
 * shield cannot be repaired.
 *
 * Idea by Varian, December 2012
 * Created by Petros, December 2012
 */

#include "../defs.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public int      m_bHasBeenBroken = 0;

/*
 * Function name: create_armour
 * Description  : In order to create an armour, you should redefine this
 *                function. Typically you use this function to set the
 *                name and description, the armour type, the armour class
 *                etcetera.
 */
public void
create_armour()
{
    set_name("shield");
    add_adj("light");
    set_adj("mithral");
    set_short("light mithral shield"); 
    set_long("As you inspect the mithril shield closely, you are "
        + "amazed by the fine craftsmanship and detail. A thin layer of "
        + "delicately etched mithril covers the solid, but lightweight, "
        + "wooden base of the shield. The etchings which have been "
        + "carved into the mithril facing are actually faintly glowing "
        + "dwarven runes which recite ancient prayers of healing. A "
        + "mithril gauntlet, which seems to be just about the exact size "
        + "of your right hand, has been fused onto the back of the "
        + "shield.\n");
    set_am(({0,0,0}));
    set_ac(40);
    set_at(A_SHIELD);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC,({15, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({
        "This " + short() + " is enchanted. ", 20,
        "This shield appears to be possessed by a strong life energy of its own. ", 40,
        "The dwarven runes will trigger and transfer its life energy to the "
          + "owner to save them from a potential death. ", 60 }));
    add_prop(OBJ_S_WIZINFO,"This shield discharges itself to prevent death "
        + "once. After that, the shield breaks and cannot be repaired.\n");
    set_wf(this_object());
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40, A_SHIELD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40 + random(5)));
    set_keep(1);
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    object wearer;
       
    setuid(); 
    seteuid(getuid());
    wearer = environment(obj);
    if (living(wearer))
    {
        // This shield can only be worn on the right hand.
        mapping tool_map = wearer->query_tool_map();
        object held_in_right_hand;
        if (objectp(held_in_right_hand = tool_map[W_RIGHT])
            && held_in_right_hand != this_object())
        {
            return "There is just no way that you can fit your left "
                + "hand into the gauntlet. It seems you will have "
                + "to wear this " + short() + " on your right hand.\n";
        }
        
        if (!m_bHasBeenBroken)
        {
            // Clone Life Saving Shadow
            object life_sh = clone_object(LOTTERY_ARM_DIR + "life_shield_sh");
            life_sh->initialize_life_shield_shadow(this_object());
            life_sh->shadow_me(wearer);
            if (!wearer->is_life_shield_shadow())
            {
                return "For some reason, you are unable to wear this " + short() + ".\n";
            }
            
            wearer->catch_tell("As your hand slips into the gauntlet, you "
                + "feel a slight jab of pain as the mithril fuses to your "
                + "skin. Suddenly, a protective warmth begins to flow up "
                + "your arm and into your body.\n");
        }
        else
        {
            // This shield has been repaired. But repaired shield cannot exert
            // the same power again.
            wearer->catch_tell("As you wear this " + short() + " you feel that the "
                + "runes on the dwarves shield briefly pulse, but settle back into "
                + "lifelessness.\n");
        }
    }

    return 0;
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public mixed
remove(object obj)
{
    object wearer;
    
    wearer = query_worn();
    if (objectp(wearer))
    {
        // Remove the shadow
        wearer->remove_life_shield_shadow();
    }
    
    return 0;
}

/*
 * Function name: query_shield_slots
 * Description:   Give a bodypart protected by a shield or magic armour
 */
public int *
query_shield_slots()
{
    return (::query_shield_slots() );
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
public varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    ::got_hit(hid, ph, att, dt, dam);
    
    object wearer = query_worn();
    mixed hitloc = wearer->query_combat_object()->query_hitloc(hid);
    string defender_message = "As " + QTPNAME(att) + " attack "
        + "strikes the shield near your " + hitloc[2] + ", a surge of "
        + "energy rushes into your body from the light mithtril shield and "
        + "heals you.\n";
    string attacker_message = "As you strike " + QTNAME(wearer)
        + ", you see the blue runes on " + wearer->query_possessive()
        + " " + short() + " pulse with a mystic energy.\n";
    string onlooker_message = "As " + QTPNAME(att) + " attack "
        + "strikes " + QTNAME(wearer) + ", the blue runes on "
        + QTPNAME(wearer) + " " + short() + " pulse with a mystic "
        + "energy.\n";
    
    if (random(1000) == 999) // 0.1% chance
    {
        wearer->catch_msg(defender_message);
        att->catch_msg(attacker_message);
        wearer->tell_watcher(onlooker_message, att, ({ att, wearer }));
        wearer->heal_hp(50);
    }
}

/*
 * Function name: remove_broken
 * Description  : The armour got broken so we remove it from the
 *                player.
 * Arguments    : int silent - true if no message should be generated
 *                             about the fact that the armour breaks.
 */
public varargs void 
remove_broken(int silent = 0)
{
    m_bHasBeenBroken = 1;
    ::remove_broken(silent);
}


/*
 * Function name: query_recover
 * Description  : Makes sure that the broken string has been 
 *                added.
 */
public string
query_recover()
{
    string base_recover = ::query_recover();
    return base_recover + "#LSHIELD#" + m_bHasBeenBroken;
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called to set
 *                the necessary variables. If you redefine the function,
 *                you must add a call to init_arm_recover or a call to
 *                ::init_recover with the string that you got after querying
 *                query_arm_recover.
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    string base;
    int    broken;

    sscanf(arg, "%s#LSHIELD#%d", base, broken);
    if (broken != 0)
    {
        m_bHasBeenBroken = broken;
    }    
    ::init_recover(base);
}
