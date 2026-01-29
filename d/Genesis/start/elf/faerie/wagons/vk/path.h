/*
 * Controls wagon messages
 * Finwe, May 2005
 */

#include "defs.h"

#define WAGON_STOPS     ({ "/d/Shire/lode/rooms/forest/landing1",  \
    "/d/Krynn/solamn/splains/dragon/landing1" })
#define CARGO_TYPES     ({ "furs", "barrels", "leathers", \
    "wines", "grains" })

#define AVOID   (VK_WAGON_DIR + "void")

#define FAERIE_TO_VK  ({ WAGON_STOPS[0], 60, \
    AVOID, 5,   \
    AVOID, 10,  \
    AVOID, 15,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 5    })


#define VK_TO_FAERIE  ({ WAGON_STOPS[1], 60, \
    AVOID, 5,   \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 15,  \
    AVOID, 10,  \
    AVOID, 5    })

#define FAERIE_TO_VK_MESSAGES ({ "@@set_wagon_full@@", \
    "The wagon heads south along a forest track.\n", \
    "The wagon heads southwest following a track up into the mountains.\n", \
    "The wagon turns west, slowly climbing higher into the mountains.\n", \
    "The wagon creeps through the mountain as an icy wind whips past it.\n", \
    "The wagon suddenly races down the side of the mountain.\n", \
    "The air feels warmer as the wagon heads out of the mountains.\n", \
    "The wagon bounces along a track in the mountains.\n", \
    "The wagon comes out of the mountains, into the plains, and heads westward.\n", \
    "The wagon continues west along a track.\n", \
    "The wagon heads west through the plains.\n"})


#define VK_TO_FAERIE_MESSAGES ({ "@@set_wagon_full@@", \
    "The wagon heads east and heads into the plains.\n", \
    "The wagon follows a track west through the plains.\n", \
    "The wagon begins winding its way up into the mountains.\n", \
    "The wagon struggles along a track in the mountains.\n", \
    "The air becomes icy as the wagon travels higher in the mountains.\n", \
    "The wagon begins heading down out of the mountains.\n", \
    "The creeps slowly through the trees, following a mountain track.\n", \
    "The wagon turns east onto a hidden track and leaves the mountains behind.\n", \
    "The wagon runs southeast along a hidden track in a forest.\n", \
    "The wagon heads north along a forest track.\n"})