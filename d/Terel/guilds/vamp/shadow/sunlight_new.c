/*
 * Sunlight Shadow Code
 *
 * This file is included in the Vampire shadow, and controls the sunlight
 * effect. This effect was rewritten from the original one because the
 * original effect was mostly cosmetic, with no real drawbacks and penalties.
 *
 * Created by Petros, October 2009 
 */
 
#include "../defs.h";

#include <stdproperties.h>

// Global Variables
public int Con_drained;
public int Last_notify;

// Defines
#define GENESIS_TIMEKEEPER      "/d/Sparkle/area/city/lib/genesis_timekeeper"
// Vampires can normally withstand minimal levels of sunlight exposure that 
// may occur during the night. Dawn/Dusk is where they begin to burn
#define VAMP_SUNLIGHT_TOLERANCE 5
// We define that a Vamp at highest sunlight can lose all CON within 90 seconds.
#define CON_DRAIN_TIME          90.0

public void
process_outside_sunlight(object player, object room)
{
    if (Con_drained == 0)
    {
        // The vampire is not currently suffering from any ill effects from
        // the sun. Just return.
        return;
    }
    
    // Being outside of the sun's rays, the Vampire now gains back
    // their con slowly.
    if (Last_notify > 0)
    {
        player->catch_msg("You find temporary refuge from the burning "
            + "sun.\n");
    }
    Last_notify = 0;
    
    int heal_amt = 0;
    if (wildmatch(ROOM_DIR + "meld_cont", MASTER_OB(room)))
    {
        // When melding, a Vampire simply gains minimal relief from the
        // sunlight. The heal rate is very slow.
        send_debug_message("vamp_sunlight", "Currently melded and "
            + "healing slowly from the burns.");         
        heal_amt = 1;
    }
    else
    {    
        // Heal 3% of con per 5 seconds outside of the sun. This results in
        // full recovery in 250 seconds (approx 4 minutes).
        heal_amt = max(1, player->query_base_stat(SS_CON) / 33);
    }
        
    // First remove the previous reduction.
    player->set_stat_extra(SS_CON, player->query_stat_extra(SS_CON) + Con_drained);
    // Set the new Con_drained amount
    Con_drained = max(0, Con_drained - heal_amt);
    // Set the new stat extra
    player->set_stat_extra(SS_CON, player->query_stat_extra(SS_CON) - Con_drained);
    send_debug_message("vamp_sunlight", "Outside of sunlight and recovering "
        + heal_amt + " con points with a current loss of " + Con_drained + ".");
}

public void
process_inside_sunlight(object player, object room, int sunlight)
{
    // We want to reduce CON by percentages. Meaning, a small vamp and
    // a big vamp will lose the same percentage of CON. In general, we
    // set the amount of time it takes to lose all CON at 30 sunlight
    // levels to be 90 seconds.
    float max_con = itof(player->query_base_stat(SS_CON));
    float max_sunlight = itof(30 - VAMP_SUNLIGHT_TOLERANCE);
    float max_reduction = itof(sunlight - VAMP_SUNLIGHT_TOLERANCE) * max_con 
                          / max_sunlight;
    float reduction = max(1.0, 5.0 * max_reduction / CON_DRAIN_TIME);
    
    // First remove the previous reduction.
    player->set_stat_extra(SS_CON, player->query_stat_extra(SS_CON) + Con_drained);
    // Set the new Con_drained amount. Can't go below 1, so we use query_stat.
    Con_drained = min(player->query_stat(SS_CON) - 1, 
                      Con_drained + ftoi(reduction));    
    // Set the new stat extra
    player->set_stat_extra(SS_CON, player->query_stat_extra(SS_CON) - Con_drained);
    send_debug_message("vamp_sunlight", "In " + sunlight + " levels of "
        + "sunlight and losing " + ftoi(reduction) + " con points for a total loss "
        + "of " + Con_drained + ".");
    
    if (Last_notify % 5 == 0 || !random(4))
    {
        int percentage_lost = Con_drained * 100 / ftoi(max_con);
        string burn_message;
        switch (percentage_lost)
        {
        case 0..10:
            burn_message = "Your skin burns under the heat of the sun.\n";
            break;
            
        case 11..25:
            burn_message = "Your burned skin begins to crackle and fall "
                + "apart under the continued assault of the sun.\n";
            break;    
            
        case 26..50:
            burn_message = "You are in excruciating pain as you suffer "
                + "from the searing heat of the sun.\n";
            break;
            
        case 51..75:
            burn_message = "You feel yourself losing control of your limbs "
                + "as your very core is being disintegrated by the flaming "
                + "sun.\n";
            break;
            
        case 76..90:
            burn_message = "Parts of your body burst into flame as you "
                + "continue to be exposed to the sun.\n";
            break;
            
        case 91..100:
            burn_message = "Flames wrack your entire body and you convulse "
                + "with pain as your whole body disintegrates.\n";
            break;
        }
        
        player->catch_msg(burn_message);
    }
    ++Last_notify;
    
    // Reduce a minimal amount of hit points.
    player->heal_hp(-sunlight / 5);
    
    if (player->query_hp() <= 0)
    {
        player->catch_msg("The intensity of the sun consumes your body.\n");
        player->do_die(room);
    }    
}

/*
 * Function:    query_sunlight_level
 * Description: This checks a room for the amount of sunlight that is in
 *              it. It uses the Genesis Timekeeper's code to do most of
 *              the sunlight calculations.
 */
public int
query_sunlight_level(object room)
{
    object player = shadow_who;
    
    setuid();
    seteuid(getuid());    
    int sunlight = GENESIS_TIMEKEEPER->query_sunlight(player);
    
    if (sunlight < VAMP_SUNLIGHT_TOLERANCE
        || room->query_prop(OBJ_I_LIGHT) <= 0)
    {
        // If the room itself is dark, or sunlight levels are too low,
        // we allow the vampire to heal from any burning that they may
        // have encountered by returning 0 for the sunlight levels
        return 0;
    }
    
    return sunlight;    
}

/*
 * Function:    check_sunlight
 * Description: This is the function called by the repeating alarm in the
 *              shadow every 5.0 seconds. It will drain the vampire if it
 *              finds the vampire exposed in sunlight.
 */
public void 
check_sunlight()
{
    object player = shadow_who;
    object room = environment(player);
    
    if (!objectp(player) || !objectp(room))
    {
        // Should never happen
        return;
    }    
    
    setuid();
    seteuid(getuid());    
    int sunlight = query_sunlight_level(room);
    
    if (!sunlight)
    {
        process_outside_sunlight(player, room);
        return;
    }
    
    process_inside_sunlight(player, room, sunlight);    
}

/*
 * Function:    query_sunlight_damage
 * Description: Returns how much the con drain has been due to the
 *              effects of the sun.
 */
public int
query_sunlight_damage()
{
    return Con_drained;
}
