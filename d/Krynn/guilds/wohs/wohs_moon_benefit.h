/* The inheritable file that sets the aid bonuses to WoHS spells depending 
 * on the phases of the moons of magic.
 *
 *  Moon phase bonuses:
 *  Night of the Eye (all three moons full): 40% bonus
 *  
 *  Maximum benefit (25%): full
 *  partial benefit (10%): waxing 3/4, waning 3/4
 *  no benefit: waxing half, waning half, waning quarter, waxing quarter
 *  partial penalty (-10%): waning crescent, waxing crescent
 *  Full penalty (-25%): new 
 *  
 *  See ~guilds/wohs/doc/WoHS.txt for specifics.
 *  
 * Arman 2017
 *  
 */

#include <stdproperties.h>

#ifndef WOHS_STELLAR_ALIGNMENT
#define WOHS_STELLAR_ALIGNMENT   ("_wohs_stellar_alignment_spell_prop")
#endif

#ifndef WOHS_MANAGER
#define WOHS_MANAGER     ("/d/Krynn/guilds/sohm/lib/sohm_manager")
#endif
/*
 *  Returns 1 if teammember has the WOHS_STELLAR_ALIGNMENT prop
 */

int
check_stellar_alignment_benefit(object actor)
{
    object *team = actor->query_team_others() & 
        all_inventory(environment(actor)) + ({ actor });

    foreach(object teammember: team)
    {
        if(teammember->query_prop(WOHS_STELLAR_ALIGNMENT))
        {
            string moon_phase = WOHS_MANAGER->query_wohs_moon_phase_aid(teammember);

            // Moon phase affects the gaining of guild experience
            if(moon_phase == "night of the eye")
                return 1;
            else if(moon_phase == "maximum")
                return 1;
            else if(moon_phase == "partial")
                return 1;
            else if(moon_phase == "none")
                return 0;
            else
                return 0;
        }
    }

    return 0;
}

void
wohs_moon_benefit(string moon_bonus, string aid_type, float aid)
{
    if(aid_type == "combat_aid")
    {
    switch(moon_bonus)
       {
        case "night of the eye":
          set_spell_combat_aid(aid * 1.4);
          break;
        case "maximum":
          set_spell_combat_aid(aid * 1.25);
          break;
        case "partial":
          set_spell_combat_aid(aid * 1.1);
          break;
        case "none":
          set_spell_combat_aid(aid * 1.0);
          break;
        case "partial_penalty":
          set_spell_combat_aid(aid * 0.9);
          break;
        case "penalty":
          set_spell_combat_aid(aid * 0.75);
          break;
        }
     }
/*
    if(aid_type == "magic_resistance_aid")
    {
    switch(moon_bonus)
       {
        case "night of the eye":
          add_resistance(MAGIC_I_RES_MAGIC, ftoi(aid * 1.4));
          break;
        case "maximum":
          add_resistance(MAGIC_I_RES_MAGIC, ftoi(aid * 1.25));
          break;
        case "partial":
          add_resistance(MAGIC_I_RES_MAGIC, ftoi(aid * 1.1));
          break;
        case "none":
          add_resistance(MAGIC_I_RES_MAGIC, ftoi(aid * 1.0));
          break;
        case "partial_penalty":
          add_resistance(MAGIC_I_RES_MAGIC, ftoi(aid * 0.9));
          break;
        case "penalty":
          add_resistance(MAGIC_I_RES_MAGIC, ftoi(aid * 0.75));
          break;
        }
     }
*/

}