/*
 * /d/Genesis/guilds/merc/merc.h
 *
 * Mercenary Guild definitions file, by Morrigan 10/2001
 *
 * Adapted from code by Gwyneth and Auberon.
 *
 * Heavilly modified and updated for Sparkle by Lunatari.
 */
#ifndef MERC_DEFS
#define MERC_DEFS

/* No definitions should be added before this line. */

/* Mudlib change defines */
/* #define NEW_MERCY 1 activate if mudlib mercy ever works */

/* Is the guild open: 0 = no, 1 = yes */
#define IS_MERC_OPEN	1

/* Do we have certain abilities?
 * Uncomment command below to disable Mercenary Lord Dogs
 */
#define MERC_DISALLOW_DOGS 0

/* 
 * Alien Inherit defines (These should be fixed)
 * 
 */
#define MERC_KRYNN_NPC   "/d/Krynn/std/monster";
#define MERC_KRYNN_BRIBE "/d/Krynn/std/bribe";
#define MERC_GONDOR_NPC  "/d/Gondor/std/monster";
#define GEN_STEED_PATH   "/d/Genesis/steed/"
#define GEN_STEED_FEED   GEN_STEED_PATH + "feeding";

/* Exit to Sparkle */
#define OUT_CAMP "/d/Sparkle/area/sparkle/room/wild/n_road2"

/* Krynn INCLUDE
 * Now this is something we really have to fix, but until
 * its all fixed and replaced I will keep it here instead of all
 * the other files.
 */
#include "/d/Krynn/common/defs.h"

#define CAP(x) capitalize(x)
#define ENV(x) environment(x)

/*
 * Basic Includes.
 */
#include <wa_types.h>
#include <filter_funs.h>
#include <const.h>
#include <cmdparse.h>
#include <files.h>
#include <language.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <options.h>
#include <composite.h>
#include <tasks.h>
#include <std.h>
#include <config.h>
#include <filter_funs.h>

/* Basic guild defines */
#define MERC_NAME	  "Luna Test Mercs"
#define MERC_STYLE	  "fighter"
#define MERC_TYPE	  "occupational"
#define MERC_TAX	  (10)
#define MERC_FOLLOWER_TAX (20)
#define MERC_ASPIRING_TAX (22)
#define MERC_LORD_TAX     (23)
#define MERC_WARLORD_TAX  (23)

#define MERC_GUILDMASTER   "lunatari"
#define MERC_GM            (SECURITY->query_guild_masters("Mercenaries"))
#define MERC_GMJUNIOR      "lunajr"
#define MERC_SHADOWVERSION (20060910001)

/* Mattack defines */
#define MATTACK_PREPARE    7
#define MATTACK_RESET      8
#define MATTACK_FAILSAFE   5

/* Directory defines */
#define MERC_DIR	"/d/Sparkle/guilds/mercs/"
#define MDIR		MERC_DIR
#define MHELP		MDIR + "help/"
#define MNPC		MDIR + "npc/"
#define MOBJ		MDIR + "obj/"
#define MROOM		MDIR + "room/"
#define MHALL           MDIR + "great_hall"
#define MLIB            MDIR + "library/"
#define MLIBS           MDIR + "lib/"
#define MLOG		MDIR + "log/"
#define MVAR            MDIR + "var/"
#define MBATTLE		MDIR + "battleground/"
#define MBOARD		MVAR + "board"
#define MLORD_BOARD     MVAR + "lord_board"

/* File defines */
#define MSOUL		(MLIBS + "luna_soul")
#define MSHADOW		(MLIBS + "luna_shadow")
#define DSHADOW		(MLIBS + "merc_defend")
#define MSTART		(MROOM + "start")
#define MTRAIN		(MROOM + "train")
#define MTRAIN2		(MROOM + "train2")
#define MTRAIN3		(MROOM + "train3")
#define MJOIN		(MROOM + "join")
#define MCREST		(MROOM + "crest_room")
#define MKENNEL         (MROOM + "kennel")
#define MERC_STATUES    (MLOG + "statues")
#define MERC_LOG	MLOG + "mercenary_guild"
#define MERC_WARN_LOG	MLOG + "warnings"
#define MERC_PUNISH_LOG MLOG + "punish"
#define MERC_BRIBE_LOG  MLOG + "bribe"
#define MERC_MERCY_LOG  MLOG + "mercy"
#define MERC_ARENA_LOG  MLOG + "arena"
#define MERC_MASTER	MVAR + "merc"
#define MERC_SERVER MVAR + "merc_server"
#define MERC_CREST      MVAR + "crest"
#define MERC_CAUSES     MLOG + "causes"
#define MERC_DOGS	MVAR + "dogs"
#define MERC_BASE_NPC   (MNPC + "merc_base")

