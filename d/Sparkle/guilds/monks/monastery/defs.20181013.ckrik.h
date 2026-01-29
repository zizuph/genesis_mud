/*******************************************************************\
| DEFS.H                                                            |
+-------------------------------------------------------------------+
| Base definitions for everything in the monk area.                 |
\*******************************************************************/

#include "../defs.h"

//-------------------------------------------------------------------

#define M_PATH		(DG_PATH + "/monastery")

#define M_PATH_NPC	(M_PATH + "/npc")
#define M_PATH_OBJ	(M_PATH + "/obj")
#define M_PATH_SYS	(M_PATH + "/sys")
#define M_PATH_VAR	(M_PATH + "/var")
#define M_PATH_HELP     (M_PATH + "/help")
#define M_PATH_ROOM	(M_PATH + "/room")
#define M_PATH_SOUL	(M_PATH + "/soul")

//

#define M_NPC_BASE                      (M_PATH_SYS + "/base_npc")
#define M_NPC_MONK_BASE	                (M_PATH_SYS + "/base_npc_monk")
#define M_OBJ_BOARD_BASE                (M_PATH_SYS + "/base_obj_board")
#define M_OBJ_BOARD_MEMBER              (M_PATH_OBJ + "/board_member")
#define M_OBJ_BOARD_COUNCIL             (M_PATH_OBJ + "/board_council")
#define M_OBJ_BOARD_RECODE              (M_PATH_OBJ + "/board_recode")
#define M_OBJ_CLOTHES_ARMOUR_BASE       (M_PATH_SYS + "/base_obj_clothes_armour")
#define M_OBJ_CLOTHES_WEARABLE_BASE     (M_PATH_SYS + "/base_obj_clothes_wearable")
#define M_ROOM_BASE	                (M_PATH_SYS + "/base_room")
#define M_ROOM_TRAINING_BASE            (M_PATH_SYS + "/base_room_training")

#define M_OBJ_LIBS   	                (M_PATH_SYS + "/libs_obj")
#define M_TEXT_LIBS                     (M_PATH_SYS + "/libs_text")
#define M_EMOTE_LIBS                    (M_PATH_SYS + "/libs_emote")
#define M_TOKEN_LIBS                    (M_PATH_SYS + "/libs_token")
#define M_PLAYER_LIBS	                (M_PATH_SYS + "/libs_player")
#define M_VOTING_LIBS	                (M_PATH_SYS + "/libs_voting")
#define M_JOINING_LIBS                  (M_PATH_SYS + "/libs_joining")
#define M_LOGGING_LIBS                  (M_PATH_SYS + "/libs_logging")

#define M_MONK_SRVR	                (M_PATH_SYS + "/srvr_monk")
#define M_SHADOW_SRVR	                (M_PATH_SYS + "/srvr_shadow")

//

#define M_PATH_VAR_LOG                  (M_PATH_VAR + "/log")
#define M_FILE_LOG_BUG                  (M_PATH_VAR_LOG + "/bug")
#define M_FILE_LOG_IDEA                 (M_PATH_VAR_LOG + "/idea")
#define M_FILE_LOG_TYPO                 (M_PATH_VAR_LOG + "/typo")
#define M_FILE_LOG_DEBUG                (M_PATH_VAR_LOG + "/debug")
#define M_FILE_LOG_WIZARD               (M_PATH_VAR_LOG + "/wizard")
#define M_FILE_LOG_COUNCIL              (M_PATH_VAR_LOG + "/council")

// Note that the order of bits here must
// match the order of logs in the array.

#define M_LOGS ({ \
  M_FILE_LOG_DEBUG, \
  M_FILE_LOG_WIZARD, \
  M_FILE_LOG_COUNCIL, \
  M_FILE_LOG_BUG, \
  M_FILE_LOG_IDEA, \
  M_FILE_LOG_TYPO })

#define M_LOG_DEBUG                     BIT (0)
#define M_LOG_WIZARD                    BIT (1)
#define M_LOG_COUNCIL                   BIT (2)
#define M_LOG_BUG                       BIT (3)
#define M_LOG_IDEA                      BIT (4)
#define M_LOG_TYPO                      BIT (5)

//

#define M_PATH_VAR_NPC                  (M_PATH_VAR + "/npc")
#define M_PATH_VAR_OBJ                  (M_PATH_VAR + "/obj")
#define M_PATH_VAR_SYS                  (M_PATH_VAR + "/sys")
#define M_PATH_VAR_SOUL                 (M_PATH_VAR + "/soul")

