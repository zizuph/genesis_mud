// Revision history:
// 22/02-200 - Boron - Added definitions for warfare
//                     module

#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Krynn/common/warfare/warfare.h"

#define SHIP_D "/d/Ansalon/taman_busuk/sanction/ship/newports/"
#define SHIP   "/d/Ansalon/taman_busuk/sanction/ship/newports/ship"
#define CABIN       SHIP_D + "cabin"
#define DECK        SHIP_D + "deck"
#define CAPTAIN     SHIP_D + "captain"
#define SHIP_NAME   "Black Seadragon"
#define TICKET      SHIP_D + "ticket"
#define TICKET_NAME  "the Sanction-Newports line"
#define PRICE      18
#define ROOM "/d/Ansalon/taman_busuk/sanction/sea/"
#define NEWPORTS     "/d/Krynn/que/newports/"

#define PIER    SANCTION + "room/city/pier07"
#define PIER2   NEWPORTS + "pier4"

#undef  DEBUG
#ifdef  DEBUG
#define TELL(x) tell_object(find_player("boron"), "\n\t* * " + x + " * *\n");
#endif
