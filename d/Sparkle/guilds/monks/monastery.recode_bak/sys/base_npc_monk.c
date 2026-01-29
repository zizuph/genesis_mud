/*******************************************************************\
| BASE_NPC_MONK.C                                                   |
+-------------------------------------------------------------------+
| Base non player character module for the monk guild.              |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Removed the focus skill
 *                      Added notifications for non player characters
 * 03/09/16 Arandir     Fixed path for saving state
 * 03/09/06 Arandir     Simplified saving and restoring state
 * 02/02/08 Arandir	Improved the asks listing
 * 02/01/25 Arandir	Ported to the new area
 * 98/05/26 Cirion	Created
 *
 */

#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>

#include "../defs.h"

inherit M_NPC_BASE;

inherit "/d/Genesis/lib/intro";

inherit DG_OBJ_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

// These are used to remember asks that are to be answered

private string  *asAsksHardCoded = ({ });
private mixed   maAsksEntered = ({ });

#define M_ASKS_QUESTIONS	0
#define M_ASKS_ANSWER		1

#define M_ASKS_MAX		100

//-------------------------------------------------------------------

void m_refresh_asks ();
void m_save_object ();
void m_restore_object ();

void m_init (int iLevel);
void m_equip (int *aiMoney, string *asEquipment);
void m_stature (int iHeight, int iWeight);

//-------------------------------------------------------------------

/*******************************************************************\
| Support for instructing monsters.                                 |
\*******************************************************************/

/*******************************************************************\
| Basics                                                            |
\*******************************************************************/

/*
 * Function name : m_can_instruct
 * Description   : Decides who can instruct a monster.
 *
 */

int m_can_instruct (object oWho)
{
  return (m_is_council_member (oWho) | m_is_authorized_wizard (oWho));
}

/*
 * Function name : m_find_ask_all
 * Function name : m_find_ask_any
 * Description   : Locates an ask in the array of asks.
 *
 */

mixed m_find_ask_all (string *asQuestions)
{
  string sQuestion;
  int    iAsk;

  sQuestion = implode (asQuestions, ";");
  for (iAsk = 0 ; iAsk < sizeof (maAsksEntered) ; iAsk ++)
    if (sQuestion == implode (maAsksEntered [iAsk][M_ASKS_QUESTIONS], ";"))
      return (maAsksEntered [iAsk]);

  return (FALSE);
}


mixed m_find_ask_any (string *asQuestions)
{
  int iAsk, iQuestion;

  for (iAsk = 0 ; iAsk < sizeof (maAsksEntered) ; iAsk ++)
    for (iQuestion = 0 ; iQuestion < sizeof (asQuestions) ; iQuestion ++)
      if (member_array (asQuestions [iQuestion], maAsksEntered [iAsk][M_ASKS_QUESTIONS]) >= 0)
        return (maAsksEntered [iAsk]);

  return (FALSE);
}


/*
 * Function name : m_action_instruct
 * Description   : A command that council members can use to instruct
 *                 the monster to respond to specific questions.
 *
 */

