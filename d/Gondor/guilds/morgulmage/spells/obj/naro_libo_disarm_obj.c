/*
 * Disarm Object - based on the Elementalists disarm spell object
 * by Jaacar, February 2017.
 *
 * For weapons that are imbued, it disarms for a limited duration
 * rather than breaking the weapon.
 *
 * Created by Arman, April 2020.
 *
 * Updated July 2022 - Zizuph.  Ported to new disable attack effect.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "disable_attack_obj";


private int attack_id;

public void set_attack_id(int id)
{
    attack_id = id;
}

public int query_attack_id()
{
    return attack_id;
}

public void
hook_attack_blocked(object player, int attack_id, object weapon)
{
    if (objectp(player))
    {
        tell_room(environment(player), QCTNAME(player) + " attempts to " 
            + "swing " + player->query_possessive() + " "
            + weapon->query_short() + ", but fear takes hold and "
            + player->query_pronoun() + " cannot muster the courage "
            + "to do so.\n", ({ player }));
        player->catch_msg("Visions of a great flaming red eye form in your "
            +"mind, causing you immense terror.\n");
    }
}

public void
hook_disable_attack_ended(object player)
{
    if (objectp(player))
    {
        player->catch_msg("The vision of the red eye slowly fades.\n");
        tell_room(environment(player), QCTNAME(player) + " looks less "
            + "fearful than before.\n");
    }
}

public void
hook_disable_attack_begin(object caster, object target)
{
    if (caster->query_mm_mounted()) {
        caster->catch_tell("Standing atop your steed, you raise your hand,"
            + " menacing " + target->query_the_name(caster)
            + ", and command: Libo makil!\n"
            + target->query_The_name(caster) + " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n");

        target->catch_tell(caster->query_The_name(target) + " rises from atop "
            + caster->query_possessive() + " steed and lifts "
            + caster->query_possessive() + " hand, menacing at you, and "
            + "commands: Libo makil!\nYou fail to understand the words, but "
            + "you are stricken dumb.\nYou feel your tongue cleave to your "
            + "mouth, and your heart labouring.\n");

        tell_room(environment(caster), QCTNAME(caster) + " rises from atop "
            + caster->query_possessive() + " steed and lifts "
            + caster->query_possessive() + " hand, menacing at "
            + QTNAME(target) + ", and commands: Libo makil!\n"
            + QCTNAME(target)+ " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n",
            ({ caster, target}));
    } else {
        caster->catch_tell("You raise your hand, menacing "
            + target->query_the_name(caster) + ", and command: Libo makil!\n"
            + target->query_The_name(caster) + " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n");

        target->catch_tell(caster->query_The_name(target) + " raises "
            + caster->query_possessive() + " hand, menacing at you, and "
            + "commands: Libo makil!\nYou fail to understand the words, but "
            + "you are stricken dumb.\nYou feel your tongue cleave to your "
            + "mouth, and your heart labouring.\n");

        tell_room(environment(caster), QCTNAME(caster) + " raises "
            + caster->query_possessive() + " hand, menacing at "
            + QTNAME(target) + ", and commands: Libo makil!\n"
            + QCTNAME(target)+ " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n",
            ({ caster, target}));
    }
}
