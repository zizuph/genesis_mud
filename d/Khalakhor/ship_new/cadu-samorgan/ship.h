#ifndef _CADU_SAMORGAN_SHIPLINE
#define _CADU_SAMORGAN_SHIPLINE 1

#include "../ship.h"

#define SHIPLINE_DIR  (DOMAIN_SHIP_DIR + "/cadu-samorgan/")

#define SHIP_CREW_DIR SHIPLINE_DIR    + "crew/"
#define SHIP_ROOM_DIR SHIPLINE_DIR    + "ship/"
#define SHIP_OBJS_DIR SHIPLINE_DIR    + "objs/"
#define SHIP_MISC_DIR SHIPLINE_DIR    + "misc/"
 
#define CABIN          (SHIP_ROOM_DIR + "cabin")
#define DECK           (SHIP_ROOM_DIR + "deck")
#define DESK           (SHIP_OBJS_DIR + "desk")
#define MAP            (SHIP_OBJS_DIR + "map")
#define GLOBE          (SHIP_OBJS_DIR + "globe")
#define TICKET         (SHIP_OBJS_DIR + "ticket")
#define CAPTAIN        (SHIP_CREW_DIR + "captain")

#define DOMAIN_AREA_DIR "/d/Khalakhor/inisi/roke"
#define DOMAIN_OBJS_DIR "/d/Khalakhor/common/"

#define CADU_PIER      (DOMAIN_AREA_DIR + "/nyreese/cadu_pier3")
#define SAMORGAN_PIER  ("/d/Khalakhor/sw_speir/samorgan/pier/pie1304")
 
#define SHIP_NAME      "Bella Diaz"
 
#endif
