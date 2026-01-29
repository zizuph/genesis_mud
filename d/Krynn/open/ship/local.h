/* Definitions for the Secret Shipline near the Cabal of Hiddukel */

#include "../local.h"

/* The places the shipline goes to */
#define PLACES          ({"Emerald","Kalad","Kalaman","Tharbad","Pelargir"/*,"Avenir","Terel"*/})
#define PIER_ON_EMERALD "/d/Emerald/mountains/volcano/pier2"
#define KABAL_ON_KALAD  "/d/Kalad/common/port/s1"
#define PORT_ON_AVENIR  "/d/Avenir/common/port/port14"
#define PIER_ON_TEREL   "/d/Terel/port/w_pier_n"
#define PIER_ON_KALAMAN "/d/Ansalon/kalaman/room/dock3"
#define PIER_ON_THARBAD "/d/Gondor/tharbad/pier/pier3"
#define PIER_ON_PELARGIR "/d/Gondor/pelargir/docks/dock9"
/* If you change anything in the lines above, please be sure to update
 * the ship.c file as well!
 */

/* Pathnames and special filenames and whatever else is needed */
#define SHIP_D          TDIR + "ship/"
#define SECRETPIER      TDIR + "cavern/har6"
#define	TICKET		SHIP_D + "ticket"
#define TICKET_NAME	"the Skull'n'Bones"
#define	PRICE		148
#define CABIN           SHIP_D + "cabin"
#define CABIN2          SHIP_D + "rowingdeck"
#define DECK            SHIP_D + "deck"
#define DECK2           SHIP_D + "for"
#define CAPTAIN         SHIP_D + "captain"
#define SHIP_NAME       "Skull'n'Bones"

/* The open sea / ocean rooms */
#define BRANCHALA_BAY   "/d/Krynn/solamn/palan/city/sea2"
#define OPEN_SEA        "/d/Krynn/solace/ship/sea3"
/*#define SEA4            "/d/Krynn/solace/ship/sea4"
#define SEA5            "/d/Krynn/solace/ship/sea5"
#define SEA6            "/d/Krynn/solace/ship/sea6"
#define SEA7            "/d/Krynn/solace/ship/sea7"
#define SEA8            "/d/Krynn/solace/ship/sea8"
#define SEA9            "/d/Krynn/solace/ship/sea9"
#define SEA10           "/d/Krynn/solace/ship/sea10"*/
#define KALADSEA1       "/d/Kalad/common/port/shipline1/sea"
#define KALADSEA2       "/d/Kalad/common/port/shipline1/sea1"
#define KALADSEA3       "/d/Kalad/common/port/shipline1/sea2"
#define KALADSEA4       "/d/Kalad/common/port/shipline1/sea3"
#define KALADSEA5       "/d/Kalad/common/port/shipline1/sea4"
