#include "../defs.h"
#include <ss_types.h>

// definitions for skill training.
// these should be moved to a separate file

// here is where skill maximums are defined. To change
// the skill configurations, simply change the appropriate
// number here.
#define MAX_OCC_UNARM_COMBAT      100
#define MAX_OCC_DEFENCE           100
#define MAX_OCC_WEP_POLEARM        75
#define MAX_OCC_BLIND_COMBAT       75
#define MAX_OCC_AWARENESS          75
#define MAX_OCC_HERBALISM          50
#define MAX_OCC_ELEMENT_AIR         5
#define MAX_OCC_FORM_DIVINATION     5
#define MAX_OCC_APPR_OBJ           50
#define MAX_OCC_APPR_MON           50
#define MAX_OCC_FOCUS             100
#define MAX_OCC_STRIKE            100
#define MAX_OCC_PLEXUS            100

#define MAX_LAY_UNARM_COMBAT       50
#define MAX_LAY_DEFENCE            50
#define MAX_LAY_WEP_POLEARM        45
#define MAX_LAY_BLIND_COMBAT       45
#define MAX_LAY_AWARENESS          60
#define MAX_LAY_HERBALISM          40
#define MAX_LAY_ELEMENT_AIR         5
#define MAX_LAY_FORM_DIVINATION     5
#define MAX_LAY_APPR_OBJ           40
#define MAX_LAY_APPR_MON           40
#define MAX_LAY_FOCUS              50
#define MAX_LAY_STRIKE             60
#define MAX_LAY_PLEXUS              0


// mapping of the configuration of all skills for the monks, of the form:
//    skill_number :
//        ({ ({ occ max, description, skill name, cost factor, limiting stat, limit weight }),
//           ({  lay max, description, skill name, cost factor, limiting stat, limit weight }) })
// used by ~monks/lib/train.c
//
// While this may seem to be a very convoluted way to set up skills,
// this method allows us to have exactly one place where all the skills
// are defined for the guild, such that any changes that need to be
// made to the skills can be done in exactly one place. This also
// allows us to do thinks like have modules that give reports on
// the available skills for wizards, etc.

// macros for indices of the definitions in the skill mapping
#define MONK_SKILL_INDEX_OCC            0
#define MONK_SKILL_INDEX_LAY            1
#define MONK_SKILL_INDEX_MAX            0
#define MONK_SKILL_INDEX_DESC           1
#define MONK_SKILL_INDEX_SKNAME         2
#define MONK_SKILL_INDEX_COST           3
#define MONK_SKILL_INDEX_LIMITING_STAT  4
#define MONK_SKILL_INDEX_LIMIT_WEIGHT   5

#define MONK_SKILL_CONFIG_MAPPING  ([                       \
    MONK_SKILL_STRIKE      :                                \
        ({ ({ MAX_OCC_STRIKE, "strike the enemy",           \
                "strike", 5, SS_OCCUP, 100 }),              \
           ({ MAX_LAY_STRIKE, "strike the enemy",           \
                "strike", 5, SS_LAYMAN, 100 }) }),          \
    SS_UNARM_COMBAT    :                                   \
        ({ ({ MAX_OCC_UNARM_COMBAT, "battle unarmed",      \
                0, 5, SS_OCCUP, 100 }),                    \
           ({ MAX_LAY_UNARM_COMBAT, "battle unarmed",      \
                0, 5, SS_LAYMAN, 100  }) }),               \
    SS_DEFENCE         :                                   \
        ({ ({ MAX_OCC_DEFENCE, "defend against attacks",   \
                0, 5, SS_OCCUP, 100  }),                   \
           ({ MAX_LAY_DEFENCE, "defend against attacks",   \
                0, 5, SS_LAYMAN, 100 }) }),                \
    SS_WEP_POLEARM     :                                   \
        ({ ({ MAX_OCC_WEP_POLEARM, "fight with a polearm", \
                0, 5, SS_OCCUP, 100 }),                    \
           ({ MAX_LAY_WEP_POLEARM, "fight with a polearm", \
                0, 5, SS_LAYMAN, 100 }) }),                \
    SS_BLIND_COMBAT    :                                   \
        ({ ({ MAX_OCC_BLIND_COMBAT, "fight in darkness",   \
                0, 5, SS_OCCUP, 100 }),                    \
           ({ MAX_LAY_BLIND_COMBAT, "fight in darkness",   \
                0, 5, SS_LAYMAN, 100 }) }),                \
    SS_AWARENESS       :                                   \
        ({ ({ MAX_OCC_AWARENESS, "be aware of surroundings",\
                0, 5, SS_OCCUP, 100 }),                     \
           ({ MAX_LAY_AWARENESS, "be aware of surroundings",\
                0, 5, SS_LAYMAN, 100 }) }),                 \
    SS_HERBALISM       :                                    \
        ({ ({ MAX_OCC_HERBALISM, "locatee and identify herbs",\
                0, 5, SS_OCCUP, 100 }),                     \
           ({ MAX_LAY_HERBALISM, "locatee and identify herbs",\
                0, 5, SS_LAYMAN, 100 }) }),                 \
    SS_ELEMENT_AIR       :                                    \
        ({ ({ MAX_OCC_ELEMENT_AIR, "cast spells of the air element",\
                0, 5, SS_OCCUP, 100 }),                     \
           ({ MAX_LAY_ELEMENT_AIR, "cast spells of the air element",\
                0, 5, SS_LAYMAN, 100 }) }),                 \
    SS_FORM_DIVINATION       :                                    \
        ({ ({ MAX_OCC_FORM_DIVINATION, "cast divining spells",\
                0, 5, SS_OCCUP, 100 }),                     \
           ({ MAX_LAY_FORM_DIVINATION, "cast divining spells",\
                0, 5, SS_LAYMAN, 100 }) }),                 \
    SS_APPR_OBJ        :                                    \
        ({ ({ MAX_OCC_APPR_OBJ, "appraise the value and properties of objects",\
                0, 5, SS_OCCUP, 100 }),                     \
           ({ MAX_LAY_APPR_OBJ, "appraise the value and properties of objects",\
                0, 5, SS_LAYMAN, 100 }) }),                 \
    SS_APPR_MON        :                                    \
        ({ ({ MAX_OCC_APPR_MON, "appraise the strengths of others",\
                0, 5, SS_OCCUP, 100 }),                     \
           ({ MAX_LAY_APPR_MON, "appraise the strengths of others",\
                0, 5, SS_LAYMAN, 100 }) }),                 \
    MONK_SKILL_FOCUS       :                                \
        ({ ({ MAX_OCC_FOCUS, "use dragon focus",            \
                "focus", 5, SS_OCCUP, 100 }),               \
           ({ MAX_LAY_FOCUS, "use dragon focus",            \
                "focus", 5, SS_LAYMAN, 100 }) }),           \
    MONK_SKILL_PLEXUS      :                                \
        ({ ({ MAX_OCC_PLEXUS, "strike against the solar plexus of humanoids",\
                "plexus", 5, SS_OCCUP, 100 }),              \
           ({ MAX_LAY_PLEXUS, "strike against the solar plexus of humanoids",\
                "plexus", 5, SS_LAYMAN, 100 }) }),          \
    ])

