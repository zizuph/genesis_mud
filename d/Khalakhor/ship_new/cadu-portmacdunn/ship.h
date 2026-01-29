#ifndef _CADU_PORTMACDUNN_SHIPLINE
#define _CADU_PORTMACDUNN_SHIPLINE 1

#include "../ship.h"

#define SHIPLINE_DIR  DOMAIN_SHIP_DIR + "/cadu-portmacdunn/"

#define SHIP_CREW_DIR SHIPLINE_DIR    + "crew/"
#define SHIP_ROOM_DIR SHIPLINE_DIR    + "ship/"
#define SHIP_OBJS_DIR SHIPLINE_DIR    + "objs/"
#define SHIP_MISC_DIR SHIPLINE_DIR    + "misc/"

#define CABIN   (SHIPLINE_DIR + "ship/cabin")
#define DECK    (SHIPLINE_DIR + "ship/deck")
#define MAST    (SHIPLINE_DIR + "ship/mast")
#define FORE    (SHIPLINE_DIR + "ship/fore")
#define TICKET  (SHIPLINE_DIR + "objs/ticket")
#define CAPTAIN (SHIPLINE_DIR + "crew/captain")

#define DOMAIN_AREA_DIR "/d/Khalakhor/inisi/roke"
#define DOMAIN_OBJS_DIR "/d/Khalakhor/common/"

#define CADU_PIER      (DOMAIN_AREA_DIR + "/nyreese/cadu_pier2")
#define MACDUNN_PIER   (MACDUNN_HARBOR + "pier12")

#define SHIP_NAME       "Corran"

#endif
