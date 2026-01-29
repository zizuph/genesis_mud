#ifndef _SHIRE_DEFS_
#define _SHIRE_DEFS_

/* Include the basic includes used for almost everyfile */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>   /* required for SECURITY definition. */

/* Include Shire information */
#include "/d/Shire/sys/files.h"
#include "/d/Shire/sys/paths.h"
#include "/d/Shire/sys/flags.h"

/* Include Gondor met_defs.h */
#include "/d/Gondor/met_defs.h"

/* Now the actual defines! */
#define TP        this_player()
#define TO        this_object()
#define TI        this_interactive()
#define PO        previous_object()
#define QSW       query_shadow_who()


#define HE_SHE(o)  (o)->query_pronoun()
#define HIS_HER(o) (o)->query_possessive()
#define HIM_HER(o) (o)->query_objective()
#define QRACE(o)   (o)->query_race_name()
#define QTRACE(o)  (o)->query_race()
#define ENV(o)    environment(o)
#define E(o)      environment(o)

#define WRITE(s)  TP->catch_msg(s) 
#define WRITEN(s) TP->catch_msg(s + "\n")
#define CAP(s)    capitalize(s)
#define LOW(s)    lower_case(s)
#define NF(s)     notify_fail(s)
#define NFN(s)    notify_fail(s + "\n")
#define NFN0(x)   { NFN(x); return 0; }

// global to set max number of unique items in domain
#define MAX_UNIQUE_ITEMS 7

//  Here for backwards compatibilty
#define BS(s)     (s)
#define BSN(s)    (s + "\n")

#define FIXEUID   { setuid(); seteuid(getuid()); }
#define CLONE_NPC(s) clone_object(s)->move_living("void",this_object())
#define MAKE_MONEY  set_alarm(1.0,0.0,"get_money")
#define ONE_OF(x)   one_of_list(x)
#define ONE_OF_LIST(x)  ONE_OF(x)
#define MODIFY_PROP(who, prop, val)  who->add_prop(prop, \
        who->query_prop(prop) + val)
#define ADD_SKILL(who,skill,val) who->set_skill_extra(skill, \
        who->query_skill_extra(skill) + val)
#define NO_STEEDS add_prop(ROOM_I_ALLOW_STEED, 0)

#define F_VOLUME_ARMOUR this_object()->query_prop(OBJ_I_WEIGHT)/4
#define F_VOLUME_WEAPON this_object()->query_prop(OBJ_I_WEIGHT)/5
#define F_VALUE_FOOD (5 + this_object()->query_amount() * \
    this_object->query_amount() / 600)

// defines for herbing
#define GONDOR_DIR       "/d/Gondor/"
#define KRYNN_DIR        "/d/Krynn/"
#ifndef GONDOR_HERB_DIR
#define GONDOR_HERB_DIR  GONDOR_DIR + "common/herbs/"
#endif
#define GONDOR_HERBS     GONDOR_DIR + "common/herbs/"
#ifndef SHIRE_HERB_DIR
#define SHIRE_HERB_DIR   COMMON_DIR + "herbs/"
#endif
#ifndef KRYNN_HERB_DIR
#define KRYNN_HERB_DIR   KRYNN_DIR + "common/herbs/"
#endif

// A define used to limit the number of an object in the game
#define UNIQUE_CLONE(file, num, alt) \
          "/d/Shire/sys/global/clones"->unique_clone(file, num, alt)

//  Important quest defines for the Quest Master
#ifdef QUEST_MASTER
#define CHECK_QUEST(player, quest_name) \
          QUEST_MASTER->check_quest(player, quest_name)
#define REWARD_QUEST(player, quest_name) \
          QUEST_MASTER->reward_quest(player, quest_name)
#define VARIABLE_REWARD_QUEST(player, quest_name, exp) \
          QUEST_MASTER->reward_quest(player, quest_name, exp)
#endif

// Quest defines for Shire quests
// Letter quest
#define KILLED_LETTER_ORC "_shire_killed_letter_orc"

// Misc items
#define GONDOR_FOLLOW_SHADOW    ("/d/Gondor/common/lib/follow_shadow")

// Guild related defs
#define NOLDOR_GUILD_NAME       "Noldor of Imladris"
#define RANGER_S_GUILD_NAME     "Rangers of the Westlands"
#define DUNEDAIN_S_GUILD_NAME	"Dunedain"
#define SINDAR_S_GUILD_NAME     "Sindar of Lorien"

#define IS_NOLDOR(x)    ((x)->query_guild_name_race() == NOLDOR_GUILD_NAME) 
#define IS_RANGER(x)    ((x)->query_guild_name_occ() == RANGER_S_GUILD_NAME)
#define IS_DUNADAN(x)	((x)->query_guild_name_race() == DUNEDAIN_S_GUILD_NAME)
#define IS_SINDAR(x)    ((x)->query_guild_name_race() == SINDAR_S_GUILD_NAME)


#define IS_GONDOR_WIZARD(x) (SECURITY->query_wiz_dom((x)->query_real_name()) \
                             == "Gondor")
#define IS_SHIRE_WIZARD(x) (SECURITY->query_wiz_dom((x)->query_real_name()) \
                             == "Shire")
                             
// Rivendell/Great Road elf travel route
#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"                                 
                             
// allows only rangers and ME wizards in certain areas.
#define R_ALLOWED   IS_RANGER(TP) || IS_SHIRE_WIZARD(TP) || IS_GONDOR_WIZARD (TP)

// define for milking cow quest, whether person is sitting on stool or not
#define ST_PROP_SITTING "_live_i_sitting_on_milking_stool"

// mmin/mmout props
/* Old Fogeys*/
#define LIMP_PROP   "_shire_is_limping"

/* Treehouse */
#define SKIP_PROP   "_shire_is_skipping"

// No more defines after this line.
#endif
