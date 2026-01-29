/* Guild.h */
 
#include <formulas.h>
#include <ss_types.h>
#include "../local.h"

#define GUILDMASTERS  ({ "arman" })
#define GUILD_NAME    "Cabal of Hiddukel"
#define THIEF_OBJ     TOBJ + "thief_obj"
#define CHALK_OBJ     OBJ + "chalk"
#define L_SHADOW      TOBJ + "lay_shadow"
#define THIEF_SOUL    TOBJ + "thief_soul_cabal"

/* STD soul - remove when thief commands go into the mudlib */ 
#define THIEF_STD_SOUL "/d/Krynn/open/cmd/thief_soul_mudlib"

#define CHALK         "Thief_Chalk"
#define THIEF_OBJ_ID  "Thief_OBJ"
#define KEYS_ON_RING  10

#define JOINPATH      LOG + "joined"
#define REJOINPATH    LOG + "rejoined"
#define BANISHPATH    LOG + "banished"
#define LEAVEPATH     LOG + "left"
#define ADMIN_FILE    LOG + "admin"
#define NEXT_JOIN     LOG + "next_join"
#define ACTION_LOG    LOG + "allactions"
#define HELP_DIR      LOG + "help_dir/"

#define START_ROOM    (GUILDR + "start")
#define JOIN_ROOM     (GUILDR + "join")
#define MASTER_ROOM   (GUILDR + "master")
#define POSTMASTER    (GUILDR + "postmaster")
#define MAILDIR       LOG + "ringleader/"

#define RACK_DIR        (GUILDR + "rack/")
#define RACK_COPY       (RACK_DIR + "rack_copy")
#define STD_RACK        (RACK_DIR + "std_rack")

#define SPECIALS        (GUILDR + "specials/")

#define KEY_I_NO_KEYRING           "_key_i_no_keyring"

#ifndef LIVE_I_GOT_BACKSTABBED
#define LIVE_I_GOT_BACKSTABBED     "_live_i_got_backstabbed"
#endif

#ifndef LIVE_M_ATTACK_THIEF
#define LIVE_M_ATTACK_THIEF        "_live_m_attack_thief"
#endif

#define VICTIM_I_ADDED_AWARENESS   "_victim_i_added_awareness"
#define AWARENESS_BONUS 5
        /* the bonus if you notice someone stealing from you */

#ifndef LIVE_I_LAST_STEAL
#define LIVE_I_LAST_STEAL          "_live_i_last_steal"
#endif

        /* time of the last steal attempt */

#define SS_SACRIFICE           108300 
#define SS_STOLEN              108301

#define LAY_TITLES ({ "undercover","secret","covert","stealthy",\
		      "furtive","clandestine","surreptitious"})
#define TAX        ({      5, 6, 7, 8, 9, 9, 10 })
#define MAX_TRAIN  ([ SS_WEP_KNIFE : ({30,35,40,45,48,52,60}), \
		      SS_OPEN_LOCK:({30,35,40,45,50,55,60}), \
		      SS_PICK_POCKET:({30,35,40,45,50,55,60}), \
		      SS_ACROBAT:({30,35,40,45,50,55,60}), \
		      SS_FR_TRAP:({30,35,40,45,50,55,60}), \
		      SS_SNEAK: ({30,35,40,45,50,55,60}), \
		      SS_HIDE : ({30,35,40,45,50,55,60}), \
		      SS_BACKSTAB :({25,30,35,40,45,50,60}), \
		      SS_APPR_VAL: ({30,38,44,50,55,60,60}), \
		      SS_AWARENESS:({30,38,44,50,55,60,60}), \
		      SS_TRADING : ({30,38,44,50,55,60,60}), \
		     ])
 
#define SKILL_OB "/lib/skill_raise"

#define GUILD_GROUP 1
#define MEMBER_BIT 11
#define BANISH_BIT 12
#define QUEST_BIT  13
 /* BITS:  11  12 result in:
  *         0   0   not a member/never was.
  *         1   0   is an occ member (not yet)
  *         1   1   is a layman member
  *	    0   1   banished/left
  *
  * BIT 13 is used as quest bit for the entrance quest
  */
#define QUEST_BIT  13
#define QUEST_EXP  1000

#define ALIGNRESTRICT 0
/* Set this to 0 if there is no alignment restriction for the guild,
 * 1 if there is. Restriction means the alignment of the players
 * must be <=0. Be sure to copy the correct version of
 * guild/log/help_dir/rules.* into help_dir/rules
 */

#define MEMBER(ob)     ob->test_bit("Krynn", GUILD_GROUP, MEMBER_BIT)
#define OCCUP(ob)      (ob->test_bit("Krynn", GUILD_GROUP, MEMBER_BIT) && (!ob->test_bit("Krynn", GUILD_GROUP, BANISH_BIT)))
#define LAYMAN(ob)     (ob->test_bit("Krynn", GUILD_GROUP, MEMBER_BIT) && ob->test_bit("Krynn", GUILD_GROUP, BANISH_BIT))
#define BANISHED(ob)   (!ob->test_bit("Krynn", GUILD_GROUP, MEMBER_BIT) && ob->test_bit("Krynn", GUILD_GROUP, BANISH_BIT))
 
/* all thief skills + knife,climb,trading,awareness*/
#define SKILLS ({ 50,51,52,53,54,55,56,3,104,111,110})

/*----sacrifice formula---*/
#define SACRIFICE_2_BONUS(who)  (who->query_skill(SS_SACRIFICE) * 5 / 2 / \
				 (who->query_stat(SS_LAYMAN) + 1))

/*------BACKSTAB FORMULAS--------*/
/* did i hit my victim? */
#define F_BS_HIT(bs,dex,aware,def)  (6*bs+2*dex-3*(aware+def)-random(100))

#define F_BS_JUST_ONE_HIT(bs,knife,aware,def) (2*bs+knife-aware-def+random(8))

/* the penetration of the backstab attack */
/*old!!!:  #define F_BS_PEN(bs, knife, wp, str)        F_PENMOD((120 * wp + 20 * bs + 50 * str + 200) / 300, (bs+knife)/2) */
#define F_BS_PEN(bs, knife, wp, str)        F_PENMOD(wp*(1+(bs+str))/10,knife)

#define F_BS_JUST_ONE_PEN(bs,knife,wp,str)  F_PENMOD((120*wp+20*bs+50*str+300)/300,(bs+knife)/2)

/*------STEALEXP FORMULA---------*/

#ifndef F_STEAL_EXP
#define F_STEAL_EXP(vic_val)         (vic_val*2>2048?2048:vic_val*2)
#endif
