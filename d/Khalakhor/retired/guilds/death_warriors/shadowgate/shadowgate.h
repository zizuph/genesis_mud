/*
 * shadowgate.h
 *
 * Header file for use with the Death Warrior's Shadowgate.
 *
 * Khail - May 5/97
 */

#ifndef SHADOWGATE_DEFINES
#define SHADOWGATE_DEFINES

/*
 * Paths
 */
#define PATH          "/d/Khalakhor/guilds/death_warriors/shadowgate/"
#define SHADOWGATE    PATH + "shadowgate"
#define SHADOWSTONE   PATH + "shadowstone"

/*
 * Skills
 *
 * THE_TALENT - "The talent", the ability of the Death Warriors to 
 *              use Shadowgates.
 */
#define THE_TALENT    146001

/*
 * Props
 *
 * LIVE_I_USED_SHADOWGATE - Used to mark players who entered 
 *                          Shadowgate using a shadowstone, as opposed
 *                          returning from linkdeath, for example.
 */
#define LIVE_I_USED_SHADOWGATE  "_live_i_used_death_warrior_shadowgate"

/*
 * Option toggles
 *
 * ENABLE_MEMORY - Define this to have Shadowgate remember shadow
 *                 exits beyond armageddon, updates, etc.
 * DEBUG_SHADOWGATE - Define this to show debugging messages and activate
 *                    or deactivate certain routines.
 */
#define ENABLE_MEMORY
#define DEBUG_SHADOWGATE

/*
 * Light limits on the shadowstones.
 *
 * SHATTER_LIGHT_LIMIT - The highest light level a shadowstone can
 *                       survive in.
 * ACTIVE_LIGHT_LIMIT - The highest light level a shadowstone will
 *                      function in.
 */
#define SHATTER_LIGHT_LIMIT  5
#define ACTIVE_LIGHT_LIMIT   2

/*
 * Misc.
 *
 * DIRS - To change the number of possible shadow exits, add or
 *        remove directions to this define.
 * MANA_COST_GATE - Base mana cost to enter Shadowgate with a 
 *                  shadowstone.
 * FATIGUE_GATE_IN - Base fatigue for entering Shadowgate using a
 *                   shadowgate.
 * FATIGUE_GATE_OUT - Base fatigue for exiting Shadowgate through
 *                    a shadow exit.
 * MANA_COST_PART - Base mana cost to 'view' the destination of a
 *                  shadow exit from Shadowgate.
 */
#define DIRS              ({"north", "south", "east", "west"})
#define MANA_COST_GATE    100
#define FATIGUE_GATE_IN   10
#define FATIGUE_GATE_OUT  10
#define MANA_COST_PART    50

#endif
        