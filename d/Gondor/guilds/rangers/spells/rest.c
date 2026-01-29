/* File         : /d/Gondor/guilds/rangers/spells/rest.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22 2000
 * Purpose      : A spell used to add fatigue to the target
 * Related Files: ~Gondor/common/guild/newspells/spell_inherit.c
 * Comments     : The ranger rest spell converted over to the new spell
 *                system. Originally created by the great Elessar Telcontar.
 * Modifications:
 *                Alto, February 2002. Move, no major modifications.
 *                Tigerlily, July 2005. Updated the formula a bit to make it
 *                   somewhat more powerful than the average fatigue
 *                   herb, since this is a spell that requires components
 *                   skills, and is taxed
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit SPELL_INHERIT;

#define SP_REST_TIRED_REDUCTION     30
#define SP_REST_EXTRA_REDUCTION     70

// Global Variables
static int Redweed;

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
    int power, rest_amt;
    string msg;

    power = caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_skill(SS_ELEMENT_LIFE) +
        caster->query_ranger_rank();

    // Only reward / punish someone for actually resting someone.
    if (targets[0]->query_fatigue() != targets[0]->query_fatigue())
        adjust_valar_disfavour(caster, targets[0], 0.5);

    if (!Redweed)
        msg = "call upon Orome, the Vala of Hunters,";
    else
        msg = "use the virtues of the red weed";

    if (targets[0] != caster)
    {
        caster->catch_tell("You " + msg + " in an attempt to envigorate " +
            targets[0]->query_the_name(caster) + ".\n");
        if (Redweed)
        {
            targets[0]->catch_tell(caster->query_The_name(targets[0]) +
                " crumbles a red weed between " + POSSESSIVE(caster) +
                " fingers and spreads the dust at your feet.\n");
        }
        else
        {
            targets[0]->catch_tell(caster->query_The_name(targets[0]) +
                " places " + POSSESSIVE(caster) + " hand upon your " +
                "weary shoulder and begins to chant in an ancient tongue.\n");
        }
    }
    else
    {
        caster->catch_tell("You " + msg + " in an attempt to rest your " +
            "weary bones.\n");
    }

    rest_amt = SP_REST_TIRED_REDUCTION + (((power - 50) *
        SP_REST_EXTRA_REDUCTION) / 100);

    // Half the rest amount if no component was used.
    if (!Redweed)
        rest_amt = rest_amt / 2;

    if (resist[0])
    {
        // Resistance may make healing less effective
        rest_amt = rest_amt - ((resist[0] * rest_amt) / 100);
    }

    if (Redweed)
    {
        tell_room(ENV(caster), QCTNAME(caster) + " crumbles a red weed to " +
            "dust between " + POSSESSIVE(caster) + " fingers, then spreads " +
            "it at " + (targets[0] == caster ? POSSESSIVE(caster) + " own" 
            : QTPNAME(targets[0])) + " feet while mumbling some words " +
            "in an ancient tongue.\n", ({ caster, targets[0] }));
    }
    else
    {
        tell_room(ENV(caster), QCTNAME(caster) +" places "+POSSESSIVE(caster)+
            " hand on " + (targets[0] == caster ? POSSESSIVE(caster) + " own" 
            : QTPNAME(targets[0])) + " weary shoulder while mumbling some " +
            "words in an ancient tongue.\n", ({ caster, targets[0] }));
    }         

    if (rest_amt <= 0 ||
      (targets[0]->query_fatigue() >= targets[0]->query_max_fatigue()))
    {
        targets[0]->catch_tell("You feel a slight tingle, but nothing " +
            "else.\n");
        if (caster != targets[0])
        {
            caster->catch_tell("You feel that your spell had no effect " +
                "on " + targets[0]->query_the_name(caster) + ".\n");
        }
    }
    else
    {
        targets[0]->add_fatigue(rest_amt);
        targets[0]->catch_tell("A tingling sensation spreads through " +
            "your weary limbs, and you feel less fatigued.\n");
    }

    if (Redweed)
    {
        if (random(6))
        {
            write("Luckily you manage to keep all ingredients intact.\n");
            reclaim_components();
        }
    }

    setuid();
    seteuid(getuid());
    log_file("rest", ctime(time()) + " " + caster->query_name() + " " +
        "rests "+ (targets[0] == caster ? OBJECTIVE(caster) + "self" 
        : targets[0]->query_name()) + " " + rest_amt + ".\n");
}

mixed
rest_ingredients(object caster)
{
    object *list;

    list = get_item_search_list(caster);
    list = filter(list, &operator(==)("redweed") @ &->query_herb_name());

    if (!sizeof(list))
    {
        Redweed = 0;
        return ({ this_object() });
    }

    Redweed = 1;
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
    set_spell_name("rest");
    set_spell_desc("Rest someone's weary feet.");
    set_spell_target(spell_target_one_present_living);

    if (!default_ranger_spell_setup(caster))
        return 1;

    set_spell_mana(30);
    set_spell_time(6);
    set_spell_ingredients(rest_ingredients);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE - caster->query_ranger_rank());
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_resist(spell_resist_healing);
    set_spell_stationary(0);
}
