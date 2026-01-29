/*
 * pAlign
 */
 
#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "../spells.h"
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 2;
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
    object tp, tar = targets[0];
    int num, a = 1;
    string s;

    if (environment(caster) != environment(tar) || !objectp(tar))
    {
        caster->catch_tell("There is noone to focus your sight on.\n");
        return;
    }

    sscanf(OB_NUM(tar),"%d",num);

    a += (100 - caster->query_skill(SS_APPR_MON)) * 4;
    a = random(2 * a, num) - a;
    a += tar->query_alignment();

    if (a < -750)
        s = "midnight black";
    else if (a < -400)
        s = "black";
    else if (a < -100)
        s = "dark grey";
    else if (a < 100)
        s = "grey";
    else if (a < 400)
        s = "light grey";
    else if (a < 750)
        s = "white";
    else
        s = "pure white";

    caster->catch_tell("You focus your sight above and beyond " +
        tar->query_the_name(caster) + ", and for a short while you can " +
            "faintly detect a " + s + " aura.\n");
    //Milan fixed runtime errors here
    tp = this_player();
    set_this_player(caster);
    all_msgbb(QTNAME(caster) + " seems to look intently at something " +
        "just behind " + QTNAME(tar) + ".\n", caster, tar);
    set_this_player(tp);

    if (caster->check_seen(tar))
        tar->catch_tell(caster->query_The_name(tar) +
            " seems to look intently at something just behind you.\n");

    if (caster->query_npc())
        caster->cast_palign_hook(s, tar);
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
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("palign");
    set_spell_desc("Detect someone's alignment");

    set_spell_time(7);
    set_spell_mana(12);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_basic);
    set_spell_target(spell_target_one_other_present_living);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);
    set_spell_stationary(1);
    set_spell_offensive(0);

    return 0;
}
