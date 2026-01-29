
/* 
    ~Calia/fireball/fireball.h 

    The main include file for Fireball

    Coded by Maniac@Genesis 1997/1998/1999

    Copyright (C) Miguel leith 1997/1998/1999  
*/ 

#ifndef FIREBALL_DEFS
#define FIREBALL_DEFS

/* directories */ 
#define FIREBALL_DIR "/d/Calia/fireball/" 
#define FIREBALL_HELP (FIREBALL_DIR + "help/")
#define FIREBALL_ARENA (FIREBALL_DIR + "arena/") 
#define FIREBALL_SURROUND (FIREBALL_DIR + "surround/") 
#define FIREBALL_TEXT (FIREBALL_DIR + "text/") 
#define FIREBALL_STAND FIREBALL_SURROUND
#define FIREBALL_WALKWAY FIREBALL_SURROUND
#define FIREBALL_INHERIT (FIREBALL_DIR + "inherit/") 
#define FIREBALL_RESULTS (FIREBALL_DIR + "results/")

/* inherit */ 
#define FIREBALL_ARENA_ROOM (FIREBALL_INHERIT + "arena_room")
#define FIREBALL_STAND_ROOM (FIREBALL_INHERIT + "stand_room")
#define FIREBALL_OUTSIDE_ROOM (FIREBALL_INHERIT + "outside_room")
#define FIREBALL_WALKWAY_ROOM (FIREBALL_INHERIT + "walkway_room")
#define FIREBALL_MONSTER (FIREBALL_INHERIT + "fireball_monster") 
#define FIREBALL_REPORTER (FIREBALL_INHERIT + "reporter")
#define FIREBALL_UTILS (FIREBALL_INHERIT + "utils") 
#define FIREBALL_POSITIONING (FIREBALL_INHERIT + "positioning")
#define FIREBALL_VIEW_SUPPORT (FIREBALL_INHERIT + "view_support")
#define FIREBALL_HELP_SUPPORT (FIREBALL_INHERIT + "help_support")
#define FIREBALL_FORMATION_FILE (FIREBALL_INHERIT + "formation")
#define FIREBALL_NPC_CONTROL (FIREBALL_INHERIT + "team_manager") 

/* special rooms */ 
#define FIREBALL_FOYER (FIREBALL_SURROUND + "foyer")

/* special */ 
#define FIREBALL_SPECIAL (FIREBALL_DIR + "special/") 
#define FIREBALL_ARENA_MAKER (FIREBALL_SPECIAL + "arena_maker")
#define FIREBALL_PLAYER_SOUL (FIREBALL_SPECIAL + "player_soul")
#define FIREBALL_GAME_HANDLER (FIREBALL_SPECIAL + "game_handler")
#define FIREBALL_TEAM_HANDLER (FIREBALL_SPECIAL + "team_handler")
#define FIREBALL_SCHEDULE_HANDLER (FIREBALL_SPECIAL + "schedule_handler")
#define FIREBALL_DAGGER_FORMATION_FILE (FIREBALL_SPECIAL + "dagger_formation")
#define FIREBALL_SCORPION_FORMATION_FILE (FIREBALL_SPECIAL + "scorpion_formation")
#define FIREBALL_SICKLE_FORMATION_FILE (FIREBALL_SPECIAL + "sickle_formation")
#define FIREBALL_ARROW_FORMATION_FILE (FIREBALL_SPECIAL + "arrow_formation")
#define FIREBALL_CMDSOUL (FIREBALL_SPECIAL + "fireball_cmdsoul")

/* obj */ 
#define FIREBALL_OBJ (FIREBALL_DIR + "obj/") 
#define FIREBALL_PLAYER_OBJ (FIREBALL_OBJ + "player_obj")

/* save */ 
#define FIREBALL_SAVE (FIREBALL_DIR + "save/") 
#define FIREBALL_GAME_SAVE (FIREBALL_SAVE + "game_save")
#define FIREBALL_SCHEDULE_SAVE (FIREBALL_SAVE + "schedule_save")
#define FIREBALL_LOCKER_SAVE (FIREBALL_SAVE + "locker_save") 

/* macros */ 
#define FIREBALL_BALL_ID "_fireball_ball_id"
#define FIREBALL_PLAYER_OBJ_ID "_fireball_player_obj_id"

#define FIREBALL_RACE_MOVES \
             ([ "elf" : "glides", \
                "dwarf" : "hastens", \
                "hobbit" : "scampers", \
                "gnome" : "scurries", \
                "human" : "runs", \
                "goblin" : "lopes", \
                "ogre" : "thunders" ])

#define FIREBALL_RACE_MOVE \
             ([ "elf" : "glide", \
                "dwarf" : "hasten", \
                "hobbit" : "scamper", \
                "gnome" : "scurry", \
                "human" : "run", \
                "goblin" : "lope", \
                "ogre" : "thunder" ])

