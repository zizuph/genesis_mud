/*  Defines for the Gondor Distributor. Please don't erase
    any defines here, rather comment them out in case they
    are needed in the future again.

    Gwyneth - April 20, 2000
*/

/* Pathname */
#define DPATH "/d/Gondor/common/distrib/"

/* All rooms which the distributor should be cloned to */
/* #define DROOMS ({"/w/gwyneth/workroom", (DPATH + "dmaster")}) */
#define DROOMS ({"/d/Gondor/pelargir/docks/dock7",  \
    "/d/Gondor/pelargir/docks/dock8",               \
    "/d/Gondor/pelargir/docks/dock5",               \
    "/d/Gondor/pelargir/docks/dock3",               \
    "/d/Gondor/pelargir/docks/dock2",               \
    "/d/Gondor/pelargir/docks/dock1",               \
    "/d/Gondor/common/guild/gondor/startchamber",   \
    "/d/Gondor/tharbad/pier/pier1",                 \
    "/d/Gondor/common/guild/ithilien/erockchamber", \
    "/d/Gondor/minas/rooms/innroom",                \
    "/d/Gondor/common/guild2/startroom",            \
    "/d/Gondor/morgul/city/rooms/hotel",            \
    "/d/Gondor/common/dunedain/rooms/start_room",   \
    "/d/Gondor/tharbad/ford/f02",                   \
    "/d/Gondor/common/dwarf_guild/start",           \
    "/d/Gondor/rohan/edoras/hotelr"})


/* Object to clone into people entering room with distributor */
#define DOBJ   "/w/stern/obj/bug.c"
/* #define DOBJ "/w/gwyneth/gwyn_boots" */

/* Message to give to person upon cloning object */
#define MESSAGE "A small bug drops down from the sky and lands in your hands.\n"

/* Message to give to person upon recalling object */
#define DEPARTURE "Your bug hops out of your hands and out of sight.\n"

/* Message to give to the room if object is not held by interactive
   upon recalling objects */
#define ROOM_DEP "A bug burrows its way into the ground and disappears.\n"

/* Individual distributor */
#define DISTRIBUTOR DPATH + "distrib.c"

/* Prop set when player receives item */
#define PLAYER_I_DISTRIB "_player_i_distrib"

