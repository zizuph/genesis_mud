/* THIS FILE IS OBSOLETE!!!!
 * 
 * Do not use it, it is only here for backwards compatablity
 *
 * Use ~Shire/sys/defs.h instead as it is the proper domain defs
 */
// Comments moved to /d/Shire/common/defscomments
 
#ifndef _SHIRE_DEFS_
#define _SHIRE_DEFS_
#define _SHIRE_DOMAIN_PATHS_
 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
/*
// Skill defines for the Spy guild
#define SS_FLURRY 112000
#define SS_ENDURANCE 112001
#define SS_DISGUISE 112002
*/

// global to set max number of unique items in domain
#define MAX_UNIQUE_ITEMS 7

// Skill defines for the Trickster Guild
#define SS_FIREBREATHING 112003
 
/* Added Temporarily by Dunstable, 5-April-94 */
#define SHIRE_DIR        "/d/Shire/"
#define COMMON_DIR       SHIRE_DIR + "common/"
#define LOG_DIR          SHIRE_DIR + "log/"
#define OPEN_DIR         SHIRE_DIR + "open/"
 
#define GONDOR_DIR       "/d/Gondor/"
#define KRYNN_DIR        "/d/Krynn/"
#ifndef GONDOR_HERB_DIR
#define GONDOR_HERB_DIR  GONDOR_DIR + "common/herbs/"
#endif
//#define GONDOR_HERBS     GONDOR_DIR + "common/herbs/"
#ifndef SHIRE_HERB_DIR
#define SHIRE_HERB_DIR   COMMON_DIR + "herbs/"
#endif
#ifndef KRYNN_HERB_DIR
#define KRYNN_HERB_DIR   KRYNN_DIR + "common/herbs/"
#endif


/* Dunstable's suggested new names 4 April 1994 follow here */
 
#define ANNUM_DIR       SHIRE_DIR + "annuminas/"
#define ARM_DIR         COMMON_DIR + "armour/"
#define BLUE_DIR        SHIRE_DIR + "bluemount/"
#define BREE_DIR        COMMON_DIR + "bree/"
#define BUCK_DIR        SHIRE_DIR + "buckland/"
#define BUCKLAND_DIR    SHIRE_DIR + "buckland/"
#define CASTLE_DIR      ANNUM_DIR + "castle/"
#define CAVE_DIR        BLUE_DIR + "dwarfcaves/"
#define VILLAGE_DIR     CAVE_DIR + "dwarfvillage/"
#define DOWNS_DIR       COMMON_DIR + "downs/"
#define ER_DIR          SHIRE_DIR + "eastroad/western/"
#define ERE_DIR  SHIRE_DIR + "eastroad/eastern/"
#define EROAD_DIR       COMMON_DIR + "eastroad/"
#define EVENDIM_DIR    SHIRE_DIR + "evendim/"
#define FOR_DIR         SHIRE_DIR + "forest/"
/* Added by Mansho for building Frogmorton */
#define FROG_DIR	"/d/Shire/mansho/frog/"
/* Will be changed when Frogmorton is moved to frog directory */
#define GWAY_DIR        COMMON_DIR + "greenway/"
#define GHAVEN_DIR      COMMON_DIR + "greyhaven/"
#define GREEN_DIR       SHIRE_DIR + "greenfields/"
#define HIN_DIR         COMMON_DIR + "guild/"
#define HINROOM_DIR     COMMON_DIR + "guild/rooms/"
#define HERB_DIR        COMMON_DIR + "herbs/"
#define HOBBIT_DIR      COMMON_DIR + "hobbiton/"
#define HOBBITMAKER_DIR SHIRE_DIR + "hobbitmaker/"
#define HOLLIN_DIR      COMMON_DIR + "hollin/"
#define KHAZAD_DIR      SHIRE_DIR + "khazad/"
#define DEEPS_DIR       KHAZAD_DIR + "deeps/"
#define LIB_DIR         COMMON_DIR + "lib/"
#define MICH_DIR        SHIRE_DIR + "michel/"
#define MITH_DIR        SHIRE_DIR + "mithlond/"
#define MOUNT_DIR       SHIRE_DIR + "mountain/"
#define MORIA_DIR	SHIRE_DIR + "moria/"
#define MINES_DIR	MORIA_DIR + "mines/"
#define NPC_DIR         COMMON_DIR + "monster/"
#define OBJ_DIR         COMMON_DIR + "obj/"
#define ORCMAKER_DIR    SHIRE_DIR + "orcmaker/"
#define QUEST_LOG       SHIRE_DIR + "log/QUESTS"
#define RHUD_DIR	SHIRE_DIR + "rhudaur/"
#define RIV_DIR         SHIRE_DIR + "rivendell/"
#define SHADOW_DIR	COMMON_DIR + "shadow/"
#define SHIP_DIR        COMMON_DIR + "ship/"
#define TOWER_DIR       COMMON_DIR + "towers/"
#define TROLLSH_DIR     COMMON_DIR + "trollsh/"
#define WEP_DIR         COMMON_DIR + "weapon/"
#define ELVVILL_DIR "/d/Shire/eastroad/elvenvillage/"
 
/* Original set up, as found on April 4, 1994 */
#ifndef CLOCK
#define CLOCK	"/d/Gondor/common/obj/clock"
#endif
#define ROOM_I_NO_ME_SUN "_room_i_no_me_sun"
 
#define STAND_PARENT	"/d/Shire/common/"
#define STAND_WEAPON	STAND_PARENT + "weapon/"
#define STAND_ARMOUR	STAND_PARENT + "armour/"
#define STAND_OBJ   	STAND_PARENT + "obj/"
#define STAND_MONSTER	STAND_PARENT + "monster/"
#define STAND_HERB	STAND_PARENT + "herbs/"
#define STAND_GUILD	STAND_PARENT + "guild/"
#define STAND_LIB	STAND_PARENT + "lib/"
 
