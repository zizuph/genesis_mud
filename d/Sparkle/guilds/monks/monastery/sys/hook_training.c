/*******************************************************************\
| HOOK_TRAINING.C                                                   |
\*******************************************************************/

/*
 * 98/06/28 Cirion	Created
 * 03/04/29 Arandir	Ported to new area and bugfixed
 * 03/08/05 Arandir     Fixed a redundant error message on improve
 * 03/12/11 Arandir     Added the punishment support
 *
 */

#include <money.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>

#include "../defs.h"
#include "hook_training.h"

inherit "/std/object";

inherit "/lib/skill_raise";
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

private object oTrainerObject;
private int    iTrainerCheck = 0;

private int     iSkillType;
private mapping mSkillMap = M_SKILL_MAP;

//-------------------------------------------------------------------

void create_object ()
{
  ::create_object ();

  set_name ("skill trainer");
  set_short ("monk skill trainer");
  set_no_show ();

  create_skill_raise ();
}


void init ()
{
  ::init ();

  // Only add skills when a monk of the correct guild type enters.

  if (m_is_monk (this_player (), iSkillType))
  {
    init_skill_raise ();
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_training_setup
 * Description   : This function will add the skills to the
 *                 training object based on the guild type
 *                 passed in. The skills to be added are
 *                 in a list of trainable_skills.
 *
 */

void m_training_setup (int iGuildType, int *aiSkills, object oTrainer)
{
  mixed xSkillData;
  int iGuildIndex;
  int iSkillIndex;

  iSkillType = iGuildType;

  switch (iGuildType)
  {
    case SS_OCCUP:  iGuildIndex = M_SKILLS_OCCUP;
                    break;
    case SS_LAYMAN: iGuildIndex = M_SKILLS_LAYMAN;
                    break;
    default:        throw ("m_training_setup: Invalid guild type.\n");
  }

  // Add the ability to train skills as per the configuration.

  for (iSkillIndex = 0 ; iSkillIndex < sizeof (aiSkills) ; iSkillIndex ++)
  {
    xSkillData = mSkillMap [aiSkills [iSkillIndex]] [iGuildIndex];
    if (pointerp (xSkillData))
    {
      if (xSkillData [M_SKILLS_MAXIMUM] > 0)
      {
        sk_add_train (aiSkills [iSkillIndex],
                      xSkillData [M_SKILLS_DESC],
                      xSkillData [M_SKILLS_NAME],
                      xSkillData [M_SKILLS_COST],
                      xSkillData [M_SKILLS_MAXIMUM],
                      xSkillData [M_SKILLS_STAT_LIMIT],
                      xSkillData [M_SKILLS_STAT_WEIGHT]);
      }
    }
  }

  // Remember whether we need the trainer object present.

  oTrainerObject = oTrainer;
  iTrainerCheck = objectp (oTrainer);
}

//-------------------------------------------------------------------

/*
 * Function name : sk_improve
 * Description   : Called when player tries to do the improve command
 *
 */

int sk_improve (string sArgs)
{
  if ((iTrainerCheck) &&
      (present (oTrainerObject, environment ())))
  {
    return (::sk_improve (sArgs));
  }
  return (FALSE);
}


/*
 * Function name : sk_do_train
 * Description   : Let a player train a skill certain number of levels
 *
 */

int sk_do_train (int iSkill, object oWho, int iLevel)
{
  // Guru level can only be trained with guru quest

  if (iLevel <= 90)
  {
    return (::sk_do_train (iSkill, oWho, iLevel));
  }
  else
  {
    if (iSkill == SS_ACROBAT)
    {
      if (m_is_acrobat_guru(oWho))
      {
        return (::sk_do_train (iSkill, oWho, iLevel)); 
      }
    }
    else
    {
      if (m_is_guru(oWho))
      {
        return (::sk_do_train (iSkill, oWho, iLevel));
      }
    }
  }
  return (FALSE);
}


/*
 * Function name : sk_hook_allow_train
 * Description   : Punished player cannot train
 *
 */

int sk_hook_allow_train (object oWho, string sSkill, string sVerb)
{
  return (!m_is_punished (oWho, M_PUNISH_NOTRAIN));
}


/*
 * Function name : sk_hook_cant_train
 * Description   : Player cannot train for some reason
 *
 */

int sk_hook_cant_train (string sSkill, int iLevel)
{
  object oMe = this_player ();

  // If the desired level was guru, the likely reason
  // is that the player did not pass the guru quest.
  // Otherwise, it might be the limiting stat.

  if (iLevel < 90)
  {
    if (objectp (oTrainerObject))
    {
      oTrainerObject->command ("grumble disappointedly");
      notify_fail ("You fail to absorb what " +
                   XTNAME (oMe, oTrainerObject) +
                   " tries to teach you.\n");
    }
    else
    {
      notify_fail ("You fail to absorb the teaching.\n");
    }
  }
  else
  {
    notify_fail ("You are not yet ready for that level of mastery.\n");
  }

  return (FALSE);
}

//-------------------------------------------------------------------

/*
 * Function name : sk_fix_cost
 * Description   : Describe the cost of training of a single skill.
 *                 When the trainer is present, this function
 *                 always commands him to utter the cost
 *                 rather than returning the string.
 *   iSkill        : The skill to describe
 *   iSteps        : The number of steps to proceed
 * Returns       : The description string
 */

string sk_fix_cost (int iSkill, int iSteps)
{
  object oMe = this_player ();

  int iLevelThis, iLevelNext, iLevelMax;
  string sRankNext, sRankMax;
  string sSkill;
  string sDesc;
  int    iCost;

  iLevelThis = oMe->query_base_skill (iSkill);
  iLevelNext = iSteps ? (iLevelThis + iSteps) : (iLevelThis + 1);
  iLevelMax = sk_query_max (iSkill);

  sRankNext = LANG_ADDART (sk_rank (iLevelNext));
  sRankMax = LANG_ADDART (sk_rank (iLevelMax));

  sSkill = capitalize (sk_query_name (iSkill));

  if (iLevelNext > iLevelMax)
  {
    sDesc = sSkill + " to the level of " +
            sRankMax + ", which you " +
            "have already reached.";
  }
  else
  {
    iCost = sk_cost (iSkill, iLevelThis, iLevelNext);
    sDesc = sSkill + " for " + LANG_WNUM (iCost) + " copper " +
            DG_AMOUNT_SWITCH (iCost, "coin", "coins") + ", " +
            "which would make you " + sRankNext + " in " +
            "the study, with the maximum possible rank " +
            "of " + sRankMax + ".";
  }

  if ((iTrainerCheck) &&
      (present (oTrainerObject, environment ())))
  {
    oTrainerObject->command ("say " + sDesc);
    return ("");
  }
  else return (sDesc + "\n");
}


/*
 * Function name : sk_hook_write_header
 * Description   : Write the header to the improve or learn list
 *   iSteps        : How many steps to improve
 *
 */

void sk_hook_write_header (int iSteps)
{
  string sDesc;

  sDesc = "These are the skills you are able to " +
          query_verb () + " " + LANG_WNUM (iSteps) + " " +
          ((iSteps == 1) ? "step " : "steps ") + "here:";

  if ((iTrainerCheck) &&
      (present (oTrainerObject, environment ())))
  {
    oTrainerObject->command ("asay politely " + sDesc);
  }
  else
  {
    write (sDesc + "\n");
  }
}


/*
 * Function name : sk_hook_skillisting
 * Description   : Write the header to the skill list
 *
 */

void sk_hook_skillisting ()
{
  string sDesc;

  sDesc = "These are the skills taught here:";

  if ((iTrainerCheck) &&
      (present (oTrainerObject, environment ())))
  {
    oTrainerObject->command ("asay politely " + sDesc);
  }
  else
  {
    write (sDesc + "\n");
  }
}

//-------------------------------------------------------------------