#define M_PATH_VAR_BOARD                (M_PATH_VAR + "/board")
#define M_PATH_BOARD_MEMBER             (M_PATH_VAR_BOARD + "/member")
#define M_PATH_BOARD_COUNCIL            (M_PATH_VAR_BOARD + "/council")
#define M_PATH_BOARD_RECODE             (M_PATH_VAR_BOARD + "/recode")

#define M_PATH_VAR_LIBRARY_PUBLIC	(M_PATH_VAR + "/library_public")
#define M_PATH_LIBRARY_PUBLIC_BOOK	(M_PATH_VAR_LIBRARY_PUBLIC + "/shelves/")
#define M_PATH_LIBRARY_PUBLIC_APPR	(M_PATH_VAR_LIBRARY_PUBLIC + "/approve/")
#define M_PATH_LIBRARY_PUBLIC_REMO	(M_PATH_VAR_LIBRARY_PUBLIC + "/removed/")

#define M_PATH_VAR_LIBRARY_PRIVATE	(M_PATH_VAR + "/library_private")
#define M_PATH_LIBRARY_PRIVATE_BOOK	(M_PATH_VAR_LIBRARY_PRIVATE + "/shelves/")
#define M_PATH_LIBRARY_PRIVATE_APPR	(M_PATH_VAR_LIBRARY_PRIVATE + "/approve/")
#define M_PATH_LIBRARY_PRIVATE_REMO	(M_PATH_VAR_LIBRARY_PRIVATE + "/removed/")

//

#define M_HELP_MONK                     (M_PATH_HELP + "/monk/")
#define M_HELP_ELDER                    (M_PATH_HELP + "/elder/")
#define M_HELP_COUNCIL                  (M_PATH_HELP + "/council/")

#define M_HOOK_TRAINING                 (M_PATH_SYS + "/hook_training")
#define M_HOOK_TRAINING_LAYMAN          (M_PATH_SYS + "/hook_training_layman")
#define M_HOOK_TRAINING_OCCUPATIONAL    (M_PATH_SYS + "/hook_training_occupational")

#define M_SOUL                          (M_PATH_SOUL + "/soul")
#define M_SHADOW_LAY	                (M_PATH_SOUL + "/shadow_layman")
#define M_SHADOW_OCC	                (M_PATH_SOUL + "/shadow_occupational")

//-------------------------------------------------------------------

// Monk guild related definitions

#define M_SKILL_STRIKE	        147002
#define M_SKILL_PLEXUS	        147003
#define M_SKILL_FORMING_CLUB    151003
#define M_SKILL_FORMING_BLADE	151004
#define M_SKILL_FORMING_STICK   151005
#define M_SKILL_ACQUIRED_HIT    151006
#define M_SKILL_ACQUIRED_PEN    151007

#define M_SKILL_MAX_FORMING     100


#define M_TAX_LAY               16
#define M_TYPE_LAY	        "layman"
#define M_STYLE_LAY	        "fighter"

#define M_TAX_OCC               30
#define M_TYPE_OCC	        "occupational"
#define M_STYLE_OCC	        "fighter"


#define M_NAME_SHORT	        "Monk"
#define M_NAME_LONG	        "Order of the Dragon"

#define M_SPIRIT_LOWER          "spirit"
#define M_SPIRIT_UPPER          "Spirit"

#define M_MASTERS_ACTIVE        ({ "arandir" })
#define M_MASTERS_RETIRED       ({ "amelia", "cirion", "lilith", "manat" })

//-------------------------------------------------------------------

// Monk quest related definitions

#define M_GURU_EXP              200

//-------------------------------------------------------------------

// Monk behavior related definitions

#define M_SIZE_COUNCIL          3
#define M_TERM_COUNCIL          DG_SEC2YRS
#define M_GRACE_COUNCIL         DG_SEC2MON

#define M_PROP_TMP_I_BUSY       "_monk_tmp_i_busy"
#define M_PROP_TMP_I_SITTING    "_monk_tmp_i_sitting"
#define M_PROP_TMP_I_FORM_ALARM "_monk_tmp_i_form_alarm"
#define M_PROP_TMP_I_FORM_STEPS "_monk_tmp_i_form_steps"
#define M_PROP_TMP_I_FORM_SKILL "_monk_tmp_i_form_skill"
#define M_PROP_TMP_I_BLESSED    "_monk_tmp_i_blessed"
#define M_PROP_TMP_I_SAFEGUARD  "_monk_tmp_i_safeguard"

//-------------------------------------------------------------------

// Monk data related definitions

