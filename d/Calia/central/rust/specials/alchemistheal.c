/* This is the alchemist's heal spell, coded by Bishop 4.1.99
in Calia */

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

public int
create_spell_alchemistheal(object caster, object *targets, 
    string argument)
{
    set_spell_time(1);
    set_spell_mana(80);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 0);
    set_spell_form(SS_FORM_ENCHANTMENT, 0);
    set_spell_ingredients(({ })); // No point in components here.
    set_spell_resist(spell_resist_beneficial);
    return 0;
}

public void
alchemistheal(object caster, int result)
{
    int heal;

    write("You heal yourself with an ancient incantation.\n");
    tell_room(environment(caster), QCTNAME(caster) + " intones" +
        " an ancient incantation, and some of his wounds close.\n",
        caster);
    heal = 300 + random(500);
    caster->heal_hp(heal);
}





