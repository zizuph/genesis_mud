
/*
 * Summoria (Peace) Spell for the Stonewalkers of Thalassia
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
#include "defs.h"
#include STONE_HEADER

public void summoria(object caster, object *targets, int *resist, int result);
public int create_spell_summoria(object caster, object *targets, string argument);

public object *
summoria_target_caster(object caster, string str)
{
    if (!present("_summoria_potion_object_",caster))
    {
        write("You are not under the effects of the summoria "+
            "potion!\n");
        return ({});
    }
    return ({ caster });
}

public void
create_spell_summoria(object caster, object *targets, string argument)
{
    set_spell_time(1);
    set_spell_mana(46); 
    set_spell_task(TASK_SIMPLE + 50);
    set_spell_element(SS_ELEMENT_EARTH, 30);  
    set_spell_form(SS_PRAYER, 30);           
    set_spell_ingredients(({ })); // Uses a potion 
    set_spell_resist(spell_resist_beneficial);                   
    return 0;
}

public void
summoria(object caster, object *targets, int *resist, int result)
{
    object *obarr, *elist;
    int i, count;

    obarr = all_inventory(environment(caster));
    count = 0;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You successfully cast the Summoria spell, but "+
            "it seems to have no effect.\n");
        return;
    }

    for (i = 0; i < sizeof(obarr); i++)
    {
        if (!function_exists("query_enemy", obarr[i]))
            continue;
        elist = obarr[i]->query_enemy(-1);
        if (!sizeof(elist))
            continue;
        obarr[i]->stop_fight(elist);
        count++;
    }
    if (!count)
    {
        write("There is no use for the Summoria spell here.\n");
        return;
    }
    write("Correctly reciting the words of the Summoria spell you calm the "+
        "hearts of all who surround you.\n");
    tell_room(environment(caster), QCTNAME(caster) + " speaks aloud an "+
        "ancient mantra and calms the hearts of all around "+C_HIM+".\n",caster);
}
