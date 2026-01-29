



/*
 * Aymil Defs file
 *
 * Varian, January 2020
 *
 */
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "/d/Gondor/met_defs.h"
#include "/d/Gondor/defs.h"
#ifndef HOUSE_DEFS
#define HOUSE_DEFS
#define HOUSE 						"/w/varian/house/"
#define LOC							HOUSE + "locations/"
#define BREE 						LOC + "bree/"
#define PEL 						LOC + "pelargir/"
#define BREEDOOR					BREE + "door/"
#define OBJ							HOUSE + "obj/"

#define HOUSE_LOG_PATH (HOUSE + "log/")
#define HOUSE_MANAGER (HOUSE + "house_manager")

#define DISPLAY_ROOM  (HOUSE + "display_room")

#define KEY_OWNER "owner"
#define KEY_COMPLETE "complete"
#define KEY_PRICE "price"
#define KEY_DESCRIPTION "description"
#define KEY_ROOMS "rooms"
#define KEY_SHORT "short"
#define KEY_LONG "long"
#define KEY_FORSALE "forsale"
#define KEY_LASTSALEPRICE "lastsaleprice"
#define KEY_LASTSALETIME "lastsaletime"

#endif HOUSE_DEFS
