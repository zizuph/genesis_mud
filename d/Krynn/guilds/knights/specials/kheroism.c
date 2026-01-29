/*
 * /d/Krynn/guilds/knights/specials/kheroism.c
 *
 * Heroism is the ability of the Knight to be granted divine
 * strength when in a dire situation. This is very similar to
 * the previous kdie, but without the dying part. Instead,
 * the Knight will experience a severe degradation of their
 * stats and abilities while the ability resets.
 *
 * Created by Petros, October 2008
 */
 
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define HEROISM_LOG     (VLOG + "kheroism_log")

public void config_ability()
{
    ::config_ability();
    set_ability_name("kheroism");
    set_ability_offensive(0);
    set_ability_hasted(0); // no haste changes to kheroism
    set_ability_prep_time(1);
    set_ability_cooldown_time(0);
    set_ability_visual(0);
    set_ability_target(target_actor);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
	actor->catch_tell("With a glance at your wounds you pull yourself "
	    + "together and pray earnestly to Paladine for the strength and "
	    + "courage to continue to fight.\n");
	tell_room(environment(actor), QCTNAME(actor) + " looks down at "
	    + actor->query_possessive() + " many wounds and grits "
	    + actor->query_possessive() + " teeth. With a cry to Paladine "
	    + actor->query_pronoun() + " he calls out for the strength "
	    + "and courage to continue this fight.\n", ({ actor }));
    
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    object poison;
    
    setuid();
    seteuid(getuid());
    poison = clone_object(SPECIALS + "objects/kheroism_object");
    poison->move(actor);
    if (actor->query_knight_level() == L_SWORD)
    {
        // Sword Knights have the special ability of enhanced heroism.
        // That means that their heroism lasts longer, and the cooldown
        // is shorter.
        // Normally: 5 minutes heroism, 100 minutes cooldown
        // Sword Knights: 10 minutes heroism, 50 minute cooldown
        poison->set_heroism_duration(poison->query_heroism_duration() * 2);
        poison->set_heroism_cooldown(poison->query_heroism_cooldown() / 2);
    }
    else
    {
        // Calling a seemingly useless set. This setting will actually
        // trigger the duration to become randomized.
        poison->set_heroism_duration(poison->query_heroism_duration());
        poison->set_heroism_cooldown(poison->query_heroism_cooldown());
    }
    
    send_debug_message("kheroism", capitalize(actor->query_real_name())
        + " uses kheroism with " + actor->query_hp() + " hit points left "
        + "and has a duration of " + poison->query_heroism_duration() 
        + ".", HEROISM_LOG);
    poison->start_poison();
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already offering up a prayer to Paladine and calling "
        + "upon your inner reserves of courage and heroism.\n");
}

public void
hook_special_in_cooldown()
{
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    if (player->query_knight_level() < L_CROWN)
    {
        player->catch_tell("You are not ready to display such acts of "
            + "heroism.\n");
        return 0;
    }
    
    if ((player->query_exp() / 3) > player->query_exp_combat() 
        && !player->query_wiz_level()
        && !player->query_npc())
    {
        player->catch_tell("You are not experienced enough to use this "
            + "command.\n");            
    	return 0;
    }

    if (!execute)
    {
        if (TP->query_hp() > (TP->query_max_hp() / 5))
        {
            player->catch_tell("You are not about to die yet, your wounds "
                + "are not severe enough.\n");
            return 0;
        }
        
        if (player->query_relaxed_from_combat())
        {
            player->catch_tell("You are not facing any foes, and cannot "
                + "summon your inner reserves of strength.\n");
    	    return 0;
    	}
    }
    
    if (present("knight_heroism_object", player))
    {
        if (player->query_prop("_knight_hero_prop"))
        {
            player->catch_tell("You are already drawing upon your inner "
                + "strength!\n");
        }
        else
        {
            player->catch_tell("You feel overly tired, and cannot muster "
                + "again so soon the inner reserves to display your courage "
                + "and heroism.\n");
        }
        return 0;
    }
    
    return 1; 
}

