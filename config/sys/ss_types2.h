/*
 * ss_types2.h
 *
 * This file defines the available stats and skills that are locally
 * configured. The only use of this file is that it should be included
 * by /sys/ss_types.h.
 */

/* These are used in guild_support.c */
#define GS_PRIMARY_FOCUS        100
#define GS_SECONDARY_FOCUS       60
#define GS_DEFAULT_FOCUS         30

/* The highest skill number available for mudlib skills */
#define SS_MUDLIB_SKILL_END    4999

/*Define this if you want skills to be limited by stats*/
#define STAT_LIMITED_SKILLS

/*
 * Limits are defined using the limiting stat and limiting weight in the
 * mapping SS_SKILL_DESC
 */

/* List of skills as is going to be used */
#define SS_WEP_FIRST               0   /* The first weapon index */

#define SS_WEP_SWORD            SS_WEP_FIRST + 0  /* W_SWORD */
#define SS_WEP_POLEARM          SS_WEP_FIRST + 1  /* W_POLEARM */
#define SS_WEP_AXE              SS_WEP_FIRST + 2  /* W_AXE */
#define SS_WEP_KNIFE            SS_WEP_FIRST + 3  /* W_KNIFE */
#define SS_WEP_CLUB             SS_WEP_FIRST + 4  /* W_CLUB */
#define SS_WEP_MISSILE          SS_WEP_FIRST + 5  /* W_MISSILE */
#define SS_WEP_JAVELIN          SS_WEP_FIRST + 6  /* W_JAVELIN */

/*
 * SS_SKILL_DESC
 *
 * Description, Costfactor(0-100) Limiting Stat, Limit Weight, Max adv guild
 *
 * When adding/renaming skills, it has to be updated in SS_SKILL_LOOKUP below too.
 */

#define SS_SKILL_DESC ([ \
/* Weapon skills */                                                    \
    SS_WEP_SWORD:     ({ "sword",                 95, SS_DEX, 125, 30 }), \
    SS_WEP_POLEARM:   ({ "polearm",               80, SS_STR, 125, 30 }), \
    SS_WEP_AXE:       ({ "axe",                   70, SS_STR, 125, 30 }), \
    SS_WEP_KNIFE:     ({ "knife",                 46, SS_DEX, 125, 30 }), \
    SS_WEP_CLUB:      ({ "club",                  50, SS_STR, 125, 30 }), \
    SS_WEP_MISSILE:   ({ "missiles",              70, SS_DEX, 125, 30 }), \
    SS_WEP_JAVELIN:   ({ "javelin",               70, SS_STR, 125, 30 }), \
/* General fighting skills */                                           \
    SS_2H_COMBAT:     ({ "two handed combat",    100, SS_DEX, 110,  0 }), \
    SS_UNARM_COMBAT:  ({ "unarmed combat",        90, SS_STR, 110, 30 }), \
    SS_BLIND_COMBAT:  ({ "blindfighting",         95, SS_DEX, 110, 20 }), \
    SS_PARRY:         ({ "parry",                 80, SS_STR, 110,  0 }), \
    SS_DEFENCE:       ({ "defence",               80, SS_DEX, 110, 30 }), \
    SS_MOUNTED_COMBAT:({ "mounted combat",       100, SS_STR, 150,  0 }), \
    SS_BLOCK:         ({ "block",                100, SS_STR, 110, 30 }), \
/* Magic skills */                                                   \
    SS_SPELLCRAFT:    ({ "spellcraft",            70, SS_INT, 125, 20 }), \
    SS_HERBALISM:     ({ "herbalism",             70, SS_WIS, 125, 20 }), \
    SS_ALCHEMY:       ({ "alchemy",               70, SS_INT, 125, 20 }), \
\
    SS_FORM_TRANSMUTATION: ({ "transmutation",    90, SS_INT, 110,  0 }), \
    SS_FORM_ILLUSION:    ({ "illusion",           70, SS_INT, 110,  0 }), \
    SS_FORM_DIVINATION:  ({ "divination",         70, SS_INT, 110,  0 }), \
    SS_FORM_ENCHANTMENT: ({ "enchantment",        80, SS_INT, 110,  0 }), \
    SS_FORM_CONJURATION: ({ "conjuration",        80, SS_INT, 110,  0 }), \
    SS_FORM_ABJURATION:  ({ "abjuration",         70, SS_INT, 110,  0 }), \
    SS_ELEMENT_FIRE:     ({ "fire spells",        70, SS_WIS, 110, 20 }), \
    SS_ELEMENT_AIR:      ({ "air spells",         70, SS_WIS, 110, 20 }), \
    SS_ELEMENT_EARTH:    ({ "earth spells",       70, SS_WIS, 110, 20 }), \
    SS_ELEMENT_WATER:    ({ "water spells",       70, SS_WIS, 110, 20 }), \
    SS_ELEMENT_LIFE:     ({ "life spells",        80, SS_WIS, 110, 20 }), \
    SS_ELEMENT_DEATH:    ({ "death spells",       90, SS_WIS, 110, 20 }), \
