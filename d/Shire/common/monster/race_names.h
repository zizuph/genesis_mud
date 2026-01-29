/* don't use this define, nothing here helps make non_humanoid creatures. */
#define NON_HUMANOID 0

/* Login races */
#define HUMAN 1 /* align: neutral, def. say: yells */
#define ELF 2 /* align: good, def. say: sings */
#define DWARF 4 /* align: good, def. say: thunders */
#define GNOME 8 /* align: neutral, def. say: yodels */
#define HOBBIT 16 /* align: good-neutral, def. say: chirps */
#define GOBLIN 32 /* align: evil, def. say: grunts */

/* Orcish races */
#define GOBLIN 32 /* align: evil, def. say: grunts */
#define ORC 64 /* align: evil, def. say: growls */
#define HOBGOBLIN 128 /* align: evil, def. say: snarls */
#define KOBOLD 256 /* align: evil, def. say: whines */
#define URUK-HAI 512 /* align: evil, def. say: growls(?) */

/* Misc. races */
#define HALF_ELF 1024 /* good-neutral, sings(?) */
#define TROLL 2048 /* evil-neutral, rumbles */
#define DRACONIAN 4096 /* evil, hisses */

/* Animalistic humanoids */
#define MERFOLK 8192 /* good, bubbles */
#define WEREWOLF 16384 /* neutral, howls */
#define CENTAUR 32768 /* neutral, brays/neighs/whinnies */

/* Faerie creatures */
#define CENTAUR 32768 /* neutral, brays/neighs/whinnies */
#define NYMPH 65536 /* neutral, whispers */
#define FAERIE 131072 /* neutral, giggles */ /* Two alternate spellings */
#define FAIRY FAERIE /* neutral, giggles */
#define DRYAD 262144 /* good, rustles */
#define LEPRECHAUN 524288 /* good, ? */
#define IMP 1048576 /* neutral, ? */

/* Giant races */
#define GIANT 2097152 /* neutral, booms */
#define MINOTAUR 4194304 /* evil, neigh/whinny/bray */
#define CYCLOPS 8388608 /* evil, ? */
#define OGRE 16777216 /* evil, growls */
#define YETI 33554432 /* neutral, ? */
#define ETTIN 67108864 /* evil, echoes */

/* Creatures of the underworld */
#define VAMPIRE 134217728 /* evil, ? */
#define ZOMBIE 268435456 /* evil, groans */
#define GHOST 536870912 /* neutral, rattles */
#define MUMMY 1073741824 /* evil, moans */
#define DEMON -2147483648 /* evil, howls/hisses(?) */


#define LOGIN_RACES (ELF | DWARF | GNOME | HUMAN | HOBBIT | GOBLIN)
#define ORCISH_RACES (ORC | GOBLIN | HOBGOBLIN | KOBOLD)
#define MISC_RACES (HALF_ELF | DRACONIAN | TROLL)
#define ANIMAL_RACES (MERFOLK | WEREWOLF | CENTAUR)
#define FAERIE_RACES (CENTAUR | NYMPH | FAERIE | DRYAD | LEPRECHAUN)
#define FAIRY_RACES FAERIE_RACES
#define GIANT_RACES (GIANT | MINOTAUR | CYCLOPS | OGRE | YETI | ETTIN)
#define UNDEAD_RACES (VAMPIRE | ZOMBIE | GHOST | MUMMY)
#define UNDERWORLD_RACES (UNDEAD_RACES | DEMON)
#define ALL_RACES (LOGIN_RACES | MISC_RACES | ORCISH_RACES | ANIMAL_RACES | FAERIE_RACES | GIANT_RACES | UNDERWORLD_RACES)

#define RACE_NUM_TO_STRING ([    \
        NON_HUMANOID : "non_humanoid" \
        HUMAN        : "human"        \
        ELF          : "elf"          \
        DWARF        : "dwarf"        \
        HOBBIT       : "hobbit"       \
        GNOME        : "gnome"        \
        GOBLIN       : "goblin"       \
        ORC          : "orc"          \
        HOBGOBLIN    : "hobgoblin"    \
        KOBOLD       : "kobold"       \
        URUK-HAI     : "uruk-hai"     \
        HALF-ELF     : "half-elf"     \
        TROLL        : "troll"        \
        DRACONIAN    : "draconian"    \
        MERFOLK      : "merfolk"      \
        WEREWOLF     : "werewolf"     \
        CENTAUR      : "centaur"      \
        NYMPH        : "nymph"        \
        FAERIE       : "faerie"       \
        DRYAD        : "dryad"        \
        LEPRECHAUN   : "leprechaun"   \
        IMP          : "imp"          \
        GIANT        : "giant"        \
        MINOTAUR     : "minotaur"     \
        CYCLOPS      : "cyclops"      \
        OGRE         : "ogre"         \
        YETI         : "yeti"         \
        ETTIN        : "ettin"        \
        VAMPIRE      : "vampire"      \
        ZOMBIE       : "zombie"       \
        GHOST        : "ghost"        \
        MUMMY        : "mummy"        \
        DEMON        : "demon"        \
        ])

#define RACE_STRING_TO_NUM ([    \
        "non_humanoid" : NON_HUMANOID \
        "human"        : HUMAN        \
        "elf"          : ELF          \
        "dwarf"        : DWARF        \
        "hobbit"       : HOBBIT       \
        "gnome"        : GNOME        \
        "goblin"       : GOBLIN       \
        "orc"          : ORC          \
        "hobgoblin"    : HOBGOBLIN    \
        "kobold"       : KOBOLD       \
        "uruk-hai"     : URUK-HAI     \
        "half-elf"     : HALF-ELF     \
        "troll"        : TROLL        \
        "draconian"    : DRACONIAN    \
        "merfolk"      : MERFOLK      \
        "werewolf"     : WEREWOLF     \
        "centaur"      : CENTAUR      \
        "nymph"        : NYMPH        \
        "faerie"       : FAERIE       \
        "dryad"        : DRYAD        \
        "leprechaun"   : LEPRECHAUN   \
        "imp"          : IMP          \
        "giant"        : GIANT        \
        "minotaur"     : MINOTAUR     \
        "cyclops"      : CYCLOPS      \
        "ogre"         : OGRE         \
        "yeti"         : YETI         \
        "ettin"        : ETTIN        \
        "vampire"      : VAMPIRE      \
        "zombie"       : ZOMBIE       \
        "ghost"        : GHOST        \
        "mummy"        : MUMMY        \
        "demon"        : DEMON        \
        ])
