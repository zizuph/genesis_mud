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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "darkvision";

/*
 * Function:    query_darkvision_ingredients
 * Description: This function defines what components are required for
 *              this dark vision spell.
 */
public string *
query_darkvision_ingredients(object caster)
{
    return ({ "holly berry"});
}

/*
 * Function:    resolve_darkvision_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_darkvision_spell(object caster, mixed * targets, int * resist, int result)
{
    if (result)
    {
        caster->catch_tell("You concentrate for a while, praying for Elbereth " +
            "to bless you with better vision at night.\n");
        tell_room(ENV(caster), QCTNAME(caster) + " gestures a little, while " +
            "mumbling something.\n", caster);
    }
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
    if (!(known_spells & SPELL_NIGHTVISION))
    {
        return 0;
    }
    if (player->query_ranger_has_virtues())
    {
        // This is a legacy spell, and is not paid for in the virtue system.
        return 0;
    }
    return 1;
}


/* Function name: config_darkvision_spell
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
public void
config_darkvision_spell(void)
{
    set_spell_name("nightvision");
    set_spell_desc("See in the darkness of twilight.");
    set_spell_form(SS_FORM_CONJURATION, 15);
    set_spell_element(SS_ELEMENT_LIFE, 25);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("Your spell fizzles and fails to take effect.\n");

    // Set the effect object filename
    set_spell_object(RANGERS_SPELL + "obj/nightv_ob");
}
