/*
 * /d/Gondor/morgul/quest/bsw/bsw_defs.h
 *
 * definitions for the quest to retrieve
 *     the Battle standard of the Witchking
 *
 * Olorin, July 1994
 */

/* BSW_DIR
 * Main quest dir
 */
#define BSW_DIR			"/d/Gondor/morgul/quest/bsw/"

/* BSW_QUEST_MASTER
 * file name of the master file with standard routines
 */
#define BSW_QUEST_MASTER	(BSW_DIR + "master")

/* BSW_I_SENT_TO_YRCHOR
 * set by Warden of the Tower in /d/Gondor/morgul/tower/warden_room.
 * 	in player trying to solve the quest
 * used by Yrchor in /d/Gondor/morgul/city/rooms/?????
 * removed ...
 */
#define BSW_I_SENT_TO_YRCHOR	"_bsw_i_sent_to_yrchor"

/* BSW_I_SENT_TO_GALDOR
 * set by Hunthor in Minas Tirith
 */
#define BSW_I_SENT_TO_GALDOR	"_bsw_i_sent_to_galdor"
#define BSW_I_SENT_TO_BARANOR	"_bsw_i_sent_to_baranor"

/* BSW_YRCHOR_SCROLL
 * The unique name of the scroll the player gets from Yrchor
 */
#define BSW_YRCHOR_SCROLL	"_bsw_yrchor_scroll"

/* BSW_S_SCROLL_OWNER
 * set by Yrchor in scroll MORGUL_DIR+"obj/standard_scroll"
 * name of player who received the scroll from Yrchor
 */
#define BSW_S_SCROLL_OWNER	"_bsw_s_scroll_owner"

/* BSW_STEWARDS_FIRST_YEAR, BSW_STEWARDS_LAST_YEAR
 * the first and the last year of the period in which the standard
 * 	could have been hidden
 */
#define BSW_STEWARDS_FIRST_YEAR		2081
#define BSW_STEWARDS_LAST_YEAR		2953

/* BSW_I_OPENED_GATE
 * Opened the gate in the House of the Stewards
 */
#define BSW_I_OPENED_GATE		"_bsw_i_opened_gate"

/* BSW_BATTLE_STANDARD_FILE
 * Path name of battle standard
 */
#define BSW_BATTLE_STANDARD_FILE	(BSW_DIR + "bstandard")

/* BSW_BATTLE_STANDARD
 * Unique name of the quest object
 */
#define BSW_BATTLE_STANDARD		"_bsw_battle_standard"

/* BSW_S_RETRIEVED_BY
 * Name of player to retrieve the battle standard
 */
#define BSW_S_RETRIEVED_BY		"_bsw_s_retrieved_by"

/* BSW_I_FOUND_IT
 * Player found the battle standard
 */
#define BSW_I_FOUND_IT			"_bsw_i_found_it"

/*
 * BSW_TREASURY_FILE
 * The path name to the treasury.
 */
#define BSW_TREASURY_FILE		"/d/Gondor/ithilien/emyn-arnen/palace/treasury"

