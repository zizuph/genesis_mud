#include "wagon.h"

#define WAGON_TEST_LOC1          9999
#define WAGON_TEST_LOC2          9998
#define WAGON_TAKES_A_REST       ({"PAUSE"})

#define VENCAR_TEST_ROUTE        (( { ROOM + "road1", ROOM + "road2", ROOM + "road3", ROOM + "road4", \
                                      ROOM + "road5", ROOM + "road6", }) )
#define VENCAR_TEST_REROUTE      (( { ROOM + "road6", ROOM + "road5", ROOM + "road4", ROOM + "road3", \
                                      ROOM + "road2", ROOM + "road1", }) )
#define VENCAR_TEST_ROUTE_MERGE  (VENCAR_TEST_ROUTE + WAGON_TAKES_A_REST +  VENCAR_TEST_REROUTE)


#define WAGON_PAX                1
#define WAGON_SOLACE             2
/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
#define PAX_TO_RED_CAMP (( { "/d/Krynn/pax/tharkas/court_yard/court_yard2" , \
    "/d/Krynn/pax/tharkas/court_yard/court_yard1" , \
    "/d/Krynn/pax/tharkas/ground_level/hollow_wall2", "SPECIAL", \
    "Call here open_gate gate" ,         "SPECIAL", \
    "Call here close_gate gate",         "/d/Krynn/pax/valley/main_gate", \
    "/d/Krynn/pax/valley/curtain_wall1", "/d/Krynn/pax/valley/curtain_wall2", \
    "/d/Krynn/pax/valley/valley_road1",  "/d/Krynn/pax/valley/valley_road2", \
    "/d/Krynn/pax/valley/valley_road3",  "/d/Krynn/pax/valley/valley_road4", \
    "/d/Krynn/pax/valley/valley_road5",  "/d/Krynn/pax/valley/valley_road6", \
    "/d/Krynn/pax/road/road1",           "/d/Krynn/pax/road/road2", \
    "/d/Krynn/pax/road/road3",           "/d/Krynn/pax/road/road4", \
    "/d/Krynn/pax/road/road5",           "/d/Krynn/pax/road/road6", \
    "/d/Krynn/pax/road/road7",           "/d/Krynn/que/newports/road2", \
    "/d/Krynn/que/newports/road1",       "/d/Krynn/que/newports/bridge_end", \
    "/d/Krynn/que/plains/newports_link", \
    "/d/Krynn/que/plains/rooms/plain-5-23-1", \
    "/d/Krynn/que/plains/rooms/plain-5-22-1", \
    "/d/Krynn/que/plains/rooms/plain-6-22-1", \
    "/d/Krynn/que/plains/rooms/plain-7-21-1", \
    "/d/Krynn/que/plains/rooms/plain-8-20-1", \
    "/d/Krynn/que/plains/rooms/plain-9-19-1", \
    "/d/Krynn/que/plains/rooms/plain-10-19-Y", \
    "/d/Krynn/que/plains/rooms/plain-11-18-1", \
    "/d/Krynn/que/plains/rooms/plain-11-17-1", \
    "/d/Krynn/que/plains/rooms/plain-12-16-1", \
    "/d/Krynn/que/plains/rooms/plain-13-15-1", \
    "/d/Krynn/que/plains/rooms/plain-14-14-1", \
    "/d/Krynn/que/plains/rooms/plain-14-13-S", \
    "/d/Krynn/que/plains/rooms/plain-13-12-L", \
    "/d/Krynn/que/plains/rooms/plain-12-12-1", \
    "/d/Krynn/que/plains/rooms/plain-11-12-1", \
    "/d/Krynn/que/plains/rooms/plain-10-12-1", \
    "/d/Krynn/que/plains/rooms/plain-9-12-1", \
    "/d/Krynn/que/plains/rooms/plain-8-12-1", \
    "/d/Krynn/que/plains/rooms/plain-7-11-1", \
    "/d/Krynn/que/plains/rooms/plain-6-10-j", \
    "/d/Krynn/que/plains/rooms/plain-6-9-1", \
    "/d/Krynn/que/plains/rooms/plain-7-9-1", \
    "/d/Krynn/que/plains/rooms/plain-8-9-1", \
    "/d/Krynn/que/plains/rooms/plain-9-8-1", \
    "/d/Krynn/que/plains/rooms/plain-9-7-1", \
    "/d/Krynn/que/plains/rooms/plain-9-6-1", \
    "/d/Krynn/que/plains/rooms/plain-9-5-1", \
    "/d/Krynn/que/camp/camp03",        "/d/Krynn/que/camp/camp12", \
    "/d/Krynn/que/camp/camp09" } ))

