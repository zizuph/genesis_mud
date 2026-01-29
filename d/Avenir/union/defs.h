/*
 * Master defines file for the Shadow Union.
 * Path: /d/Avenir/union/defs.h
 *
 * Lucius Dec 2007: Removed no-longer-used defines.
 * Lilith Aug 2014: Updated drunk define to allow god-intoxication.
 * Cotillion      : Fixed runtime in drunk define
 * Lucius May 2016: Removed more unused defines.
 * Lucius Jul 2017: Added bits to support mudlib specials.
 * Lucius Jul 2017: Cleanup and Re-coded.
 * Arman Nov 2019:  Balanced Union-only quest rewards, reducing
 *                  from 20k/10k respectively to 2k/1k respectively.
 * Lilith May 2021  Moved filters.h to the fling and slash files.
 * Lilith May 2022  Fixed indentation (I hope)
 */
#ifndef __SHADOW_UNION__
#define __SHADOW_UNION__

#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/relation.h"

#define LIST		(UNION + "list")
#define GUILD_CLOSED	LIST->query_guild_closed()

#define SPECIAL		(UNION + "special/")
#define CEREMONY	(UNION + "cerem/")
#define VISIONS		(UNION + "visions/")
#define ROOM		(UNION + "room/")
#define LIB		(UNION + "lib/")
#define NPC		(UNION + "npc/")
#define OBJ		(UNION + "obj/")
#define TUNNEL		(ROOM + "tunnel/")

#define BASE		(ROOM + "base")
#define NOVLIB		(LIB + "novlib")
#define HOME		(ROOM + "guild")
#define JOIN		(ROOM + "pendentive")
#define ENTRY		(ROOM + "entry")
#define HALL		(ROOM + "hall")
#define BLUE		(ROOM + "blue")
#define DROP		(ROOM + "arsenal")
#define POST		(ROOM + "post")
#define VOID		(ROOM + "void")

/* The following are rooms where skills can be learned */
#define TRAINER		(ROOM + "train")
#define ALCOVE		(ROOM + "alcove")
#define WHITE		(ROOM + "white")
#define LIBRARY		(ROOM + "novlib0")
#define FORGE		(ROOM + "forge")
#define ELITE		(ROOM + "elite")

#define SAVINGS		(UNION + "save/")
#define BOARDS		(SAVINGS + "boards/")
#define LIBSAVE		(SAVINGS + "library/")

#define GUILDLOG	(UNION + "log/")
#define GUILD_LOG	(GUILDLOG + "log")
#define COUNC_LOG	(GUILDLOG + "council")
#define ERROR_LOG	(GUILDLOG + "errlog")
#define MENTOR_LOG	(GUILDLOG + "mentor")

/* Attack master for Ogre raids of the Union */
#define OGRE_ATTACK	(L5 + "ogre_attack")

/* Unique skills to the Union */
#define SS_SWAY		139050
#define SS_SLASH	139051
#define SS_FLING	139052
#define OCC_LEVEL	139053

/* Union 'virtues' */
#define US_DIGNITY	139055
#define US_PRIDE	139056
#define US_GRACE	139057
#define US_PURITY	139058

#define US_VIRTUE_MAX	 1200
#define US_VIRTUE_MIN	-1200

/* Shadow, Soul, Token, Logs   */
#define OCC_SHADOW	(UNION + "shadow")
#define OCC_SOUL	(UNION + "occ_soul")
#define ELDER_SOUL	(UNION + "elder_soul")
#define TOKEN_OBJ	(OBJ + "stone")
#define CEREMONY_OBJ	(CEREMONY + "ceremony")

#define BAR_ID		    "_Shadow_Union_Defence_Token"
#define TOKEN_ID	    "_Shadow_Union_Token"
#define BAND_ID		    "_Shadow_Union_knifeholder"
#define SWAY_ID		    "_Union_the_Sway_"
#define SWAY_ID_AGG     "_Union_the_Sway_Aggressively_"
#define SWAY_ID_UNERR   "_Union_the_Sway_Unerringly_"
#define SWAY_ID_DEF     "_Union_the_Sway_Defensively_"
#define SWAY_ID_ALL		"_Union_the_Sway_All"

#define UCORPSE_PROP(x) ("_union_o_corpse_of_" + lower_case(x))
#define UNION_I_MOVE    "_Union_I_Last_Move"
#define UNION_FLINGING  "_Union_am_flinging"
#define CLEANSED        "_Union_cleansed_in_astuary"
#define ANTISNOOP  \
    add_prop(ROOM_M_NO_SCRY, VBFC("anti_snoop:" + HOME));
#define ANTIMAGIC  \
    add_prop(ROOM_M_NO_MAGIC, VBFC("anti_magic:" + HOME)); \
    add_prop(ROOM_M_NO_TELEPORT, VBFC("anti_magic:" + HOME)); \
    add_prop(ROOM_M_NO_TELEPORT_TO, VBFC("anti_magic:" + HOME));

#define NUM_ITEMS(x)		sizeof(filter(all_inventory(), &->id(x)))
#define MAX_GUILD_MESSAGES	8

