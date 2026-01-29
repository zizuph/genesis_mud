/*
   /d/Kalad/sys/stdproperties.h
   
   Kalad's standard properties
 */
#ifndef _KALAD_PROP_DEF
#define _KALAD_PROP_DEF

#include "/sys/stdproperties.h"

#define SEWER_I_NO_STENCH     "_sewer_i_no_stench"

#define ROOM_I_NO_TIME_DESC   "_room_i_no_time_desc"
// Kept for backwards compatibility
#define ROOM_NO_TIME_DESC     ROOM_I_NO_TIME_DESC

// How dirty is a player
#define LIVE_I_DIRTY          "_live_i_dirty"
#define DIRTY_OBJECT_ID       "_kalad_dirty_object"

// Maximum value for hearing a bell
#define MAX_HEAR_BELL       4

// Raumdor guards
#define IS_ENEMY_OF_DRAKMERE  "_is_enemy_of_drakmere"
#define IS_ENEMY_OF_TORBODON  "_is_enemy_of_torbodon"

#endif
