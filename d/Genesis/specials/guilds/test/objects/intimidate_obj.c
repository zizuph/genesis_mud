/*
 * Dragonarmy Intimidate Object
 *
 * Behaves like Dragonfear, but applies only indoors
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>
#include <files.h>
#include <ss_types.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public int      defence_effect;
public int      parry_effect;
public float    duration;

// Prototypes
public void     start_intimidate_effects(object player);
public void     remove_intimidate_effects(object player);

// Defines
#define INTIMIDATE_SH   ("/w/petros/test/objects/intimidate_sh")

public void
set_intimidate_duration(float seconds)
{
    duration = seconds;
}

public float
query_intimidate_duration()
{
    return duration;
}

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("da_intimidate_object");
    set_short("hidden dragonarmy intimidate object");
    set_long("Players should not see this object.\n");

    set_no_show();
    set_intimidate_duration(60.0);    
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
public void
enter_env(object to, object from)
{
    object * others;
    
    ::enter_env(to, from);
    
    // Make sure that we cannot have more than
    // one of these objects
    others = filter(all_inventory(to), &->id("da_intimidate_object"));
    others -= ({ this_object() });
    if (sizeof(others))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    if (to != from && IS_LIVING_OBJECT(to))
    {
        start_intimidate_effects(to);
        if (!to->has_intimidate_shadow())
        {
            setuid();
            seteuid(getuid());
            clone_object(INTIMIDATE_SH)->shadow_me(to);
        }
        // Remove the benefits after a certain amount of time
        set_alarm(query_intimidate_duration(), 0.0, remove_object);        
    }
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (old != dest && IS_LIVING_OBJECT(old))
    {
        remove_intimidate_effects(old);
        old->remove_intimidate_shadow();
    }
}

public void
start_intimidate_effects(object player)
{
    // Start out by removing all running effects
    remove_intimidate_effects(player);
    
    // Default values for defence and parry
    defence_effect = 20;
    parry_effect = 20;
    
    if (player->query_skill(SS_DEFENCE) - defence_effect < 0)
    {
        defence_effect = player->query_skill(SS_DEFENCE);
    }
    
    if (player->query_skill(SS_PARRY) - parry_effect < 0)
    {
        parry_effect = player->query_skill(SS_PARRY);
    }
    
    player->set_skill_extra(SS_DEFENCE, player->query_skill_extra(SS_DEFENCE)
                            - defence_effect);
    player->set_skill_extra(SS_PARRY, player->query_skill_extra(SS_PARRY)
                            - parry_effect);                            
}

public void
remove_intimidate_effects(object player)
{
    if (!defence_effect && !parry_effect)
    {
        return;
    }
    
    player->set_skill_extra(SS_DEFENCE, player->query_skill_extra(SS_DEFENCE)
                            + defence_effect);
    player->set_skill_extra(SS_PARRY, player->query_skill_extra(SS_PARRY)
                            + parry_effect);
    defence_effect = 0;
    parry_effect = 0;                            
}
