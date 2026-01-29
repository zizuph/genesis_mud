/*
 * swordcoast/south_highroad/mobiles/road_patrol.h
 *
 * This file contains the parameters determining the number of soldiers in
 * the patrol that patrols the southern high road leading to the gates of
 * Waterdeep, as well as the exact path they take. Please be mindful of
 * correctness if you edit this, otherwise the patrol will fail.
 *
 * Created by Brine aug 2021
 */

#ifndef SHR_ROAD_PATROL

#define NUM_GUARDS      4
#define PATROL_PATH     ({ \
        SOUTH_HIGHROAD_ROOM + "s_hroad15", \
        SOUTH_HIGHROAD_ROOM + "s_hroad14", \
        SOUTH_HIGHROAD_ROOM + "s_hroad13", \
        SOUTH_HIGHROAD_ROOM + "s_hroad12", \
        SOUTH_HIGHROAD_ROOM + "s_hroad11", \
        SOUTH_HIGHROAD_ROOM + "s_hroad10", \
        SOUTH_HIGHROAD_ROOM + "s_hroad09", \
        SOUTH_HIGHROAD_ROOM + "s_hroad08", \
        SOUTH_HIGHROAD_ROOM + "s_hroad07", \
        SOUTH_HIGHROAD_ROOM + "s_hroad06", \
        SOUTH_HIGHROAD_ROOM + "s_hroad05", \
        SOUTH_HIGHROAD_ROOM + "s_hroad04", \
        SOUTH_HIGHROAD_ROOM + "s_hroad03", \
        SOUTH_HIGHROAD_ROOM + "s_hroad02", \
        SOUTH_HIGHROAD_ROOM + "s_hroad01" \
    })

#endif
