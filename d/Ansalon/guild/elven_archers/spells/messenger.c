/* This spell is based off /d/Genesis/newmagic/spells/darkvision.c
 *
 * A basic summoning spell. It clones a messenger bird for the summoners
 * use to send messages to other players.
 *
 * Arman Kharas 01/07/2003
 */


#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/elven_archers/guild.h"
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You raise your hands to the sky and begin "+
        "whispering elven words of magic.\n");
    tell_room(environment(caster), QCTNAME(caster) + 
        " raises " +HIS(caster)+ " hands to the sky and begins "+
        "whispering in elven.\n", caster);

}

public void
create_spell()
{
    set_spell_name("summon-falcon");
    set_spell_desc("Summon a winged messenger to you");
    set_spell_time(6);
    set_spell_mana(50);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);

    set_spell_target(spell_target_caster);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
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
    object target = targets[0];
    object falcon;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }

    if (E(caster)->query_prop(ROOM_I_INSIDE))
    {
        caster->catch_tell("Being indoors, no bird of prey responds to " +
           "your call.\n");
        return;
    }


    caster->catch_tell("From the heavens you hear the shrill cry " +
        "of a bird of prey, answering your summons. \nThe noble "+
        "form of a peregrine falcon swoops from the skies, landing "+
        "gracefully on your outstretched arm.\n");
    tell_room(environment(caster), "From the heavens you hear the shrill "+
        "cry of a bird of prey, answering " +QTNAME(caster)+ "'s " +
        "summons. \nThe noble form of a peregrine falcon suddenly swoops " +
        "from the skies, landing gracefully on " +QTNAME(caster)+ "'s "+
        "outstretched arm.\n", caster);

    falcon = clone_object(GUILD_DIR + "falcon");
    falcon->set_owner(caster);
    falcon->move(caster);

}
