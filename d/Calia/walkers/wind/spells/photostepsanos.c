
 /*
   * Photostepsanos (Invisibility) Spell for the Windwalkers
   * by Jaacar
   * April 24th, 1998
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
#include WIND_HEADER

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
    set_spell_element(SS_ELEMENT_AIR,50);
    set_spell_form(SS_PRAYER,50);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(photostepsanos);
    set_spell_object(INVIS_OBJ);
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
        write("Winds suddenly pick up around you, blowing around "+
            "your body swiftly making it impossible to do anything "+
            "except close your eyes and wait for it to pass.  "+
            "As you feel the winds subside, "+
            "you put your hand in front of your face, but "+
            "do not see anything.  You are invisible!\n");
        tell_room(environment(caster),"Winds suddenly pick up around "+
            QNAME(caster)+", quickly making it impossible to see "+
            C_HIM+" through all the debris they have picked up.  When "+
            "the winds die down, "+C_HE+" is gone!\n",({ caster }));
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
            " on the shoulder.  Winds pick up around "+TS_HIM+", quickly "+
            "making it impossible to see "+TS_HIM+" through all the debris "+
            "they have picked up.  When the winds die down, "+TS_HE+" is "+
            "gone!\n");
        targets[0]->catch_tell(caster->query_The_name(targets[0])+" reaches out and "+
            "touches your shoulder.  Winds suddenly pick up around you, "+
            "blowing around your body swiftly making it impossible to do "+
            "anything except close your eyes and wait for it to pass.  "+
            "As you feel the winds subside, you put your hand in front "+
            "of your face, but do not see anything.  You are invisible!\n");
        tell_room(environment(caster),QCTNAME(caster)+" reaches out "+
            "and touches "+QNAME(targets[0])+" on the shoulder.  "+
            "Winds pick up around "+TS_HIM+", quickly "+
            "making it impossible to see "+TS_HIM+" through all the debris "+
            "they have picked up.  When the winds die down, "+TS_HE+"is "+
            "gone!\n",({ caster, targets[0] }));
        targets[0]->add_prop(LIVE_I_SEE_INVIS,
            (int)targets[0]->query_prop(LIVE_I_SEE_INVIS) + 1);
        caster->add_mana(-150);  // Extra 150 mana for target not being caster
        make_spell_effect_object(query_spell_object(), caster, targets[0],
            resist, result);
    }
}