/* 
 * A few function defines 
 * Member query functions and some sword/club queries. 
 */
#define IS_MERC(x)	MJOIN->query_member(x->query_name())
#define MEMBER_CLUB(x)  MJOIN->query_club_member(x->query_name())
#define MEMBER_SWORD(x) MJOIN->query_sword_member(x->query_name())

/* If not defined Mercenaries cannot hide their title */
#define MERC_CHANGE_TITLE_ABILITY	1

/* If not defined Mercenaries cannot use mercy */
#define MERC_MERCY_ABILITY              0

/*
 * Definitions related to leaving the guild and the penalty involved
 * FULL = 25%, MID = 20%, LOW = 10%, NO = 0% 
 */
#define FULL_PENALTY(x) (x->query_exp_combat() / 4)
#define MID_PENALTY(x)  (x->query_exp_combat() / 5)
#define LOW_PENALTY(x)  (x->query_exp_combat() / 10)
#define NO_PENALTY(x) 	0			

/*
 * Set these levels to determine who gets each penalty, at this level and 
 * above, mercenary qualifies for the this penalty 
 */
#define FULL_PENALTY_LEVEL 15
#define MID_PENALTY_LEVEL  11
#define LOW_PENALTY_LEVEL  5
#define NO_PENALTY_LEVEL   0

/* Status defines */
#define MERC_STATUS_NONE     0
#define MERC_STATUS_ASPIRING 1
#define MERC_STATUS_LORD     2
#define MERC_STATUS_WARLORD  3

/* Lord and tabard defines */
#define LORD_LEVEL	  106
#define JOIN_LORD_LEVEL   40
#define LORD_FOLLOWING    3
#define WARLORD_FOLLOWING 8

/* Lord Defines */
#define IS_MERC_LORD_ASPIRANT(x) \
	(MCREST->query_lord_status(x->query_name()) == 1 ? 1 : 0)
#define IS_MERC_LORD(x) \
	(MCREST->query_lord_status(x->query_name()) == 2 ? 1 : 0)
#define IS_MERC_WARLORD(x) \
	(MCREST->query_lord_status(x->query_name()) == 3 ? 1 : 0)
#define IS_MERC_SUBLORD(x) (member_array(x->query_name(),\
	MCREST->query_sublords(MCREST->query_members_lord(x->query_name()))) > -1 ? "1" : "0")
#define CAN_JOIN_LORD(x) (x->query_stat(SS_OCCUP) >= JOIN_LORD_LEVEL ? 1 : 0)

/* 
 * Tabard and Camp defines 
 * The camp entry prop is used to check who is in the camp.
 */
#define TABARD		(MOBJ + "tabard")
#define TABARD_ID	("_merc_tabard_object_")
#define MERC_MESSAGE_ID ("_merc_message_object_")
#define MERC_CAMP_ENTRY ("_merc_camp_enter_leave")
#define MITEM           (MLIBS + "merc_item")
#define MITEM_ID        ("_merc_guild_item_")

/* Guild title defines */
#define MAX_GUILD_LEVEL 20
#define MERC_MTITLES  ({ \
    "New Mercenary", \
    "Fresh Mercenary", \
    "Unproven Mercenary", \
    "Rising Mercenary", \
    "Blooded Mercenary", \
    "Skilled Mercenary", \
    "Accomplished Mercenary", \
    "Deadly Mercenary", \
    "Feared Mercenary", \
    "Renowned Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Celebrated Mercenary", \
    "Fabled Warrior", \
    "Epic Warrior", \
    "Legendary Warrior", \
    "Mythical Warrior of the Realms" })

