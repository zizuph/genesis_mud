
 /*
   * Anatome (Resist Earth) Spell for the Stonewalkers
   * by Jaacar
   * November 7th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include STONE_HEADER

public void anatome(object caster, object *targets, int *resist,
    int result);
public int create_spell_anatome(object caster, object *targets,
    string argument);

public int
create_spell_anatome(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(130);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_EARTH,50);
    set_spell_form(SS_PRAYER,50);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(anatome);
    set_spell_object(ANATOME_OB);
    return 0;
}

public object *
anatome_target_one_present_living(object caster, string str)
{
    object *oblist;

    if (!present("_anatome_potion_object_",caster))
    {
        write("You are not under the effects of the anatome "+
            "potion!\n");
        return ({});
    }

    if (!strlen(str))
    {
        return ({ caster });
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == caster->query_real_name()))
	{
	    return ({ caster });
	}

	caster->catch_tell("There is no " + str + " here.\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }
        
    return oblist;
}

public void
anatome(object caster, object *targets, int *resist, int result)
{
    object resob;

    if (targets[0] == caster)
    {
        if (present("_anatome_object_", caster))
        {
            caster->catch_tell("You are already protected!\n");
            return;
        }
    }

    if (present("_anatome_object_", targets[0]))
    {
        caster->catch_tell("They are already protected!\n");
        return;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to "+
            "have no effect.\n");
        return;
    }

    make_spell_effect_object(query_spell_object(), caster, targets[0],
        resist, result)->move(targets[0]);
    
    if (targets[0] == caster)
    {
        write("Your skin glows briefly.  You feel you are "+
            "somehow more resistant to earth magic.\n");
        tell_room(environment(caster), QCTNAME(caster)+"'s skin glows "+
            "briefly for a moment.\n",({caster,targets[0]}));
        seteuid(getuid());
        resob = clone_object("/std/resistance");
        resob->set_res_type(MAGIC_I_RES_EARTH);
        resob->set_strength(45);
        resob->set_time(180);
        resob->move(caster,1);
    }
    else
    {
    targets[0]->catch_tell("Your skin glows briefly.  You feel you "+
        "are somehow more resistance to earth magic.\n");
    tell_room(environment(caster), QCTNAME(targets[0]) +"'s skin glows "+
        "briefly for a moment.\n",({caster, targets[0]}));
    caster->catch_tell("You concentrate on the image of "+targets[0]->query_the_name(caster)+
        " and call upon the powers of Anatome.  "+targets[0]->query_The_name(caster)+
        "'s skin glows briefly for a moment.\n");
    seteuid(getuid());
    resob = clone_object("/std/resistance");
    resob->set_res_type(MAGIC_I_RES_EARTH);
    resob->set_strength(45);
    resob->set_time(180);
    resob->move(targets[0],1);
    }
}
