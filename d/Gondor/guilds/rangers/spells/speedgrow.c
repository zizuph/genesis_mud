/* File         : /d/Gondor/common/guild/newspells/speedgrow.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : June 10th, 2000
 * Purpose      : 
 * Comments     : 
 * Modifications:
 *                Alto, February 2002. Move, no major modifications.
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit SPELL_INHERIT;

#define ROOM_I_NO_RANGER_REGROWTH  "_room_i_no_ranger_regrowth"
#define ROOM_I_RANGER_REGROWTH     "_room_i_ranger_regrowth"

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
    mixed calls;
    int i, reset_time;

    if (!sizeof(targets[0]->query_herb_files()))
    {
        caster->catch_tell("Your spell fails, since this area is " +
            "too barren to grow any herbs.\n");
        return;
    }

    if (!targets[0]->query_searched())
    {
        caster->catch_tell("Your spell fails, since this area is already " +
            "flourishing with herbs.\n");
        return;
    }

    calls = targets[0]->query_alarms();
    i = -1;
    while(++i < sizeof(calls))
    {
        if (calls[i][1] == "reset")
        {
            reset_time = ftoi(calls[i][2]);
            break;
        }
    } 

    targets[0]->add_prop(ROOM_I_RANGER_REGROWTH, time() + reset_time);
    targets[0]->set_searched(0);

    caster->catch_tell("You bow your head down in quiet prayer " +
        "to Yavanna, Giver of Fruits, seeking her blessing upon " +
        "the land so that herbs may grow here once again.\n");
    tell_room(environment(caster), QCTNAME(caster) + " chants an " +
        "ancient prayer to Yavanna and then touches the ground with " +
        POSSESSIVE(caster) + " hand.\n", caster);

    setuid();
    seteuid(getuid());
    log_file("speedgrowth", ctime(time()) + " " + caster->query_real_name() +
        " cast regrowth in " + file_name(targets[0]) + ".\n");
}

/*
 * Function name: spell_target_caster_environment
 * Description  : Targets the room the caster is in.
 * Arguments    : object caster - the spell caster
 *                string str
 * Returns      : object * - the target object or empty array
 */
object *
spell_target_caster_environment(object caster, string str)
{
    object target;

    target = environment(caster);

    if (target->query_prop(ROOM_I_NO_RANGER_REGROWTH))
    {
        caster->catch_tell("Forces stronger than the Valar " +
            "prevent you from repopulating this area with herbs.\n");
        return ({ });
    }

    if (target->query_prop(ROOM_I_RANGER_REGROWTH) &&
      time() <= target->query_prop(ROOM_I_RANGER_REGROWTH))
    {
        caster->catch_tell("You sense the blessing of Yavanna is " +
            "already present here and shall have to wait some time " +
            "before you can call upon it for this area again.\n");
        return ({ });
    }

    return ({ target });
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
    set_spell_name("regrowth");
    set_spell_desc("Quicken the regrowth of herbs.");
    set_spell_target(spell_target_caster_environment);

    if (!default_ranger_spell_setup(caster))
        return 1;

    set_spell_ingredients(({"regrowth_ingredient"}));
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_mana(70);
    set_spell_time(8);
    set_spell_stationary(1);
    set_spell_peaceful(1);
}