#define RED_CAMP_TO_PAX (( {"/d/Krynn/que/camp/camp09", \
    "/d/Krynn/que/camp/camp12", "/d/Krynn/que/camp/camp03", \
    "/d/Krynn/que/plains/rooms/plain-9-5-1", \
    "/d/Krynn/que/plains/rooms/plain-9-6-1", \
    "/d/Krynn/que/plains/rooms/plain-9-7-1", \
    "/d/Krynn/que/plains/rooms/plain-9-8-1", \
    "/d/Krynn/que/plains/rooms/plain-8-9-1", \
    "/d/Krynn/que/plains/rooms/plain-7-9-1", \
    "/d/Krynn/que/plains/rooms/plain-6-9-1", \
    "/d/Krynn/que/plains/rooms/plain-6-10-j", \
    "/d/Krynn/que/plains/rooms/plain-7-11-1", \
    "/d/Krynn/que/plains/rooms/plain-8-12-1", \
    "/d/Krynn/que/plains/rooms/plain-9-12-1", \
    "/d/Krynn/que/plains/rooms/plain-10-12-1", \
    "/d/Krynn/que/plains/rooms/plain-11-12-1", \
    "/d/Krynn/que/plains/rooms/plain-12-12-1", \
    "/d/Krynn/que/plains/rooms/plain-13-12-L", \
    "/d/Krynn/que/plains/rooms/plain-14-13-S", \
    "/d/Krynn/que/plains/rooms/plain-14-14-1", \
    "/d/Krynn/que/plains/rooms/plain-13-15-1", \
    "/d/Krynn/que/plains/rooms/plain-12-16-1", \
    "/d/Krynn/que/plains/rooms/plain-11-17-1", \
    "/d/Krynn/que/plains/rooms/plain-11-18-1", \
    "/d/Krynn/que/plains/rooms/plain-10-19-Y", \
    "/d/Krynn/que/plains/rooms/plain-9-19-1", \
    "/d/Krynn/que/plains/rooms/plain-8-20-1", \
    "/d/Krynn/que/plains/rooms/plain-7-21-1", \
    "/d/Krynn/que/plains/rooms/plain-6-22-1", \
    "/d/Krynn/que/plains/rooms/plain-5-22-1", \
    "/d/Krynn/que/plains/rooms/plain-5-23-1", \
    "/d/Krynn/que/plains/newports_link", \
    "/d/Krynn/que/newports/bridge_end", \
    "/d/Krynn/que/newports/road1", \
    "/d/Krynn/que/newports/road2", \
    "/d/Krynn/pax/road/road7", \
    "/d/Krynn/pax/road/road6", \
    "/d/Krynn/pax/road/road5", \
    "/d/Krynn/pax/road/road4", \
    "/d/Krynn/pax/road/road3", \
    "/d/Krynn/pax/road/road2", \
    "/d/Krynn/pax/road/road1", \
    "/d/Krynn/pax/valley/valley_road6", \
    "/d/Krynn/pax/valley/valley_road5", \
    "/d/Krynn/pax/valley/valley_road4", \
    "/d/Krynn/pax/valley/valley_road3", \
    "/d/Krynn/pax/valley/valley_road2", \
    "/d/Krynn/pax/valley/valley_road1", \
    "/d/Krynn/pax/valley/curtain_wall2", \
    "/d/Krynn/pax/valley/curtain_wall1", \
    "/d/Krynn/pax/valley/main_gate", \
    "SPECIAL", "Call here open_gate gate", \
    "/d/Krynn/pax/tharkas/ground_level/hollow_wall2", \
    "SPECIAL", "Call here close_gate gate", \
    "/d/Krynn/pax/tharkas/court_yard/court_yard1" , \
    "/d/Krynn/pax/tharkas/court_yard/court_yard2" } ))


