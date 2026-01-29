/*******************************************************************\
| HOOK_TRAINING.H                                                   |
\*******************************************************************/

/*
 * 06/09/13 Arandir     Updated maximum values after combat changes
 * 06/08/16 Arandir     Removed the ability to focus
 *                      Removed the polearm skill
 * 03/05/03 Arandir	Ported to new area and bugfixed
 * 98/06/28 Cirion	Created
 *
 */

//-------------------------------------------------------------------

// This is where the skill limits are defined. To change
// the skill configuration, simply change the appropriate
// number here.

#define M_SKILL_MAX_OCC_UNARMED         100
#define M_SKILL_MAX_OCC_DEFENCE         100
#define M_SKILL_MAX_OCC_BLINDFIGHT      90
#define M_SKILL_MAX_OCC_AWARENESS       90
#define M_SKILL_MAX_OCC_HERBALISM       75
#define M_SKILL_MAX_OCC_ELEMENTAIR      5
#define M_SKILL_MAX_OCC_DIVINATION      5
#define M_SKILL_MAX_OCC_APPROBJ         60
#define M_SKILL_MAX_OCC_APPRMON         60
#define M_SKILL_MAX_OCC_STRIKE          100
#define M_SKILL_MAX_OCC_PLEXUS          100

#define M_SKILL_MAX_LAY_UNARMED         50
#define M_SKILL_MAX_LAY_DEFENCE         50
#define M_SKILL_MAX_LAY_BLINDFIGHT      45
#define M_SKILL_MAX_LAY_AWARENESS       60
#define M_SKILL_MAX_LAY_HERBALISM       50
#define M_SKILL_MAX_LAY_ELEMENTAIR      5
#define M_SKILL_MAX_LAY_DIVINATION      5
#define M_SKILL_MAX_LAY_APPROBJ         50
#define M_SKILL_MAX_LAY_APPRMON         50
#define M_SKILL_MAX_LAY_STRIKE          60
#define M_SKILL_MAX_LAY_PLEXUS          0

//-------------------------------------------------------------------

// Mapping of the configuration of all skills for the monks.
//
// ([ skill :
//   ({
//     ({ occ max, description, name, cost, stat limit, stat weight }),
//     ({ lay max, description, name, cost, stat limit, stat weight }) }) ])
//
// This method allows us to have exactly one place where all the skills
// are defined for the guild, such that any changes that need to be
// made to the skills can be done in exactly one place. This also
// allows us to do things like have modules that give reports on
// the available skills for wizards, etc.

#define M_SKILLS_OCCUP          0
#define M_SKILLS_LAYMAN         1

#define M_SKILLS_MAXIMUM        0
#define M_SKILLS_DESC           1
#define M_SKILLS_NAME           2
#define M_SKILLS_COST           3
#define M_SKILLS_STAT_LIMIT     4
#define M_SKILLS_STAT_WEIGHT    5

#define M_SKILL_LIST ({ \
  SS_UNARM_COMBAT, \
  SS_DEFENCE, \
  SS_BLIND_COMBAT, \
  SS_AWARENESS, \
  SS_HERBALISM, \
  SS_ELEMENT_AIR, \
  SS_FORM_DIVINATION, \
  SS_FORM_DIVINATION, \
  SS_APPR_OBJ, \
  SS_APPR_MON, \
  M_SKILL_STRIKE, \
  M_SKILL_PLEXUS })

#define M_SKILL_MAP ([ \
    SS_UNARM_COMBAT : \
      ({ ({ M_SKILL_MAX_OCC_UNARMED, "fight unarmed", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_UNARMED, "fight unarmed", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_DEFENCE : \
      ({ ({ M_SKILL_MAX_OCC_DEFENCE, "defend against attacks", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_DEFENCE, "defend against attacks", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_BLIND_COMBAT : \
      ({ ({ M_SKILL_MAX_OCC_BLINDFIGHT, "fight in darkness", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_BLINDFIGHT, "fight in darkness", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_AWARENESS : \
      ({ ({ M_SKILL_MAX_OCC_AWARENESS, "be aware of surroundings", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_AWARENESS, "be aware of surroundings", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_HERBALISM : \
      ({ ({ M_SKILL_MAX_OCC_HERBALISM, "locate and identify herbs", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_HERBALISM, "locate and identify herbs", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_ELEMENT_AIR : \
      ({ ({ M_SKILL_MAX_OCC_ELEMENTAIR, "cast air spells", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_ELEMENTAIR, "cast air spells", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_FORM_DIVINATION : \
      ({ ({ M_SKILL_MAX_OCC_DIVINATION, "cast divining spells", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_DIVINATION, "cast divining spells", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_APPR_OBJ : \
      ({ ({ M_SKILL_MAX_OCC_APPROBJ, "appraise objects", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_APPROBJ, "appraise objects", \
            0, 5, SS_LAYMAN, 100 }) }), \
    SS_APPR_MON : \
      ({ ({ M_SKILL_MAX_OCC_APPRMON, "appraise others", \
            0, 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_APPRMON, "appraise others", \
            0, 5, SS_LAYMAN, 100 }) }), \
    M_SKILL_STRIKE : \
      ({ ({ M_SKILL_MAX_OCC_STRIKE, "strike opponents", \
            "strike", 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_STRIKE, "strike opponents", \
            "strike", 5, SS_LAYMAN, 100 }) }), \
    M_SKILL_PLEXUS : \
      ({ ({ M_SKILL_MAX_OCC_PLEXUS, "stun opponents", \
            "plexus", 5, SS_OCCUP, 100 }), \
         ({ M_SKILL_MAX_LAY_PLEXUS, "stun opponents", \
            "plexus", 5, SS_LAYMAN, 100 }) }), \
  ])

//-------------------------------------------------------------------

