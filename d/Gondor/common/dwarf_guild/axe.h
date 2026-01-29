/*
 * /d/Gondor/common/dwarf_guild/axe.h
 *
 * Copyright (C) Stas van der Schaaf - January 25 1994
 *               Mercade @ Genesis
 *
 * This definition defines the possibility to tell the smith what kind of
 * axe they like. The define it a mapping with in it an array with:
 * - the possible answers (array of string)
 * - the cost for the answers (array of int) in silver coins
 *   (the difference wrt the default answer)
 * - the default answer of the question.
 * - a description explaining the different solutions.
 *
 * The index to the mapping is a string of what property it is about.
 *
 * Revision history:
 */

#define MAX_HIT_PEN        40

#define WOOD_TYPE_DESC     ({ "fir", "birch", "alder", "beech", "oak" })
#define WOOD_TYPE_PRICE    ({ -10,  -6,   0,   5,   9 })
#define WOOD_TYPE_DEF      "alder"
#define WOOD_TYPE_BREAK    ({   5,   3,   0,  -2,  -4 })
#define WOOD_TYPE_ITEM     ({ "low quality", "not so strong", "average", \
			      "strong", "very strong" })
#define WOOD_TYPE_VOLUME   ({   7,   4,   0,   0,  -1 })
#define WOOD_TYPE_WEIGHT   ({  -3,  -2,   0,   3,   5 })

#define METAL_TYPE_DESC    ({ "aluminium", "zinc", "tin", "iron", "bronze", \
			      "steel", "silver", "gold", "platinum" })
#define METAL_TYPE_PRICE   ({ -13,  -9,  -4,   0,   4,   8,  14,  19,  25 })
#define METAL_TYPE_DEF     "iron"
#define METAL_TYPE_DULL    ({  12,   8,   4,   0,  -3,  -6,  -9, -12, -15 })
#define METAL_TYPE_CORR    ({   9,   6,   3,   0,  -2,  -4,  -6,  -8, -10 })
#define METAL_TYPE_PEN     ({  -3,  -2,  -1,   0,   1,   2,   3,   4,   5 })
#define METAL_TYPE_VOLUME  ({   2,   2,   1,   1,   0,   0,  -1,  -1,  -2 })
#define METAL_TYPE_WEIGHT  ({ -24,  -8,  -4,   0,   8,   0,  20,  40,  60 })

#define BLADE_SIZE_DESC    ({ "small", "normal", "medium", "broad" })
#define BLADE_SIZE_PRICE   ({  -9,   0,   5,  13 })
#define BLADE_SIZE_DEF     "normal"
#define BLADE_SIZE_PEN     ({  -3,   0,   3,   6 })
#define BLADE_SIZE_HIT     ({  -1,   0,   2,   5 })
#define BLADE_SIZE_ITEM    ({ "small", "normal-sized", "medium-sized", \
			      "broad" })
#define BLADE_SIZE_VOLUME  ({  -5,   0,   5,  10 })
#define BLADE_SIZE_WEIGHT  ({  -7,   0,   8,  15 })

#define HAFT_LENGTH_DESC   ({ "short", "normal", "medium", "long" })
#define HAFT_LENGTH_PRICE  ({  -9,   0,   7,  16 })
#define HAFT_LENGTH_DEF    "normal"
#define HAFT_LENGTH_BREAK  ({  -2,   0,   2,   3 })
#define HAFT_LENGTH_HIT    ({   4,   0,  -3,  -5 })
#define HAFT_LENGTH_PEN    ({  -2,   0,   2,   3 })
#define HAFT_LENGTH_ITEM   ({ "short", "normal-sized", "medium-sized", \
			      "long" })
#define HAFT_LENGTH_VOLUME ({ -15,   0,  10,  20 })
#define HAFT_LENGTH_WEIGHT ({ -15,   0,  10,  20 })

#define NUM_HANDS_DESC     ({ "one", "two" })
#define NUM_HANDS_PRICE    ({   0,  10 })
#define NUM_HANDS_DEF      "one"
#define NUM_HANDS_ADJ      ({ "single", "double" })
#define NUM_HANDS_PEN      ({   0,   5 })
#define NUM_HANDS_HIT      ({   0,  -3 })

/* The indices to the AXES_DEFINITION mapping.
 */
#define INDEX_TYPES        0
#define INDEX_PRICES       1
#define INDEX_DESCRIPTION  2

/* The order of the properties.
 */
#define INDEX_WOOD_TYPE     0
#define INDEX_METAL_TYPE    1
#define INDEX_BLADE_SIZE    2
#define INDEX_HAFT_LENGTH   3
#define INDEX_NUM_HANDS     4

#define AXE_PROPERTIES_ORDER ({ \
  "wood",                       \
  "metal",                      \
  "blade",                      \
  "haft",                       \
  "hands"                       \
  })

#define AXES_DEFINITION ([                                                  \
  "wood" : ({                                                               \
     WOOD_TYPE_DESC,                                                        \
     WOOD_TYPE_PRICE,                                                       \
     "The quality of the wood of the haft is determines how quick the " +   \
     "haft will break. Good quality will last longer, though is more " +    \
     "expensive naturally."                                                 \
     }),                                                                    \
  "metal" : ({                                                              \
     METAL_TYPE_DESC,                                                       \
     METAL_TYPE_PRICE,                                                      \
     "The type of metal that is used for the blade determines how " +       \
     "durable the blade is. Also, it gives you more status to have a " +    \
     "golden blade than to have a blade that is made of iron."              \
     }),                                                                    \
  "blade" : ({                                                              \
     BLADE_SIZE_DESC,                                                       \
     BLADE_SIZE_PRICE,                                                      \
     "With a broad blade you will do more damage to your opponent than " +  \
     "with a smaller blade."                                                \
     }),                                                                    \
  "haft" : ({                                                               \
     HAFT_LENGTH_DESC,                                                      \
     HAFT_LENGTH_PRICE,                                                     \
     "If your axe has a short haft, you will be able to hit your enemy " +  \
     "easily, however, you will do less damage. With a long haft you " +    \
     "will have more problems hitting, though when you hit, you will do " + \
     "more damage."                                                         \
     }),                                                                    \
  "hands" : ({                                                              \
     NUM_HANDS_DESC,                                                        \
     NUM_HANDS_PRICE,                                                       \
     "A two-handed axe will do more damage than a single-handed axe, " +    \
     "though it is harder to handle one, i.e. harder to hit with."          \
     })                                                                     \
  ])

#define DEFAULT_AXE_PROPERTIES ([ \
  "wood"  : WOOD_TYPE_DEF,        \
  "metal" : METAL_TYPE_DEF,       \
  "blade" : BLADE_SIZE_DEF,       \
  "haft"  : HAFT_LENGTH_DEF,      \
  "hands" : NUM_HANDS_DEF,        \
  ])
