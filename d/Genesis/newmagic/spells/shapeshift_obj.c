/*
 *  /d/Genesis/newmagic/spells/shapeshift_obj.c
 *
 *  Spell effect object for the shapeshifting spell. This object handles
 *  all the transformations, based on the configuration set in the 
 *  originating spell. 
 *
 *  Created by Eowul, November 2008
 */
 
#pragma strict_types
#pragma no_shadow

#include <files.h>

inherit "/d/Genesis/newmagic/spell_effect_object";

// Variables
private object  player;

// Prototypes
public  void    remove_spell_effect_object();

#define OBJECT_HOLDING ("/d/Genesis/newmagic/spells/shapeshift_closet")
#define POISON_F_TIME_LEFT "_poison_f_time_left"

/*
 * Function name: valid_shapeshift_target
 * Description  : Perform checks to see if the targeted object is a valid 
 *              : destination for our shapeshift spell.
 * Arguments    : target - the object to check
 * Returns      : 1/0 - shapeshift allowed/not allowed
 */
private nomask int
valid_shapeshift_target(object target) 
{
    string filename = file_name(target);
    
    if(filename[0..26] == "/d/Genesis/race/shapeshift/")
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name: set_player
 * Description  : Set the player that is about to be shapeshifted
 * Arguments    : ob - the player object
 */
public nomask void
set_player(object ob) 
{
    player = ob;
}

/*
 * Function name: query_player
 * Description  : Return the player object belonging to this shapeshift
 *              : effect.
 * Returns      : a player object
 */
public nomask object
query_player()
{
    return player;
}
 
/*
 * Function name: move_poisons
 * Description  : Move poisons from one object to the other
 * Arguments    : from - the object to move poisons from
 *              : to - the object to move poisons to
 */
private nomask void 
move_poisons(object from, object to)
{
    object *poisons;

    poisons = FILTER_POISON_OBJECTS(all_inventory(from));

    foreach(object poison : poisons) 
    {
        poison->linkdeath_hook(from, 1);
        int time_left = poison->query_time_left();
        if(time_left > 0) {
            poison->set_time(time_left);
            poison->move(to, 1);
            poison->start_poison(0);
        }
    }
}

/*
 * Function name: abort_shapeshift
 * Description  : Stops the shapeshift effect
 */
public nomask void
abort_shapeshift()
{
    if(!interactive(query_spell_effect_target())) 
    {
        return;
    }
    
    if(!objectp(player) || interactive(player)) 
    {
        query_spell_effect_target()->catch_tell("Your original body "
            + "is no longer available. Please contact a wizard.\n");
        return;
    }
    
    player->move(environment(query_spell_effect_target()), 1);
    player->set_new_living_name(player->query_real_name());
    query_spell_effect_target()->hook_pre_shapeshift_return();
    
    if(!exec(player, query_spell_effect_target())) 
    {
        query_spell_effect_target()->catch_tell("Unable to switch "
            + "you back to your original body. Please contact a "
            + "wizard.\n");
        return;
    }
    
    move_poisons(query_spell_effect_target(), player);
    query_spell_effect_target()->hook_post_shapeshift_return();
    query_spell_effect_target()->move(find_object(OBJECT_HOLDING));
    set_alarm(0.5, 0.0, remove_spell_effect_object);
}

/*
 * Function name: remove_spell_effect_object
 * Description:   Remove the spell effect object, unregistering it as
 *                well.
 */
public void
remove_spell_effect_object()
{
    // Cleanup the spell target in case we get removed
    if(objectp(query_spell_effect_target()) 
        && !interactive(query_spell_effect_target())) 
    {
        query_spell_effect_target()->remove_object();
    }
    
    ::remove_spell_effect_object();
}

/*
 * Function name: start
 * Description;   Start up the shapeshift. 
 * Returns:       1/0 - effect started/not started
 */
public nomask int
start()
{
    if(!valid_shapeshift_target(query_spell_effect_target())) 
    {
        query_spell_effect_caster()->catch_tell("There is a permission "
            + "problem with your shapeshift spell. Please contact a "
            + "wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    if(interactive(query_spell_effect_target())) 
    {
        query_spell_effect_caster()->catch_tell("The intended "
            + "target for your shapeshift spell is already in use. "
            + "Please contact a wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    if(!objectp(player) || !interactive(player)) {
        query_spell_effect_caster()->catch_tell("The target for your "
            + "spell is not a real interactive player. Please contact "
            + "a wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    catch(OBJECT_HOLDING->teleledningsanka());
    object holding_room = find_object(OBJECT_HOLDING);
    if(!objectp(holding_room)) {
        query_spell_effect_caster()->catch_tell("There was an error "
            + "loading the holding area. Please contact a wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    // Setup the shapeshift target
    query_spell_effect_target()->set_spell_effect(this_object());
    query_spell_effect_target()->setup_for_player(player);
    query_spell_effect_target()->hook_prepare_shapeshift_target();
    
    // Have both the player and the target object in the room so messages can
    // be written properly.
    query_spell_effect_target()->move(environment(player), 1);
    query_spell_effect_target()->hook_pre_shapeshift_transform();
    
    if(!exec(query_spell_effect_target(), player)) 
    {
        query_spell_effect_caster()->catch_tell("Unable to switch "
            + "target to the shapeshifted object. Please contact a "
            + "wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    move_poisons(player, query_spell_effect_target());
    
    // Then move the old player object to the holding area
    query_spell_effect_target()->hook_post_shapeshift_transform();
    player->set_new_living_name("original_" + player->query_real_name());
    player->move(holding_room, 1);
    
    return 1;
}

/*
/*
 * Function name: dispel_spell_effect
 * Description:   Cause this spell effect to be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_spell_effect(object dispeller)
{
    abort_shapeshift();
}