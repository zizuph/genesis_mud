/* This is a set of handy definitions for the Grunts guild.                */
/* Coded on 20/08/1995 by Tulix III.                                       */
/* Note - GRUNTS_DIR is defined in the file /d/Emerald/defs.h so make sure */
/* all objects that include this file also include the above file first!   */

#ifndef GRUNTS_DEFS
#define GRUNTS_DEFS

#undef GUILD_NAME

/* Define the general race guild characteristics */
#define GUILD_NAME               "Grunts guild"
#define GUILD_TYPE               "race"
#define GUILD_STYLE              "race"
#define GUILD_SOUL_ID            "grunts"

#define GUILD_TAX                 1

#undef  GRUNTS_DIR
#define GRUNTS_DIR                "/d/Emerald/common/guild/grunts/"
#define GRUNTS_OBJ_DIR            GRUNTS_DIR + "obj/"
#define GRUNTS_HELP_DIR           GRUNTS_DIR + "help/"
#define GRUNTS_LOG_DIR            GRUNTS_DIR + "log/"
#define GRUNTS_SOUL_DIR           GRUNTS_DIR + "soul/"
#define GRUNTS_ROOM_DIR           GRUNTS_DIR + "room/"
#define GRUNTS_NPC_DIR            GRUNTS_DIR + "npc/"

#define GUILD_OBJECT              GRUNTS_DIR + "obj/grunts_collar"
#define GRUNTS_GUILD_EMBLEM       GRUNTS_OBJ_DIR + "grunts_collar"
#define GRUNTS_GUILD_SOUL         GRUNTS_SOUL_DIR + "grunts_soul"
#define GUILD_SOUL                GRUNTS_DIR + "obj/grunts_soul"
#define GUILD_SHADOW              GRUNTS_DIR + "obj/grunts_shadow"

#define ADVERB_MANAGER            (GRUNTS_LOG_DIR + "adverbs")
#define GRUNTS_CRAP               GRUNTS_DIR + "obj/grunts_crap"
#define GRUNTS_STINK              GRUNTS_DIR + "obj/grunts_stink"
#define GRUNTS_SLIP_TIMER         GRUNTS_DIR + "obj/grunts_slip_timer"
#define GRUNTS_SPIKE              GRUNTS_DIR + "obj/grunts_spike"
#define GRUNTS_ROASTED_FLEA       GRUNTS_DIR + "obj/roasted_flea"
#define GRUNTS_LIVE_FLEA          GRUNTS_DIR + "obj/live_flea"

#define GRUNTS_WARCRY_DIR         GRUNTS_DIR + "warcry/"

#define LIVE_AS_GRUNTS_HERITAGE   "_live_as_grunts_heritage"
#define LIVE_AS_GRUNTS_RECRUITED  "_live_as_grunts_recruited"

#define LIVE_S_GRUNTS_WARCRY      "_live_s_grunts_warcry"
#define LIVE_I_SLIP_POSSIBLE      "_live_i_slip_possible"
#define LIVE_I_CRAPPED_NUMBER     "_live_i_crapped_number"
#define LIVE_I_HAS_BEEN_THINKING  "_live_i_has_been_thinking"
#define LIVE_I_HARVESTED_FLEAS    "_live_i_harvested_fleas"

#define GRUNT_KILLS_COUNT         132060

#endif
