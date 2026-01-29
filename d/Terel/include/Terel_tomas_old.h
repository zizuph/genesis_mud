/*
 * Master include file for Terel domain.  All rooms should include this
 * file first.
 *
 * September 1994 Sorgum 
 */

/*
 * If an include file like this one is included more than once it will
 * cause errors since the macros will be defined more than once.
 * The following two lines insure that the macros will only be defined once
 * even if this file included multiple times.
 */

#ifndef _TEREL_H_
#define _TEREL_H_

#include <stdproperties.h>
#include <macros.h>

/*
 * Some handy shorthand definitions
 */

#define TP         this_player()
#define TO         this_object()
#define TI         this_interactive()

#define NF(mesg)   notify_fail(mesg)
#define ENV(arg)   environment(arg)
#define ETO        environment(this_object())
#define ETP        environment(this_player())

#define CAP(x)     capitalize(x)

/*
 * BS and BSN are not needed anymore as the gd does it for us.  The following
 * two defs are for backward compatibility.
 */
#define BS(mesg)   break_string(mesg, 70)
#define BSN(mesg)  break_string(mesg, 70) + "\n"

#define SET_MAX_HP      set_hp(query_max_hp())
#define SET_MAX_MANA    set_mana(query_max_mana())
#define SET_MAX_FATIGUE set_fatigue(query_max_fatigue())
#define SKIN "/d/Khalakhor/common/obj/leftover/skin"
#define ADDSKIN add_leftover(SKIN, "skin", 1, "", 0, 1)
#define MEAT "/d/Terel/std/meats"
#define ADDMEAT(x) add_leftover(MEAT, "meat", x, "", 0, 1)

#define BRAVE           set_whimpy(0)
#define AGGRESSIVE      set_aggressive(1)
#define PASSIVE         set_aggressive(0)

#define POSSESSIVE(x)   (x->query_possessive())
#define OBJECTIVE(x)    (x->query_objective())
#define PRONOUN(x)      (x->query_pronoun())

#define FIX_EUID seteuid(getuid(this_object()))
 
#define ME(x) if (find_player("sorgum")) \
              find_player("sorgum")->catch_msg(x + "\n")
/*
 * Pathnames.  Define and use these from here so we can reorganize the
 * directory structure transparently.
 */

#define DOMAIN_DIR    "/d/Terel/"
#define TEREL_DIR     "/d/Terel/"
#define GUILDS_DIR     "/d/Terel/guilds/"
#define STD_DIR       "/d/Terel/std/"

#define SORGUM_DIR    "/d/Terel/sorgum/"
#define MECIEN_DIR    "/d/Terel/mecien/"
#define MORTRICIA_DIR "/d/Terel/mortricia/"
#define CEDRIC_DIR    "/d/Terel/cedric/"
#define VADER_DIR     "/d/Terel/vader/"
#define REDHAWK_DIR   "/d/Terel/redhawk/"
#define JANUS_DIR     "/d/Terel/janus/"
#define DUST_DIR      "/d/Terel/dust/" 
#define TOMAS_DIR     "/w/tomas/"

#define HERB_DIR      "/d/Gondor/common/herbs/"
#define TER_HERB      "/d/Terel/common/herbs/"
#define GON_HERB      "/d/Gondor/common/herbs/"
#define KRY_HERB      "/d/Krynn/common/herbs/"
#define AVE_HERB      "/d/Avenir/common/herbs/"
#define CAL_HERB      "/d/Calia/common/herbs/"
#define KHA_HERB      "/d/Khalakhor/common/herbs/"
#define SHI_HERB      "/d/Shire/common/herbs/"

#define CALATHIN_DIR "/d/Terel/calathin/"
#define MANSION      "/d/Terel/common/town/mansion/"
#define DARK_DIR     "/d/Terel/dark/"

#define ORC_CAVE_DIR  "/d/Terel/orc_cave/"
#define ZODIAC_DIR    "/d/Terel/zodiac/"
#define SILVER_DIR    "/d/Terel/silver/"
#define LOD_DIR       "/d/Terel/LoD/"
#define SHIP_DIR      "/d/Terel/ships/"
#define PORT_DIR      "/d/Terel/port/"
#define NPORT_DIR     "/d/Terel/n_port/"
#define ENCHANT_DIR   "/d/Terel/enchanted/"
#define GARDEN_DIR    "/d/Terel/garden/"
#define RIBOS_DIR     "/d/Terel/ribos/"
#define FROST2_DIR     "/d/Terel/common/frost/"
#define FROST_DIR     "/d/Terel/sorgum/frost/"        
#define LAST_DIR      "/d/Terel/last/"
#define TROLL_CAVE_DIR    "/d/Terel/common/moor/tcaves/"
#define TROLL_DIR    "/d/Terel/mountains/tcave/"
#define MOOR_DIR      "/d/Terel/common/moor/"
#define COMPANY         "/d/Terel/company/"
#define DABAAY_DIR    "/d/Terel/dabaay/"
#define MOUNTAIN_DIR  "/d/Terel/mountains/"

#ifndef T_WIZ
#define T_WIZ(xx)      ((xx)->query_wiz_level() &&\
"/secure/master"->query_wiz_dom(xx->query_real_name())=="Terel")
#endif

/*
 * These should be in some mudlib file somewhere.
 */

#define MALE (0)
#define FEMALE (1)
#define NEUTER (2)


#define STDROOM       STD_DIR + "room"
#define STDSHOP        STD_DIR + "shop"
#define STDOBJECT     STD_DIR + "object"
#define STDWEAPON     STD_DIR + "weapon"
#define STDARMOUR     STD_DIR + "armour"
#define STDWEARABLE    STD_DIR + "wearable_item"
#define STDCREATURE   STD_DIR + "creature"
#define STDMONSTER    STD_DIR + "monster"
#define STDFOOD       STD_DIR + "food"
#define STDDRINK      STD_DIR + "drink"
#define STDDOOR       STD_DIR + "door"    
#define STDHSEARCH    STD_DIR + "herbsearch"

#define INSIDE   add_prop(ROOM_I_INSIDE, 1)
#define OUTSIDE  add_prop(ROOM_I_INSIDE, 0)
#define DARK     add_prop(ROOM_I_LIGHT, 0)

/*
 * This is here for compatibility with zodiac orc fire quest
 */
    
#define ROOM_HAS_WATER  "_obj_i_contain_water"

#define LIVE_I_INTRO_ENABLED "_live_i_intro_enabled"
    
/*
 * For use in any race size based item.
 */
#define RACE_SIZE_TRACKER "/d/Terel/lib/race_size_tracker"
#define SMALL 1
#define MEDIUM 2
#define LARGE 4
#define HUGE 8
#define ANY_SIZE 15

/*
 * For use with hordes.
 */
#define HORDE_MASTER "/d/Terel/torm/hm"
#define HORDE_SAVE "/d/Terel/torm/horde_save"
#define OBJ_S_HORDE_OWNER "_obj_s_horde_owner"

#define WEATHER_MASTER "/d/Terel/lib/weather"

/*
 * Definitions for the Hand
 */
#define HAND_MARK "Hand_mark"

#endif
