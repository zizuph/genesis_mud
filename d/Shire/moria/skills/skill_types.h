#ifndef _SKILL_TYPES_H_
#define _SKILL_TYPES_H_

#include "/d/Shire/skills.h"

#define SKILL_DIR                "/d/Shire/moria/skills/"
#define BASH_FILE                (SKILL_DIR + "bash")
#define BRAWL_FILE               (SKILL_DIR + "brawl")
#define DISARM_UNARMED_FILE      (SKILL_DIR + "disarm")
#define DISARM_ARMED_FILE        (SKILL_DIR + "disarm_a")
#define EVAL_ARMS_FILE           (SKILL_DIR + "evalarms")
#define EVAL_WEPS_FILE           (SKILL_DIR + "evalwep")
#define FUMBLE_FILE              (SKILL_DIR + "fumble")
#define FIST_PUNCH_FILE          (SKILL_DIR + "fist")
#define WEAVE_FILE               (SKILL_DIR + "weave")

#define _BASH(who, tp)           BASH_FILE->bash(who, tp)
#define _BRAWL(who, tp)          BRAWL_FILE->brawl(who, tp)
#define _COMP_ARMS(o1, o2)       EVAL_ARMS_FILE->eval_arms(o1, o2)
#define _COMP_WEPS(o1, o2)       EVAL_WEPS_FILE->eval_weapon(o1, o2)
#define _DISARM_U(who, tp)       DISARM_UNARMED_FILE->disarm_foe_unarmed(who, tp)
#define _DISARM_A(who, tp)       DISARM_ARMED_FILE->disarm_foe_armed(who, tp)
#define _EVAL_ARMS(obj)          EVAL_ARMS_FILE->eval_arms(obj)
#define _EVAL_WEPS(obj)          EVAL_WEPS_FILE->eval_weapon(obj)
#define _PUNCH(who, tp)          FIST_PUNCH_FILE->fist_punch(who, tp)
#define _WEAVE(who, tp)          WEAVE_FILE->start_weaving(who, tp)

#endif
