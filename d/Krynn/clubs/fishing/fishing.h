#define FISH_DIR             "/d/Krynn/clubs/fishing/"
#define FISH_DATA            FISH_DIR + "data/"
#define FISH_LOG             FISH_DIR + "log/"

// Master Objects
#define FISHING_MANAGER      (FISH_DIR + "fishing_manager")

// Fishing Club
#define CLUB_SOUL            FISH_DIR + "angler_club_soul"
#define CLUB_OBJ             FISH_DIR + "angler_club_obj"

// Useful Macros
#define IS_ANGLER(x)                FISHING_MANAGER->query_is_member(x)
#define FISHING_DEBUG(x)	    find_player("arman")->catch_msg("[Fishing] " + x + "\n")

// Fishing levels
#define FISHING_CLUB_XP(x)          FISHING_MANAGER->query_fishing_experience(x)
#define FISHING_CLUB_STAT(x)        (x)->exp_to_stat(FISHING_CLUB_XP(x))


#define FISHING_NUM_AV_LEVELS 16
#define FISHING_AV_TITLES ({ "novice",           \
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

#define FISHING_AV_LEVELS ({   7, \
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

