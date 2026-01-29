#ifndef WATER_DEFS
#define WATER_DEFS

#define IN_WATER(player)  \
     (environment(player)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)  

#define UNDER_WATER(player) \
     (environment(player)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) 

#define IN_DEEP_WATER(player) \
     (IN_WATER(player) && stringp(environment(player)->query_sink_path())) 

#define IN_SHALLOW_WATER(player) \
     (IN_WATER(player) && !(IN_DEEP_WATER(player))) 


#define DROWN_OBJECT "/d/Faerun/std/drown_ob" 
#define DROWN_OBJECT_NAME "drown_object" 

#define MOBILITY_OBJECT "/d/Faerun/std/mobility_ob" 
#define MOBILITY_OBJECT_NAME "mobility_object" 


#define LIVE_I_GILLS "_live_i_gills"
#define LIVE_O_DROWN_OB "_live_o_drown_ob"
#define OBJ_I_FLOAT "_obj_i_float"
#define DROWN_HEARTBEAT 10
#define NO_SAY_UNDER_WATER "You cannot converse under water, you will "+\
                           "have to signal instead.\n"
                           
#define NO_UNDER_WATER "You cannot do that under water.\n"

#endif
