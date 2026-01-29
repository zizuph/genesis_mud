/*
 * /d/Calia/guilds/scop/specials/resurrection_sh.c
 *
 * This is the resurrection shadow. It prevents true death from
 * affecting a person until 30 minutes after the death. Thus
 * allowing them time to get back to the Temple and for a Cleric
 * to perform the resurrection ceremony.
 *
 * Created by Petros, July 2008
 */
          
#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include <std.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "../defs.h"

// Defines
// Gives 30 minutes for the person to be resurrected
#define RESURRECTION_TIME_LIMIT     1800.0

// Global variables
object  my_killer   = 0;
int     death_alarm = 0;

// Prototypes
public void         proceed_with_death();

/*
 * Function name:   second_life
 * Description:     Handles all that should happen to a dying player.
 * Arguments        object killer - the object that killed us.
 * Returns:         True if the living object should get a second life
 */
public int
second_life(object killer)
{
    // This function does everything the original second_life call in
    // death_sec.c does, except for the following:
    // 1. It does not scar
    // 2. It does not reduce stats
    // 3. It does not perform the death sequence.
    if (shadow_who->query_wiz_level())
    {
        return 0;
    }
    
    my_killer = killer;
    
    shadow_who->set_m_in(F_GHOST_MSGIN);
    shadow_who->set_m_out(F_GHOST_MSGOUT);

    shadow_who->set_intoxicated(0);
    shadow_who->set_stuffed(0);
    shadow_who->set_soaked(0);
    shadow_who->set_mana(shadow_who->query_max_mana());

    shadow_who->stop_fight(shadow_who->query_enemy(-1)); /* Forget all enemies */

    tell_object(this_object(), F_DEATH_MESSAGE);

    tell_object(this_object(), "A gentle silvery tendril appears from the "
              + "darkness and grows to envelop you. From the shadows "
              + "behind, you can see Death standing and waiting, but you "
              + "know that for now, you are protected by the powers of "
              + "the Elemental of Spirit, Psuchae.\n");
    
    death_alarm = set_alarm(RESURRECTION_TIME_LIMIT, 0.0, 
                            &proceed_with_death());
    
    return 1;
}

public void
proceed_with_death()
{
    // Given that the time limit expired on the time to resurrect, we
    // continue with the original death, which was paused.
    tell_object(this_object(), "From the edge of your perception, you "
              + "begin to detect a graying of the silvery substance that "
              + "envelops you. Gradually, it fades to nothingness, and "
              + "you feel a familiar sensation as you relive the "
              + "experience from just a little while ago.\n");
    
    shadow_who->second_life(my_killer);
}

public int
query_time_remaining()
{
    mixed * call;
    
    call = get_alarm(death_alarm);
    if (!call)
    {
        return 0;
    }
    
    if (floatp(call[2]))
    {
        // The alarm should return a floating point value.
        return ftoi(call[2]);
    }
    
    // Should never get here.
    return 0;
}