#define M_VOTE_MEMBERSONLY      BIT (0)
#define M_VOTE_ELDERSONLY       BIT (1)
#define M_VOTE_COUNCILONLY      BIT (2)
#define M_VOTE_PLAYERVOTES      BIT (3)
#define M_VOTE_YESNOVOTES       BIT (4)
#define M_VOTE_ANONYMOUS        BIT (5)
#define M_VOTE_SECRET           BIT (6)
#define M_VOTE_WINNER           BIT (7)
#define M_VOTE_MAJORITY         BIT (8)

#define M_VOTE_INFINITE         0

#define M_PUNISH_NOTRAIN        BIT (2)
#define M_PUNISH_EXILE          BIT (3)
#define M_PUNISH_BANISH         BIT (4)
#define M_PUNISH_NOBUY          BIT (5)
#define M_PUNISH_DISGRACE       BIT (6)
#define M_PUNISH_NOVOTE         BIT (7)

#define M_STAT_STR              0
#define M_STAT_DEX              1
#define M_STAT_CON              2
#define M_STAT_INT              3
#define M_STAT_WIS              4
#define M_STAT_DIS              5

// Used to configure title in both guild file and guild soul

#define M_TITLE_SELECT_FEW      85
#define M_TITLE_SELECT_ALL      100

#define M_TITLE_BASE_RANK       "monk"
#define M_TITLE_BASE_CHAR       "heart"
#define M_TITLE_BASE_CLERGY     "dancer"

#define M_TITLE_ADJ_NONE        "none"
#define M_TITLE_ADJ_RANK        "ancient"
#define M_TITLE_ADJ_CHAR        "hallowed"
#define M_TITLE_ADJ_ALIGN       "resplendent"

//-------------------------------------------------------------------

// Monk combat shadow related definitions

#define M_PROP_LIVE_NO_SPECIAL          "_live_m_no_"

// What is the level above which weapons are suspect
#define M_WEAPON_SUSPECT_HIT            55
#define M_WEAPON_SUSPECT_PEN            55

// How many minutes before acquired hit and pen decay
#define M_ACQUIRE_DECAY(int,wis)        \
  (((int) + (wis)) / 5)

#define M_PLEXUS_HIT                    110

// How long from starting to hitting with plexus
#define M_PLEXUS_LAND_DELAY(plexus,dex,wis) \
  (dg_random_adjust (3000.0 / itof ((plexus) + (dex) + (wis)), 0.1))
// How long stun phase of plexus
#define M_PLEXUS_STUN_DELAY(plexus,str,dex) \
  (dg_random_adjust (pow (itof ((plexus) + (str) + (dex)), 0.5) / 2.0, 0.1))
// How long slow phase of plexus
#define M_PLEXUS_SLOW_DELAY(plexus,dex,wis) \
  (dg_random_adjust (pow (itof ((plexus) + (dex) + (wis)), 0.5) / 3.0, 0.1))

#define M_PLEXUS_STUN_ID                "_monk_plexus_stun"

#define M_STRIKE_HIT(strike,acquired,dex) \
  ((acquired) + F_UNARMED_HIT (strike, dex))
#define M_STRIKE_PEN(strike,acquired,str) \
  (F_PENMOD ((acquired) + F_UNARMED_PEN ((strike), (str)), (strike)))

// How long from starting to hitting with strike
#define M_STRIKE_DELAY(strike,con) \
  (dg_random_adjust (100.0 / pow (itof ((strike) + (con)), 0.5), 0.1))

//-------------------------------------------------------------------

// Monk character shadow related definitions

// Note that the M_EMOTE definitions may not be extended
// without a corresponding change in m_classify_emote,
// which any sensible person should avoid, really.

#define M_EMOTE_UNKNOWN                 BIT(0)
#define M_EMOTE_NEUTRAL                 BIT(1)
#define M_EMOTE_MILD                    BIT(2)
#define M_EMOTE_EXTREME                 BIT(3)
#define M_EMOTE_FONDNESS                BIT(4)
#define M_EMOTE_HOSTILITY               BIT(5)
#define M_EMOTE_ADMIRATION              BIT(6)
#define M_EMOTE_DEBASEMENT              BIT(7)
#define M_EMOTE_FRIENDSHIP              BIT(8)
#define M_EMOTE_POLITENESS              BIT(9)
#define M_EMOTE_DISAGREEMENT            BIT(10)

#define M_CHARACTER_POSITIVE            0
#define M_CHARACTER_NEGATIVE            1

#define M_TRAIT_PERFECTION              0
#define M_TRAIT_HONESTY                 1
#define M_TRAIT_EFFORT                  2
#define M_TRAIT_RESPECT                 3
#define M_TRAIT_PEACEFULNESS            4

//-------------------------------------------------------------------

