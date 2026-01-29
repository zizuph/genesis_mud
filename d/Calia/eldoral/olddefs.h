#include <stdproperties.h>
#include <macros.h>

/* Some standard paths */
#define STDROOM     "/std/room"
#define BASE        "/d/Calia/eldoral/"
#define ARM         BASE + "armours/"
#define CAVERNS     BASE + "caverns/"
#define FOREST      BASE + "forest/"
#define GROTTO      BASE + "grotto/"
#define LAKE        BASE + "lake/"
#define MOUNT       BASE + "mountain/"
#define NPC         BASE + "npc/"
#define OBJ         BASE + "objects/"
#define RAVINE      BASE + "ravine/"
#define RUIN        BASE + "ruins/"
#define SHORE       BASE + "shore/"
#define WEP         BASE + "weapons/"
#define SPECIAL     BASE + "special/"

/* Property shortcuts. */
#define INSIDE      add_prop(ROOM_I_INSIDE, 1);
#define DARK        add_prop(ROOM_I_LIGHT, -1);

/* Function shortcuts. */
#define TP          this_player()
#define TO          this_object()
#define NF(x)       notify_fail(x)

/* Misc. props used in various places. */
#define ROOM_I_IS_SKIFF_PORT    "_room_i_is_skiff_port"
#define ROOM_I_CAN_SEE_WEATHER  "_room_i_can_see_weather"
#define LIVE_I_HAS_COMPARED     "_live_i_has_compared"
#define LIVE_I_DID_SEER_QUEST   "_live_i_did_seer_quest"
#define LIVE_I_KILLED_BEAST     "_live_i_killed_beast"
#define OBJ_S_ORIG_SHORT        "_obj_s_orig_short"
#define OBJ_I_LORD_SAW_ME       "_obj_i_lord_saw_me"

/* Props and flags for tracking status of the horn quest. */
#define LIVE_I_HORN_QUEST       "_live_i_horn_quest"
#define HQ_KILLED_KROUG         1
#define HQ_FOUND_HORN           2
#define HQ_HUNG_HORN            4

/* Props and flags for tracking status of seer quest. */
#define LIVE_I_SEER_QUEST       "_live_i_seer_quest"
#define SEQ_SPOKE_SEER          1
#define SEQ_FOUND_DAGGER        2
#define SEQ_FOUND_CLOTH         4
#define SEQ_SPOKE_LORD          8

/* Props and flags for tracking status of sword quest. */
#define LIVE_I_SWORD_QUEST      "_live_i_sword_quest"
#define SWQ_FOUND_PARCH         1
#define SWQ_FOUND_CHAR          2
#define SWQ_COPY_CHIM           4
#define SWQ_COPY_WARR           8
#define SWQ_MARKED_X            16
#define SWQ_WEIGHT_STONE        32
#define SWQ_FAILED              64

/* Props and flags for tracking status of the beast quest. */
#define LIVE_I_BEAST_QUEST      "_live_i_beast_quest"
#define BQ_SPOKE_FIRESTORM      1
#define BQ_FOUND_SCEPTRE        2
#define BQ_USED_SCEPTRE         4
#define BQ_KILLED_LORD          8

/* Names for special items in the area. */
#define ELDORAL_PARCHMENT_NAME  "_eldoral_quest_parchment"
#define ELDORAL_CHARCOAL_NAME   "_eldoral_quest_charcoal"
#define ELDORAL_BEAST_EYE_NAME  "_eldoral_beast_eye"
#define ELDORAL_DAGGER_NAME     "_eldoral_seer_dagger"
#define ELDORAL_CLOTH_NAME      "_eldoral_seer_cloth"
#define QUEST_TRACKER_NAME      "_eldoral_quest_tracker"
#define SKELETAL_WARRIOR        "_eldoral_skele_warrior"
#define DEATH_KNIGHT            "_eldoral_d_knight"
#define DEATH_LORD              "_eldoral_d_lord"
#define RUBBLE_NAME             "_eldoral_rubble"
#define SHIMMERING_SWORD_NAME     "_eldoral_shimmering_sword"

/* Defines for bit group and numbers. */
#define ELDORAL_QUEST_GROUP      4
#define ELDORAL_HORN_QUEST_BIT   0
#define ELDORAL_SEER_QUEST_BIT   1
#define ELDORAL_SWORD_QUEST_BIT  2
#define ELDORAL_BEAST_QUEST_BIT  3
#define ELDORAL_GURU_QUEST_BIT   4
#define ELDORAL_SECRET_WAY_BIT   5

/* Shortcuts for various master/brain objects. */
#define BITMASTER      (SPECIAL + "bitmaster")
#define SWORD_BRAIN    (SPECIAL + "sword_brain")
#define SEER_BRAIN     (SPECIAL + "seer_brain")
#define BEAST_BRAIN    (SPECIAL + "beast_brain")
#define GURU_BRAIN     (SPECIAL + "guru_brain")
#define MOUNTAIN_BRAIN (SPECIAL + "mountain_brain")
#define HERBMASTER     SPECIAL + "herbmaster"
#define NAME_FILE      (SPECIAL + "name_macros")

/* Herb-related defines. */
#define HERBPATH       "/d/Krynn/common/herbs/"
#define HERBSEARCH     "/d/Krynn/std/herbsearch"
#define NO_HERBS       1
#define NO_HERB_FILES  2

/* Names for special skills set. */
#define SK_ELDORAL_CASTLE_NAME  114090
#define SK_ELDORAL_NAME_VALUE   1
#define SK_CASTLE_NAME_VALUE    2
#define CASTLE_KNOWN   NAME_FILE->player_knows_castle()
#define ELDORAL_KNOWN  NAME_FILE->player_knows_eldoral()
#define CASTLE_NAME    "@@castle_name:" + NAME_FILE + "@@"
#define LAKE_NAME      "@@lake_name:" + NAME_FILE + "@@"
#define ISLAND_NAME    "@@island_name:" + NAME_FILE + "@@"


