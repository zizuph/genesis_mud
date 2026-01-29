/* File         : /d/Gondor/guilds/rangers/spells/heal.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22 2000
 * Purpose      : A spell used to heal someones injuries/
 * Related Files: /d/Gondor/common/guild/newspells/spell_inherit.c
 * Comments     : The ranger healing spell converted over to the new 
 *                spellcasting system.  Originally coded by the great
 *                Elessar Telecontar.
 * Modifications:
 *                Alto, February 2002. Move, no major modifications.
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit SPELL_INHERIT;

// Global Variables
static int Lothore;

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
    int heal, power;
    string msg;

    power = (caster->query_stat(SS_OCCUP) +
        caster->query_skill(SS_ELEMENT_LIFE) +
        caster->query_skill(SS_SPELLCRAFT));

    if (targets[0] == caster)
    {
        if (!caster->query_company() && !caster->query_wiz_level())
            power /= 2;
    }
    else
    {
        // Only reward / punish someone for actually healing someone.
        if (targets[0]->query_hp() != targets[0]->query_max_hp())
            adjust_valar_disfavour(caster, targets[0], 1.5);
    }

    if (!Lothore)
        msg = "call upon Este, the Valie of Healers";
    else
        msg = "use the virtues of the red heart-shaped flower";

    if (targets[0] != caster)
    {
        caster->catch_tell("You " + msg + " in a attempt to " +
            "heal some of " + targets[0]->query_the_possessive_name(caster) +
            " wounds.\n");

        targets[0]->catch_tell(caster->query_The_name(targets[0]) +
            " presses " + POSSESSIVE(caster) + " hand to your forehead " +
            "and murmurs a soft chant in an ancient tongue.\n");
    }
    else
    {
        caster->catch_tell("You " + msg + " in an attempt to heal " +
            "yourself.\n");
    }

    /* Finally start doing the actual healing */
    heal = (5 + F_PENMOD(success + 25, (power / 3)));

    // No lothore, then heal effectiveness is halved.
    if (!Lothore)
    {
        heal = heal / 2;
    }
    if (resist[0])
    {
        // Resistance may make healing less effective
        heal = heal - ((resist[0] * heal) / 100);
    }
    if (targets[0] == caster)
    {
        // 10% less healing power if healing yourself
        heal = heal - ((10 * heal) / 100);
    }
    // If we heal others give us a 10% bonus
    // (Trade off for 10% reduction in healing self and the
    // ability to "save" the ingredient from the old system)
    else
    {
        heal = heal + ((10 * heal) / 100);
    }

    /* Downgrading the heal output a little now to balance it up.
     *
     * Rangers have a 9 HP per Mana rate now vs.
     * SCOP        : 6.0 HP per Mana
     * POT         : 4.4 HP per Mana
     * layman heals: 2-3 HP per Mana
     *
     * Downing it with 10%. This change is also to ease
     * into the re-make to the new system later on.
     */
    heal = heal - ((10 * heal) / 100);

    setuid();
    seteuid(getuid());
    log_file("heal", caster->query_name() + " heals " +
        targets[0]->query_name() + " by " + heal + " hp on " +
        ctime(time()) + " (" + success + ", " +
        caster->query_stat(SS_OCCUP) + ", " +
        caster->query_skill(SS_ELEMENT_LIFE) + ", " +
        caster->query_skill(SS_SPELLCRAFT) + "\n");

    tell_room(ENV(caster), QCTNAME(caster) + " presses " +
        POSSESSIVE(caster) + " hand on " +
        (targets[0] == caster ? POSSESSIVE(caster) + " own" :
         QTPNAME(targets[0])) + " forehead, mumbling some words in an " +
        "ancient tongue.\n", ({ caster, targets[0] }));

    if (heal <= 0 || (targets[0]->query_hp() == targets[0]->query_max_hp()))
    {
        targets[0]->catch_tell("You feel a slight tingle, but " +
            "nothing more.\n");
        if (caster != targets[0])
            caster->catch_tell("You feel that your prayer had no effect.\n");
    }
    else
    {
        targets[0]->heal_hp(heal);
        caster->catch_tell("You feel someone answering your prayer.\n");
        targets[0]->catch_tell("Strange energies flow through your " +
            "wounds, and you feel healthier!\n");
    }

    if (Lothore)
    {
        if (random(6))
        {
            write("Luckily you manage to keep all ingredients intact.\n");
            reclaim_components();
        }
    }
}

mixed
heal_ingredients(object caster)
{
    object *list;

    list = get_item_search_list(caster);
    list = filter(list, &operator(==)("lothore") @ &->query_herb_name());

    if (!sizeof(list))
    {
        Lothore = 0;
        return ({ this_object() });
    }

    Lothore = 1;
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
    set_spell_name("heal");
    set_spell_desc("Heal someone's wounds.");
    set_spell_target(spell_target_one_present_living);

    if (!default_ranger_spell_setup(caster))
        return 1;

    set_spell_mana(75);
    set_spell_time(6);
    set_spell_ingredients(heal_ingredients);
    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE - (caster->query_ranger_rank()/2));
    set_spell_resist(spell_resist_healing);
    set_spell_stationary(0);
}
