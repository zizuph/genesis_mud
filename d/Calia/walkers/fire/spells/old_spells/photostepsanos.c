
 /*
   * Photostepsanos (Fire Aura) Spell for the Firewalkers
   * by Jaacar
   * April 28th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void photostepsanos(object caster, object *targets, int *resist, 
    int result);
public int create_spell_photostepsanos(object caster, object *targets, 
    string argument);

public object *
photostepsanos_target_one_present_living(object caster, string str)
{
    object *oblist;

    if (!present("_photostepsanos_potion_object_",caster))
    {
        write("You are not under the effects of the photostepsanos "+
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

public int
create_spell_photostepsanos(object caster, object *targets, string argument)
{
    set_spell_time(1);
    set_spell_mana(150);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE,50);
    set_spell_form(SS_PRAYER,50);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(photostepsanos);
    set_spell_object(PHOTOSTEPSANOS_OB);
    set_spell_peaceful(1);
    return 0;
}

public void
photostepsanos(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to have "+
            "no effect.\n");
        return;
    }

    if (targets[0] == caster)
    {
        write("Slowly, flames surround you, burning "+
            "your mortal flesh away from your body, but leaving you "+
            "in no pain at all.  As you feel the flames pass your "+
            "eyes, you put your hand in front of your face, but "+
            "do not see anything.  You are invisible!\n");
        tell_room(environment(caster),"Flames surround "+
            QNAME(caster)+", slowly burning the flesh from "+
            C_HIS+" body until there is no trace left that "+
            C_HE+" was even here.\n",({ caster }));
        caster->add_prop(LIVE_I_SEE_INVIS,
            (int)caster->query_prop(LIVE_I_SEE_INVIS) + 1);
        make_spell_effect_object(query_spell_object(), caster, caster,
            resist, result);
    }
    else
    {
        if (caster->query_mana() < 150)
        {
            write("You do not have enough mana!\n");
            return;
        }
        caster->catch_tell("Reaching out, you touch "+targets[0]->query_the_name(caster)+
            " on the shoulder.  Flames surround "+TS_HIM+", slowly "+
            "burning the flesh away from "+TS_HIM+" until there is "+
            "no trace left of "+TS_HIM+".\n");
        targets[0]->catch_tell(caster->query_The_name(targets[0])+" reaches out and "+
            "touches your shoulder.  Flames suddenly appear at your "+
            "feet and begin to slowly burn the flesh from your body.  You "+
            "notice that you are not in pain as this is happening.  As you "+
            "feel the flames pass your eyes, you raise your hand to "+
            "look at the damage this fire has caused and realize you "+
            "can no longer see it.  You are invisible!\n");
        tell_room(environment(caster),QCTNAME(caster)+" reaches out "+
            "and touches "+QNAME(targets[0])+" on the shoulder.  "+
            "Flames erupt at "+QNAME(targets[0])+"'s feet, slowly "+
            "burning "+TS_HIM+" until there is no trace left that "+
            TS_HE+" was here.\n",({ caster, targets[0] }));
        targets[0]->add_prop(LIVE_I_SEE_INVIS,
            (int)targets[0]->query_prop(LIVE_I_SEE_INVIS) + 1);
        caster->add_mana(-150);  // Extra 150 mana for target not being caster
        make_spell_effect_object(query_spell_object(), caster, targets[0],
            resist, result);
    }
}
