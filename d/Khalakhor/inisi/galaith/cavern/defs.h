#ifndef CAVERN_DEFS
#define CAVERN_DEFS

#define THIS_DIR      "/d/Khalakhor/inisi/galaith/cavern/"

#define ARM      (THIS_DIR + "arm/")
#define MON      (THIS_DIR + "mon/")
#define NPC      (THIS_DIR + "npc/")
#define ROOM     (THIS_DIR + "room/")
#define WEP      (THIS_DIR + "wep/")

#define CAVEBASE   (ROOM + "cavebase")
#define CAVE_BASE  (ROOM + "cave_base")
#define CAVERNBASE (ROOM + "cavernbase")

#define GONDOR     ("/d/Gondor/common/herbs/")
#define RAUM       ("/d/Raumdor/common/herbs/")

#define CAVERN_HERBS ({ \
        (GONDOR + "dajla"), (RAUM + "redeye"), (RAUM + "darfern"), \
        (RAUM + "numbis"), (RAUM + "vinerot"), (GONDOR + "laurel"), \
        (GONDOR + "garlic"), (GONDOR +"myrtle"), (GONDOR + "fennel"), \
        (GONDOR + "hemlock"), (RAUM + "pumpkin"), (RAUM + "flameroot"), \
        (GONDOR + "coccinea"), (RAUM + "fungari"), (RAUM + "nightshade"), \
})

#endif CAVERN_DEFS
