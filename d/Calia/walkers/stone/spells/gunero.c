
 /*
  * Gunero (Moonshine) Spell for the Stonewalkers Guild
  * by Jaacar
  * November 7th, 1998
  */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "defs.h"
#include STONE_HEADER

public void gunero(object caster, object *targets, int *resist, int result);
public int create_spell_gunero(object caster, string argument, object *targets);

public object *
gunero_target_one_present_living(object caster, string str)
{
    object *oblist;

    if (!present("_nero_potion_object_",caster))
    {
        write("You are not under the effects of the nero "+
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
create_spell_gunero(object caster, string argument, object *targets)
{
    set_spell_time(1);
    set_spell_mana(28);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_EARTH,30);
    set_spell_form(SS_PRAYER,30);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object(GUNERO_OB);
    return 0;
}

public void
gunero(object caster, object *targets, int *resist, int result)
{
    object decanter;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You successfully cast the Gunero spell, but "+
            "it seems to have no effect.\n");
        return;
    }

    if (caster == targets[0])
    {
        write("You pray upon the powers of Lady Gu to grant you "+
            "the magical decanter of gunero.  A sparkling crystal "+
            "decanter appears in your hands.\n");
        tell_room(environment(caster),QCTNAME(caster) + " concentrates "+
            "intensely for a moment.\n",({caster}));
        seteuid(getuid());
        decanter = clone_object(GUNERO_OB);
        decanter->move(TP,1);
    }
    else
    {
        caster->catch_msg("Your eyes flash as you incant the arcane words of "+
            "Gunero and concentrate on the image of "+QTNAME(targets[0])+".\n");
        tell_room(environment(caster),QCTNAME(caster)+"'s eyes flash as "+
            C_HE+" stares intensely at "+QTNAME(targets[0])+".\n",({ caster, targets[0]}));
        targets[0]->catch_msg(caster->query_The_name(targets[0])+ " mumbles "+
            "some strange words and stares intensely at you.  Suddenly a sparkling "+
            "crystal decanter appears in your hands.\n");
        seteuid(getuid());
        decanter = clone_object(GUNERO_OB);
        decanter->move(targets[0],1);
    }
}