/* Guild type defs */
#define OCC_TAX		30  /* Per ~Avenir/union/doc/union */
#define OCC_NAME	"Union of the Warriors of Shadow"
#define OCC_SHORT	"Union"
#define OCC_STYLE	"fighter"
#define OCC_TYPE	"occupational"
#define DENY_RACES	({ "dwarf", "goblin" })
#define DENY_GUILDS	({ "Thanarian human race guild" })

/* OCC_LEVEL values */
#define NOVICE        1
#define NORMAL        4
#define ELDER         9

/*
 * The quest group and bits for the Union
 * Also see: lib/bits.h
 */
#include "/d/Avenir/union/lib/bits.h"
#define ACCEPTED_BIT 1 /* Player has been accepted for membersh */
#define PROHIBIT	 2 /* Player can never again join the guild */
#define TRAINING	 3 /* Player can train to guru skills       */
#define AKRAM_DQ	 4 /* Player has done Akram quest           */

#define GURU_EXP	2000 /* Exp for doing the guru quest */
#define AKRAM_EXP	1000 /* Exp for doing the akram quest */

#define MIN_FLAME_STATE    1
#define MAX_FLAME_STATE    10000
#define STATE	HOME->query_state()
/* Percentage of the Flame state */
#define PSTATE	((STATE * 100) / MAX_FLAME_STATE)
/* sk = skill; st = PSTATE;
 * Lower skills by 50% when flame hits 25%
 */
#define FLAME_DIFF(sk, st) \
    (((sk) * (100 - ((st) <= 25 ? 50 : 100))) / 100)
/* The strength of the Flame will affect skills. (slash, fling, sway) */
//#define SKILLS_AFFECTED_BY_FLAME

#define ALTER_PROP(who, what, diff) \
    (who)->add_prop((what), (who)->query_prop(what) + (diff))
#define ALTER_SKILL(who, what, diff) \
    (who)->set_skill_extra((what), (who)->query_skill_extra(what) + (diff))
#define ALTER_STAT(who, what, diff) \
    (who)->set_stat_extra((what), (who)->query_stat_extra(what) + (diff))

/* Are we presently a member? */
#define IS_MEMBER(x)	((x)->query_guild_name_occ() == OCC_NAME)
/* Eligible to start guru / tornu / akram quest? */
#define VALID_GURU(x)	LIST->valid_guru(x)
/* Has completed guru / tornu / akram quest. */
#define IS_TORNU(x)	(IS_MEMBER(x) && \
    (x)->test_bit("Avenir", GUILD_GROUP, TRAINING))

#define LEVEL(x)	   (x)->query_skill(OCC_LEVEL)
#define IS_ELDER(x)	   (LEVEL(x) == ELDER)
#define IS_GMASTER(x)	LIST->gmaster(x)
#define ENEMY(x)	    LIST->query_enemy(x)
#define FRIEND(x)	    LIST->query_friend(x)

/* Gives % intoxicated */
#define DRUNK(x)	(((x)->query_intoxicated() * 100) / (x)->intoxicated_max())
#define NM(x)		capitalize((x)->query_real_name())

#define LOG_FMT(x)	(ctime(time()) +" "+ x +"\n")
#define LOG_ERR(x)	write_file(ERROR_LOG,  LOG_FMT(x))
#define LOG_EVENT(x)	write_file(GUILD_LOG,  LOG_FMT(x))
#define LOG_COUNC(x)	write_file(COUNC_LOG,  LOG_FMT(x))
#define LOG_MENTOR(x)	write_file(MENTOR_LOG, LOG_FMT(x))

/*
 * Punishment definitions/macros
 */
#define UNION_BIT(x)		(1 << (x))
/* Can't start in the guild. */
#define U_PUNISHED_NOSTART	UNION_BIT(2)
/* Can't train in the guild. */
#define U_PUNISHED_NOTRAIN	UNION_BIT(3)
/* Cannot purchase anything in the guild. */
#define U_PUNISHED_NOBUY	UNION_BIT(4)
/* May not enter the guild. */
#define U_PUNISHED_NOENTER	UNION_BIT(5)
/* Guild NPCs will autoattack you. */
#define U_PUNISHED_AUTOKILL	UNION_BIT(6)
/* Cannot access the case. */
#define U_PUNISHED_NOCASE	UNION_BIT(7)
/* Cannot access the shelf. */
#define U_PUNISHED_NOSHELF	UNION_BIT(12)
/* Skills will decay. */
#define U_PUNISHED_DECAY	UNION_BIT(8)
/* Member has punishment title. */
#define U_PUNISHED_TITLE	UNION_BIT(9)
/* Member may not use the library. */
#define U_PUNISHED_LIBRARY	UNION_BIT(10)
/* Member has reward title. */
#define U_REWARD_TITLE		UNION_BIT(11)

/* Will give the punished level of a player. */
/* Can either be a player object or a player's name */
#define U_PUNISHED_LEVEL(x)		LIST->query_union_punished_level(x)
#define U_IS_PUNISHED(who, type)	(U_PUNISHED_LEVEL(who) & type)

