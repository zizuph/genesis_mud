/*

Lampas spell for the Firewalkers. Coded by Bishop, June 21st, 1999.

*/

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

public void lampas(object caster, object *targets, int *resist,
    int result);
public int create_spell_lampas(object caster, object *targets,
    string argument);

public object *
lampas_target_all_present_livings(object caster, string str)
{
    object *oblist;
    int i;

    oblist = FILTER_LIVE(all_inventory(environment(caster)));
    i = 0;

    oblist -= ({caster});

    while (i < sizeof(oblist))
    {
        if (oblist[i]->query_wiz_level() || 
            present("_lampas_obj_", oblist[i]))
        {
            oblist -= ({oblist[i]});
        }
        else
        {
            i++;
        }
    }

    if (!sizeof(oblist))
    {
        oblist += ({caster});
    }

    return oblist;
}


public void
create_spell_lampas(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(150);
    set_spell_task(TASK_ROUTINE + 100);
    set_spell_element(SS_ELEMENT_FIRE, 70);
    set_spell_form(SS_FORM_CONJURATION, 70);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(lampas);
    set_spell_object(LAMPAS_OBJ);
    return 0;
}

public void
lampas(object caster, object *targets, int *resist, int result)
{
    int i;

    i = 0;

    caster->catch_msg("You complete the spell, and raise your hands over" +
        " your head. Suddenly a flash of intense light issues forth, filling" +
        " the area. You remain unaffected, though.\n");
    tell_room(environment(caster), QCTNAME(caster) + " completes the spell" +
        " and raises " + caster->query_possessive() + " hands over " +
        caster->query_possessive() + " head. Suddenly an intense, blinding" +
        " flash of light issues forth, filling the area and making" +
        " everything go white!\n", caster); 


    while (i < sizeof(targets))
    {
        if (random(100) < resist[i])
        {
            targets[i]->catch_msg("You are unaffected by the burst of" +
                " light.\n");
            targets -= ({targets[i]});
        }
        else
        if (targets[i] == caster)
        {
            targets -= ({targets[i]});
        }
        else
        {
            targets[i]->catch_msg("The burst of light sends you reeling," +
                " blinded and unable to act!\n");            
            i++;
        }
    }

    for (i = 0 ; i < sizeof(targets) ; i++)
    {
        make_spell_effect_object(query_spell_object(), caster, targets[i], 
            resist, result)->move(targets[i]);
    }
}