#define FIREBALL_KICKS ({ ({ "taps", "knocks", "rolls" }), \
                          ({ "kicks", "strokes", "directs" }), \
                          ({ "boots", "drives", "strikes" }), \
                          ({ "belts", "launches", "punts"}) }) 

#define FIREBALL_KICK ({ ({ "tap", "knock", "roll" }), \
                         ({ "kick", "stroke", "direct" }), \
                         ({ "boot", "drive", "strike" }), \
                         ({ "belt", "launch", "punt"}) }) 

/* pitch areas */ 
#define FIREBALL_WEST_POINT "West Point"
#define FIREBALL_SOUTHWEST_FIELD "Southwest Field"
#define FIREBALL_WEST_FIELD "West Field"
#define FIREBALL_NORTHWEST_FIELD "Northwest Field"
#define FIREBALL_SOUTH_GOAL "South Goal"
#define FIREBALL_SOUTH_FIELD "South Field"
#define FIREBALL_MID_FIELD "Mid Field"
#define FIREBALL_NORTH_FIELD "North Field"
#define FIREBALL_NORTH_GOAL "North Goal"
#define FIREBALL_SOUTHEAST_FIELD "Southeast Field"
#define FIREBALL_EAST_FIELD "East Field"
#define FIREBALL_NORTHEAST_FIELD "Northeast Field"
#define FIREBALL_EAST_POINT "East Point"

#define IS_FIREBALL_ARENA_ROOM(ob) \
   (objectp(ob) && \
    function_exists("check_fireball_arena_room", ob) == FIREBALL_ARENA_ROOM)  

#define IS_FIREBALL_STAND_ROOM(ob) \
   (objectp(ob) && \
    function_exists("check_fireball_stand_room", ob) == FIREBALL_STAND_ROOM)  

#define IS_FIREBALL_OUTSIDE_ROOM(ob) \
   (objectp(ob) && \
    function_exists("check_fireball_outside_room", ob) == FIREBALL_OUTSIDE_ROOM)  

/* team positions and sides */ 
#define FIREBALL_POS_BACK "defence"
#define FIREBALL_POS_LEFT_MIDFIELD "left midfield" 
#define FIREBALL_POS_RIGHT_MIDFIELD "right midfield" 
#define FIREBALL_POS_FORWARD "attack"  

#define FIREBALL_KICKING_SOUTH 1
#define FIREBALL_KICKING_NORTH 2

#define FIREBALL_MAX_TEAM_SIZE 4
#define FIREBALL_MIN_TEAM_SIZE 4

/* Prices in cc */ 
#define FIREBALL_REGISTRATION_FEE 50
#define FIREBALL_LOCKER_FEE 20 

#define FIREBALL_NPC_CAPTAIN "_fireball_npc_captain"

/* properties */ 
#define FIREBALL_LIVE_S_TEAM_POS "_fireball_live_s_team_pos" 
#define FIREBALL_LIVE_I_KICK_DIRECTION "_fireball_live_i_kick_direction" 
#define FIREBALL_LIVE_I_RECOVERING "_fireball_live_i_recovering" 

/* formations */ 
#define FIREBALL_FORMATION_DAGGER "dagger" 
#define FIREBALL_FORMATION_SCORPION "scorpion" 
#define FIREBALL_FORMATION_SICKLE "sickle" 
#define FIREBALL_FORMATION_ARROW "arrow" 

/* Start of game handler defs */

#define FIREBALL_LIVE_I_LINKDEAD_FROM_ARENA "_fireball_live_i_linkdead_from_arena"

/* time between npc team moves */ 
#define FIREBALL_NPC_MOVE_INTERVAL 4.7
#define FIREBALL_PLAYER_MOVE_INTERVAL 2.3
#define FIREBALL_TACKLE_STUN_INTERVAL 6.0
#define FIREBALL_TACKLE_RECOVER_INTERVAL 3.3
#define FIREBALL_KICK_RECOVER_INTERVAL 3.3
#define FIREBALL_PASS_RECOVER_INTERVAL 3.3

/* match states */ 
#define FIREBALL_MS_NO_MATCH "no match"
#define FIREBALL_MS_PRE_MATCH "pre match"
#define FIREBALL_MS_INTRO_FIRST_HALF "buildup to first half"
#define FIREBALL_MS_FIRST_HALF "first half"
#define FIREBALL_MS_HALF_TIME "half time"
#define FIREBALL_MS_INTRO_SECOND_HALF "buildup to second half"
#define FIREBALL_MS_SECOND_HALF "second half"
#define FIREBALL_MS_POST_MATCH "final score"
#define FIREBALL_MS_PRACTICE "practice session"

/* match substates */ 
#define FIREBALL_MSS_GOAL_SCORED "interval between goal and kick off"
#define FIREBALL_MSS_AWAITING_KICKOFF "awaiting kick off"