int m_action_instruct (string sWhat)
{
  string *asQuestions;
  string sQuestion;
  string sAnswer;
  mixed  mRecord;
  int    iQuestion;
  int    iAsk;

  if (!m_can_instruct (this_player ())) return (FALSE);

  notify_fail ("If you want to instruct this monk to answer " +
               "specific questions with a certain answer, do " +
               "'instruct answer <question> with <response>'. " +
               "If you want to delete a question, do 'instruct " +
               "forget <question>'. If you want to list questions " +
               "currently answered, do 'instruct list' or 'instruct " +
               "brief'. Multiple words of a question can be separated " +
               "by semicolons.\n");

  if (!strlen (sWhat))
  {
    return (FALSE);
  }

  // instruct answer <question[;question...]> with <response>

  else if (parse_command (sWhat, ({ }), "'answer' %s 'with' %s", sQuestion, sAnswer))
  {
    if (sizeof (maAsksEntered) < M_ASKS_MAX)
    {
      asQuestions = explode (sQuestion, ";");
      mRecord = m_find_ask_any (asQuestions);
      if (mRecord)
      {
        command ("ask " + OB_NAME (this_player ()) + " Sorry, but I will not answer the question '" + sQuestion + "'.");
        command ("ask " + OB_NAME (this_player ()) + " This question collides with the question '" + implode (mRecord [M_ASKS_QUESTIONS], ";") + "'.");
        command ("shrug helplessly");
        return (TRUE);
      };

      maAsksEntered += ({ ({ asQuestions, sAnswer }) });
      m_refresh_asks ();
      m_save_object ();
      command ("ask " + OB_NAME (this_player ()) + " I will answer the question '" + sQuestion + "' with '" + sAnswer + "'.");
    }
    else
    {
      command ("ask " + OB_NAME (this_player ()) + " Sorry, but I will not answer the question '" + sQuestion + "'.");
      command ("ask " + OB_NAME (this_player ()) + " This question would exceed the limit of " + M_ASKS_MAX + " questions.");
      command ("shrug helplessly");
    };

    return (TRUE);
  }

  // instruct forget <question[;question...]>

  else if (parse_command (sWhat, ({ }), "'forget' %s", sQuestion))
  {
    asQuestions = explode (sQuestion, ";");
    mRecord = m_find_ask_all (asQuestions);

    if (mRecord)
    {
      maAsksEntered -= ({ mRecord });
      m_refresh_asks ();
      m_save_object ();
      command ("ask " + OB_NAME (this_player ()) + " I will no longer answer the question '" + sQuestion + "'.");
    }
    else
    {
      command ("ask " + OB_NAME (this_player ()) + " Sorry, but I do not answer the question '" + sQuestion + "'.");
      command ("shrug helplessly");
    };

    return (TRUE);
  }

  // instruct brief

  else if (parse_command (sWhat, ({ }), "'brief'"))
  {
    if (sizeof (maAsksEntered))
    {
      string *asQuestions = ({ });
      for (iAsk = 0 ; iAsk < sizeof (maAsksEntered) ; iAsk ++)
      {
        asQuestions += ({ "'" + implode (maAsksEntered [iAsk][M_ASKS_QUESTIONS], ";") + "'" });
      };
      command ("ask " + OB_NAME (this_player ()) + " I answer the " + (sizeof (asQuestions) == 1 ? "question " : "questions ") + COMPOSITE_WORDS (asQuestions) + ".");
    }
    else
    {
      command ("ask " + OB_NAME (this_player ()) + " I do not answer any questions.");
    };

    return (TRUE);
  }

  // instruct list

  else if (parse_command (sWhat, ({ }), "'list'"))
  {
    if (sizeof (maAsksEntered))
    {
      for (iAsk = 0 ; iAsk < sizeof (maAsksEntered) ; iAsk ++)
      {
        command ("ask " + OB_NAME (this_player ()) + " I answer the question '" + implode (maAsksEntered [iAsk][M_ASKS_QUESTIONS], ";") + "' with '" + maAsksEntered [iAsk][M_ASKS_ANSWER] + "'.");
      };
    }
    else
    {
      command ("ask " + OB_NAME (this_player ()) + " I do not answer any questions.");
    };

    return (TRUE);
  };

  return (FALSE);
}

/*******************************************************************\
| Hooks                                                             |
\*******************************************************************/

/*
 * Function name : long
 * Description   : Adds an information about the possibility to
 *                 instruct a monster to its long description.
 *
 */

varargs string long (mixed xAsker)
{
  object oAsker = objectp (xAsker) ? xAsker : this_player ();

  if (m_can_instruct (oAsker))
  {
    return (::long (oAsker) +
            "You may 'instruct' this monk to " +
            "respond to specific questions.\n");
  };

  return (::long (oAsker));
}


/*
 * Function name : add_ask
 * Description   : Keeps track of asks added through code.
 *
 */

