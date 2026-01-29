/*
 * Summon Shadow
 * 
 * This is a default shadow for the summoning spell that adds a shadow
 * to each summoned monster. The purpose of this shadow is so that when
 * the summoned npc is destroyed/killed, it will also end the maintained
 * spell effect.
 *
 * Created by Petros, May 2011
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include "defs.h"

// Global Variables
public object      spell_object = 0;

/*
 * Function:    has_summon_shadow
 * Description: Indicates that the object shadowed has the summoned shadow
 *              on them.
 */
public int
has_summon_shadow()
{
    return 1;
}

/*
 * Function:    remove_summon_shadow
 * Description: Removes this particular shadow
 */
public void
remove_summon_shadow()
{
    remove_shadow();
}

/*
 * Function:    set_spell_object
 * Description: Sets the spell object that is associated with this
 *              shadow.
 */
public void
set_spell_object(object obj)
{
    spell_object = obj;
}

/*
 * Function:    get_spell_object
 * Description: Returns the spell object that is associated with
 *              this particular shadow
 */
public object
get_spell_object()
{
    return spell_object;
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    if (objectp(spell_object))
    {
        spell_object->summon_object_killed(killer);
    }
    
    shadow_who->do_die(killer);
}

public void
remove_object()
{
    if (objectp(spell_object))
    {
        spell_object->summon_object_killed(this_player());
    }
    
    shadow_who->remove_object();
}
