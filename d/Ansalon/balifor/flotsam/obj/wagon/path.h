// Do NOT add .c after filenames or it will not work

#define WAGON_STOPS     ({ ROOM_FLOTSAM + "alley",  \
    ROOM_NERAKA + "backyard" })

#define CARGO_TYPES     ({ "grain", "sacks", "crates", \
    "potatoes", "furs" })

#define NERAKA_TO_FLOTSAM  ({ WAGON_STOPS[1], 60, \
    AVOID, 1,   \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1    })

#define FLOTSAM_TO_NERAKA  ({ WAGON_STOPS[0], 60, \
    AVOID, 1,   \
    AVOID, 1,  \
    AVOID, 1, \
    AVOID, 1, \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1,  \
    AVOID, 1    })

#define NERAKA_TO_FLOTSAM_MESSAGES ({ "@@set_wagon_empty@@",           \
    "The sounds of the encampment fade away as the wagon "+ \
        "heads south on the dusty road.\n", \
    "The wagon follows the road up out of a wide valley.\n", \
    "As the wagon travels further into the mountains, the air gets "+ \
        "colder and chilly wind whistles through the opening in the "+ \
        "canvas.\n", \
    "The air is decidedly freezing-cold and you pass several "+ \
        "snow-clad peaks.\n", \
    "The wagon travels downhill into a small valley and the air "+ \
        "warms up a bit.\n", \
    "The wagon follows a winding road out of the valley.\n", \
    "The wagon raids down out of the mountains. Moist and warm "+ \
        "air refreshes you.\n", \
    "The wagon heads east as it follows the road into the wilderness.\n", \
    "Gaining in speed, the wagon heads southeast along the narrow "+ \
        "path.\n", \
    "The wagon heads east along a sandy road.\n", \
    "The wagon slows down as he comes near the city. Soon after, " +\
        "wheels start their staccato on cobblestones.\n" })

#define FLOTSAM_TO_NERAKA_MESSAGES ({ "@@set_wagon_full@@", \
    "Wheels clatter on cobblestones as the wagon rides through the "+\
        "city and then it heads westwards along a sandy road.\n", \
    "Gaining in speed, the wagon heads northwest along the narrowing "+ \
        "path.\n", \
    "The wagon rides west as it follows the road into the " +\
        "wilderness.\n", \
    "Rolling across the plains the wagon advance toward the mountains.\n", \
    "The air grows chilly as the wagon follows a winding track in "+ \
        "the mountains. You hear horses whine and loudly neigh.\n", \
    "The wagon travels downhill into a small valley.\n", \
    "The road climbs again and the air is getting even colder.\n", \
    "As you travel through narrow passage you hear the wind whistling "+ \
        "in the openings in the canvas.\n", \
    "Slowly the wagon follows the road down into wide valley.\n", \
    "The wagon heads north on a dusty road.\n", \
    "The wheels of the wagon clatter on cobblestones as it rides "+ \
        "through the city.\n" })
