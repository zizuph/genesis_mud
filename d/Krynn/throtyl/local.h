/*
 * local.h file for the Throtyl road
 *
 * Arman, June 2020
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"
#include <macros.h>

/* This defines the pathnames of this dir */
#define TDIR           "/d/Krynn/throtyl/"

/* non area base room */
#define ROOM_BASE	TDIR + "throtyl_base"
#define LIVING          TDIR + "living/"
#define ROOMS           TDIR + "rooms/"

/* connections to the world */
#define EPLAIN_LINK     "/d/Krynn/solamn/eplains/rooms/eplain-23-24-T"
#define SANCTION_LINK   "/d/Ansalon/taman_busuk/sanction/room/city/sanction_entry"

#define DEBUG(x)	find_player("arman")->catch_tell(x);
