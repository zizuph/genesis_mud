#ifndef __SILENT_FOREST__
#define __SILENT_FOREST__

#define SFOREST  ("/d/Calia/argos/sforest/")
#define ROOM     (SFOREST + "room/")
#define SHOBJ    (SFOREST + "obj/")
#define NPC	 (SFOREST + "npc/")
#define MON      (SFOREST + "mon/")


// -------- Definitions for random herbs -------

#define GONDOR(X) ("/d/Gondor/common/herbs/X")
#define KALAD(X)   ("/d/Kalad/common/herbs/X")

#define FOREST_HERBS ({ \
        GONDOR(dajla), KALAD(redeye), KALAD(darfern), KALAD(numbis), \
        KALAD(vinerot), GONDOR(laurel), GONDOR(garlic), GONDOR(myrtle), \
        GONDOR(fennel), GONDOR(hemlock), KALAD(pumpkin), KALAD(flameroot), \
        GONDOR(coccinea), KALAD(fungari), KALAD(nightshade), \
})

#endif __SILENT_FOREST__