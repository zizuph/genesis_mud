/*
 *  /d/Gondor/clubs/nisse/nisse_defs.h
 *
 *  Header file for the Nisse Ohtar club.
 *
 *  Deagol, February 2003
 */

#ifndef NISSE_DEFINITIONS
#define NISSE_DEFINITIONS

#define NISSE_DIR		"/d/Gondor/clubs/nisse/"
#define NISSE_LIB_DIR		(NISSE_DIR + "lib/")
#define NISSE_SOUL_DIR		(NISSE_DIR + "soul/")
#define NISSE_SHADOW_DIR	(NISSE_DIR + "shadow/")
#define NISSE_ROOM_DIR		(NISSE_DIR + "room/")
#define NISSE_OBJ_DIR		(NISSE_DIR + "obj/")
#define NISSE_NPC_DIR		(NISSE_DIR + "npc/")
#define NISSE_LOG_DIR		(NISSE_DIR + "log/")
#define NISSE_HELP_DIR		(NISSE_DIR + "help/")
#define NISSE_BOARD_DIR		(NISSE_DIR + "board/")

#define NISSE_LOG		(NISSE_LOG_DIR + "nisse_log")

#define NISSE_SOUL		(NISSE_SOUL_DIR + "nisse_soul")
#define NISSE_SHADOW		(NISSE_SHADOW_DIR + "nisse_shadow")

#define NISSE_ADMIN_OBJ		(NISSE_OBJ_DIR + "nisse_admin")
#define MANAGER			(NISSE_DIR + "manager")
#define CEREMONY		(NISSE_OBJ_DIR + "ceremony")

#define NISSE_START		(NISSE_ROOM_DIR + "hollow")
#define HAWK_ROOM		(NISSE_ROOM_DIR + "hawk_room")
#define HAWK_MSG		(NISSE_OBJ_DIR + "message")
#define NISSE_HAWK		(NISSE_OBJ_DIR + "hawk")
#define NISSE_FEATHER		(NISSE_OBJ_DIR + "feather")
#define HAWK_FEED		(NISSE_OBJ_DIR + "hawk_feed")
#define NEWS_SCROLL		(NISSE_OBJ_DIR + "scroll")
#define NISSE_GRIT		(NISSE_OBJ_DIR + "grit")
#define NISSE_STAKE		(NISSE_OBJ_DIR + "stake")

#define NISSE_HAWK_ID		"_nisse_hawk_id_"
#define NISSE_FEATHER_ID	"_nisse_feather_id_"
#define HAWK_SUBLOC_ID		"_nisse_subloc_id_"
#define NISSE_SUBLOC_ID		"_nisse_subloc_id_1_"
#define HAWK_FEED_ID		"_nisse_hawk_feed_id_"
#define NISSE_GLOVE_ID		"_nisse_glove_id_"
#define NISSE_HOOD_ID		"_nisse_hood_id_"
#define NISSE_JESSES_ID		"_nisse_jesses_id_"
#define NISSE_WOAD_ID		"_nisse_woad_id_"

#define NISSE_GUARD_ID		"_nisse_guard_id_"
#define NISSE_COOK_ID		"_nisse_cook_id_"

#define NISSE_PRIV_BOARD	(NISSE_BOARD_DIR + "nisse_priv_board")

#define NISSE_MEMBER(x)         ((x)->query_nisse_member())

#define NISSE_TRAINER		(NISSE_NPC_DIR + "trainer")
#define NISSE_HAWKMISTRESS	(NISSE_NPC_DIR + "hawkmistress")

#define NON_MEMBER_LEVEL	0
#define TAN_LEVEL		1
#define LIGHT_BROWN_LEVEL	2
#define BROWN_LEVEL		3
#define DEEP_BROWN_LEVEL	4
#define RED_LEVEL		5
#define GOLD_LEVEL		6
#define BRONZE_LEVEL		7

#define LOG_SIZE	9000

#endif NISSE_DEFINITIONS
