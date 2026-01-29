/* File         : /d/Gondor/common/guild/newspells/whistle.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22 2000
 * Purpose      : This is a spell used to summon a carrier pigon
 * Related Files: ~Gondor/common/guild/obj/pigon.c
 *                ~Gondor/common/guild/newspells/spell_inherit.c
 * Comments     : This is the ranger whistle spell converted over to
 *                to new spellcasting system.  Orignally coded by the
 *                great Elessar Telcontar.
 * Modifications:
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include "spells.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

inherit SPELL_INHERIT;

#define RANGER_PIGEON_OB        "_ranger_o_pigeon"

/* Function name: no_result
 * Description  : if the pigeon can't find it's waay to its owner this
 *                message is given to him/her.
 * Arguments    : pl - player who cast the spell
 */
void
no_result(object pl)
{
    pl->catch_tell("You don't see any sign of your carrier pigeon.\n");
}

/* Function name: pigeon_arriving
 * Description  : This function notifies the player that a pigeon
 *                has arrived and is available for use
 * Arguments    : pl - person who cast the spell
 */
void
pigeon_arriving(object pl)
{
    object pigeon = pl->query_prop(RANGER_PIGEON_OB);

    if (!objectp(pigeon))
    {
	FIX_EUID
	pigeon = clone_object(RANGER_DIR + "obj/pigeon");
	pigeon->set_owner(pl);
	pigeon->set_times_to_fly((pl->query_skill(SS_ANI_HANDL)/6)+1);
	pigeon->start_place();
	pl->add_prop(RANGER_PIGEON_OB, pigeon);
	return;
    }
    else if (pigeon->query_busy())
    {
	set_alarm(4.0, 0.0, &no_result(pl));
	return;
    }
    else if (living(ENV(pigeon)))
    {
	if (!ENV(ENV(pigeon))) 
	{
	    set_alarm(6.0, 0.0, &no_result(pl));
	    return;
	}
	if (ENV(ENV(pigeon))->query_prop(ROOM_I_INSIDE))
	{
	    set_alarm(6.0, 0.0, &no_result(pl));
	    return;
	}
	if (ENV(pigeon)->query_prop(ROOM_I_INSIDE))
	{
	    set_alarm(6.0, 0.0, &no_result(pl));
	    return;
	}
    }
    else
	pigeon->return_to(pl);
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
    if (resist[0])
    {
	if (caster->query_prop(RANGER_PIGEON_OB) &&
	  ENV(caster->query_prop(RANGER_PIGEON_OB)) == caster)
	{
	    caster->catch_tell("Your pigeon is already with you.\n");
	    return;
	}
	if (ENV(caster)->query_prop(ROOM_I_INSIDE))
	{
	    caster->catch_tell("You cannot summon your pigeon from inside "+
	      "a room.\n");
	    return;
	}
	if (ENV(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
	{
	    caster->catch_tell("You are unable to summon your pigeon "+
	      "from underneath the water.\n");
	    return;
	}
	set_alarm(7.0, 0.0, &no_result(caster));
    }
    else
	set_alarm(1.0, 0.0, &pigeon_arriving(caster));

    caster->catch_tell("You purse your lips and whistle a low, "
      + "ululating sound to summon your carrier pigeon.\n");
    tell_room(ENV(caster), QCTNAME(caster) + " purses "
      + POSSESSIVE(caster) + " lips and whistles a low, ululating "
      + "sound.\n", ({caster}));
}

/* Function name: whistle_resist
 * Description  : A custom resist function for this spell since to make
 *                sure the pigeon is available to fly off to the caster.
 * Arguments    : caster          - person casting the spell
 *                target          - target of the spell
 *                element         - spell element used in the spell
 *                difficulty      - how difficult is it to resist the spell
 *                casting_success - how well the spell was cast
 * Returns      : How well the spell was resisted from 1-100;
 */
int
whistle_resist(object caster, object target, int element, int difficulty, int casting_sucess)
{
    object pigeon, room;

    if (ENV(caster)->query_prop(ROOM_I_INSIDE) ||
      (ENV(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
	return 100;

    if (!objectp(pigeon = caster->query_prop(RANGER_PIGEON_OB)))
	return 0;
    if (pigeon->query_busy())
	return 100;
    if (ENV(pigeon) == caster)
	return 100;

    while (!room->query_prop(ROOM_I_IS))
    {
	if (!objectp(room))
	    room = environment(pigeon);
	else
	    room = environment(room);
    }

    if (room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER ||
      room->query_prop(ROOM_I_INSIDE))
	return 100;

    return 0;
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
    set_spell_name("whistle");
    set_spell_desc("Summon a carrier pigeon.");
    set_spell_target(spell_target_caster);

    if (!default_ranger_spell_setup(caster))
	return 1;
    set_spell_mana(25);
    set_spell_mana_fail(66);
    set_spell_time(2);
    set_spell_visual(0);
    set_spell_ingredients(0);
    set_spell_vocal(1);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_CONJURATION, 5);
    set_spell_resist(whistle_resist);
    return 0;
}