/* durations of match states */ 
#define FIREBALL_IVL_INIT 1
#define FIREBALL_IVL_PRE_MATCH 80
#define FIREBALL_IVL_INTRO_FIRST_HALF 30
#define FIREBALL_IVL_FIRST_HALF 300
#define FIREBALL_IVL_HALF_TIME 120
#define FIREBALL_IVL_INTRO_SECOND_HALF 20
#define FIREBALL_IVL_SECOND_HALF 300
#define FIREBALL_IVL_POST_MATCH 60
#define FIREBALL_IVL_GOAL_TO_KICKOFF 15
#define FIREBALL_IVL_KICKOFF_MAX 15

/* classes of tackle */ 
#define FIREBALL_IMPACT_KICK 1
#define FIREBALL_IMPACT_PUNCH 2
#define FIREBALL_IMPACT_BUTT 3

/* tackle hitlocs */ 
#define FIREBALL_HITLOC_FEET 1
#define FIREBALL_HITLOC_LEGS 2
#define FIREBALL_HITLOC_WAIST 3
#define FIREBALL_HITLOC_ARMS 4
#define FIREBALL_HITLOC_CHEST 5 
#define FIREBALL_HITLOC_HEAD 6

/* tackle description mappings */ 
#define FIREBALL_IMPACT_VERB \
  ([   FIREBALL_IMPACT_KICK : ({ ({"kick", "kicks"}), ({"boot", "boots"}), \
                                 ({"hack", "hacks"}) }), \
       FIREBALL_IMPACT_PUNCH : ({ ({"punch", "punches"}), \
                               ({"strike", "strikes"}), ({"thump", "thumps"}),\
                               ({"hit", "hits"}) }), \
       FIREBALL_IMPACT_BUTT : ({ ({"butt", "butts"}) }) ])


#define FIREBALL_IMPACT_ADVERB \
  ([   FIREBALL_IMPACT_KICK : ({ "with little effect", "", \
                                 "powerfully", "viciously", \
                                 "like a wild horse" }),  \
       FIREBALL_IMPACT_PUNCH : ({ "with little effect", "", \
                                  "hard", "resoundingly", \
                                  "like a true heavyweight" }), \
       FIREBALL_IMPACT_BUTT : ({ "with little effect", "", \
                                 "heavily", "mightily", \
                                 "like a battering ram" }) ])

    /* hitlocs_smaller: tackler of much lower volume than target  */ 
#define FIREBALL_HITLOCS_SMALLER ([ \
       FIREBALL_HITLOC_FEET : ({ "left foot", "right foot", \
                                 "left shin", "right shin" }), \
       FIREBALL_HITLOC_LEGS : ({ "left knee", "right knee", \
                                 "left thigh", "right thigh" }), \
       FIREBALL_HITLOC_WAIST : ({ "abdomen", "stomach", \
                                  "left hip","right hip" }), \
       FIREBALL_HITLOC_CHEST : ({ "left pectoral", "right pectoral", \
                                  "collar bone",  "throat", \
                                  "left shoulder", "right shoulder" }), \
       FIREBALL_HITLOC_ARMS : ({ "left forearm", "right forearm", \
                                 "left upper arm",  "right upper arm"}), \
       FIREBALL_HITLOC_HEAD :  ({ "nose", "mouth", "chin", "forehead" }) ])

    /* hitlocs_mid: tackler of broadly comparable volume to target */ 
#define FIREBALL_HITLOCS_EQUAL ([ \
       FIREBALL_HITLOC_FEET : ({ "feet", "shins" }), \
       FIREBALL_HITLOC_LEGS : ({ "knees", "thighs" }), \
       FIREBALL_HITLOC_WAIST : ({ "abdomen", "hips" }), \
       FIREBALL_HITLOC_CHEST : ({ "pectorals", "ribs" }), \
       FIREBALL_HITLOC_ARMS : ({ "left arm", "right arm" }), \
       FIREBALL_HITLOC_HEAD :  ({ "face", "temple" }) ]) 

    /* hitlocs_bigger: tackler of much higher volume than target */ 
#define FIREBALL_HITLOCS_BIGGER  ([ \
       FIREBALL_HITLOC_FEET : ({ "shins" }), \
       FIREBALL_HITLOC_LEGS : ({ "legs" }), \
       FIREBALL_HITLOC_WAIST : ({ "midriff" }), \
       FIREBALL_HITLOC_CHEST : ({ "chest" }), \
       FIREBALL_HITLOC_ARMS : ({ "chest" }), \
       FIREBALL_HITLOC_HEAD :  ({ "head" }) ])

/* Types of rebound on the ball hitting the wall around the fire */ 
#define FIREBALL_REBOUND_X 1 
#define FIREBALL_REBOUND_Y 2

#endif
