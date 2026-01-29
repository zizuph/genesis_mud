/* File         : /d/Gondor/guilds/rangers/nightvision.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22nd 2000
 * Purpose      : A spell which allows a player to see outdoors when it is dark
 * Related Files: /d/Gondor/common/newspells/obj/nightv_shadow.c
 *                /d/Gondor/common/newspells/spell_inherit.c
 * Comments     : The ranger nightvison spell converted to the new spellsystem.
 *                Originally created by the great Elessar Telcontar.
 * Modifications:
 *                Alto, February 2002. Move, no major revisions.
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit SPELL_INHERIT;

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
    if (caster->query_ranger_nightivision())
    {
        caster->catch_tell("You are already under the effects of the " +
            "nightvision spell.\n");
        return;
    }
    if (random(100) <= resist[0])
    {
        caster->catch_tell("Your spell fizzles and fails to take effect.\n");
        return;
    }

    if (present("Ranger_Blind_Object", caster))
    {
        setuid();
        seteuid(getuid());
        log_file("nightvision", caster->query_name() + " tried to cast "+
            "nightvison while blinded by brawl, " + ctime(time()) + ".\n");
    }

    caster->catch_tell("You concentrate for a while, praying for Elbereth " +
        "to bless you with better vision at night.\n");
    tell_room(ENV(caster), QCTNAME(caster) + " gestures a little, while " +
        "mumbling something.\n", caster);
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
        resist, success);
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
    set_spell_name("nightvision");
    set_spell_desc("See in the darkness of twilight.");
    set_spell_target(spell_target_caster);

    if (!default_ranger_spell_setup(caster))
        return 1;
    set_spell_ingredients(({"holly berry"}));
    set_spell_mana(40);
    set_spell_time(8);
    set_spell_task(TASK_ROUTINE);
    set_spell_form(SS_FORM_CONJURATION, 15);
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_object(RANGER_SPELL_OBJ_DIR + "nightv_shadow");
}
