/*
 * Achievement Shadow
 *
 * This shadow keeps track of events that happen to players which may
 * trigger an achievement badge. Examples would be killing an npc or
 * gaining a particular skill.
 *
 * Created by Petros, November 2013
 */

#pragma strict_types

#include <files.h>
#include <macros.h>

inherit "/std/shadow";

// Defines
#define  BRACELET_UNIQUE_ID           "_genesis_achievement_bracelet"
#define  ACHIEVEMENT_MASTER           "/d/Genesis/specials/achievements/achievement_master"

// Global Variables
public object       source_bracelet_object = 0;

public void
remove_achievement_shadow()
{
    remove_shadow();
}

public int
has_achievement_shadow()
{
    return 1;
}

public void
set_bracelet_object(object obj)
{
    source_bracelet_object = obj;
}

public object
query_bracelet_object()
{
    if (!objectp(source_bracelet_object))
    {
        return present(BRACELET_UNIQUE_ID, shadow_who);
    }
           
    return source_bracelet_object;
}

// Shadowed Functions

/*
 * Function name: notify_you_killed_me
 * Description  : This routine is called in the killer when it causes the death
 *                of the victim. It can be used for additional processing.
 *
 *                This routin does not actually exist. It is a trick to fool
 *                the document maker.
 * Arguments    : object victim - the victim we caused to perish.
 */
public void
notify_you_killed_me(object victim)
{
    ACHIEVEMENT_MASTER->trigger_event_enemy_kill(shadow_who, victim);
    // Call the shadowed function
    shadow_who->notify_you_killed_me(victim);
}

