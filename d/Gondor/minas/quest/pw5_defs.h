/*
 *  Definitions for the Password Quest to the 5th Circle
 */

#define MT_PW5_DIR		"/d/Gondor/minas/quest/"

/*
 * The quest master object
 */
#define MT_PW5_MASTER		(MT_PW5_DIR + "pw5_master")

/*
 * The suspects
 */
#define MT_PW5_SUSPECT		"/d/Gondor/minas/npc/citizens/suspect"

/*
 * MT_PW5_I_HUNTHOR_SENT_ME
 * asked Hunthor for the task 
 */
#define MT_PW5_I_HUNTHOR_SENT_ME	"_MT_PW5_i_hunthor_sent_me"

/*
 * MT_PW5_GIMILZOR_START
 * the room where the first guard is to be loaded
 */
#define MT_PW5_GIMILZOR_START	"/d/Gondor/minas/houses/g1ncrc4"

/*
 * MT_PW5_I_SEEN_BLOOD
 * examined grating in houses/g3ncrc4.c
 * to be checked when searching for dagger in the sewer
 */
#define MT_PW5_I_SEEN_BLOOD	"_MT_PW5_i_seen_blood"

/*
 * MT_PW5_I_FOUND_MOTIVE
 * bit 1 - found the IOUs in the study
 * bit 2 - found and read the ledger
 */
#define MT_PW5_I_FOUND_MOTIVE	"_MT_PW5_i_found_motive"

/*
 * MT_PW5_O_SEWER_KEY
 * The key to the sewers that the player receives from Hunthor
 */
#define MT_PW5_O_SEWER_KEY	"_MT_PW5_o_sewer_key"

/*
 * MT_PW5_SEWER_KEY
 * The unique name of that key
 */
#define MT_PW5_SEWER_KEY	"_MT_PW5_sewer_key"

/*
 * MT_PW5_I_FOUND_WEAPON
 * 1 - found the murder weapon in the sewers
 * 2 - talked to Merdol about the murder weapon
 */
#define MT_PW5_I_FOUND_WEAPON	"_MT_PW5_i_found_weapon"

/*
 * MT_PW5_MURDER_WEAPON
 * The unique name of the murder weapon
 */
#define MT_PW5_MURDER_WEAPON	"_MT_PW5_murder_weapon"

/*
 * MT_PW5_MURDER_WEAPON_FILE
 * The file name of the murder weapon
 */
#define MT_PW5_MURDER_WEAPON_FILE	("/d/Gondor/minas/quest/murder_dagger")

/*
 * MT_PW5_SEWER_ROOM
 * The room in the sewers where the murder weapon can be found
 */
#define MT_PW5_SEWER_ROOM	("/d/Gondor/minas/sewer/d4c4")

/*
 * MT_PW5_MERDOL_TESTIMONY
 * Merdol identified the murderer as buyer of the dagger.
 */
#define MT_PW5_I_MERDOL_TESTIMONY	"_MT_PW5_i_merdol_testimony"

/*
 * MT_PW5_S_OWNER
 * The name of the player who actually found this key or ledger.
 */
#define MT_PW5_S_OWNER	"_MT_PW5_s_owner"

/*
 * MT_PW5_S_KEY_SOURCE
 * The name of the player who gave this key to Dior.
 */
#define MT_PW5_S_KEY_SOURCE	"_MT_PW5_s_key_source"
