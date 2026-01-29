/*
 *  /d/Faerun/std/drow_npc
 *
 *  Standard drow
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <options.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit FAERUN_STD + "faerun_npc";
inherit FAERUN_LIB + "spellcasting";

int drow_levitating;

/*
 * Function name: drow_setup
 * Description  : set up routines for drow
 */
void drow_setup()
{
    drow_levitating = 0;
    set_race_name("drow");
    add_name("elf");

    // Default casting chance
    set_cast_chance(50);

    // Add some default skills
    set_skill(SS_SPELLCRAFT, 80);
    set_skill(SS_ELEMENT_AIR, 80);
    set_skill(SS_FORM_CONJURATION, 80);
    set_skill(SS_ELEMENT_WATER, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 65);

    // Default properties
    add_prop(LIVE_I_SEE_DARK, 50);

    // All drow's can levitate
    add_spell(P_FAERUN_SPELLS + "drow_levitate");
    setup_spellcasting();
}

/*
 * Function name: using_missile_weapon
 * Description  : See if we are using a missile weapon
 * Returns      : 0 if we are not, 1 if we are
 */
int using_missile_weapon()
{
    object *obs;

    // Find all weapons and filter them for launch weapons
    obs = this_object()->query_weapon(-1);
    obs = filter(obs, &operator(==)("/std/launch_weapon") @ 
        &function_exists("create_weapon"));

    // See if we have any weapons left
    return (sizeof(obs) > 0);
}

/*
 * Function name: special_attack
 * Description  : Special attack that will do the spellcasting and the
 *              : ability to levitate
 * Arguments    : ob - the target of our attacks
 */
int special_attack(object ob)
{
    // Cast spells
    if(special_attack_spellcast(ob))
        return 1;
    
    // If we are levitating, and we didnt cast a spell, see if we use
    // a missile weapon, then allow the round to continue, otherwise
    // fail.
    if(drow_levitating && !using_missile_weapon())
        return 1;

    // Just continue with the round
    return 0;
}

/*
 * Function name: query_not_attack_me
 * Description  : If we are levitating, make all attacks but missile
 *              : attacks and spells fail
 * Returns      : true if we are supposed to miss
 */
int query_not_attack_me(object who, int aid)
{
    object  ob;
    string  attacking_with;

    // Dont do anything if we are not levitating
    if(!drow_levitating)
        return ::query_not_attack_me(who, aid);
    
    // Find the weapon we are attacking with
    ob = who->query_weapon(aid);

    // See if it is a missile weapon
    if(objectp(ob) && (function_exists("create_weapon", ob) == 
        "/std/launch_weapon"))
        return 0;

    // Find our weapon
    attacking_with = who->query_combat_object()->cb_attack_desc(aid);

    // Write our messages
    who->tell_watcher_miss(QCTNAME(who) + " aims at " + QTNAME(this_object()) +
        " with " + who->query_possessive() + " " + attacking_with + " but " +
        " cannot reach " + this_object()->query_objective() + ".\n", 
        ({ who, this_object() }) );
    if(!who->query_option(OPT_GAG_MISSES))
        who->catch_msg("You aim at " + QTNAME(this_object()) + " with your " +
        attacking_with + " but cannot reach " + 
        this_object()->query_objective() + ".\n");

    // Fail
    return 1;
}

/*
 * Function name: query_option
 * Description  : Return the option for unarmed combat, if we are leviting
 *              : we do not want to use unarmed
 */
int query_option(int opt)
{
    // We never use unarmed when we are levitating
    if((opt == OPT_UNARMED_OFF) && drow_levitating)
        return 1;

    // Return the original
    return ::query_option(opt);
}

/*
 * Function name: query_cast_chance
 * Description  : How often do we cast, modified so that levitation will 
 *              : give a 100% chance of casting, unless they wield a bow
 *              : then dont alter it.
 * Returns      : a percentage
 */
int query_cast_chance()
{
    // Always return 100% chance if we are levitating and not using a 
    // missile weapon.
    if(drow_levitating && !using_missile_weapon())
        return 100;

    // Return our normal cast chance
    return ::query_cast_chance();
}

/*
 * Function name: set_drow_levitating
 * Description  : Called from the levitate spell, it will make the drow 
 *              : levitate, dodging everything but spell attacks
 * Arguments    : levitate - levitate or not
 */
void set_drow_levitating(int levitate)
{
    drow_levitating = levitate;
}

/*
 * Function name: query_drow_levitating
 * Description  : See if we are levitating or not
 * Returns      : 0 if we are not levitating, 1 if we are
 */
int query_drow_levitating()
{
    return drow_levitating;
}

/*
 * Function name: spellcast_check
 * Description  : Called from the special_attack_spellcast function, allows
 *              : us to disable some spells
 * Arguments    : name - the name of the spell
 * Returns      : 0 when not using, 1 when using the spell
 */
int spellcast_check(string name)
{
    // If we are levitating, do not allow levitate again
    if((name == "levitate") && drow_levitating)
        return 0;

    // Allow the rest of the spells
    return 1;
}

/*
 * Function name: do_die
 * Description  : Called when the drow bites the dust, we write a messgae
 *              : that he drops to the ground if he's levitating
 */
void do_die(object killer)
{
    if(drow_levitating)
    {
        tell_room(environment(this_object()),
            "The lifeless body of " + QTNAME(this_object()) + " drops " +
            "back to the ground.\n");
    }

    ::do_die(killer);
}