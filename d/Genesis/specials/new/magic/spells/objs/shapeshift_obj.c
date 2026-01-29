/*
 *  Shapeshift Object
 *
 *  Spell effect object for the shapeshifting spell. This object handles
 *  all the transformations, based on the configuration set in the 
 *  originating spell. 
 *
 *  Created by Eowul, November 2008
 *  Adapted by Petros, May 2012, for the new Genesis Magic System
 */
 
#pragma strict_types
#pragma no_shadow

#include <files.h>
#include <stdproperties.h>
#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Prototypes
public  void    remove_spell_effect_object();

#define OBJECT_HOLDING              (SPELL_OBJ_DIR + "shapeshift_closet")
#define POISON_F_TIME_LEFT          "_poison_f_time_left"
#define LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"

// Global Variables
public object   shapeshift_body = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_shapeshift_object_");
    set_short("shapeshift spell object");    
    set_long("This is the standard shapeshift spell's object. It handles "
        + "the actions involved in moving the player from one body "
        + "to another.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the shapeshift spell.\n");
    set_spell_effect_desc("shapeshift");    
}

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
 * Function:    query_shapeshift_original_body
 * Description: This function should return the actual original player body
 *              prior to the shapeshift. By default, this returns the effect
 *              target, because that is where the actual effect will exist
 */
public object
query_shapeshift_original_body()
{
    return query_spell_effect_target();
}

/*
 * Function:    query_shapeshift_body
 * Description: This function should return the body that the player shifted
 *              into.
 */
public object
query_shapeshift_body()
{
    return shapeshift_body;
}

/*
 * Function:    set_shapeshift_body
 * Description: Once a new shapeshift body is cloned, one should set the
 *              body variable so that it can be referenced later.
 */
public void
set_shapeshift_body(object body)
{
    shapeshift_body = body;
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
 * Function name: copy_souls
 * Description  : Copy the command souls from one to the other, skipping
 *                the basic ones.
 * Arguments    : from - the object to move souls from
 *              : to - the object to move souls to
 */
private nomask void 
copy_souls(object from, object to)
{
    string * command_souls = from->query_cmdsoul_list();
    if (!sizeof(command_souls))
    {
        return;
    }
    
    foreach (string soul : command_souls)
    {
        if (wildmatch("/d/Genesis/cmd/*", soul)
            || wildmatch ("/cmd/live/*", soul))
        {
            continue;
        }
        to->add_cmdsoul(soul);
    }
    to->update_hooks();
}

/*
 * Function:    add_additional_spell_effect
 * Description: Each caster has a property that defines what spell effects
 *              are currently being maintained. This functions adds a spell
 *              effect to the list for the caster.
 */
public void
add_additional_spell_effect(object caster, object effect)
{
    object * effects = caster->query_prop(LIVE_O_MAINTAINED_EFFECTS);
    if (!pointerp(effects))
    {
        effects = ({ effect });
    }
    else
    {
        effects += ({ effect });
    }
    effects -= ({ 0 }); // clear deleted effects
    caster->add_prop(LIVE_O_MAINTAINED_EFFECTS, effects);
}

/*
 * Function name: abort_shapeshift
 * Description  : Stops the shapeshift effect
 */
public nomask void
abort_shapeshift()
{
    if(!interactive(query_shapeshift_body())) 
    {
        return;
    }
    
    object original_body = query_shapeshift_original_body();
    object shapeshift_body = query_shapeshift_body();
    original_body->move(environment(shapeshift_body), 1);
    original_body->set_new_living_name(original_body->query_real_name());
    shapeshift_body->hook_pre_shapeshift_return();
    
    if(!exec(original_body, shapeshift_body)) 
    {
        // Since the exec didn't succeed, move the original body back to the
        // holding area.
        original_body->move(find_object(OBJECT_HOLDING), 1);
        shapeshift_body->catch_tell("Unable to switch "
            + "you back to your original body. Please contact a "
            + "wizard.\n");
        return;
    }
    
    move_poisons(shapeshift_body, original_body);
    shapeshift_body->hook_post_shapeshift_return();
    shapeshift_body->move(find_object(OBJECT_HOLDING));
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
    if(objectp(query_shapeshift_body()) 
        && !interactive(query_shapeshift_body())) 
    {
        query_shapeshift_body()->remove_object();
    }
    
    ::remove_spell_effect_object();
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public nomask int
setup_spell_effect()
{
    mapping input = query_spell_effect_input();
    // Get the shape that we want to transform into from the spell input
    string shape_file = input["shape_file"];
    object shapeshift_spell = input["shapeshift_spell"];
    if (!strlen(shape_file) || !objectp(safely_load_master_file(shape_file)))
    {
        query_spell_effect_caster()->catch_tell("There is an issue with the "
            + "shapeshift into that form. Please contact a wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    setuid();
    seteuid(getuid());
    object target_shape = clone_object(shape_file);
    set_shapeshift_body(target_shape);
    if(!valid_shapeshift_target(target_shape)) 
    {
        target_shape->remove_object();
        shapeshift_spell->hook_cannot_clone_shape(query_spell_effect_caster(), target_shape->query_race_name());
        remove_spell_effect_object();
        return 0;
    }
    
    object original_body = query_shapeshift_original_body();
    if(!objectp(original_body) 
       || !interactive(original_body)) {
        target_shape->remove_object();
        query_spell_effect_caster()->catch_tell("The target for your "
            + "spell is not a real interactive player. Please contact "
            + "a wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    catch(OBJECT_HOLDING->teleledningsanka());
    object holding_room = find_object(OBJECT_HOLDING);
    if(!objectp(holding_room)) {
        target_shape->remove_object();
        query_spell_effect_caster()->catch_tell("There was an error "
            + "loading the holding area. Please contact a wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    // Setup the shapeshift target
    target_shape->set_spell_effect(this_object());
    target_shape->setup_for_player(original_body);
    target_shape->hook_prepare_shapeshift_target();
    
    // Have both the player and the target object in the room so messages can
    // be written properly.
    target_shape->move(environment(original_body), 1);
    target_shape->hook_pre_shapeshift_transform();
    
    if(!exec(target_shape, original_body)) 
    {
        target_shape->remove_object();
        query_spell_effect_caster()->catch_tell("Unable to switch "
            + "target to the shapeshifted object. Please contact a "
            + "wizard.\n");
        remove_spell_effect_object();
        return 0;
    }
    
    move_poisons(original_body, target_shape);
    copy_souls(original_body, target_shape);
    add_additional_spell_effect(target_shape, this_object());
    
    // Then move the old player object to the holding area
    target_shape->hook_post_shapeshift_transform();
    original_body->move(holding_room, 1);
    
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