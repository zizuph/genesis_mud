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

#include "/d/Genesis/specials/local.h"

inherit SPELL_DIR + "cleanse";
inherit VIRTUE_SPELL_INHERIT;

#define ATHELAS_KEEP_PERCENTAGE (50)

void
config_cleanse_spell()
{
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_cleanse_all(1);
}

public string *
query_cleanse_ingredients(object caster)
{
    return ({ "athelas" });
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
    if (!(known_spells & SPELL_CLEANSE))
    {
        return 0;
    }
    if (player->query_ranger_has_virtues())
    {
        return has_spellcasting_virtue(player);
    }
    return 1;
}

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
        if (random(100) < ATHELAS_KEEP_PERCENTAGE)
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

public void
hook_no_cleanseable_poisons(object caster, object target)
{
        if (target == caster)
            caster->catch_tell("You sense that you are not poisoned.\n");
        else
            caster->catch_tell("You sense that " +
                target->query_the_name(caster) + " is not poisoned.\n");
}


public void
hook_no_poisons_cleansed(object caster, object target)
{
    caster->catch_tell("You fear the poison was too strong for " +
        "your attempt.\n");

    if (caster != target)
        target->catch_tell("You still feel the poison within " +
            "your veins.\n");
}

public void
hook_some_poisons_cleansed(object caster, object target)
{
    caster->catch_tell("You fear poisons still remain after " +
        "your attempt.\n");

    if (caster != target)
        target->catch_tell("You still feel poisons within " +
            "your veins.\n");
}

public void
hook_all_poisons_cleansed(object caster, object target)
{
    caster->catch_tell("The treatment seems to clear the poisons.\n");

    if (caster != target)
        target->catch_tell("You no longer feel the poisons within " +
            "your veins.\n");
}

public void
hook_describe_cleanse_cast(object caster, object * targets)
{
    adjust_valar_disfavour(caster, targets[0], 2.5);

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
}
