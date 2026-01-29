/*
 * /d/Shire/skills.h
 * 
 * To ensure no conflicts in skills used in Shire,
 * a file like this is to be included and updated
 * by the wizards, whenever they make a new skill.
 * Please follow a system, so that it is easy to
 * figure out which skills belong where.
 *
 * Sir Rogon.
 *
 * For the Shire, we can use skill numbers from
 * 112000 - 112999.
 *
 */

#ifndef _SHIRE_SKILLS_H
#define _SHIRE_SKILLS_H


/*
 * Skills for orcs and orc captain in the Mines of Moria.
 * I will use skill numbers 112500-599. The implementation
 * of these skills are in /d/Shire/moria/skills/
 */

#define SS_DIS_FOE_ARMED   112501
#define SS_DIS_FOE_UNARMED 112502
#define SS_PUNCH           112503
#define SS_BASH            112504
#define SS_EVAL_WEP        112505
#define SS_EVAL_ARM        112506
#define SS_WEP_WHIP        112507

/* Skill 112508 has been absurbed by the Noldor in
 * their fight against the nameless one...Actually
 * It is because that is what I was told to use.
 * /Gil-galad
 */
#define SS_ART_ENHANCE		112508

/*
 * Skills for use with mortals in the new parts
 * of Moria being expanded. Reserving 112510 to
 * 112519.
 * 
 * While this file is not used actively, I am
 * making a note here so people know which
 * skills are being used.
 *
 * Varian, May 2020
 */

#define SS_MORIA_LORE		112510

/* The Tricksters will require the following skills
 * SS_SET_TRAPS, SS_DISGUISE to accomplish
 * what I want them to be.
 * Igneous, 09/02/96
 * SS_SHINKICK I want in case i make a combat special
 * Igneous, 11/18/96
 */

#define SS_SET_TRAPS         112000
#define SS_DISGUISE          112001
#define SS_SHINKICK          112002

/* The Smiths Guild and Artificiers will require
 * these skills. More may come so skill number
 * 112100 to 112010 should not be used for other
 * purposes.
 * Morinir, 2/13/96
 */

#define SS_FORGING       112100
#define SS_FORGE_XP      112101
#define SM_MASTER        112102
#define SELECTED_WEAPON  112103
#define SS_STRIKE        112104
#define SS_MENDING_ARMOURS 112105
#define SS_MENDING_WEAPONS 112106

/* Angmar's Army has the skill numbers 112200 -> 112210
 * reserved for the guild.
 * Igneous, Jan 98
 */
#define SS_SMASH_AA    112200
#define SS_SHIELD_AA   112201
#define SS_BASH_AA     112202
#define SS_RETREAT_AA  112203

/* Counter for Horse Rustlers Club
 * Finwe, Dec 2004
 */

#define RUSTLED_TOTAL   112250

#endif
