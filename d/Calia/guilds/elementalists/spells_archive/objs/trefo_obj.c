/*
 * Nourishment Basket Summoning Spell for the Elemental Clerics of Calia
 * 
 * This is the summoning spell that allows an Air Cleric to summon
 * a nourishment basket with some fruit and water in it. It is based
 * on the Genesis Magic System's generic summon spell.
 *
 * Created by Jaacar, March 2017
 */

#pragma strict_types

#include <const.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/summon_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_trefo_object_");
    set_short("summon spell object");    
    set_long("This is the standard summon spell's object. It exists "
        + "to keep track of the caster's maintained effects.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the summon spell.\n");
    set_spell_effect_desc("summoned nourishment");
    
    set_dispel_time(600); 
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
    object caster = query_spell_effect_caster();
    string caster_name = caster->query_real_name();
    if (objectp(caster))
    {
        caster->catch_msg("Lady Gu answers your prayer and a large basket "+
            "appears in your hands. Knowing it won't last long, you should "+
            "gather everything out of it quickly before it disappears.\n");
    	
        tell_room(environment(caster), QCTNAME(caster)+" is suddenly holding "+
            "a large basket in "+caster->query_possessive() + " hands.\n",
            caster);
         
    }
    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
               
}