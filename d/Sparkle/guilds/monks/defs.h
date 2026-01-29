/*******************************************************************\
| DEFS.H                                                            |
+-------------------------------------------------------------------+
| Base definitions for everything in the dragon area.               |
\*******************************************************************/

#include "../../sys/defs.h"

#define DG_PATH                 (S_DOMAIN_GUILD_DIR + "monks")

//-------------------------------------------------------------------

// Definitions of system files relative to the base path

#define DG_NPC_BASE	        (DG_PATH + "/sys/base_npc")
#define DG_OBJ_TABLE_BASE       (DG_PATH + "/sys/base_obj_table")
#define DG_ROOM_BASE	        (DG_PATH + "/sys/base_room")

#define DG_OBJ_LIBS	        (DG_PATH + "/sys/libs_obj")
#define DG_MISC_LIBS            (DG_PATH + "/sys/libs_misc")
#define DG_TEXT_LIBS            (DG_PATH + "/sys/libs_text")
#define DG_PLAYER_LIBS	        (DG_PATH + "/sys/libs_player")

//-------------------------------------------------------------------

/*******************************************************************\
| System related definitions                                        |
\*******************************************************************/

#ifndef FALSE
#define FALSE           0
#define TRUE            1
#endif

#ifndef NULL
#define NULL            0
#endif

#define MAILREADER      "/secure/mail_reader"
#define MAILCHECKER     "/secure/mail_checker"

//-------------------------------------------------------------------

// Constants that describe library arguments

#define ACT_OBSERVED            FALSE
#define ACT_UNOBSERVED          TRUE

#define ACTION_PARTIAL          1

#define ALARM_NONE             -1

#define ASK_STRING              FALSE
#define ASK_COMMAND             TRUE

#define ATTACK_SPECIAL          -1

#define EXIT_DELAY_DISABLED     1

#define HITLOC_ANY              -1

#define HITRES_PHURT            0
#define HITRES_HITLOC_DESC      1
#define HITRES_PHIT             2
#define HITRES_DAMAGE           3
#define HITRES_HITLOC_ID        4

#define MAIL_NONE               0
#define MAIL_ALL_READ           1
#define MAIL_SOME_NEW           2
#define MAIL_SOME_UNREAD        3

#define MOVE_SUBLOC_ALWAYS      1

#define PROP_WATER_INFINITE    -1

#define WEAR_NO                -1
#define WEAR_OK                 0
#define WEAR_OK_SILENT          1

//-------------------------------------------------------------------

// Constants that are not library related

#define DG_LINELEN              80

#define DG_SEC2MIN              60
#define DG_SEC2HRS              3600
#define DG_SEC2DAY              86400
#define DG_SEC2WEK              604800
#define DG_SEC2MON              2592000
#define DG_SEC2YRS              31558464

#define DG_HERBS_CLIFFS         0
#define DG_HERBS_FOREST         1
#define DG_HERBS_GARDEN         2
#define DG_HERBS_MEADOW         3

//-------------------------------------------------------------------

// Macros that combine library functions

#define DG_LOAD(sObj) \
  { DG_FIXUID; (sObj)->get_this_object (); }

#define DG_FIXUID \
  { setuid (); seteuid (getuid (this_object ())); }

#define DG_AMOUNT_SWITCH(iAmount,sSingular,sPlural) \
  (((iAmount) == 1) ? (sSingular) : (sPlural))

#define DG_GENDER_SWITCH(oWho,xMale,xFemale) \
  ((oWho)->query_gender () != G_FEMALE ? (xMale) : (xFemale))

#define DG_REMOVE_ALARM(iAlarm) \
  { if (iAlarm != ALARM_NONE) { remove_alarm (iAlarm); iAlarm = ALARM_NONE; } }

//-------------------------------------------------------------------

// Macros that help in displaying stuff

#define QOBJ(o)         QMET ("query_objective", (o))
#define XOBJ(o)         o->query_objective ()
#define XCOBJ(o)        capitalize (o->query_objective ())
#define QPOS(o)         QMET ("query_possessive", (o))
#define XPOS(o)         o->query_possessive ()
#define XCPOS(o)        capitalize (o->query_possessive ())
#define QPNOUN(o)       QMET ("query_pronoun", (o))
#define XPNOUN(o)       o->query_pronoun ()
#define XCPNOUN(o)      capitalize (o->query_pronoun ())

#define XNAME(m,o)      o->query_art_name (m)
#define XPNAME(m,o)     o->query_art_possessive_name (m)
#define XTNAME(m,o)     o->query_the_name (m)
#define XCPNAME(m,o)    o->query_Art_possessive_name (m)
#define XCTNAME(m,o)    o->query_The_name (m)

#define XSHORT(o)       o->short ()

//-------------------------------------------------------------------

/*******************************************************************\
| Area related definitions                                          |
\*******************************************************************/

// The requirements for knowing local names in the area.

#define DG_DIFFICULTY_KNOWNAME_EASY     TASK_ROUTINE
#define DG_DIFFICULTY_KNOWNAME_HARD     TASK_DIFFICULT
#define DG_DIFFICULTY_KNOWNAME_RARE     TASK_FORMIDABLE

#define DG_SKILLS_KNOWNAME      ({ TS_WIS, SS_AWARENESS })

//-------------------------------------------------------------------

/*******************************************************************\
| Definitions factored out into parent domain                       |
\*******************************************************************/

// The clock library was factored out in its entirety.

#define DG_CLOCK_LIBS                   S_LIB_CLOCK

#define dg_get_time                     s_get_time
#define dg_get_time_hour_of_period      s_get_time_hour_of_period
#define dg_get_time_hour_of_day         s_get_time_hour_of_day
#define dg_get_time_day_of_year         s_get_time_day_of_year

#define dg_get_stime_hour_of_period     s_get_stime_hour_of_period
#define dg_get_stime_period             s_get_stime_period
#define dg_get_stime_season             s_get_stime_season

#define dg_embed_stime_season           s_embed_stime_season

#define dg_is_morning                   s_is_morning
#define dg_is_afternoon                 s_is_afternoon
#define dg_is_evening                   s_is_evening
#define dg_is_night                     s_is_night

#define dg_is_spring                    s_is_spring
#define dg_is_summer                    s_is_summer
#define dg_is_autumn                    s_is_autumn
#define dg_is_winter                    s_is_winter

#define dg_embed_when_morning           s_embed_when_morning
#define dg_embed_when_afternoon         s_embed_when_afternoon
#define dg_embed_when_evening           s_embed_when_evening
#define dg_embed_when_night             s_embed_when_night

#define dg_embed_when_not_night         s_embed_when_not_night

#define dg_embed_when_spring            s_embed_when_spring
#define dg_embed_when_summer            s_embed_when_summer
#define dg_embed_when_autumn            s_embed_when_autumn
#define dg_embed_when_winter            s_embed_when_winter

#define dg_embed_when_not_winter        s_embed_when_not_winter

#define dg_get_when_morning             s_get_when_morning
#define dg_get_when_afternoon           s_get_when_afternoon
#define dg_get_when_evening             s_get_when_evening
#define dg_get_when_night               s_get_when_night

#define dg_get_when_not_night           s_get_when_not_night

#define dg_get_when_spring              s_get_when_spring
#define dg_get_when_summer              s_get_when_summer
#define dg_get_when_autumn              s_get_when_autumn
#define dg_get_when_winter              s_get_when_winter

#define dg_get_when_not_winter          s_get_when_not_winter

//-------------------------------------------------------------------

