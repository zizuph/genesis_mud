/* !!!!!!!!!!!!!!!!!!!!!!!!!!! IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!
 * This file is obsolete!! The current defs.h is ~Shire/sys/defs.h
 *
 * Lord Igneous of the Shire
 */
/*
 * This file is to be included in just about every file below
 * ~Shire/common/, by including it in the local directories defs.h.
 * This file should _NOT_ be used for files being placed in
 * ~Shire/common directly, as it defines STAND_PARENT as the
 * directory it is in, and doesn't define STAND_DIR.
 * Please use this file, and the defs.h files in the subdirectories,
 * in all Shire objects.
 *
 * Astro!
 *
 * To insure that we can smoothly rename directories I have defined
 * the include file: /d/Shire/common/dirs.h
 *
 * Sir Rogon.
 */
 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
#ifndef _SHIRE_DEFS_
#define _SHIRE_DEFS_ 1
 
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

/* Added by Mansho for building Frogmorton */
#define FROG_DIR	"/d/Shire/mansho/frog/"
/* Will be changed when Frogmorton is moved to frog directory */
 
#define STAND_ROOM	"/d/Shire/common/lib/room"
 
#include "/d/Shire/common/dirs.h"
#include "/d/Shire/common/files.h"
 
#define TP this_player()
#define TO this_object()
#define PO previous_object()
#define QSW query_shadow_who()
 
#define CAP(x) capitalize(x)
#define LOW(x) lower_case(x)
#define NF(x) notify_fail(x)
#define HE_SHE(x) x->query_pronoun()
#define HIM_HER(x) x->query_objective()
#define HIS_HER(x) x->query_possessive()
#define ENV(x) environment(x)
#define EO environment(this_object())
#define EP environment(this_player())
 
#define ADD_SKILL(ob,sk,x) ob->set_skill_extra(sk, ob->query_skill_extra(sk) + x)
#define ADD_PROP(ob,prop,x) ob->add_prop(prop, ob->query_prop(prop)+x)
#define ADD_STAT(ob,s,x) ob->set_stat_extra(s, ob->query_stat_extra(s)+x)
 
#define STR(x) x->query_stat(SS_STR)
#define DEX(x) x->query_stat(SS_DEX)
#define CON(x) x->query_stat(SS_CON)
#define INT(x) x->query_stat(SS_INT)
#define WIS(x) x->query_stat(SS_WIS)
#define DIS(x) x->query_stat(SS_DIS)
 
#define HP(x)  x->query_hp()
#define MAX_HP(x) x->query_max_hp()
 
#define FIXEUID { setuid(); seteuid(getuid()) }
 
#define WRITE(x) this_player()->catch_msg(x)
 
#define LIVE_I_DONT_CLING "_live_i_dont_follow"
 
/* Room specific things */
 
#ifndef NORTH
#define EXIT(where,dir) add_exit(STAND_DIR+where,dir,0)
#define NORTH(where) add_exit(STAND_DIR+where,"north",0)
#define EAST(where) add_exit(STAND_DIR+where,"east",0)
#define WEST(where) add_exit(STAND_DIR+where,"west",0)
#define SOUTH(where) add_exit(STAND_DIR+where,"south",0)
#define UP(where) add_exit(STAND_DIR+where,"up",0)
#define DOWN(where) add_exit(STAND_DIR+where,"down",0)
 
#define NORTHEAST(where) add_exit(STAND_DIR+where,"northeast",0)
#define SOUTHEAST(where) add_exit(STAND_DIR+where,"southeast",0)
#define NORTHWEST(where) add_exit(STAND_DIR+where,"northwest",0)
#define SOUTHWEST(where) add_exit(STAND_DIR+where,"southwest",0)
 
#define ITEM(what,desc) add_item(what,desc)
#define CMD_ITEM(what,how,desc) add_cmd_item(what,how,desc)
 
#endif
 
#define SKY add_item(({"sky"}), "You examine the sky and find that is is currently " + tod() + " in the realm.\n")
#endif
