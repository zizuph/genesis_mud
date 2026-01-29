/*
 * /d/Gondor/guilds/rangers/spells/bless.c
 *
 * Related files:
 *  /d/Gondor/guilds/rangers/spells/spell_inherit.c
 *  /d/Gondor/guilds/rangers/spells/obj/bless_shadow.c
 *
 * Coded by Gwyneth on 10/20/03
 *
 * Description:
 * This spell is for the Rangers of Ithilien, being the combat
 * oriented company. A Ranger of Ithilien may call upon Aule,
 * the Valar smith to strengthen their weapon. It will have a
 * somewhat random effect on the item, that the caster can't
 * control. Some possible effects are:
 * Increased hit and/or pen
 * Glowing blue and doing more damage to orcs/goblins
 * Increased ac
 * Stunning
 * Increased durability
 * Decreased weight
 *
 * All effects will temporarily add the magic property to the
 * weapon. The bless may only be used by the Ranger who cast
 * it. A bless can be cast over it by another Ranger, which
 * will nullify the previous bless.
 *
 * Modification log:
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit SPELL_INHERIT;

/* Global variables */
int Wenya;

/* Function name: resolve spell
 * Description  : This is the "guts" of the spell. Everything worked
 *                and the spell was cast, this function does the spell
 *                effect and finishes the job.
 * Arguments    : caster  - the person who cast the spell
 *                targets - Who the spell was cast on
 *                resist  - How must the targets resisted the spell
 *                success - How well the spell was cast
 */
void
resolve_spell(object caster, object *targets, int *resist, int success)
{
    int power;
    string wdesc;

    if (caster->query_company() != "ithilien")
    {
        caster->catch_tell("You are unable to cast this spell.\n");
        return;
    }

    power = caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_skill(SS_ELEMENT_LIFE) +
        (caster->query_ranger_rank() / 2);

    if (!targets[0]->check_weapon())
    {
        caster->catch_tell("You can only cast this spell on a weapon.\n");
        return;
    }

    wdesc = targets[0]->short();

    if (!Wenya)
    {
        caster->catch_tell("You call upon Aule, the Vala of Smiths, to " +
            "strengthen  your " + wdesc + ".\n");
        tell_room(environment(caster), QCTNAME(caster) + " holds " +
            POSSESSIVE(caster) + " hand above " + wdesc + " while " +
            " mumbling some words in an ancient language.\n", caster);
        power *= 2;
        power /= 3;
    }
    else
    {
        caster->catch_tell("You use the virtues of the wenya potion " +
            "to strengthen your " + wdesc + ".\n");
        tell_room(environment(caster), QCTNAME(caster) + " pours a " +
            "green liquid on " + POSSESSIVE(caster) + " " + wdesc +
            "while mumbling some words in an ancient language.\n", caster);
    }

    setuid();
    seteuid(getuid());
    log_file("bless", ctime(time()) + " " + caster->query_name() + " " +
        "blessed "+ wdesc + ".\n");

    make_spell_effect_object(query_spell_object(), caster, targets,
        resist, success);
}

/*
 * Function name: bless_ingr
 * Description  : Finds the wenya potion for ingredients.
 * Arguments    : object caster - The spellcaster
 * Returns      : the ingredient or TO
 */
mixed
bless_ingr(object caster)
{
    object *list;

    list = get_item_search_list(caster);
    list = filter(list, &operator(==)("wenya potion") @ &->query_potion_name());

    if (!sizeof(list))
    {
        Wenya = 0;
        return ({ this_object() });
    }

    Wenya = 1;
    return ({ list[0] });
}

/* 
 * Function name: config_spell
 * Description  : configures the spell, allowing you to set the
 *                various spell functions tothe values you wish
 *                for the spell.  Used much like the create_*
 *                function for rooms, monsters, objects etc...
 * Arguments    : caster  - person casting the spell
 *                targets - what the spell is cast on
 *                args    - Extra arguments for the spell
 * Returns      : 1 if the configuration didn't work
 *                0 if everything went ok
 */
int
config_spell(object caster, object *targets, string args)
{
    set_spell_name("bless");
    set_spell_desc("Call on Aule to bless a weapon.");
    set_spell_target(spell_target_one_present_non_living);

    if (!default_ranger_spell_setup(caster))
        return 1;

    set_spell_mana(100);
    set_spell_time(7);
    set_spell_ingredients(bless_ingr);
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE - (caster->query_ranger_rank()/2));
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_object(RANGER_SPELL_OBJ_DIR + "bless_shadow");
}
