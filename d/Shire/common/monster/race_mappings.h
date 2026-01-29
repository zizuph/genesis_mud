/*
 * Mappings of alignment, stats, forms of speaking, height, weight, and skills
 * (and properties?) used by the random_race.c template.
 */

/*
 * RACESTATMOD
 *
 * This mapping holds the standard modifiers of each stat, i.e. a dwarf
 * should have it easier to raise con than other races, but get a harder
 * time raising its int.
 *
 * Mapping is: race:  str, dex, con, int, wis, dis
 */
#define RACESTATMOD ([       \
        NON_HUMANOID : ({ 100, 100, 100, 100, 100, 100 }), \
	HUMAN        : ({ 100, 100, 100, 100, 100, 100 }), \
	ELF          : ({  70, 120,  80, 150, 140,  90 }), \
        DWARF        : ({ 150,  50, 150,  80,  90, 130 }), \
        HOBBIT       : ({  60, 220,  80, 110, 100,  90 }), \
        GNOME        : ({  90, 140,  70, 190,  80,  80 }), \
        GOBLIN       : ({ 180,  90, 140,  60,  90,  60 }), \
        ORC          : ({ 200, 100, 160,  75,  80,  80 }), \
        HOBGOBLIN    : ({ 110, 120, 110,  60,  90, 100 }), \
        KOBOLD       : ({  80, 110,  90,  75,  85,  80 }), \
        URUK-HAI     : ({ 180, 120, 200,  90, 100, 100 }), \
        HALF-ORC     : ({ 120,  90, 110,  90, 110,  90 }), \
        HALF-ELF     : ({  90, 110,  90, 130, 130, 100 }), \
        TROLL        : ({ 300,  50, 275,  20, 120, 130 }), \
        DRACONIAN    : ({ /* Ask Nick, Percy to fill in these percentages. */ }), \
/* Should draconians be in my 'animal_races' list? */ \
        MERFOLK      : ({  80, 120, 150, 100, 130, 100 }), \
        WEREWOLF     : ({ 170, 120, 140,  60,  70, 200 }), \
        CENTAUR      : ({ 200,  80, 170,  90, 110,  90 }), \
/* Are centaurs humanoid enough for this list? */ \
        NYMPH        : ({ 100, 110, 100, 100, 110, 150 }), \
/* Are nymphs different enough from humans? */ \
        FAERIE       : ({   5, 200,  10, 200, 300, 120}), \
        LEPRECHAUN   : ({  60, 180,  50, 180, 200, 100 }), \
/* Leprechauns seem to be a lot like imps. */ \
        IMP          : ({  60, 190,  40, 160, 170,  90 }), \
        GIANT        : ({ 300,  80, 300,  50,  80, 150 }), \
        MINOTAUR     : ({ 350, 120, 320,  70,  60, 200 }), \
        CYCLOPS      : ({ 320,  60, 350,  35,  50, 180 }), \
        OGRE         : ({ 270,  80, 250,  30,  30, 120 }), \
        YETI         : ({ 220, 100, 340,  10,  10,  80 }), \
        ETTIN        : ({ 300,  70, 400,  75,  75, 150 }), \
        VAMPIRE      : ({ 150, 100, 200, 110, 110, 150 }), \
        ZOMBIE       : ({ 110, 100,  70,   0,   0, 100 }), \
        GHOST        : ({  50, 120, 150, 100, 100, 130 }), \
        MUMMY        : ({ 130,  80, 120,   0,   0, 130 }), \
	DEMON        : ({ 120, 100, 160,  90, 120, 130 }), \
        ])

#define RACIAL_GOOD_ALIGN_MAP ([  \
        NON_HUMANOID : 100, \
        HUMAN        : 100, \
        ELF          : 150, \
        DWARF        : 110, \
        GNOME        : 100, \
        HOBBIT       : 110, \
        GOBLIN       :   0, \
        ORC          :   0, \
        HOBGOBLIN    :   0, \
        KOBOLD       :   0, \
        URUK-HAI     :   0, \
        HALF-ORC     :  20, \
        HALF-ELF     : 120, \
        TROLL        :  50, \
        DRACONIAN    :   0, \
        MERFOLK      : 120, \
        WEREWOLF     :  30, \
        CENTAUR      :  60, \
        NYMPH        :  20, \
        FAERIE       :  60, \
        LEPRECHAUN   :  80, \
        IMP          :  20, \
        GIANT        :  75, \
        MINOTAUR     :  10, \
        CYCLOPS      :   0, \
        OGRE         :   5, \
        YETI         :  40, \
        ETTIN        :   5, \
        VAMPIRE      :   0, \
        ZOMBIE       :   0, \
        GHOST        :  90, \
        MUMMY        :   0, \
        DEMON        :  40, \
        ])

