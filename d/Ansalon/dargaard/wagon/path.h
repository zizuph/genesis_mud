#define WAGON_STOPS     ({ DROOM + "road2",  \
    DROOM + "road1" })

#define CARGO_TYPES     ({ "torches", "sacks", "crates"})

#define NIGHTLUND_TO_DARGAARD  ({ WAGON_STOPS[0], 60, \
    AVOID, 5,  \
    AVOID, 7,  \
    AVOID, 10, \
    AVOID, 7,  \
    AVOID, 7,  \
    AVOID, 7,  \
    AVOID, 5    })

#define DARGAARD_TO_NIGHTLUND  ({ WAGON_STOPS[1], 60, \
    AVOID, 5,   \
    AVOID, 7,  \
    AVOID, 7,  \
    AVOID, 7,  \
    AVOID, 10,  \
    AVOID, 7,  \
    AVOID, 5    })

#define DARGAARD_TO_NIGHTLUND_MESSAGES ({ "@@set_wagon_empty@@",        \
    "The chariot heads east along a small mountainroad.\n",             \
    "The chariot turns to the south and begins a steep climb into " +   \
    "the Dargaard Mountains.\n",                                        \
    "A cold wind blows through the chariot as the wagon continues " +   \
    "on its way in the mountains.\n",                                   \
    "The chariot heads southeast towards Dargaard Keep.\n",             \
    "The chariot continues to the southeast.\n",                        \
    "The blackened Dargaard Keep arises in the distance.\n",            \
    "The chariot enters a small road close to Dargaard Keep.\n"})

#define NIGHTLUND_TO_DARGAARD_MESSAGES ({ "@@set_wagon_full@@",         \
    "The chariot enters a small road close to Dargaard Keep.\n",        \
    "The blackened Dargaard Keep disappears in the distance.\n",        \
    "The chariot heads northwest away from Dargaard Keep.\n",           \
    "The chariot continues to the northwest.\n",                        \
    "A cold wind blows through the chariot as the wagon continues " +   \
    "on its way in the mountains.\n",                                   \
    "The chariot turns to the south and begins a steep climb into " +   \
    "the Dargaard Mountains.\n",                                        \
    "The chariot heads west along a small mountainroad.\n"})
    
    
                        
