#ifndef _BRAWL_DEFINITIONS_
#define _BRAWL_DEFINITIONS_

/* Uncomment the next two defines for debugging mode. */
//#define BRAWLDEBUG
//#define BRAWLDEBUG_MSG(x) \
//                   find_player("alto")->catch_tell("DEBUG: " + x + "\n");

/* Comment out the next define for debugging mode. */
#define BRAWLDEBUG_MSG(x)

#ifdef DEBUG
static int *Brawl_Stats = allocate(23);
static int *Fail_Stats  = allocate(23);
#endif
 
/* Set this prop in an NPC to prevent it from being brawled at all. */
#define RANGER_M_NOT_BRAWL       "_ranger_m_not_brawl"
#define RANGER_I_NOT_BRAWL       "_ranger_i_not_brawl"

/* Set this prop in an NPC if you want to prevent blinding. */
#define RANGER_M_NOT_BLIND       "_ranger_m_not_blind"
#define RANGER_I_NOT_BLIND       "_ranger_i_not_blind"

/* Set this prop in an NPC to prevent disarming. */
#define RANGER_M_NOT_DISARM      "_ranger_m_not_disarm"
#define RANGER_I_NOT_DISARM      "_ranger_i_not_disarm"

/* Set this prop in an NPC to prevent tripping. */
#define RANGER_M_NOT_TRIP        "_ranger_m_not_trip"
#define RANGER_I_NOT_TRIP        "_ranger_i_not_trip"

/*
 * The level of preparation of a brawl this player is in.
 * 0                    = no preparation, he can brawl again
 * PREPARE_BRAWL        = he is preparing a brawl.
 * RECOVER_BRAWL        = he is recovering from the brawl
 * MOVED_WHILE_BRAWLING = he moved out of the room while preparing a brawl.
 */
#define RANGER_I_PREPARE_BRAWL   "_ranger_i_prepare_brawl"

/* The location where preparation was started */
#define RANGER_O_START_BRAWL     "_ranger_o_start_brawl"

/* The type of brawl a player wants to perform */
#define RANGER_I_BRAWL_TYPE      "_ranger_i_brawl_type"

/* The exact time() the brawl was started. */
#define RANGER_I_TIME_BRAWL      "_ranger_i_time_brawl"

/* The time the player has to recover to brawl again. */
#define RANGER_I_TIME_RECOVER    "_ranger_i_time_recover"

/* How good someone is in recognizing when someone prepares to
 * brawl. This value is compared to brawl and sneak skills:
 */
#define RANGER_I_RECOGNIZE_BRAWL "_ranger_i_recognizing_brawl"

/* Some props for keeping track of alarm-ids */
#define RANGER_DB_AID            "_ranger_do_brawl_alarm_id"
#define RANGER_CBA_AID           "_ranger_can_brawl_again_alarm_id"
 
#define PREPARE_BRAWL            1
#define RECOVER_BRAWL            2
#define MOVED_WHILE_BRAWLING     3
 
#define BRAWL_UNKNOWN            0
#define BRAWL_BLIND              1
#define BRAWL_DISARM             2
#define BRAWL_TRIP               3
#define BRAWL_KNEE               4
 
#define MAX_TIME_TO_RECOVER      35

/* directly following from the function */
#define MIN_TIME_TO_RECOVER      15
#define MAX_TIME_BRAWL           22
#define MIN_TIME_BRAWL           7
#define TIME_BEFORE_ACTUAL_BRAWL 6

/* read BUG in 'man time' */
#define TIME_TO_PROTECT_ERRORS   20
#define BRAWL_CHOOSE_MIN         90
#define BRAWL_CHOOSE_CHANCE      66
#define BRAWL_BASE_TRIP_RATE     20
 
/* Max rate increase for BRAWL_I_RECOGNIZE_BRAWL (at awareness of  100): */
#define BRAWL_RECOGNIZE_RATE     3

/* Time to brawl again after a succesful brawl. */
#define TIME_TO_BRAWL_AGAIN(o)   (MIN(MAX((MAX_TIME_TO_RECOVER -       \
                                 ((o->query_skill(SS_BRAWLING)) / 5)), \
                                 MIN_TIME_TO_RECOVER),                 \
                                 MAX_TIME_TO_RECOVER))

/* Time to recover is someone prevented your brawl. */
#define TIME_AFTER_BRAWL_FUMBLE(o) (MAX((TIME_TO_BRAWL_AGAIN(o) / 2), \
                                   MIN_TIME_TO_RECOVER))
#define BRAWL_BUG_LOG            "brawl"

#define BLIND_OBJECT             (RANGERS_OBJ + "blind_ob")
#define DISARM_OBJECT            (RANGERS_OBJ + "disarm_ob")

#endif _BRAWL_DEFINITIONS_
