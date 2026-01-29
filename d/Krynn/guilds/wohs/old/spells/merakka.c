/*
 * Merakka
 *
 * Description: Detect invisible
 * Class:       2
 * Ingredients: garlic, and silver dust
 * Mana:        40 (1/3)
 * Tax:         N/A
 * Skills:      SS_ELEMENT_AIR     3
 *              SS_FORM_DIVINATION 4
 * Task:        TASK_ROUTINE
 * Restriction: Must not be engaged in combat,
 *              the caster must not be gagged and the caster must
 *              have something to cast the spell on.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>
#include <language.h>

#include "../guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("merakka");
    set_spell_desc("See invisible");

    set_spell_element(SS_ELEMENT_AIR, 3);
    set_spell_form(SS_FORM_DIVINATION, 4);

    set_spell_time(4);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(80);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(({ "garlic", "silver dust" }));

    set_spell_peaceful(1);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob;
    object tar = targets[0];
    object *effects = tar->query_magic_effects();
    int size;



    tell_room(E(caster), QCTNAME(caster) + " blows some powder into " +
        "the room, while mumbling a few words.\n", caster);

    caster->catch_msg("You crush the garlic and mix it with the silver powder, " +
        "blow the powder into the while you speak the magic words.\n");

    tar->catch_msg("The shining powder settles around you. Your eyes start to " +
        "relax, and everything in the room gets a translucent feeling,\n");

    ob = make_spell_effect_object(SPELL_OBJ + "merakka", caster, tar, 0,
        result);
    ob->set_spell_duration(240 + (result > 1000 ? 1000 : result) * 2);
}






