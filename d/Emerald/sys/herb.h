#ifndef EMERALD_HERB_DEFS
#define EMERALD_HERB_DEFS

#define EMERALD_HERB ("/d/Emerald/std/herb")

/*
 * HERB_DIR - The directory where the specific herbs are
 */
#define HERB_OBJ_DIR ("/d/Emerald/herbs")

/*
 * HERB_MANAGER - The herb manager object
 */
#define HERB_MANAGER ("/d/Emerald/sys/global/herb_manager")

/*
 * HERB_SHOP_FILE - The standard herb shop code
 */
#define HERB_SHOP_FILE (HERB_DIR + "herb_shop")

/*
 * RANDOM_HERB - Get a random herb from the standard herbs.  If rarity is >= 0,
 *              herbs with rarity greater than that value will be excluded.
 *              This macro returns a clone of such an herb.
 */
#define RANDOM_HERB(rarity) (object)HERB_MANAGER->random_herb(rarity);

/*
 * RANDOM_HERB_BY_RARITY - Get a random herb, taking rarity into account:  rarer
 *                        herbs are less likely to be chosen than more common
 *                        herbs.  If rarity is >= 0, herbs with rarity greater
 *                        than that value will be excluded. This macro returns
 *                        a clone of such an herb.
 */
#define RANDOM_HERB_BY_RARITY(rarity) \
    (object)HERB_MANAGER->random_herb_by_rarity(rarity);

/*
 * Herb rarity values
 */
#define HERB_EXTREMELY_RARE   1
#define HERB_VERY_RARE        2
#define HERB_RARE             4
#define HERB_SOMEWHAT_RARE    8
#define HERB_SLIGHTLY_RARE    16
#define HERB_SLIGHTLY_COMMON  32
#define HERB_SOMEWHAT_COMMON  64
#define HERB_COMMON           128
#define HERB_VERY_COMMON      256
#define HERB_EXTREMELY_COMMON 512

/*
 * Herb addiction factors
 */
#define HERB_GUARANTEED_ADDICTIVE  100
#define HERB_EXTREMELY_ADDICTIVE    90
#define HERB_VERY_ADDICTIVE         70
#define HERB_ADDICTIVE              50
#define HERB_SOMEWHAT_ADDICTIVE     30
#define HERB_SLIGHTLY_ADDICTIVE     10
#define HERB_NOT_ADDICTIVE           0

#endif
