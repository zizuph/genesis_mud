/* File         : /d/Gondor/common/guild/newspells/whistle.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22 2000
 * Purpose      : This is a spell used to summon a carrier pigon
 * Related Files: ~Gondor/guilds/rangers/obj/pigeon.c
 *              : ~Gondor/guilds/rangers/obj/ferret.c
 *                ~Gondor/guilds/spells/spell_inherit.c
 * Comments     : This is the ranger whistle spell converted over to
 *                to new spellcasting system.  Orignally coded by the
 *                great Elessar Telcontar.
 * Modifications:
 *   Alto, February 2002. Move, no major revisions.
 *   Gwyneth, Added ferret argument checks
 *   Toby, 11 Feb, 2007: set_spell_time set to 6 according to new rules
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";
inherit VIRTUE_SPELL_INHERIT;

/* Function name: messenger_arriving
 * Description  : This function notifies the player that a messenger
 *                has arrived and is available for use
 * Arguments    : pl - person who cast the spell
 */
void
messenger_arriving(object pl, int type)
{
    
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
resolve_spell(object caster, mixed *targets, int *resist, int success)
{
    int gType = targets[0][1];
    
    FIX_EUID
    object messenger;
    
    if (gType == 1)
    {
        messenger = clone_object(RANGERS_OBJ + "ferret");
    }
    else
    {
        messenger = clone_object(RANGERS_OBJ + "pigeon");
    }

    messenger->set_owner(caster);
    messenger->set_times_to_fly((caster->query_skill(SS_ANI_HANDL)/4)+1);
    messenger->start_place();
    return;

}

public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    int gType = targets[0][1];
    
    if (ENV(caster)->query_prop(ROOM_I_INSIDE) && !gType)
    {
        caster->catch_tell("You cannot summon your pigeon from inside " +
            "a room.\n");
        return 0;
    }

    if (ENV(caster)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        caster->catch_tell("You are unable to summon your " +
            gType ? "ferret" : "pigeon" +
            " from underneath the water.\n");
        return 0;
    }
    
    return 1;
}

void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You purse your lips and whistle a low, " +
        "ululating sound to summon your messenger.\n");
    tell_room(ENV(caster), QCTNAME(caster) + " purses " +
        POSSESSIVE(caster) + " lips and whistles a low, ululating " +
    "sound.\n", ({ caster }));
}


public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    int known_spells = player->query_skill(SS_RANGER_SPELL_LIST);
    if (!(known_spells & SPELL_WHISTLE))
    {
        return 0;
    }
    return 1;
}


/*
 * Function name: target_animal_type
 */
public object *
target_animal_type(object actor, string str)
{
    int gType = 0;
    
    if (strlen(str))
    {
        if (lower_case(str) == "ferret" || lower_case(str) == "for ferret")
            gType = 1;
    }

    return ({ ({ actor, gType }) });
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
void
config_spell()
{
    set_spell_name("whistle");
    set_spell_desc("Summon a messenger.");
    set_spell_target(target_animal_type);

    set_spell_time_factor(1.5);

    set_spell_visual(0);
    set_spell_ingredients(0);
    set_spell_vocal(1);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_CONJURATION, 5);
    return 0;
}
