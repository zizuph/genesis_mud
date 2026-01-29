/*
 * pGem
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>  
#include <cmdparse.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 11;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;
    
    set_this_player(caster);
    caster->catch_tell("You begin to intone a prayer to the Queen " +
        "of Darkness.\n");
    all_msgbb(QCTNAME(caster) + " begins to intone a prayer.\n", caster);
    set_this_player(old_tp);
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
    object tar, gem;

    if (!sizeof(targets))
    {
    	caster->catch_tell("No such item present to be transformed by pgem.\n");
    	return;
    }
    tar = targets[0];

    if (!tar)
    {
    	caster->catch_tell("Oops, it seems the object has disappeared!\n");
    	return;
    }

    if (!tar->id("gem"))
    {
    	caster->catch_tell("The object of the transformation must be a " +
    	"gem to start with!\n");
    	return;
    }

    if (tar->query_prop(MAGIC_AM_MAGIC))
    {
    	caster->catch_tell("The gem resists the transformation.\n");
    	return;
    }

    setuid();
    seteuid(getuid());
    gem = clone_object(SOULGEM_OBJ);

    gem->move(E(tar),1);

    if (E(gem) == caster)
    {
        caster->catch_tell("The " + tar->short() + " shines brightly, and " +
            "when the light fades, it has changed to " +
            LANG_ADDART(gem->short()) + ".\n");
        all_msgbb("A bright light shines for a while between " +
    	    QTNAME(caster) + "'s hands.\n", caster);
    }
    else
    {
        tell_room(E(gem),"The " + tar->short() + " shines brightly, and " +
        "when the light fades, it has changed to " +
        LANG_ADDART(gem->short()) + ".\n");
    }

    if (tar->query_prop(HEAP_I_IS))
    {
        tar->set_heap_size(tar->num_heap() - 1);
    }
    else
    {
        tar->remove_object();	
    }
}

public object *
pgem_target(object caster, string str)
{
    object *arr;

    if (!stringp(str))
    {
        caster->catch_tell("You need a target.\n");
        return ({ });
    }
    
    arr = FIND_STR_IN_OBJECT(str, caster);
    if (!sizeof(arr))
    {
        caster->catch_tell("You need a target.\n");
        return ({ });
    }
    
    if (sizeof(arr) >= 2)
    {
        caster->catch_tell("Multiple targets would probably be a bad idea.\n");
        return ({ });
    }
    
    if (!arr[0]->id("gem"))
    {
        caster->catch_tell("The target must be a gem.\n");
        return ({ });
    }

    return arr;
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
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("pgem");
    set_spell_desc("Create a soul gem out of an ordinary gem");

    set_spell_element(SS_ELEMENT_EARTH, 15);
    set_spell_form(SS_FORM_TRANSMUTATION, 35);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_vocal(1);

    set_spell_time(15);
    set_spell_mana(110);

    set_spell_task(TASK_ROUTINE);

    set_spell_target(spell_target_present_objects);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"skullcap","heart"}));
#endif

    return 0;
}
