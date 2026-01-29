/*
 * Neidar Tireless Shadow
 * 
 * Neidar never run out of fatigue while actively in combat.
 *
 * Petros, April 2009
 */
 
#pragma strict_types 

inherit "/std/shadow";

// DEFINES
//   Tireless lasts for 30 seconds past the last combat hit
#define TIRELESS_DURATION   30
//   Announce tireless every 15 seconds
#define TIRELESS_ANNOUNCE   15

// Global Variables
public int      last_announce_time = 0;

// Prototypes
public void     announce_tireless(object player, int tireless_value, int current_fatigue);

public int
has_tireless_shadow()
{
    return 1;
}

public void
remove_tireless_shadow()
{
    remove_shadow();
}

/*
 * Function:    query_fatigue
 * Description: Returns the fatigue value of the Neidar. When in tireless
 *              mode, they will have a minimum of 25% of their fatigue
 *              value
 */
public int
query_fatigue()
{    
    int current_fatigue, max_fatigue, tireless_value;    

    current_fatigue = shadow_who->query_fatigue(); 
    if (shadow_who->query_combat_time() + TIRELESS_DURATION < time())
    {
       // Tireless ability works for TIME_DURATION seconds past the 
       // last combat hit.
       return current_fatigue;
    }
    
    max_fatigue = shadow_who->query_max_fatigue();
    tireless_value = max(current_fatigue, max_fatigue / 4);
    set_alarm(0.0, 0.0, 
        &announce_tireless(shadow_who, tireless_value, current_fatigue));
    
    return tireless_value;   
}

/*
 * Function:    announce_tireless
 * Description: Announces to the Neidar that their tireless effect
 *              in acting when they have less fatigue than than
 *              25%. Announcements are done every TIRELESS_ANNOUNC
 *              seconds so that they will not be spammed.
 */
public void
announce_tireless(object player, int tireless_value, int current_fatigue)
{
    if (tireless_value > current_fatigue
        && last_announce_time + TIRELESS_ANNOUNCE < time())
    {
        // We tell the neidar that they are tireless
        last_announce_time = time();
        if (shadow_who->query_attack())
        {
            shadow_who->catch_tell("\nThe adrenaline rush of battle "
                + "keeps you from feeling the effects of your "
                + "fatigue.\n\n");
        }
        else
        {
            shadow_who->catch_tell("\nThough you are not in battle, you "
                + "still feel tireless from your previous "
                + "engagement.\n\n");
        }
    }
}
