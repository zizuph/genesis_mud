/*
 * metaballo.c
 *
 * Metaballo (Convert Weapon) spell for the Spirit Circle of Psuchae
 * This will give the player a new club weapon out of their target
 * weapon with 95% of the hit and pen of the original.
 *
 * Copyright (C): Jaacar, August 4th, 2003 
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Changes, Bishop. July 2004.
 *
 * Spell Redone in the late fall of 2006 by Navarre
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

#define METABALLO_LOG "spirit_circle/metaballo_log"

string
query_spell_level()
{
    return "Master";
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (caster == 0)
    {
        set_spell_name("metaballo");
        set_spell_desc("Convert Weapon");
        set_spell_target(spell_target_one_present_object);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(8);
        set_spell_mana(175);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - caster->query_stat(SS_OCCUP));
        set_spell_element(SS_ELEMENT_SPIRIT, 60);
        set_spell_form(SS_FORM_CONJURATION, 35);
        set_spell_ingredients(({"_metaballo_component_", "_leftover_thighbone"}));
        set_spell_peaceful(0);
        set_spell_stationary(1);
        set_spell_resist(spell_resist_identify);
        set_spell_object(SPIRIT_SPELLS + "metaballo_obj");
    }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts while " +
                               "intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts while " +
                               "you are not good aligned.\n");
            return 1;
        }
        if (objectp(present("_metaballo_weapon_", caster)))
        {
            caster->catch_tell("You already have such a weapon!\n");
            return 1;
        }
        if (!targets[0]->check_weapon())
        {
            caster->catch_tell("You can only use this gift on a weapon.\n");
            return 1;
        }
        if (!present(targets[0],caster))
        {
            caster->catch_tell("You can only use this gift on a weapon you "+
                               "are carrying.\n");
            return 1;
        }
        if (!targets[0]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
        {
            caster->catch_tell("Metaballo only works on magical weapons!\n");
            return 1;
        }
        if (targets[0]->query_broken())
        {
            caster->catch_tell("You cannot use this gift on a broken " +
                               "weapon.\n");
            return 1;
        }    
    }
    return 0;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You summon the energies of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int stat, weapon_goodness;
    object weapon;
    object tar = targets[0];
    stat = caster->query_stat(SS_WIS) + caster->query_stat(SS_OCCUP) +
           random(200);
    weapon_goodness = tar->query_hit() + tar->query_pen() +
                      MIN(40, tar->query_value()/100);
    setuid();
    seteuid(getuid());
    weapon = make_spell_effect_object(query_spell_object(), caster, caster, 
                                      resist, result);
    if (tar->query_hands() == W_BOTH)
    {
        weapon->set_twoh();
    }
    if (stat > 400 && weapon_goodness > 110)
    {
       weapon->configure_weapon(3);
    }
    else if (stat > 250 && weapon_goodness > 90)
    {
        weapon->configure_weapon(2);
    }
    else
    {
       weapon->configure_weapon(1);
    }
    weapon->move(caster, 1);
    caster->catch_msg("As you complete the spell, you hold your " + 
                      tar->query_short() +" up high, praying that " +
                      "Psuchae will see fit to transform it into a " +
                      "weapon you can use to combat the soulless. " +
                      "Shadows blossom from your outstretched hand, " +
                      "and as they withdraw again, you are holding a " +
                      weapon->short() + "!\n" +
                      " Use <wepdispel> if you wish to be rid of it.\n");
    tell_room(environment(caster), "As " + QTNAME(caster) + " completes " + 
              caster->query_possessive() + " spell, " + 
              caster->query_pronoun() + " holds a " + tar->query_short() +
              " up in the air. Shadows blossom from " +
              caster->query_possessive() + " outstretched" +
              " hand, engulfing the weapon. The shadows withdraw, " +
              "leaving a " + weapon->short() + ".\n", caster);
    tar->remove_object();
} 
