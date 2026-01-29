/*
 * Ships definition stuff
 * TAPAKAH, 2007, 2008
 */

#ifndef SHIP_DEFS
#define SHIP_DEFS

#define SHIP_DIR "/d/Genesis/gsl_ships/"
#define SHIP_LOG_DIR     (SHIP_DIR + "log/")
#define SHIP_CONTROL_DIR (SHIP_DIR + "control/")
#define SHIP_DATA_DIR    (SHIP_DIR + "data/")

#define STDTICKET   (SHIP_DIR + "std/ticket")
#define STDCAPTAIN  (SHIP_DIR + "std/captain")
#define STDSHIP     (SHIP_DIR + "std/ship")
#define STDSEA      (SHIP_DIR + "std/sea")
#define STDSHORE    (SHIP_DIR + "std/shore")
#define STDPIER     (SHIP_DIR + "std/pier")
#define STDSIGN     (SHIP_DIR + "std/sign")
#define STDSHIPROOM (SHIP_DIR + "std/shiproom")

#define LIBSHORE    (SHIP_DIR + "lib/shore")
#define LIBPIER     (SHIP_DIR + "lib/pier")

#define X_OCEAN_SIZE       (500)
#define Y_OCEAN_SIZE       (500)
#define MAX_PIER_DESC      (30)
#define MAX_STOPS_IN_OCEAN (3)
#define STOP_TIME_AT_SEA   (3.0)
#define STOP_TIME_AT_PORT  (60.0)
#define FREE_RIDE_AVG      (25)

#define ROOM_I_HAS_PIER          "_room_i_has_pier"
#define ROOM_I_IS_SHORE          "_room_i_is_shore"
#define ROOM_I_DIVING_DIFFICULTY "_room_i_diving_difficulty"
#define X_OCEAN_COORD            "_x_ocean_coord"
#define Y_OCEAN_COORD            "_y_ocean_coord"

#define SHIP_SPEED_DESCS  ({"SLOW", "MODERATE", "FAST"})

#ifndef TP
#define TP        this_player()
#endif TP

#ifndef TO
#define TO        this_object()
#endif TO

#ifndef ENV
#define ENV       environment()
#endif ENV

#ifndef ENVX
#define ENVX(x)   environment(x)
#endif ENVX

#ifndef NF0
#define NF0(text) { notify_fail(text + "\n"); return 0; }
#endif NF0

#define SHIP_DATABASE     (SHIP_DATA_DIR + "ship_database")
#define PIER_DATABASE     (SHIP_DATA_DIR + "pier_database")

#define SHIP_MANAGER        (SHIP_CONTROL_DIR + "ship_manager")
#define PIER_MANAGER        (SHIP_CONTROL_DIR + "pier_manager")
#define NAVIGATION_MANAGER  (SHIP_CONTROL_DIR + "navigation_manager")
#define ALARMS_MANAGER      (SHIP_CONTROL_DIR + "alarms_manager")

#define CONTROLROOM       (SHIP_CONTROL_DIR + "room")
#define CONTROLLER        (SHIP_CONTROL_DIR + "controller")

#define PIER_ACCESS_LOG   (SHIP_LOG_DIR + "pier_log")
#define SHIP_ACCESS_LOG   (SHIP_LOG_DIR + "ship_log")
#define SHORE_ACCESS_LOG  (SHIP_LOG_DIR + "shore_log")
#define NAVIGATION_LOG    (SHIP_LOG_DIR + "navigation_log")
#define CONTROL_LOG       (SHIP_LOG_DIR + "room_log")
#define BOARD_LOG         (SHIP_LOG_DIR + "board_log")
#define TLOG              (SHIP_LOG_DIR + "t_log")

#endif SHIP_DEFS
