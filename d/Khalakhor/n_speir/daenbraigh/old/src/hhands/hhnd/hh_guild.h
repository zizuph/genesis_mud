/*
 * Hammerhand basic include file
 *
 */

#ifndef _HH_GUILD
#define _HH_GUILD

#include "../hhands.h"
#include <wa_types.h>

#define HHANDS_NAME "Hammerhands"
#define HHANDS_STYLE "fighter"
#define HHANDS_TAX   10
#define HHANDS_SKILL 75

#define HHANDS_DIR HHGLD

#define HHANDS_SHADOW   HHANDS_DIR + "hh_shadow"
#define HHANDS_SOUL     HHANDS_DIR + "hh_soul"
#define HHANDS_TATTOO   HHANDS_DIR + "hh_tattoo"
#define HHANDS_STARTLOC HHANDS_DIR + "dorm"

#define HHANDS_ID       HHANDS_NAME + "__tattoo"

#define HHANDS_TITLE    ({ \
    "The Fresh Hammerhand",\
    "The Amateur Hammerhand",\
    "The Aspiring Hammerhand",\
    "The Practiced Hammerhand",\
    "The Able Hammerhand",\
    "The Steady Hammerhand",\
    "The Stalwart Hammerhand",\
    "The Weighty Hammerhand",\
    "The Skilled Hammerhand",\
    "The Impressive Hammerhand",\
    "The Famous Hammerhand",\
    "The Powerful Hammerhand",\
    "The Superior Hammerhand",\
    "The Titanic Hammerhand",\
    "The Crushing Hammerhand",\
    "The Hammermaster",\
    "The Legendary Hammermaster",\
    })

#define HHANDS_MAXLEVEL 16
#define HHANDS_SUBLOC   HHANDS_NAME + "__subloc"

#define HH_WP_SKILL_TO_TYPE ([
             W_SWORD: SS_WEP_CLUB,
	     W_POLEARM: SS_WEP_POLEARM,
	     W_AXE: SS_WEP_AXE,
	     W_SWORD: SS_WEP_SWORD
	])
#define HH_SKILL 75

#define HH_ATTACK_JAB 1
#define HH_ATTACK_HOOK 2
#define HH_ATTACK_JOINT 3
#define HH_ATTACK_WHIRLWIND 4
#define HH_ATTACK_NAME ("jab","hook","joint","whirlwind"})
#define HH_ATTACK "_hh_attack"
#define HH_ATTACK_STATE "_hh_attack_state"
#define HH_ATTACK_PREPARE 1
#define HH_ATTACK_RELAX 2
#define HH_ATTACK_READY 0
#define HH_ATTACK_CHANCE_BASE 500
#define HH_ATTACK_PREPARE_TIME 5.0
#define HH_ATTACK_RELAX_TIME 5.0

#define SS_HH_JAB_SKILL 146150
#define SS_HH_HOOK_SKILL 146151
#define SS_HH_JOINT_SKILL 146152
#define SS_HH_WHIRLWIND_SKILL 146153


#endif _HH_GUILD