varargs int add_ask (mixed mQuestions, string sAnswer, int iCommand = 0)
{
  // We remember asks added through code. When refreshing the ask
  // list of the monster, this list is checked so that the asks
  // added through code are not overridden.

  if (stringp (mQuestions))
  {
    asAsksHardCoded += ({ mQuestions });
  }
  else if (pointerp (mQuestions))
  {
    asAsksHardCoded += mQuestions;
  };

  return (::add_ask (mQuestions, sAnswer, iCommand));
}


/*
 * Function name : m_refresh_asks
 * Description   : Rebuilds the monster ask list.
 *
 */

void m_refresh_asks ()
{
  mixed mAsks;
  int   iAsk;
  int   iQuestion;

  // First, empty the ask list of the monster of all asks
  // except those added through code. These we want to keep.

  mAsks = query_ask ();

  for (iAsk = 0 ; iAsk < sizeof (mAsks) ; iAsk ++)
  {
    for (iQuestion = 0 ; iQuestion < sizeof (mAsks [iAsk][0]) ; iQuestion ++)
    {
      if (member_array (mAsks [iAsk][0][iQuestion], asAsksHardCoded) < 0)
      {
        remove_ask (mAsks [iAsk][0][iQuestion]);
      };
    };
  };

  // Now, repopulate the ask list of the monster again.

  for (iAsk = 0 ; iAsk < sizeof (maAsksEntered) ; iAsk ++)
  {
    ::add_ask (maAsksEntered [iAsk][M_ASKS_QUESTIONS], "say " + maAsksEntered [iAsk][M_ASKS_ANSWER], TRUE);
  };
}

//-------------------------------------------------------------------

/*******************************************************************\
| Support for talking                                               |
\*******************************************************************/

/*
 * Function name : m_say
 * Description   : Says something, later on maybe using monk language
 *   sText         : What to say
 *   iDelay        : How long before saying it
 *
 */

varargs void m_say (string sText, int iDelay = 0)
{
  if (iDelay) set_alarm (itof (iDelay), 0.0, &command ("say " + sText));
         else command ("say " + sText);
}

//-------------------------------------------------------------------

/*
 * Function name : introduce
 * Description   : What we do when somebody introduces themselves.
 *
 */

void introduce (object oWho)
{
  set_alarm (1.0, 0.0, &command ("introduce myself to " + OB_NAME (oWho)));

  set_alarm (2.0, 0.0, &command ((this_object ()->query_gender () == G_FEMALE) ?
    one_of_list (({ "nod warmly", "smile softly", "curtsey gracefully" })) :
    one_of_list (({ "nod sagely", "smile seriously", "bow politely" }))));
}

//-------------------------------------------------------------------

/*
 * Function name : m_init
 * Description   : Initializes the monster to be a proper monk.
 *   iLevel        : Level from 0 to 100 roughly determines size.
 *
 */

#define M_STAT_MIN	70
#define M_STAT_MAX	200
#define M_SKILL_MIN	10
#define M_SKILL_MAX	100

#define M_HEIGHT_MIN	150
#define M_HEIGHT_MAX	200
#define M_WEIGHT_MIN	50
#define M_WEIGHT_MAX	100

#define M_RAND_RANGE(iMin,iMax)		(random (iMax-iMin) + iMin)
#define M_RAND_LEVEL(iMin,iMax,iLvl)	((random (iMax-iMin) / 10) + iMin + iLevel)

void m_init (int iLevel = 60)
{
  object oShadow;

  add_name ("monk");

  set_stats (({ M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel),
                M_RAND_LEVEL (M_STAT_MIN, M_STAT_MAX, iLevel) }));

  set_skill (SS_UNARM_COMBAT, M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_BLIND_COMBAT, M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_DEFENCE,      M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (M_SKILL_STRIKE,  M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (M_SKILL_PLEXUS,  M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_AWARENESS,    M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_LANGUAGE,     M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_SWIM,         M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_CLIMB,        M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_LOC_SENSE,    M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));
  set_skill (SS_HERBALISM,    M_RAND_LEVEL (M_SKILL_MIN, M_SKILL_MAX, iLevel));

  m_stature (M_RAND_RANGE (M_HEIGHT_MIN, M_HEIGHT_MAX),
             M_RAND_RANGE (M_WEIGHT_MIN, M_WEIGHT_MAX));

  add_prop (NPC_I_NO_LOOKS, TRUE);

  oShadow = clone_object (M_SHADOW_OCC);
  oShadow->shadow_me (this_object (), M_TYPE_OCC, M_STYLE_OCC, M_NAME_LONG);
}


