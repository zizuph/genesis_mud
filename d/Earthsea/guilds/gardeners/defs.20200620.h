/* --- Directories --- */

#define GARDENER_DIR "/d/Earthsea/guilds/gardeners/"
#define GARDENER_HELP "/d/Earthsea/guilds/gardeners/help/"

/* --- Files --- */

#define GARDENER_SHADOW_LAY (GARDENER_DIR + "shadow")
#define GARDENER_SHADOW_CFT (GARDENER_DIR + "shadow_cft")
#define GARDENER_SOUL (GARDENER_DIR + "soul")
#define GARDENER_HERBS (GARDENER_DIR + "herbdb")
#define GARDENER_LOG_MEMBERS (GARDENER_DIR + "log/members")
#define GARDENER_NEWS (GARDENER_DIR + "news.txt")
#define GARDENER_TRAINER (GARDENER_DIR + "room/shed")

/* --- Member Files --- */

#define MEMBER_DIR(x) (GARDENER_DIR + "members/" + x[0..0] + "/" + x + "/")
#define MEMBER_DATA(x) (MEMBER_DIR(x) + "data")
#define MEMBER_NOTES(x) (MEMBER_DIR(x) + "notes")
#define MEMBER_JOURNAL(x) (MEMBER_DIR(x) + "journal")
#define MEMBER_HERBS(x) (MEMBER_DIR(x) + "herbs")
#define GEN_OLD_MEMBER_DIR(x) (GARDENER_DIR + "members/" + x[0..0] + "/old_" + x + "_" + time() + "/")

/* --- Objects --- */

#define GARDENER_JOURNAL_OBJ (GARDENER_DIR + "obj/book")
#define GARDENER_JOURNAL_ID "_earthsea_gardener_lay_journal"
#define GARDENER_NOTEBOOK_OBJ (GARDENER_DIR + "obj/notepad")
#define GARDENER_NOTEBOOK_ID "_earthsea_gardener_lay_notepad"

/* --- Properties --- */

#define GARDENER_COPY_START_TIME "_earthsea_gardener_copy_start_time"
#define GARDENER_COPY_TIME_LENGTH "_earthsea_gardener_copy_time_length"

/* --- Raw Guild Information --- */

#define GARDENER_NAME "Gardeners of Gont"
#define GARDENER_STYLE "ranger"
#define GARDENER_TAX 5

/* --- Skill --- */
#define GARDENER_SKILL_TITLE 147000

/* --- Other --- */

#define GARDENER_TYPE_LAY 1
#define GARDENER_TYPE_CFT 2

#define GARDENER_TITLE_NOSHOW 1
#define GARDENER_TITLE_SUBLOC 2
#define GARDENER_TITLE_PRES 3

#define GARDENER_MAX_STAT 150
#define GARDENER_NUM_TITLES 6

#define GARDENER_TITLES ({ \
   "Apprentice Gardener of Gont", \
   "Associate Gardener of Gont", \
   "Talented Gardener of Gont", \
   "Famed Gardener of Gont", \
   "Master Gardener of Gont", \
   "Grandmaster Gardener of Gont", \
})

#define GARDENER_BOOKS ({ \
   "new", "dusty", "well-used", "worn", "tattered", "ancient" \
})

#define HERB_FILE(x) explode(file_name(x) + "#", "#")[0]
