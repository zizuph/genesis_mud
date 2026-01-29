/*
 * /d/Gondor/guilds/militia/militia.h
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Militia definitions
 *
 * Coded by Auberon@Genesis on 19 February 2001
 * 10/13/03 - Changed ALIGN_MIN to MILITIA_ALIGN_MIN to not conflict
 *            with the mud-wide alignment.h
 */
#ifndef MILITIA_DEFS
#define MILITIA_DEFS
/* No definitions should be added before this line. */
#include "/d/Gondor/defs.h"

/* Basic guild defines */
#define MILITIA_NAME		"Thornlin Militia"
#define MILITIA_STYLE		"fighter"
#define MILITIA_TAX		(12)

#define TOBJ			THORN_DIR + "obj/"
#define MBOARD			MILITIA_DIR + "board"
#define MHELP			MILITIA_DIR + "help/"
#define MNPC			MILITIA_DIR + "npc/"
#define MOBJ			MILITIA_DIR + "obj/"
#define MROOM			MILITIA_DIR + "room/"

/* Other defines */
#define MSOUL			(MILITIA_DIR + "militia_soul")
#define MSHADOW			(MILITIA_DIR + "militia_shadow")
#define MIMPALE_OBJ  	(MILITIA_DIR + "impale_obj")
#define OCCSHADOW		(MILITIA_DIR + "occ_militia_sh")
#define MPOST			(THORN_DIR + "po")
#define MSTART			(MROOM + "start")
#define MTRAIN			(MROOM + "train")
#define MJOIN			(MROOM + "join")
#define MITEM			(MOBJ + "guild_item")
#define MITEM_ID		("_militia_item_")
#define MILITIA_LOG		"militia"
#define MILITIA_GM		(SECURITY->query_guild_masters("Militia"))
#define MILITIA_ALIGN_MIN	150
#define ALIGN_WARN		100

#define BANNED_GUILDS		({ "Morgul Mages", "Dragonarmy", \
                        	   "Priests of Takhisis" })

/* Special defines */
#define PLAYER_I_JAB_RESET	"_player_i_jab_reset"
#define PLAYER_I_JAB_PREPARE	"_player_i_jab_prepare"
#define PLAYER_I_EVADE_RESET	"_player_i_evade_reset"

#endif //MILITIA_DEFS
