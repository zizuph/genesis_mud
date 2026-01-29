#define TOROID_DIR		"/d/Sparkle/clubs/toroid/"
#define TOROID_DATA		TOROID_DIR + "data/"
#define TOROID_LOG		TOROID_DIR + "log/"

// Master Objects
#define TOROID_MANAGER      (TOROID_DIR + "fishing_manager")

// Fishing Club
#define CLUB_SOUL            TOROID_DIR + "toroid_club_soul"
#define CLUB_OBJ             TOROID_DIR + "toroid_club_obj"

// Useful Macros
#define IS_CLUB_MEMBER(x)	TOROID_MANAGER->query_is_member(x)
#define TOROID_DEBUG(x)	    find_player("cherek")->catch_msg("[Toroid] " + x + "\n")

// Fishing levels
#define TOROID_CLUB_XP(x)          TOROID_MANAGER->query_fishing_experience(x)
#define TOROID_CLUB_STAT(x)        (x)->exp_to_stat(TOROID_CLUB_XP(x))


#define TOROID_NUM_AV_LEVELS 16
#define TOROID_AV_TITLES ({ "novice",           \
			"amateur",       \
			"enthusiastic",         \
			"weathered",       \
			"practiced",         \
			"experienced",       \
			"adept",            \
			"skillful", \
			"veteran",          \
			"expert",           \
			"professional",      \
			"phenomenal",             \
			"prodigious",            \
			"champion",         \
			"legendary",           \
			"master" })

#define TOROID_AV_LEVELS ({   7, \
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