#define MERC_FTITLES  ({ \
    "New Mercenary", \
    "Fresh Mercenary", \
    "Unproven Mercenary", \
    "Rising Mercenary", \
    "Blooded Mercenary", \
    "Skilled Mercenary", \
    "Accomplished Mercenary", \
    "Deadly Mercenary", \
    "Feared Mercenary", \
    "Renowned Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Famous Mercenary", \
    "Celebrated Mercenary", \
    "Fabled Warrior", \
    "Epic Warrior", \
    "Legendary Warrior", \
    "Mythical Warrior of the Realms" })

#define MERC_LORD_TITLES ({ "Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Mercenary Lord", \
		"Famous Mercenary Lord", \
		"Famous Mercenary Lord",\
		"Celebrated Mercenary Lord",\
		"Fabled Mercenary Lord",\
                "Epic Mercenary Lord",\
		"Legendary Mercenary Lord",\
		"Mythical Lord of Mercenaries" })

#define MERC_LADY_TITLES ({ "Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Mercenary Lady", \
		"Famous Mercenary Lady", \
		"Famous Mercenary Lady",\
		"Celebrated Mercenary Lady",\
		"Fabled Mercenary Lady",\
                "Epic Mercenary Lady",\
		"Legendary Mercenary Lady",\
		"Mythical Lady of Mercenaries" })

#define MERC_WARLORD_TITLES ({ "Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Warlord of the Mercenaries", \
		"Famous Warlord of the Mercenaries", \
		"Famous Warlord of the Mercenaries",\
		"Celebrated Warlord of the Mercenaries",\
		"Fabled Warlord of the Mercenaries",\
                "Epic Warlord of the Mercenaries",\
		"Legendary Warlord of the Mercenaries",\
		"Mythical Warlord of the Realms" })

#define MERC_WARLADY_TITLES ({ "Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Warlady of the Mercenaries", \
		"Famous Warlady of the Mercenaries", \
		"Famous Warlady of the Mercenaries",\
		"Celebrated Warlady of the Mercenaries",\
		"Fabled Warlady of the Mercenaries",\
                "Epic Warlady of the Mercenaries",\
		"Legendary Warlady of the Mercenaries",\
		"Mythical Warlady of the Realms" })

/* Skill level defines */
#define CLUB_MEMBER_CLUB_MAX	90
#define CLUB_MEMBER_SWORD_MAX	64
#define SWORD_MEMBER_CLUB_MAX	64
#define SWORD_MEMBER_SWORD_MAX	84
#define UNDEC_MEMBER_CLUB_MAX	64
#define UNDEC_MEMBER_SWORD_MAX	64

/* Special skill defines */
#define SS_MERC_TACTICS		33331
#define SS_MERC_GAG_DOG		33334
#define SS_MERC_AUTOCOMPLY	33335
#define SS_MERC_AUTOMATTACK	33336
#define SS_MERC_MERCY           33337
#define SS_MERC_TITLE		33338
#define SS_MERC_RACK		33339

/* NPC defines */
#define MERC_GUILD_NPC		"_merc_guild_npc_"

/* Properties used in specials defines */
#define PLAYER_I_MATTACK_RESETTING	"_player_i_mattack_reset"
#define PLAYER_I_MATTACK_PREPARING	"_player_i_mattack_prepare"
#define PLAYER_I_MDEFEND_RESETTING	"_player_i_mdefend_resetting"
#define MERC_O_ADVANCING		"_merc_o_advancing"
#define MERC_O_RETREATING		"_merc_o_retreating"

/* Other property defines */
#define MALIGANT_CHOOSE_PERMISSION	"_player_i_maligant_choose_permission"
#define MALIGANT_JOIN_PERMISSION	"_player_i_maligant_join_permission"
#define MALIGANT_REDUCED_LEAVE_PENALTY  "_player_i_maligant_reduced_leave_penalty"
#define MALIGANT_REMOVED_LEAVE_PENALTY  "_player_i_maligant_removed_leave_penalty"
#define MERC_S_DEFAULT_BATTLECRY	"_merc_s_default_battlecry"
#define MERC_S_DEFAULT_HAIL		"_merc_s_default_hail"
#define MERC_S_DEFAULT_FAREWELL		"_merc_s_default_farewell"

#define MAX_MESSAGE_SIZE	(60)

#endif
