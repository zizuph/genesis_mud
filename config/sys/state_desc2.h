/*
 * /sys/state_desc2.h
 *
 * Holds all textual descriptions of state descriptions of livings.
 *
 * Here local changes are made to the arrays defined in
 * /sys/state_desc.h
 */

/*
 * If you insert changes you are recommended to copy /sys/state_desc.h
 * to here and make changes. It is important that the below define is
 * defined afterwards:
 *    #ifndef SD_DEFINED
 *    #define SD_DEFINED
 *    #endif
 */

/*
 * SD_AV_TITLES - the titles themselves.
 * SD_AV_LEVELS - the stat level from which you get a title.
 * SD_NUM_AV_LEVELS - the number of titles and levels.
 *
 * The mortal 'level' titles.
 */

#define SD_NUM_AV_LEVELS 16
#define SD_AV_TITLES ({ "novice",           \
			"greenhorne",       \
			"beginner",         \
			"apprentice",       \
			"wanderer",         \
			"adventurer",       \
			"adept",            \
			"great adventurer", \
			"veteran",          \
			"expert",           \
			"rising hero",      \
			"hero",             \
			"titan",            \
			"champion",         \
			"legend",           \
			"myth" })

#define SD_AV_LEVELS ({   7, \
			 15, \
			 24, \
			 33, \
			 43, \
			 53, \
			 64, \
			 75, \
			 87, \
			 99, \
			112, \
			125, \
			140, \
			155, \
			170, \
			190 })

/*
 * SD_NEWBIE_INDEX - Index to the highest title in SD_AV_TITLES at which you
 *                   may be considered a newbie for game purposes.
 * SD_NEBWIE_TITLE - The highest title at which you may be considered a newbie
 *                   for game purposes. Hardcoded for speed reasons.
 *                   By definition: SD_AV_TITLES[SD_NEWBIE_INDEX]
 * SD_NEWBIE_LEVEL - The stat average below which you may be considered a
 *                   newbie for game purposes. AVSTAT < SD_NEWBIE_LEVEL.
 *                   Hardcoded for speed reasons.
 *                   By definition: SD_AV_LEVELS[SD_NEWBIE_INDEX + 1]
 */
#define SD_NEWBIE_INDEX 4
#define SD_NEBWIE_TITLE "wanderer"
#define SD_NEWBIE_LEVEL 53
