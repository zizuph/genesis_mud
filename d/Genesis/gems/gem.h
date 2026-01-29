/*
 * /d/Genesis/gems/gem.h
 *
 * This header contains the necessary definitions for the Genesis gem system.
 */

#include "/d/Genesis/sys/gem.h"

/*
 * Indices to the arrays in the ALL_GEMS mapping.
 */
#define GEM_INDEX_TYPE   (0)
#define GEM_INDEX_PTYPE  (1)
#define GEM_INDEX_COLOUR (2)
#define GEM_INDEX_RARITY (3)
#define GEM_INDEX_VALUE  (4)
#define GEM_INDEX_VOLUME (5)
#define GEM_INDEX_WEIGHT (6)
#define GEM_INDEX_RANDOM (7)

/*
 * ALL_GEMS
 *
 * This definition contains a mapping with all gem known gem types. The index
 * of the mapping is the file name of the file used in the gem directory.
 *
 *  "File_name" : ({ "gem type", "plural type", "colour", rarity, value, volume, weight })
 */

