/*
 * Tutorial Quest Orb
 *
 * Specific quest orb, just for the Tutorial. This will only list the
 * quests that are applicable by masking the get_eligible_quests
 * function.
 *
 * Created February 2010, by Petros
 */
 
#pragma strict_types

// Inherits for Validation Functions
inherit "/d/Sparkle/area/city/obj/quest_orb";

/*
 * Function name:       create_object
 * Description  :       creates the object.
 */
public void
create_object()
{
    ::create_object();
        
    set_orb_domain("sparkle");
}

/* Function name:       get_eligible_quests
 * Description  :       Helper function to assist in retrieving
 *                      all the quests the player is eligible for
 *                      in a particular domain. Used for both printing
 *                      and giving hints
 * Arguments    :       domain - domain to check quests in
 *                      player - player to test bits in
 * Returns      :       subset of the quests that they're eligible for
 */
public mixed
get_eligible_quests(string domain, object player)
{
    mixed * eligible_quests, * quests;
    quests = ::get_eligible_quests(domain, player);
    eligible_quests = ({ });
        
    // We filter out the quests that are not in the tutorial
    foreach (string * details : quests)
    {
        if (wildmatch("Tutorial *", details[1]) == 1)
        {
            eligible_quests += ({ details });
        }
    }
    
    return eligible_quests;
}