#define U_PUNISHED_STR  ([ \
    U_PUNISHED_TITLE    : "punished with Lesser Warrior title",      \
    U_REWARD_TITLE      : "rewarded with Pride of the Union title",  \
    U_PUNISHED_DECAY    : "will begin to lose skills through decay", \
    U_PUNISHED_AUTOKILL : "will be attacked on sight by disciples of the Union", \
    U_PUNISHED_LIBRARY  : "may not use the Union archives",          \
    U_PUNISHED_NOBUY    : "can purchase no goods in the Halls",      \
    U_PUNISHED_NOCASE   : "may not have access to the case",         \
    U_PUNISHED_NOENTER  : "may not enter the Halls of Shadow",       \
    U_PUNISHED_NOSHELF  : "may not have access to the shelf",        \
    U_PUNISHED_NOSTART  : "may not start in the Halls of Shadow",    \
    U_PUNISHED_NOTRAIN  : "may train no skills within the Union",    \
])

#define U_PUNISHED_TYPE  ([ \
    "badtitle"   : U_PUNISHED_TITLE,     \
    "goodtitle"  : U_REWARD_TITLE,       \
    "decay"      : U_PUNISHED_DECAY,     \
    "die"        : U_PUNISHED_AUTOKILL,  \
    "noarchives" : U_PUNISHED_LIBRARY,   \
    "nobuy"      : U_PUNISHED_NOBUY,     \
    "nocase"     : U_PUNISHED_NOCASE,    \
    "noenter"    : U_PUNISHED_NOENTER,   \
    "noshelf"    : U_PUNISHED_NOSHELF,   \
    "nostart"    : U_PUNISHED_NOSTART,   \
    "notrain"    : U_PUNISHED_NOTRAIN,   \
])

/* Automatically add all npc-killers to the enemy list */
#define MAKE_KILLERS_ENEMIES
/* Automatically add all npc-killers to the enemy list */
#undef MAKE_KILLERS_INFIDELS

/* Track things that change their virtues */
#define LOG_VIRTUES          0
/* Track only things that lower their virtues */
#define LOG_VIRTUE_LOSSES    1

/* query members sphere. */
#define SPHERE(x)	(x)->query_union_sphere()
/* Check membership against a Sphere */
#define MEMBER_SPHERE(x, y)  \
    (IS_GMASTER(x) || IS_ELDER(x) || (x)->query_union_sphere() == y)
/* Check membership against multiple Spheres */
#define MEMBER_SPHERES(x, yyy)  \
    (IS_GMASTER(x) || IS_ELDER(x) || \
	(member_array((x)->query_union_sphere(), yyy) != -1))

#define SPH_BEAUTY	      "beauty"
#define SPH_DIPLOMACY	  "diplomacy"
#define SPH_DUTY	      "duty"
#define SPH_FLAME	      "flame"
#define SPH_HISTORY	      "history"
#define SPH_INQUISITION	  "inquisition"
#define SPH_INTEL	      "intel"
#define SPH_ISOLATION	  "isolation"
#define SPH_MENTOR	      "mentor"
#define SPH_PROTECTION	  "protection"
#define SPH_TRAINING	  "training"
#define SPH_VENGEANCE	  "vengeance"
#define SPH_VOICE	      "voice"
#define SPH_WEAPONRY	  "weaponry"
#define SPH_ETERNAL       "eternal_flame"

#define SPHERES ([ \
      SPH_BEAUTY	  : "Aesthetics", \
      SPH_DIPLOMACY	  : "Diplomacy", \
      SPH_DUTY		  : "Duty", \
      SPH_FLAME		  : "the Flame", \
      SPH_HISTORY	  : "History", \
      SPH_INQUISITION : "Inquisition", \
      SPH_INTEL		  : "Intelligence", \
      SPH_ISOLATION	  : "Isolation", \
      SPH_MENTOR	  : "Shadow Mentors", \
      SPH_PROTECTION  : "Protection", \
      SPH_TRAINING	  : "Training", \
      SPH_VENGEANCE	  : "Zaren", \
      SPH_VOICE		  : "the Voice", \
      SPH_WEAPONRY	  : "Weapons Master", \
      SPH_ETERNAL     : "Eternal Flame", \
])

/* SPHERE_OBJECTS defines those objects that will be cloned into
 * the inventory of the member upon login.
 */
#define SPHERE_OBJECTS ([ ])

#define DEFAULT_SPHERE	SPH_TRAINING

/* Special Union Adverbs */
#define UADVERBS_FILE	(UNION + "adverbs")
#define UNION_ADVERBS	(SAVINGS + "UNION_ADVERBS")

/* Special Union Death Sequence */
#define UNION_DEATH	    (UNION + "death/death_mark")
#define UNION_CORPSE	(UNION + "death/corpse")

/* Union Options */
#define UOPT_LSHORT	    UNION_BIT(1)
#define UOPT_LLONG	    UNION_BIT(2)
//#define UOPT_STOUCH	UNION_BIT(3)
//#define UOPT_RMTXT	UNION_BIT(4)

#endif  __SHADOW_UNION__
