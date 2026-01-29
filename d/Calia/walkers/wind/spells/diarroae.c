
 /*
   * Diarroae (Slow) Spell for the Windwalkers
   * by Jaacar
   * May 22nd, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include WIND_HEADER

public void diarroae(object caster, object *targets, int *resist,
    int result);
public int create_spell_diarroae(object caster, object *targets,
    string argument);

public object *
diarroae_target_one_other_present_living(object caster, string str)
{
    object *oblist;

    if (!present("_diarroae_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "diarroae potion!\n");
        return ({});
    }

    if (!strlen(str))
    {
        caster->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

    if (!sizeof(oblist))
    {
        caster->catch_tell("Whom do you wish to target?\n");
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
create_spell_diarroae(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(130);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR,50);
    set_spell_form(SS_PRAYER,50);
    set_spell_ingredients(({"spotted feather"})); // Uses a potion as well
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(diarroae);
    set_spell_object(DIARROAE_OB);
    return 0;
}

public void
diarroae(object caster, object *targets, int *resist, int result)
{

    if (present("_diarroae_object_", targets[0]))
    {
        caster->catch_tell("They are already slowed!\n");
        return 0;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to "+
            "have no effect.\n");
        return;
    }

    make_spell_effect_object(query_spell_object(), caster, targets[0],
        resist, result)->move(targets[0]);

    caster->catch_tell("You concentrate on the image of "+targets[0]->query_the_name(caster)+
        " and call upon the powers of Diarroae.  "+targets[0]->query_The_name(caster)+
        "'s exposed skin begins to ice over.  The ice slowly works it's way "+
        "into "+TS_HIS+" body, freezing "+TS_HIS+" muscles.\n");    
    targets[0]->catch_tell("Your exposed skin suddenly begins to ice over.  "+
        "The ice slowly works it's way into your body and freezes your "+
        "muscles to the point where you can barely move.\n");
    tell_room(environment(caster), QCTNAME(targets[0]) +"'s exposed skin "+
        "begins to ice over.  The ice slowly works it's way into "+TS_HIS+
        " skin, freezing "+TS_HIS+" muscles.\n",({caster, targets[0]}));

}

