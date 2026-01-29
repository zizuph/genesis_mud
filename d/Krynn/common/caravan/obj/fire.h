/*
*
*    Created by Vencar 07/10/2003
*
*    Copyright by Peter Bech Lund (Vencar)
*    10/2003
*
*    Damage done by the fire damage, in different
*    situations, to make it very easy to balance
*    the fire code one should ALWAYS make
*    definitions here instead of hardcoding values
*    around.
*
*/

/* Default values... */
#define FIRE_DEFAULT_DAMAGE            500
#define FIRE_DEFAULT_DOT_DAMAGE         28
#define FIRE_DEFAULT_LVL_START           3
#define FIRE_DEFAULT_DOT_TIME        180.0

/* Firewand if one fails to point it correctly */
#define FIREWAND_FAIL_DAMAGE           750
#define FIREWAND_FAIL_DOT_DAMAGE        45
#define FIREWAND_FAIL_LVL_START          4

/* Firewand effect if succeed at pointing it */
#define FIREWAND_DAMAGE                500
#define FIREWAND_DOT_DAMAGE             35
#define FIREWAND_LVL_START               3

/* Firewand recharge failure */
#define FIREWAND_RECHARGE_DAMAGE      1500
#define FIREWAND_RECHARGE_DOT_DAMAGE    60
#define FIREWAND_RECHARGE_START          5

/* Wagons on fire damage */
#define WAGON_FIRE_DAMAGE              150
#define WAGON_FIRE_DOT                  25
#define WAGON_FIRE_LVL_START             3

/* Firetrap on chest damage */
#define CHEST_FIRE_DAMAGE             1000
#define CHEST_FIRE_DOT                  35
#define CHEST_FIRE_LVL_START             3
