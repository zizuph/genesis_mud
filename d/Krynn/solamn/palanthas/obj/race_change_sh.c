
inherit "/std/shadow";

#include <formulas.h>
#include <options.h>
#include <stdproperties.h>


/*
 * Function name:   second_life
 * Description:     Handles all that should happen to a dying player.
 * Arguments        object killer - the object that killed us.
 * Returns:         True if the living object should get a second life
 */
public int
second_life(object killer)
{
    if (shadow_who->query_prop(TEMP_BACKUP_BRIEF_OPTION))
    {
        shadow_who->set_option(OPT_BRIEF, 0);
        shadow_who->remove_prop(TEMP_BACKUP_BRIEF_OPTION);
    }

    shadow_who->set_m_in(F_GHOST_MSGIN);
    shadow_who->set_m_out(F_GHOST_MSGOUT);

    shadow_who->set_intoxicated(0);
    shadow_who->set_stuffed(0);
    shadow_who->set_soaked(0);
    shadow_who->set_mana(shadow_who->query_max_mana());

    shadow_who->stop_fight(shadow_who->query_enemy(-1)); /* Forget all enemies */

    this_object()->death_sequence();
    shadow_who->save_me(); /* Save the death badge if player goes linkdead. */

    return 1;
}