/* Thief skills */                                                  \
    SS_OPEN_LOCK:     ({ "open lock",             70, SS_DEX, 110, 20 }), \
    SS_PICK_POCKET:   ({ "pick pocket",           70, SS_DEX, 110, 20 }), \
    SS_ACROBAT:       ({ "acrobat",               70, SS_DEX, 110, 20 }), \
    SS_FR_TRAP:       ({ "find/remove traps",     70, SS_DEX, 110, 20 }), \
    SS_SNEAK:         ({ "sneak",                 70, SS_DEX, 125, 20 }), \
    SS_HIDE:          ({ "hide",                  70, SS_DEX, 125, 20 }), \
    SS_BACKSTAB:      ({ "backstab",              70, SS_DEX, 110,  0 }), \
/* General skills */                                                  \
    SS_APPR_MON:      ({ "appraise enemy",        50, SS_WIS, 150, 30 }), \
    SS_APPR_OBJ:      ({ "appraise object",       50, SS_WIS, 150, 30 }), \
    SS_APPR_VAL:      ({ "appraise value",        50, SS_WIS, 150, 30 }), \
    SS_SWIM:          ({ "swim",                  50, SS_STR, 150, 30 }), \
    SS_CLIMB:         ({ "climb",                 50, SS_STR, 125, 30 }), \
    SS_ANI_HANDL:     ({ "animal handling",       50, SS_WIS, 125, 30 }), \
    SS_LOC_SENSE:     ({ "location sense",        50, SS_WIS, 110, 30 }), \
    SS_TRACKING:      ({ "tracking",              50, SS_WIS, 125, 30 }), \
    SS_HUNTING:       ({ "hunting",               50, SS_INT, 125, 30 }), \
    SS_LANGUAGE:      ({ "language",              50, SS_INT, 110, 30 }), \
    SS_AWARENESS:     ({ "awareness",             50, SS_WIS, 110, 30 }), \
    SS_TRADING:       ({ "trading",               50, SS_INT, 110, 30 }), \
    SS_RIDING:        ({ "riding",                75, SS_DEX, 125, 30 }), \
])

/*
 * Reverse lookup of skill number from the name. Used for GMCP.
 * When adding/renaming skills, it has to be updated here too.
 */
#define SS_SKILL_LOOKUP ([ "sword": SS_WEP_SWORD, "polearm": SS_WEP_POLEARM, "axe": SS_WEP_AXE, \
    "knife": SS_WEP_KNIFE, "club": SS_WEP_CLUB, "missiles": SS_WEP_MISSILE, "javelin": SS_WEP_JAVELIN, \
    "two handed combat": SS_2H_COMBAT, "unarmed combat": SS_UNARM_COMBAT, "blindfighting": SS_BLIND_COMBAT, \
    "parry": SS_PARRY, "defence": SS_DEFENCE, "mounted combat": SS_MOUNTED_COMBAT, "block": SS_BLOCK, \
    "spellcraft": SS_SPELLCRAFT, "herbalism": SS_HERBALISM, "alchemy": SS_ALCHEMY, \
    "transmutation": SS_FORM_TRANSMUTATION, "illusion": SS_FORM_ILLUSION, \
    "divination": SS_FORM_DIVINATION, "enchantment": SS_FORM_ENCHANTMENT, \
    "conjuration": SS_FORM_CONJURATION, "abjuration": SS_FORM_ABJURATION, \
    "fire spells": SS_ELEMENT_FIRE, "air spells": SS_ELEMENT_AIR, "earth spells": SS_ELEMENT_EARTH, \
    "water spells": SS_ELEMENT_WATER, "life spells": SS_ELEMENT_LIFE, "death spells": SS_ELEMENT_DEATH, \
    "open lock": SS_OPEN_LOCK, "pick pocket": SS_PICK_POCKET, "acrobat": SS_ACROBAT, \
    "find/remove traps": SS_FR_TRAP, "sneak": SS_SNEAK, "hide": SS_HIDE, "backstab": SS_BACKSTAB, \
    "appraise enemy": SS_APPR_MON, "appraise object": SS_APPR_OBJ, "appraise value": SS_APPR_VAL, \
    "swim": SS_SWIM, "climb": SS_CLIMB, "animal handling": SS_ANI_HANDL, "location sense": SS_LOC_SENSE, \
    "tracking": SS_TRACKING, "hunting": SS_HUNTING, "language": SS_LANGUAGE, "awareness": SS_AWARENESS, \
    "trading": SS_TRADING, "riding": SS_RIDING ])