#define RACIAL_BAD_ALIGN_MAP ([  \
        NON_HUMANOID : 100, \
        HUMAN        : 100, \
        ELF          :  20, \
        DWARF        :  40, \
        GNOME        : 100, \
        HOBBIT       :  75, \
        GOBLIN       : 150, \
        ORC          : 200, \
        HOBGOBLIN    : 180, \
        KOBOLD       : 120, \
        URUK-HAI     : 250, \
        HALF-ORC     : 160, \
        HALF-ELF     :  75, \
        TROLL        : 150, \
        DRACONIAN    : 200, \
        MERFOLK      :  60, \
        WEREWOLF     :  50, \
        CENTAUR      :  40, \
        NYMPH        :  60, \
        FAERIE       :  30, \
        LEPRECHAUN   :  50, \
        IMP          : 140, \
        GIANT        : 150, \
        MINOTAUR     : 200, \
        CYCLOPS      : 220, \
        OGRE         : 160, \
        YETI         :  70, \
        ETTIN        : 205, \
        VAMPIRE      : 300, \
        ZOMBIE       :  80, \
        GHOST        : 110, \
        MUMMY        :  80, \
        DEMON        : 300, \
        ])

#define RACIAL_HEIGHT_MAP ([    \
        NON_HUMANOID : 100, \
        HUMAN        : 100, \
        ELF          :  72, \
        DWARF        :  66, \
        GNOME        :  50, \
        HOBBIT       :  61, \
        GOBLIN       :  80, \
        ORC          : 120, \
        HOBGOBLIN    :  90, \
        KOBOLD       :  50, \
        URUK-HAI     : 130, \
        HALF-ORC     : 100, \
        HALF-ELF     :  95, \
        TROLL        : 140, \
        DRACONIAN    :  65, \
        MERFOLK      : 100, \
        WEREWOLF     : 110, \
        CENTAUR      : 120, \
        NYMPH        : 100, \
        FAERIE       :   8, \
        LEPRECHAUN   :  60, \
        IMP          :  20, \
        GIANT        : 180, \
        MINOTAUR     : 160, \
        CYCLOPS      : 200, \
        OGRE         : 150, \
        YETI         : 150, \
        ETTIN        : 160, \
        VAMPIRE      : 100, \
        ZOMBIE       :  95, \
        GHOST        : 100, \
        MUMMY        : 105, \
        DEMON        : 100, \
        ])

#define RACIAL_WEIGHT_MAP ([    \
        NON_HUMANOID : 100, \
        HUMAN        : 100, \
        ELF          :  65, \
        DWARF        : 100, \
        GNOME        :  65, X\
        HOBBIT       :  55, X\
        GOBLIN       :  90, X\
        ORC          : 120, \
        HOBGOBLIN    :  70, \
        KOBOLD       :  60, \
        URUK-HAI     : 140, \
        HALF-ORC     : 110, \
        HALF-ELF     :  80, \
        TROLL        : 160, \
        DRACONIAN    :  70, \
        MERFOLK      : 100, \
        WEREWOLF     : 110, \
        CENTAUR      : 200, \
        NYMPH        : 100, \
        FAERIE       :   2, \
        LEPRECHAUN   :  50, \
        IMP          :  10, \
        GIANT        : 300, \
        MINOTAUR     : 250, \
        CYCLOPS      : 350, \
        OGRE         : 200, \
        YETI         : 200, \
        ETTIN        : 250, \
        VAMPIRE      : 100, \
        ZOMBIE       :  80, \
        GHOST        :   0, \
        MUMMY        : 115, \
        DEMON        : 100, \
        ])
