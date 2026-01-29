/* File         : /d/Gondor/guilds/rangers/spells/cleanse.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22nd 2000         
 * Purpose      : Ranger Cleanse spell.
 * Related Files: ~Gondor/common/guild/newspells/spell_inherit.c
 * Comments     : This is the ranger cleansing spell.
 *                Originally created by the great Elessar Telcontar
 * Modifications:
 *                Alto, February 2002. Move, no major modifications.
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <poison_types.h>

inherit SPELL_INHERIT;

/* Function name : Find_poisons
 * Arguments     : player: the player we want to search for poisons
 * Description   : find any poisons in the player given
 * Returns       : an array of poison objects
 */
private object
find_poisons(object player)
{
    object *poison;

    if (!objectp(player))
        return 0;

    poison = filter(all_inventory(player), &operator(==)(POISON_OBJECT) @ 
        &function_exists("create_object",));

    if (!sizeof(poison))
        return 0;    
    else
        return poison[random(sizeof(poison))];
}

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
    object poison;
    string p_file, p_type;
    int power, cleansed, p_str;

    if (!objectp(poison = find_poisons(targets[0])))
    {
        if (targets[0] == caster)
            caster->catch_tell("You sense that you are not poisoned.\n");
        else
            caster->catch_tell("You sense that " +
                targets[0]->query_the_name(caster) + " is not poisoned.\n");
        return;
    }

    if (targets[0] == caster)
    {
        if (!caster->query_company() && !caster->query_wiz_level())
        {
            caster->catch_tell("You feel unable to cast this spell " +
                "on yourself.\n");
            return;
        }
    }
    else
        adjust_valar_disfavour(caster, targets[0], 2.5);

    power = caster->resolve_task(TASK_ROUTINE - 
        (caster->query_ranger_rank() / 2), ({ SKILL_AVG, TS_INT, TS_WIS,
        SKILL_END, SKILL_WEIGHT, 20, SS_SPELLCRAFT, SKILL_END, SKILL_WEIGHT,
        30, SS_ELEMENT_LIFE, SKILL_END, SKILL_WEIGHT, 50, SS_FORM_ABJURATION}));

    if (resist[0])
    {
        power = power - ((resist[0] * power) / 100);
    }

    p_file = MASTER_OB(poison);
    p_type = poison->query_poison_type();
    p_str = poison->query_strength();

    if (targets[0] != caster)
    {
        caster->catch_tell("You clench the athelas herb within your hand " +
            "and press it against " +
            targets[0]->query_the_possessive_name(caster) + " forehead, " +
            "attempting to cleanse " + POSSESSIVE(targets[0]) + " blood.\n");
        targets[0]->catch_tell(caster->query_The_name(targets[0]) +
            " clenches a green leaf within "+POSSESSIVE(caster) +
            "hand and presses it on your forehead, while chanting softly " +
            "in an ancient tongue.\n");
        tell_room(ENV(caster), QCTNAME(caster) + " clenches a green leaf " +
            "within " + POSSESSIVE(caster) + " hand and presses " +
            "it on " + QTPNAME(targets[0]) + " forehead, while chanting " +
            "softly in an ancient tongue.\n", ({ caster, targets[0] }));
    }
    else
    {
        caster->catch_tell("You clench the athelas herb within your hand " +
            "and press it upon your forehead, attempting to " +
            "cleanse your own blood.\n");
        tell_room(ENV(caster), QCTNAME(caster) + " clenches a green leaf " +
            "within " + POSSESSIVE(caster) + " hand and presses " +
            "it upon " + POSSESSIVE(caster) + " own forehead, " +
            "while chanting softly in an ancient tongue.\n", caster);
    }

    if (cleansed = poison->cure_poison(({ p_type, POISON_CURE_FATIGUE, 
      POISON_CURE_HP, POISON_CURE_MANA, POISON_CURE_STAT }), power))
    {
        caster->catch_tell("The treatment seems to have some effect.\n");
    }
    else
    {
        caster->catch_tell("You fear the poison was too strong for " +
            "your attempt.\n");

        if (caster != targets[0])
            targets[0]->catch_tell("You still feel the poison within " +
                "your veins.\n");
    }

    if (random(6))
    {
        write("Luckily you manage to keep all ingredients intact.\n");
        reclaim_components();
    }

    setuid();
    seteuid(getuid());
    log_file("cleanse", ctime(time()) + ": "+
        caster->query_name() + (cleansed ? " succeeds" : " fails") +
        " in cleansing " + p_type + " poison (" + p_file + ") "+
        "of strength " + p_str + " in "+
        (caster == targets[0] ? OBJECTIVE(caster) + "self" :
        targets[0]->query_name()) + " with strength " + power + ".\n");

}

/* Function name: config_spell
 * Description  : configures the spell, allowing you to set the
 *                various spell functions to the values you wish
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
    set_spell_name("cleanse");
    set_spell_desc("Cleanse a poison from someone.");
    set_spell_target(spell_target_one_present_living);

    if (!default_ranger_spell_setup(caster))
        return 1;
    set_spell_peaceful(0);
    set_spell_mana(100);
    set_spell_time(10);
    set_spell_ingredients(({"athelas"}));
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_task(TASK_ROUTINE - (caster->query_ranger_rank() / 2));
    set_spell_resist(spell_resist_healing);
    return 0;
}
