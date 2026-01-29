/*
 * send
 *
 * Description: Send an object to the player.
 * Class:       no idea
 * Ingredients: feather
 * Mana:        120
 * Tax:         N/A
 * Skills:      SS_ELEMENT_AIR 80
 *              SS_FORM_TRANSMUTATION 90
 * Task:        TASK_DIFFICULT
 * Restriction: The caster must not be engaged in combat.
 */

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "../guild.h";
#include "/d/Krynn/common/defs.h"

inherit SPELL_STD;

public object*
spell_target_player(object caster, string argval)
{
    mixed   entity, player;

    if (!parse_command(argval || "", ({ }), "%s 'to' %s", entity, player))
    {
        caster->catch_tell("Send what to whom?\n");
        return ({ });
    }

    if (!(player = find_player(player)) || (player == caster) ||
        !caster->query_met(player->query_real_name()))
    {
        caster->catch_tell("Send what to whom?\n");
        return ({ });
    }

    if (!sizeof(entity = FIND_STR_IN_OBJECT(entity, caster)))
    {
        caster->catch_tell("Send what to whom?\n");
        return ({ });
    }

    if (sizeof(entity) >= 2 || (entity[0]->num_heap() >= 2))
    {
        caster->catch_tell("You cannot send so many items at once.\n");
        return ({ });
    }

    return ({ player }) + entity;
}

public varargs int
config_spell(object caster, object *target, string argval)
{
    set_spell_name("send");
    set_spell_desc("Send an item to person");

    set_spell_element(SS_ELEMENT_AIR, 80);
    set_spell_form(SS_FORM_TRANSMUTATION, 90);

    set_spell_time(5);
    set_spell_task(TASK_DIFFICULT);

    set_spell_mana(120);
    set_spell_target(spell_target_player);
    set_spell_ingredients(({ "feather" }));

    set_spell_peaceful(1);
    set_spell_vocal(1);
}

public void
resolve_spell(object caster, object *target, int *resist, int result)
{
    object  player = target[0], entity = target[1];

    entity->split_heap(1);

    caster->catch_tell("A vortex opens above your head as you pronounce" +
        " the words of power.\n");

    tell_room(environment(caster), "A vortex opens above your head as" +
        QTNAME(caster) + " pronounces the words of power.\n", caster);

    if (!player || (environment(player) == environment(caster)) ||
        (environment(entity) != caster) || entity->move(player))
    {
        tell_room(environment(caster), "The vortex above your head" +
            " closes casting a silence upon the surroundings.\n");
        caster->catch_tell("Something went terribly wrong.\n");
        return;
    }

    caster->catch_tell("Drawn out of your hands by unnatural powers " +
        LANG_THESHORT(entity) + " dissapears in the vortex.\n");

    tell_room(environment(caster), "Drawn out of " + QTNAME(caster) +
        " hands by unnatural powers " + LANG_ASHORT(entity) +
        " dissapears in the vortex.\n", caster);

    tell_room(environment(caster), "The vortex above your head closes" +
        " casting a silence upon the surroundings.\n");

    tell_room(environment(player), "The skies explode and a terrible" +
        " vortex opens above your head.\n");

    player->catch_tell("Unable to resist you extend your hand towards" +
        " the vortex and a second later " + LANG_ASHORT(entity) +
        " appears in it.\n");

    tell_room(environment(player), QCTNAME(player) + " extends " +
        player->query_possessive() + " hand towards the vortex and a" +
        " second later " + LANG_ASHORT(entity) + " appears in it.\n", player);

    tell_room(environment(player), "The vortex above your head closes" +
        " casting a silence upon the surroundings.\n");
}
