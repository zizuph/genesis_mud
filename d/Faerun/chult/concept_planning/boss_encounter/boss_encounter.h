/*  
 *  Generic Boss Encounter definitions
 *
 *  Nerull 2018.
 *
 */

#ifndef __RAIDBOSS_DEFINITIONS__
#define __RAIDBOSS_DEFINITIONS__

#define BOSS_DIR   "/d/Faerun/chult/concept_planning/boss_encounter/"


// Boss special properties -----------------------------------------------

// Nemezis - Can't be hurt by any means. A player 
// can only run/flee from the encounter in order to
// survive.
#define NEMEZIS                                  0

// Breaks the weapon if enabled vs nonmagical
// weapons.
#define NON_MAGIC_BREAK_WEAPON                   0

// Need an undead slayer weapon to harm the monster
#define WEAPON_UNDEAD_SLAYER_REQUIRED            0

// Boss regens to 100% health if it no longer is 
// engaged in combat.
#define MAX_HEALTH_WHILE_NOT_IN_COMBAT           1
//------------------------------------------------------------------------



// Boss hitpoints
#define BOSS_HITPOINTS                       30000


// Boss xpfactor (in percent)
#define BOSS_EXP_FACTOR                        100


// Boss aggressive or not. 1 if aggressive.
#define BOSS_AGGRESSIVE                          1


// Boss weight in grams
#define BOSS_WEIGHT                        1100000


// Boss height in centimeters
#define BOSS_HEIGHT                            412


// Stats for boss
#define BOSS_STR                               410
#define BOSS_DEX                               210
#define BOSS_CON                               320
#define BOSS_INT                               143
#define BOSS_WIS                               120
#define BOSS_DIS                               280


// Boss Hit for Unarmed combat
#define BOSS_HIT_1                              55
#define BOSS_HIT_2                              55
#define BOSS_HIT_3                              55
#define BOSS_HIT_4                              55
#define BOSS_HIT_5                              55


// Boss Pen for Unarmed combat
#define BOSS_PEN_1                              55
#define BOSS_PEN_2                              55
#define BOSS_PEN_3                              55
#define BOSS_PEN_4                              55
#define BOSS_PEN_5                              55


// Boss chance of usage per combat round in %
#define BOSS_USAGE_1                            80
#define BOSS_USAGE_2                             0
#define BOSS_USAGE_3                             0
#define BOSS_USAGE_4                             0
#define BOSS_USAGE_5                             0


// AC of boss encounter
#define BOSS_HEAD                               80
#define BOSS_RARM                               80
#define BOSS_LARM                               80
#define BOSS_BODY                               80
#define BOSS_LEGS                               80


// BOSS SPECIAL VARIABLES  (first value + (random(second value)))
#define BOSS_SPECIAL_HITME_DEFAULT_VALUE      1000
#define BOSS_SPECIAL_HITME_RANDOM_ADD_VALUE    200


// Random(value). If for example 5, Boss will execute a special
// every 5 combat round.
#define BOSS_SPECIAL_SPEED                      5


// Boss special combat effect alarm. This function serves as a special
// encounter event that runs in paralell regardless if the boss is stunned
// or not.
// 
// Examples:
//
//    1. Players have x time to defeat the encounter before it goes into
//       enraged modus
//
//    2. Boss performs special events (aoe blasts, time warp effects etc)
//
//    3. Boss summons minions every tick
//
//    4. Boss uses abilities (legendary actions, or lair actions)
//             
//    5. Boss regenerates to full HP if it's no longer engaged
//
//    6. AOE paralyze objects for boss and players to enable scripted
//       dialogues, or phazed steps
//
//
#define BOSS_CROUTINE_ALARM                    10.0



//-----------------------ITEM REWARDS AND LOGGING----------------------------
// Boss encounter loot drop directory
#define B_DROPDIR          "/d/Faerun/mere/npcs/boss_encounter/drop_loot_dir/"


// Epic item drop log
#define DROP_LOG(x,y)       write_file(B_DROPDIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#endif