#include "files.h"
 
#ifndef DO_I_TELL_RUMOURS
#define DO_I_TELL_RUMOURS "_do_i_tell_rumours"
#endif
 
#define TP this_player()
#define TO this_object()
#define PO previous_object()
 
#define LOW(x) lower_case(x)
#define CAP(x) capitalize(x)
#define HE_SHE(x) x->query_pronoun()
#define HIM_HER(x) x->query_objective()
#define HIS_HER(x) x->query_possessive()
#define ENV(x) environment(x)
#define EO environment(this_object())
#define EP environment(this_player())
#define ETO environment()
#define ETP environment(this_player())
 
#define F_VOLUME_ARMOUR this_object()->query_prop(OBJ_I_WEIGHT)/4
#define F_VOLUME_WEAPON this_object()->query_prop(OBJ_I_WEIGHT)/5
#define F_VALUE_FOOD (5 + this_object()->query_amount() * \
    this_object->query_amount() / 600)
#define ONE_OF_LIST(array) one_of_list(array)
 
#define MAKE_MONEY set_alarm(1.0,0.0,"get_money")
#define ADD_SKILL(ob,sk,x) \
    ob->set_skill_extra(sk, ob->query_skill_extra(sk) + x)
#define ADD_PROP(ob,prop,x) ob->add_prop(prop, ob->query_prop(prop)+x)
#define ADD_STAT(ob,s,x) ob->set_stat_extra(s, ob->query_stat_extra(s)+x)
 
#define SHIRE_TROLLS_KILLED "i_killed_trollshaw_trolls"
 
#define STR(x) x->query_stat(SS_STR)
#define DEX(x) x->query_stat(SS_DEX)
#define CON(x) x->query_stat(SS_CON)
#define INT(x) x->query_stat(SS_INT)
#define WIS(x) x->query_stat(SS_WIS)
#define DIS(x) x->query_stat(SS_DIS)
 
#define HP(x)  x->query_hp()
#define MAX_HP(x) x->query_max_hp()
 
#define FIXEUID { setuid(); seteuid(getuid()); }
 
#define WRITE(x) this_player()->catch_msg(x)
#define WRITEN(x) write(BSN(x))
 
/* Room specific things */
 
#ifndef NORTH
#  define EXIT(where,dir) add_exit(STAND_DIR+where,dir,0)
#  define NORTH(where) add_exit(STAND_DIR+where,"north",0)
#  define EAST(where) add_exit(STAND_DIR+where,"east",0)
#  define WEST(where) add_exit(STAND_DIR+where,"west",0)
#  define SOUTH(where) add_exit(STAND_DIR+where,"south",0)
#  define UP(where) add_exit(STAND_DIR+where,"up",0)
#  define DOWN(where) add_exit(STAND_DIR+where,"down",0) 
#  define NORTHEAST(where) add_exit(STAND_DIR+where,"northeast",0)
#  define SOUTHEAST(where) add_exit(STAND_DIR+where,"southeast",0)
#  define NORTHWEST(where) add_exit(STAND_DIR+where,"northwest",0)
#  define SOUTHWEST(where) add_exit(STAND_DIR+where,"southwest",0)
#endif
 
#define ITEM(what,desc) add_item(what,desc)
#define CMD_ITEM(what,how,desc) add_cmd_item(what,how,desc)
 
#define EVILKILL_FILE include "/d/Shire/common/lib/evilkill.h"
#define GOODKILL_FILE include "/d/Shire/common/lib/goodkill.h"
 
// Qualification macros, useful in items, quests, spells, etc
#define PHYS_STATS(x) (STR(x) + DEX(x) + CON(x))
#define MENT_STATS(x) (INT(x) + WIS(x) + DIS(x))

#define IS_OCC_RANGER query_guild_style_occ() == "ranger"
#define IS_OCC_MAGE query_guild_style_occ() == "magic"
#define IS_LAY_MAGE query_guild_style_lay() == "magic"
#define IS_OCC_CLERIC query_guild_style_occ() == "cleric"
#define IS_LAY_CLERIC query_guild_style_lay() == "cleric"
#define IS_OCC_FIGHTER query_guild_style_occ() == "fighter"
#define IS_LAY_FIGHTER query_guild_style_lay() == "fighter"
#define IS_OCC_THIEF query_guild_style_occ() == "thief"
#define IS_LAY_THIEF query_guild_style_lay() == "thief"
 
/* New defs added by Dunstable, 3-25-94, for added utility */
#define PRONOUN(x)     (x->query_pronoun())
 
#define SET_MAX_HP      set_hp(query_max_hp());
#define SET_MAX_MANA    set_mana(query_max_mana());
#define SET_MAX_FATIGUE set_fatigue(query_max_fatigue());
#define REFRESH         refresh_mobile();
 
#define QRACE(x) (x->query_race_name())
#define TI       this_interactive()
#define BS(x)    break_string(x, 75)
#define BSN(x)   (BS(x) + "\n")
#define NF(x)    notify_fail(x)
#define NFN(x)   NF(BSN(x))
#define NFN0(x)  { NFN(x); return 0; }

// A define used to limit the number of an object in the game
#define UNIQUE_CLONE(file, num, alt) \
          "/d/Shire/sys/global/clones"->unique_clone(file, num, alt)


/*
#define ADD_SKIN \
   add_leftover("/d/Khalakhor/common/obj/leftover/skin", "skin",1,"",1,1);
*/
 
/* Useful extras to be easily called from any room */
#define SKY \
   add_item(({"sky"}), \
	    "The sky is right above you, you might check the time.\n")
 
#endif
 
#include "/d/Gondor/met_defs.h"
