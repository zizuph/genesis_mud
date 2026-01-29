/*
 * /d/Genesis/sys/gem.h
 *
 * This header contains the necessary definitions for the Genesis gem system.
 */

#ifndef GEM_DEFINITIONS
#define GEM_DEFINITIONS

/*
 * GEM_DIR          - The base directory where gem-related files are.
 * GEM_OBJ_DIR      - The directory where the specific gems are.
 * GEM_OBJECT(name) - The complete file name of the gem with file name 'name'.
 * GEM_FILE         - The standard gem object.
 * GEM_MANAGER      - The gem manager object.
 * GEM_SHOP_FILE    - The standard gem shop code.
 */
#define GEM_DIR          ("/d/Genesis/gems/")
#define GEM_OBJ_DIR      (GEM_DIR + "obj/")
#define GEM_OBJECT(name) (GEM_OBJ_DIR + (name))
#define GEM_FILE         (GEM_DIR + "gem")
#define GEM_MANAGER      (GEM_DIR + "gem_manager")
#define GEM_SHOP_FILE    (GEM_DIR + "gem_shop")

/*
 * IS_GEM_OBJECT(obj) - Test whether this is a valid Genesis gem object. To be
 *                      a valid gem object, the item must have its code in the
 *                      Genesis gem dir. Note that the length of the #define
 *                      GEM_OBJ_DIR is implicitly defined herein for speed. 
 */
#define IS_GEM_OBJECT(obj) (extract(file_name(obj), 0, 19) == GEM_OBJ_DIR)

/*
 * FILTER_GEMS(array) - Validate all items in an array to see whether they are
 *                      Genesis gem objects. See the remark at IS_GEM_OBJECT.
 */
#define FILTER_GEMS(array) filter((array), &operator(==)(GEM_OBJ_DIR, ) @ &extract(, 0, 19) @ file_name)

/*
 * QUERY_GEM_NAMES(rarity)
 *
 * Return the names of all gems with a certain rarity or less rare. If GEM_ALL
 * or an invalid rarity then all gem names are returned. Note, the returned
 * names are the filenames in the gem directory.
 */
#define QUERY_GEM_NAMES(rarity) (string *)GEM_MANAGER->query_gem_names(rarity)

/*
 * RANDOM_GEM(rarity)
 * RANDOM_GEM_BY_RARITY(rarity)
 *
 * Get a random gem from the standard gems. If rarity is > GEM_ALL, gems more
 * rare than that value will be excluded. This macro returns a clone of such
 * a gem. RANDOM_GEM uses equal chance on all gems, while RANDOM_GEM_BY_RARITY
 * gives more chance to more common gems.
 */
#define RANDOM_GEM(rarity) (object)GEM_MANAGER->random_gem(rarity)
#define RANDOM_GEM_BY_RARITY(rarity) (object)GEM_MANAGER->random_gem_by_rarity(rarity)

/*
 * IDENTIFY_GEMS(text)
 *
 * Find out which gems a player could mean with a certain text. It will give
 * return an array with the (file)names of all gems that match the text.
 */
#define IDENTIFY_GEMS(text) (string *)GEM_MANAGER->identify_gems(text)

/*
 * QUERY_GEM_PROPERTIES(name) - Gets an array with the properties of a gem.
 *
 * QUERY_GEM_TYPE(name)   - The type of a gem name.
 * QUERY_GEM_PTYPE(name)  - The plural type of a gem.
 * QUERY_GEM_COLOUR(name) - The colour of a gem name.
 * QUERY_GEM_RARITY(name) - The rarity of a gem name.
 * QUERY_GEM_VALUE(name)  - The value of a gem name.
 * QUERY_GEM_VOLUME(name) - The volume of a gem name.  
 * QUERY_GEM_WEIGHT(name) - The weight of a gem name.
 */
#define QUERY_GEM_PROPERTIES(name) GEM_MANAGER->query_gem_properties(name)

#define QUERY_GEM_TYPE(name)   (string)GEM_MANAGER->query_gem_property((name), GEM_INDEX_TYPE)
#define QUERY_GEM_PTYPE(name)  (string)GEM_MANAGER->query_gem_property((name), GEM_INDEX_PTYPE)
#define QUERY_GEM_COLOUR(name) (string)GEM_MANAGER->query_gem_property((name), GEM_INDEX_COLOUR)
#define QUERY_GEM_RARITY(name) (int)GEM_MANAGER->query_gem_property((name), GEM_INDEX_RARITY)
#define QUERY_GEM_VALUE(name)  (int)GEM_MANAGER->query_gem_property((name), GEM_INDEX_VALUE)
#define QUERY_GEM_VOLUME(name) (int)GEM_MANAGER->query_gem_property((name), GEM_INDEX_VOLUME)
#define QUERY_GEM_WEIGHT(name) (int)GEM_MANAGER->query_gem_property((name), GEM_INDEX_WEIGHT)

/*
 * Gem rarity values. Use GEM_ALL to ignore rarity.
 */
#define GEM_ALL                (0)
#define GEM_EXTREMELY_RARE     (1)
#define GEM_VERY_RARE          (2)
#define GEM_RARE               (4)
#define GEM_SOMEWHAT_RARE      (8)
#define GEM_SLIGHTLY_RARE     (16)
#define GEM_SLIGHTLY_COMMON   (32)
#define GEM_SOMEWHAT_COMMON   (64)
#define GEM_COMMON           (128)
#define GEM_VERY_COMMON      (256)
#define GEM_EXTREMELY_COMMON (512)

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

/*
 * ALL_GEMS
 *
 * This definition contains a mapping with all gem known gem types. The index
 * of the mapping is the file name of the file used in the gem directory.
 *
 *  "File_name" : ({ "gem type", "plural type", "colour", rarity, value, volume, weight })
 */

/* No definitions beyond this line. */
#endif GEM_DEFINITIONS
