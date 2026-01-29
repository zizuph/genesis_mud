#define WAGON_STOPS     ({ NOUTER + "main/r8",  \
    "/d/Ansalon/taman_busuk/sanction/room/city/pier05" })

#define CARGO_TYPES     ({ "turnips", "sacks", "crates", \
    "potatoes", "furs" })

#define NERAKA_TO_SANCTION  ({ WAGON_STOPS[0], 60, \
    AVOID, 5,   \
    AVOID, 10,  \
    AVOID, 15,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 5    })

#define SANCTION_TO_NERAKA  ({ WAGON_STOPS[1], 60, \
    AVOID, 5,   \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 10,  \
    AVOID, 15,  \
    AVOID, 10,  \
    AVOID, 5    })

#define NERAKA_TO_SANCTION_MESSAGES ({ "@@set_wagon_empty@@",           \
    "The wagon heads north along a bumpy road.\n",                      \
    "The wagon heads west as it follows the road climbing up into " +   \
    "the mountains.\n",                                                 \
    "The air grows chilly as the wagon follows a winding track in " +   \
        "the mountains.\n",                                             \
    "The wagon travels downhill into a warmer valley.\n",               \
    "The road climbs again, but the air is getting warmer.\n",          \
    "A thick smell of sulphur permeates the air that steadily grows " + \
        "warmer as the wagon travels southwards.\n",                    \
    "The wheels of the wagon clatter on cobblestones.\n"    })

#define SANCTION_TO_NERAKA_MESSAGES ({ "@@set_wagon_full@@",            \
    "The wagon heads north out of the city.\n",                         \
    "The wagon climbs slowly up into the mountains.\n",                 \
    "The air is getting fresher as you leave behind you the " +         \
        "volcanic mountains of Sanction.\n",                            \
    "The wagon follows a winding road in the mountain, heading " +      \
        "northeastwards.\n",                                            \
    "The air is decidedly chilly and you pass several snow-clad " +     \
        "peaks.\n",                                                     \
    "The wagon follows the track down into a wide valley.\n",           \
    "The wagon heads south on a dusty road.\n"  })
    
    
                        
