/*
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */
#ifndef KENDER_GUILD_DEFS
#define KENDER_GUILD_DEFS

#include "/d/Ansalon/goodlund/kendermore/local.h"

#define GUILD_NAME          "Secret Society of Uncle Trapspringer"
#define GUILD_STYLE         "thief"
#define GUILD_TAX           (28)

/* Directory defines */
#define KENDERG_DIR         "/d/Ansalon/guild/society/"
#define TEST_DIR            "/d/Ansalon/guild/kender_occ/"
#define KGHELP              (KENDERG_DIR + "help/")
/* FIX ME!! */
#define KGLOG               (TEST_DIR    + "log/")
#define KGOBJ               (KENDERG_DIR + "obj/")
#define KGROOM              (KENDERG_DIR + "room/")
#define KGNPC               (KENDERG_DIR + "npc/")
#define KGLIB               (KENDERG_DIR + "library/")
#define KGTEXT              (KENDERG_DIR + "text/")

#define LIVE_I_DODGE_BRIEF	"_live_i_dodge_brief"
#define TAUNT_LIST		    (KENDERG_DIR + "taunt_list")

/* Specials */
#define TAUNT_SH            ("/d/Ansalon/guild/kender_occ/taunt_sh.c")
#define TAUNT_OBJ           ("/d/Ansalon/guild/kender_occ/taunt_obj.c")
#define DODGE_OBJ           ("/d/Ansalon/guild/kender_occ/dodge_obj.c")
#define DODGE_ABILITY       (TEST_DIR + "dodge.c")
#define SLING_ABILITY       (TEST_DIR + "sling.c")

#define ALTER_LIST          ({                                                 \
    "/d/Krynn/solace/new_village/town_square/thimah/item/complex_staff",       \
                            })

/* Room and object defines */
#define GUILD_POST		    (KGROOM     + "po")
#define GUILD_STARTLOC	    (KGROOM     + "start")
/*#define GUILD_EMBLEM	    (KGOBJ      + "gitem")*/
#define GUILD_EMBLEM        (KGOBJ      + "new_gitem")

#define KENDERG_SHADOW      (TEST_DIR   + "kender_shadow")
#define GUILD_CMDSOUL       (TEST_DIR   + "kender_soul")
#define HOOPAK_SHADOW       (TEST_DIR   + "alter_shadow")
#define HOOPAK_CREATION     (TEST_DIR   + "hoopak_creation")
#define HOOPAK_SLING        (TEST_DIR   + "hoopak_sling")

#define KENDER_BOARD	    (KGLOG      + "boards")
#define KVOTE_BOARD		    (KGLOG      + "vboards")
#define KINT_BOARD		    (KGLOG      + "iboards")
#define GUILD_EMBLEM_ID	    (GUILD_NAME + "emblem")
#define VMASTER			    (KGROOM     + "vote_room")

/* Log file define, last three for backwards compatibility */

#define KEN_LOG			    "kender_log"
#define JOINED			    "kender_log"
#define LEFT			    "kender_log"
#define ACCEPTED		    "kender_log"

#define MEMBER(x) x->query_guild_member(GUILD_NAME)

#define LIVE_I_DODGE_BRIEF	"_live_i_dodge_brief"
#define SLING_PREPARE		"_ken_sling_spec_prepare"
#define SLING_RESET		    "_ken_sling_spec_reset"
#define DODGE_DODGING		"_ken_dodge_spec_dodging"
#define DODGE_RESET		    "_ken_dodge_spec_reset"
#define TAUNT_PREPARE		"_ken_taunt_spec_prepare"
#define TAUNT_RESET		    "_ken_taunt_spec_reset"
#define TAUNT_LIST		    (KENDERG_DIR + "taunt_list")

/* The skill numbers for the guild's special skills assigned by the liege. */

#define SS_CTACT_SPECIAL	143010
#define SS_TAUNT_SPECIAL	143011
#define SS_RACK_TALLY		143012
#define SS_HOOPAK_ALTER		143013

/* Place all definitions above this line. */

#endif KENDER_GUILD_DEFS
