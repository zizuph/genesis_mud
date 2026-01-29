/*
 * Cast Shadow Wall Object - based on the Standard Blind Object
 *
 * It tracks that a target has cast a Shadow Wall
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, February 2017.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <time.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

object shadow_wall = 0;
int wall_time;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_cast_shadow_wall_object_");
    set_short("cast shadow wall spell object");    
    set_long("This is the standard cast shadow wall spell object. " +
             "It means this person has an existing shadow wall already "+
             "cast.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the shadow wall spell.\n");
    set_spell_effect_desc("shadow wall");  
    set_dispel_time(30);  
}   

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    return 1;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    string direction = caster->query_prop("_shadow_wall_cast");
    
    shadow_wall = clone_object(ELEMENTALIST_SPELL_OBJS + "tihosskias_wall_obj");

	if (objectp(caster))
    {
		caster->catch_msg("You wave your arms in an intricate design forming " +
	                      "a shadow. The shadow shatters throwing shadowy " +
	                      "tendrils in your carefully chosen direction. "+
	                      "As the tendrils stop, a mesh of shadows pervade " +
	                      "the area leading " + direction + ".\n");
	
	    tell_room(environment(caster), QCTNAME(caster)+" waves "+
	        caster->query_possessive() +
	        " arms in an intricate design forming a shadow. The shadow " +
	        "shatters throwing shadowy tendrils in a carefully chosen " +
	        "direction. As the tendrils stop, a mesh of shadows pervade " +
	        "the area leading " + direction + ".\n", caster);
	    
	    caster->remove_prop("_shadow_wall_cast");
	    caster->remove_prop("_shadow_wall_time");
	}

    wall_time = (caster->query_skill(SS_SPELLCRAFT) + 
        caster->query_skill(SS_ELEMENT_LIFE) +
        caster->query_skill(SS_FORM_CONJURATION));
    wall_time = MIN(wall_time, TIHOSSKIAS_TIME);
     
    shadow_wall->set_blocked_exit(direction);
    shadow_wall->set_caster(caster);
    shadow_wall->move(environment(caster),1);    
    shadow_wall->set_wall_duration(wall_time);
    shadow_wall->start();
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object caster = query_spell_effect_caster();
    
    if (objectp(caster))
    {
    	int cooldown = caster->query_prop(LIVE_I_TIHOSSKIAS_CAST);
	    if (cooldown) 
	    {
	    	if (cooldown <= time())
	    	{
		    	caster->catch_msg("You feel that you can use the gift "+
		    		"of Tihosskias again.\n");
		    }		    
		}
	}
     
    shadow_wall->remove_object();
           
}
