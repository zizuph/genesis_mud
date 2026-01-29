#ifndef _SHIRE_DEFS_
#define _SHIRE_DEFS_

/* Include the basic includes used for almost everyfile */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

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

// No more defines after this line.
#endif
