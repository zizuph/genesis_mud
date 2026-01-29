/*
 * /d/Genesis/guilds/merc/merc.h
 *
 * Mercenary Guild definitions file, by Morrigan 10/2001
 *
 * Adapted from code by Gwyneth and Auberon.
 *
 */

/* Directory defines */
#define MERC_DIR	"/d/Genesis/guilds/merc/"
#define LAY_MERC_DIR    MERC_DIR + "layman"
#define MDIR		MERC_DIR
#define MBOARD		MERC_DIR + "board"
#define MLORD_BOARD     MERC_DIR + "lord_board"
#define MHELP		MERC_DIR + "help/"
#define MNPC		MERC_DIR + "npc/"
#define MOBJ		MERC_DIR + "obj/"
#define MROOM		MERC_DIR + "room/"
#define MHALL           MERC_DIR + "great_hall"
#define MLIB            MERC_DIR + "library/"
#define MLOG		MERC_DIR + "log/"
#define MBATTLE		MERC_DIR + "battleground/"

/* Defines unique to merc camp */
#define MERC_CAMP	("/d/Genesis/start/human/merc_camp/")
#define MERC_CAMP_ROOM  (MERC_CAMP + "room/")
#define MERC_CAMP_OBJ	(MERC_CAMP + "obj/")
#define MERC_CAMP_NPC	(MERC_CAMP + "npc/")

/* File defines */
#define MSOUL		(MERC_DIR + "merc_soul")
#define MSHADOW		(MERC_DIR + "merc_shadow")
#define DSHADOW		(MERC_DIR + "defended_shadow")
#define MSTART		(MROOM + "start")
#define MJOIN		(MROOM + "join")
#define MCREST		(MROOM + "crest_room")
#define MITEM		(MERC_DIR + "guild_item")
#define MITEM_ID	("_merc_guild_item_")

#define TABARD		MOBJ + "tabard"
#define TABARD_ID	"_merc_tabard_object_"
#define MESSAGE_OBJECT  "_merc_message_object_"

#define SS_MERC_TACTICS		33331

/* NPC defines */
#define MERC_GUILD_NPC		"_merc_guild_npc_"

/* Properties used in specials defines */
#define PLAYER_I_MATTACK_RESETTING	"_player_i_mattack_reset"
#define PLAYER_I_MATTACK_PREPARING	"_player_i_mattack_prepare"
#define PLAYER_I_MDEFEND_RESETTING	"_player_i_mdefend_resetting"
#define MERC_O_ADVANCING		"_merc_o_advancing"
#define MERC_O_RETREATING		"_merc_o_retreating"

/* Other property defines */
#define MERC_S_DEFAULT_BATTLECRY	"_merc_s_default_battlecry"
#define MERC_S_DEFAULT_HAIL		"_merc_s_default_hail"
#define MERC_S_DEFAULT_FAREWELL		"_merc_s_default_farewell"
#define PLAYER_I_ATTACK_MERC_CAMP	"_player_i_attack_merc_camp"

#define MAX_MESSAGE_SIZE	(60)
