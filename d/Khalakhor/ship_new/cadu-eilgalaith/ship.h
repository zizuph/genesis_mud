#ifndef _CADU_GALAITH_SHIPLINE
#define _CADU_GALAITH_SHIPLINE 1
 
#include "../ship.h"

#define SHIPLINE_DIR  (DOMAIN_SHIP_DIR + "/cadu-eilgalaith/")

#define SHIP_CREW_DIR SHIPLINE_DIR    + "crew/"
#define SHIP_ROOM_DIR SHIPLINE_DIR    + "ship/"
#define SHIP_OBJS_DIR SHIPLINE_DIR    + "objs/"
#define SHIP_MISC_DIR SHIPLINE_DIR    + "misc/"
 
#define CABIN          (SHIP_ROOM_DIR + "cabin")
#define DECK           (SHIP_ROOM_DIR + "deck")
#define TICKET         (SHIP_OBJS_DIR + "ticket")
#define CAPTAIN        (SHIP_CREW_DIR + "captain")

#define DOMAIN_AREA_DIR "/d/Khalakhor/inisi/roke"
#define DOMAIN_OBJS_DIR "/d/Khalakhor/common/"

#define CADU_PIER      (DOMAIN_AREA_DIR + "/nyreese/cadu_pier4")
#define GALAITH_PIER  ("/d/Khalakhor/inisi/galaith/pier/pier1")

#define SHIP_NAME    "Coral Lady"
 
#endif
