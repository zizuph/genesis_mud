#ifndef _WROAD_H_
#define _WROAD_H_

#include "/d/Gondor/defs.h"

#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
    "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])
#define AREA_DIR "/d/Gondor/lebennin/"
#define LEBENNIN_CORSAIR_PATROL "_lebennin_corsair_patrol"
#define LEBENNIN_STD_DIR AREA_DIR + "std/"
#define LEBENNIN_HERBS ([\
    0:({ HERB_DIR + "alfirin", HERB_DIR + "attanar", HERB_DIR + "basil",\
    HERB_DIR + "blackberry", HERB_DIR + "blueberry", HERB_DIR + "lissuin",\
    HERB_DIR + "lothore", HERB_DIR + "mint", HERB_DIR + "redweed",\
    HERB_DIR + "tuo", HERB_DIR + "tyelka", HERB_DIR + "ungolestel" }),\
    1:({ HERB_DIR + "astaldo", HERB_DIR + "athelas", HERB_DIR + "blung",\
    HERB_DIR + "braspberry", HERB_DIR + "caraway", HERB_DIR + "carrot",\
    HERB_DIR + "foxglove", HERB_DIR + "garlic", HERB_DIR + "ginger",\
    HERB_DIR + "gonion", HERB_DIR + "handasse", HERB_DIR + "holly",\
    HERB_DIR + "myrtle", HERB_DIR + "seregon", HERB_DIR + "suranie",\
    HERB_DIR + "tuo" }),\
    2:({ HERB_DIR + "athelas", HERB_DIR + "holly", HERB_DIR + "lothore",\
    HERB_DIR + "redweed", }),\
    3:({ HERB_DIR + "alfirin", HERB_DIR + "astaldo", HERB_DIR + "blung",\
    HERB_DIR + "braspberry", HERB_DIR + "caraway", HERB_DIR + "carrot",\
    HERB_DIR + "foxglove", HERB_DIR + "lothore", HERB_DIR + "redweed",\
    HERB_DIR + "tuo" }),\
    4:({ HERB_DIR + "alfirin", HERB_DIR + "astaldo", HERB_DIR + "attanar",\
    HERB_DIR + "basil", HERB_DIR + "blackberry", HERB_DIR + "blueberry",\
    HERB_DIR + "blung", HERB_DIR + "braspberry", HERB_DIR + "foxglove",\
    HERB_DIR + "tuo" }),\
    5:({ HERB_DIR + "athelas", HERB_DIR + "garlic", HERB_DIR + "gonion",\
    HERB_DIR + "ginger", HERB_DIR + "handasse", HERB_DIR + "holly",\
    HERB_DIR + "lothore", HERB_DIR + "redweed", HERB_DIR + "tyelka",\
    HERB_DIR + "ungolestel" }),\
    6:({ HERB_DIR + "astaldo", HERB_DIR + "attanar", HERB_DIR + "basil",\
    HERB_DIR + "blackberry", HERB_DIR + "blueberry", HERB_DIR + "blung",\
    HERB_DIR + "braspberry", HERB_DIR + "foxglove", HERB_DIR + "ginger",\
    HERB_DIR + "handasse", HERB_DIR + "myrtle", HERB_DIR + "seregon",\
    HERB_DIR + "tyelka", HERB_DIR + "ungolestel" }),\
    7:({ HERB_DIR + "athelas", HERB_DIR + "holly", HERB_DIR + "suranie",\
    HERB_DIR + "tuo", HERB_DIR + "tyelka", HERB_DIR + "ungolestel" }),\
    8:({ HERB_DIR + "alfirin", HERB_DIR + "astaldo", HERB_DIR + "athelas",\
    HERB_DIR + "caraway", HERB_DIR + "carrot", HERB_DIR + "foxglove",\
    HERB_DIR + "garlic", HERB_DIR + "gonion", HERB_DIR + "holly",\
    HERB_DIR + "lissuin", HERB_DIR + "lothore", HERB_DIR + "mint",\
    HERB_DIR + "myrtle", HERB_DIR + "redweed", HERB_DIR + "seregon",\
    HERB_DIR + "tuo" }) ])

#define LATE_NIGHT    0
#define LATE_NIGHT_RANGE    0..3    /*12am-3am*/
#define EARLY_MORNING 1
#define EARLY_MORNING_RANGE 4..7    /*4am-7am*/
#define MORNING       2
#define MORNING_RANGE       8..10   /*8am-10am*/
#define NOON          3
#define NOON_RANGE          11..13  /*11am-1pm*/
#define AFTERNOON     4
#define AFTERNOON_RANGE     14..17  /*2pm-5pm*/
#define EVENING       5
#define EVENING_RANGE       18..21  /*6pm-9pm*/
#define EARLY_NIGHT   6
#define EARLY_NIGHT_RANGE   22..24  /*10pm-12am*/

#define DAYLIGHT ([ EARLY_NIGHT:"moonlight", LATE_NIGHT:"starlight",\
    EARLY_MORNING:"morning light", MORNING: "morning sunlight",\
    NOON: "noon sunlight", AFTERNOON: "afternoon sunlight",\
    EVENING: "evening light" ])
#define DAY ([ EARLY_NIGHT:"early night", LATE_NIGHT:"late night",\
    EARLY_MORNING:"early morning", MORNING: "morning", NOON: "noon",\
    AFTERNOON: "afternoon", EVENING: "evening" ])
#define DAYTIME ([ EARLY_NIGHT:"night", LATE_NIGHT:"night",\
    EARLY_MORNING:"morning", MORNING: "morning", NOON: "noon",\
    AFTERNOON: "afternoon", EVENING: "evening" ])
#define SUN_MOON ([ EARLY_NIGHT:"moon", LATE_NIGHT:"stars",\
    EARLY_MORNING:"sun", MORNING: "sun", NOON: "sun", AFTERNOON: "sun",\
    EVENING: "sun" ])
#define LIGHT_TYPE ([ EARLY_NIGHT:"moonlight", LATE_NIGHT:"starlight",\
    EARLY_MORNING:"haze of dawn", MORNING: "sunlight", NOON: "sunlight",\
    AFTERNOON: "sunlight", EVENING: "glow of dusk" ])

#define CORSAIR_ADJ1 ({"scarred", "pock-marked", "handsome", "swarthy",\
    "angry", "shifty", "grim", "dirty", "haggard", "savage"})
#define CORSAIR_ADJ2 ({"young", "red-haired", "plump", "skinny",\
    "dark-skinned", "tall", "tiny"})
#endif /* _WROAD_H_ */
