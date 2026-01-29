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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "refresh";
inherit VIRTUE_SPELL_INHERIT;

#define REDWEED_KEEP_PERCENTAGE (83)

public void resolve_refresh_spell(object caster, mixed * targets, int * resist, int result)
{
    
}

public void
consume_components(object *ingrs)
{
    foreach (object ingredient : ingrs)
    {
        if (ingredient->query_prop("_savable_from_consumption"))
        {
            this_object()->restore_components(({ ingredient }));
        }
        else
        {
            ingredient->remove_object();
        }
    }
} /* consume_components */


/*
 * Function name: hook_use_ingredients
 * Description:   This function should return the message that will be printed
 *                to the caster when he/she has used some ingredients.
 * Arguments:     ingrs - The ingredients that will be used.
 * Returns:       The message to print.
 */
public void
hook_use_ingredients(object *ingrs)
{
    object * consumed = ({ });
    foreach(object ob : ingrs) 
    {
        if (random(100) < REDWEED_KEEP_PERCENTAGE)
        {
            write("Luckily, you manage to keep all ingredients intact.\n");
            ob->add_prop("_savable_from_consumption", 1);
        }
        else
        {
            consumed += ({ ob });
        }
    }

    consumed = filter(consumed, &->check_seen(this_player()));
    desc_use_ingredients(consumed);
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    mixed ingredients = query_ability_found_components(this_player());

    if (sizeof(ingredients))
      return 100.0;
  
    return 50.0;
}

public void desc_refresh_cast(object caster, object * targets, int amount)
{
    mixed ingredients = query_ability_found_components(caster);
    string msg;

    if (!sizeof(ingredients))
        msg = "call upon Orome, the Vala of Hunters,";
    else
        msg = "use the virtues of the red weed";

    if (targets[0] != caster)
    {
        caster->catch_tell("You " + msg + " in an attempt to envigorate " +
            targets[0]->query_the_name(caster) + ".\n");
        if (sizeof(ingredients))
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

    if  (targets[0]->query_fatigue() >= targets[0]->query_max_fatigue())
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
        // Only reward / punish someone for actually resting someone.
        adjust_valar_disfavour(caster, targets[0], 0.5);
        targets[0]->catch_tell("A tingling sensation spreads through " +
            "your weary limbs, and you feel less fatigued.\n");
    }
}

mixed query_refresh_ingredients(object caster)
{
    return ({});
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
    if (!(known_spells & SPELL_REST))
    {
        return 0;
    }
    if (player->query_ranger_has_virtues())
    {
        return has_spellcasting_virtue(player);
    }
    return 1;
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
config_refresh_spell()
{
    set_spell_name("rest");
    set_spell_desc("Rest someone's weary feet.");

    set_spell_optional_ingredients(({ "redweed" }));
    
    set_ability_stats(STAT_WEIGHTING);

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_resist(spell_resist_healing);
}
