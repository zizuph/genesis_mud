/*
 * /d/Gondor/guilds/rangers/spells/conceal.c
 *
 * Related files:
 *  /d/Gondor/guilds/rangers/spells/spell_inherit.c
 *  /d/Gondor/guilds/rangers/spells/obj/conceal_shadow.c
 *
 * Coded by Gwyneth on 10/20/03
 *
 * Description:
 * This spell is for the Rangers of the North, being the stealth
 * oriented company. A Ranger of the North may call upon Aule,
 * the Valar smith to make their body-armour or cloaks conceal them
 * better. 
 *
 * This will temporarily add the magic property to the
 * armour. The conceal may only be used by the Ranger who cast
 * it. A conceal can be cast over it by another Ranger, which
 * will nullify the previous conceal.
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
int Curugwath;

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
    int power, at;
    string adesc;

    if (caster->query_company() != "north")
    {
        caster->catch_tell("You are unable to cast this spell.\n");
        return;
    }

    power = caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_skill(SS_ELEMENT_LIFE) +
        (caster->query_ranger_rank() / 2);

    if (!sizeof(targets))
    {
        caster->catch_tell("What did you want to cast it on?\n");
        return;
    }

    at = targets[0]->query_at();
    if (at != A_BODY && at != A_TORSO && at != A_BACK && at != A_ROBE &&
      at != A_CHEST)
    {
        caster->catch_tell("You can only cast this spell on a body " +
            "armour or cloak.\n");
        return;
    }

    adesc = targets[0]->short();

    if (!Curugwath)
    {
        caster->catch_tell("You call upon Aule, the Vala of Smiths, to " +
            "enhance your " + adesc + " to better conceal you.\n");
        tell_room(environment(caster), QCTNAME(caster) + " holds " +
            + POSSESSIVE(caster) + " hand above " + adesc + " while " +
            " mumbling some words in an ancient language.\n", caster);
        power *= 2;
        power /= 3;
    }
    else
    {
        caster->catch_tell("You use the virtues of the curugwath " +
            "to improve your " + adesc + ".\n");
        tell_room(environment(caster), QCTNAME(caster) + " rubs a " +
            "silver leaf on " + POSSESSIVE(caster) + " " + adesc +
            "while mumbling some words in an ancient language.\n", caster);
    }

    setuid();
    seteuid(getuid());
    log_file("conceal", ctime(time()) + " " + caster->query_name() + " " +
        "concealed " + adesc + ".\n");

    make_spell_effect_object(query_spell_object(), caster, targets,
        resist, success);
}

mixed
conceal_ingr(object caster)
{
    object *list;

    list = get_item_search_list(caster);
    list = filter(list, &operator(==)("curugwath") @ &->query_herb_name());

    if (!sizeof(list))
    {        
        Curugwath = 0;
        return ({ this_object() });
    }

    Curugwath = 1;
    return ({ list[0] });
}

/* Function name: config_spell
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
    set_spell_name("conceal");
    set_spell_desc("Call on Aule to make an armour be able to conceal you.");
    set_spell_target(spell_target_one_present_non_living);

    if (!default_ranger_spell_setup(caster))
        return 1;

    set_spell_mana(100);
    set_spell_time(7);
    set_spell_ingredients(conceal_ingr);
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE - (caster->query_ranger_rank()/2));
    set_spell_resist(spell_resist_basic);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_object(SPELL_OBJ_DIR + "conceal_shadow");
}