/*
 * Function name : m_equip
 * Description   : Equips the monster to be a proper monk.
 *   aiMoney       : The amount of money to give the monster.
 *   asEquipment   : The additional items to give the monster.
 *
 */

void m_equip (
  int *aiMoney = ({ }),
  string *asEquipment = ({ }))
{
  object oCoins;
  object oItem;
  int    iCoins;
  int    iItem;

  // Give the monster the necessary amount of money.

  if (sizeof (aiMoney) > sizeof (MONEY_TYPES)) throw ("m_equip: Input array of coins too long.");

  for (iCoins = 0 ; iCoins < sizeof (aiMoney) ; iCoins ++)
  {
    if (aiMoney [iCoins] > 0)
    {
      oCoins = MONEY_MAKE (aiMoney [iCoins], MONEY_TYPES [iCoins]);
      oCoins->move (this_object (), 1);
    };
  };

  // Clone the specified equipment for the monster.

  DG_FIXUID;

  for (iItem = 0 ; iItem < sizeof (asEquipment) ; iItem ++)
  {
    oItem = clone_object (asEquipment [iItem]);
    oItem->move (this_object (), 1);
  };

  // Add default equipment that all monks have.

  clone_object (M_PATH_OBJ + "/belt")->move (this_object (), MOVE_SUBLOC_ALWAYS);
  clone_object (M_PATH_OBJ + "/robe")->move (this_object (), MOVE_SUBLOC_ALWAYS);
  clone_object (M_PATH_OBJ + "/pants")->move (this_object (), MOVE_SUBLOC_ALWAYS);
  clone_object (M_PATH_OBJ + "/shirt")->move (this_object (), MOVE_SUBLOC_ALWAYS);
  clone_object (M_PATH_OBJ + "/sandals")->move (this_object (), MOVE_SUBLOC_ALWAYS);

  // Guess what :-) ...

  command ("wear all");
  command ("wield all");
}


/*
 * Function name : m_stature
 * Description   : Sets the stature of a monster.
 *
 */

void m_stature (int iHeight, int iWeight)
{
  add_prop (CONT_I_HEIGHT, iHeight);
  add_prop (CONT_I_WEIGHT, iWeight * 1000);
}

//-------------------------------------------------------------------

/*
 * Function name : m_filename
 * Function name : m_save_object
 * Function name : m_restore_object
 * Description   : Functions to save and restore the object.
 *
 */

string m_filename ()
{
  return (M_PATH_VAR_NPC + "/" + dg_base_name ());
}

void m_save_object ()
{
  DG_FIXUID;
  save_object (m_filename ());
}

void m_restore_object ()
{
  DG_FIXUID;
  restore_object (m_filename ());
}

//-------------------------------------------------------------------

/*
 * Function name : special_attack
 * Description   : Called during combat to issue special attacks.
 *
 */

int special_attack (object oTarget)
{
  // We always try for a special attack. We also always return
  // a value of 0, indicating that normal attacks should
  // proceed even when the specials are being fired off.

  command ("mk plexus");
  command ("mk strike");

  return (0);
}


void m_notify_plexus_landed ()
{
  command ("mk plexus");
}


void m_notify_strike_landed ()
{
  command ("mk strike");
}

//-------------------------------------------------------------------

/*
 * Function name : create_monster
 *
 */

void create_monster ()
{
  ::create_monster();

  m_restore_object ();
  m_refresh_asks ();
}


/*
 * Function name : init_living
 *
 */

void init_living ()
{
  ::init_living ();

  add_action (m_action_instruct, "instruct");
}

//-------------------------------------------------------------------

