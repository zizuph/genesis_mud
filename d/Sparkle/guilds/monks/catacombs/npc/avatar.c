/*******************************************************************\
| AVATAR.C                                                          |
\*******************************************************************/

/*
 * 08/02/02 Arandir	Fixed for use with modified quest logging
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 *                      Removed the focus skill
 * 06/02/01 Arandir     Incorporated domain quest support
 * 04/08/18 Arandir     Disabled reaction to monsters
 * 04/08/14 Arandir     Made the possibility of death in fight obvious
 * 04/01/17 Arandir     Made the avatar copy weight and volume too
 * 03/09/09 Arandir     More meaningful messages on victory
 * 03/07/23 Arandir     Created
 *
 */

#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#include "../defs.h"
#include "../../monastery/defs.h"

#include S_DOMAIN_SYS_QUESTS

inherit M_NPC_MONK_BASE;

inherit S_LIB_PLAYER;
inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

object oOpponent    = NULL;
string sOpponent    = "";
string sOpponentCap = "";

int    iReaction = ALARM_NONE;


#define CC_TALK_DELAY           10.0 + itof (random (5))

//-------------------------------------------------------------------

void cc_ask_test ()
{
  if ((this_player () == oOpponent) &&
      (oOpponent != query_attack ()) &&
      (!m_is_guru (oOpponent)))
  {
    command ("emote challenges you: As your final test, defeat me " +
             "in a fight to death. Only that will prove that your " +
             "body is up to the task of following the Way.");
    command ("mk bow " + OB_NAME (oOpponent));
    command ("mk kill " + OB_NAME (oOpponent));
  }
  else command ("say And just how did you get here ?");
}


void cc_ask_mind ()
{
  if ((this_player () == oOpponent) &&
      (oOpponent != query_attack ()))
  {
    command ("emote raises " + XPOS (this_object ()) + " arm " +
             "in a soothing gesture.");
    command ("say It is your mind that gives your body the will to " +
             "manifest your self in a tangible way. That is why your " +
             "mind must act in unison with your body, lest you " +
             "forsake the Way forever.");

    if (!m_is_guru (oOpponent))
    {
      command ("smile approvingly");
      command ("asay seriously Unlike your body, your mind has already " +
               "been tested in this endeavour. By finding your way here, " +
               "you have demonstrated that your mind is up to the task " +
               "of following the Way.");
    }
  }
  else command ("say And just how did you get here ?");
}


void cc_ask_body ()
{
  if ((this_player () == oOpponent) &&
      (oOpponent != query_attack ()))
  {
    command ("emote raises " + XPOS (this_object ()) + " arm " +
             "in a warning gesture.");
    command ("say It is your body that gives your mind the power to " +
             "manifest your self in a tangible way. That is why your " +
             "body must act in unison with your mind, lest you " +
             "forsake the Way forever.");

    if (!m_is_guru (oOpponent))
    {
      command ("smile questioningly");
      command ("asay seriously Unlike your mind, your body has not " +
               "yet been tested in this endeavour. If you feel up " +
               "to it, ask me about the test.");
    }
  }
  else command ("say And just how did you get here ?");
}


void cc_ask_way ()
{
  if ((this_player () == oOpponent) &&
      (oOpponent != query_attack ()))
  {
    command ("emote opens " + XPOS (this_object ()) + " arms " +
             "in an encompassing gesture.");
    command ("asay thoughtfully It is in the unity of mind and body " +
             "that the Way of the Dragon is found.");
  }
  else command ("say And just how did you get here ?");
}

//-------------------------------------------------------------------

void cc_react_intro ()
{
  iReaction = ALARM_NONE;

  if ((present (oOpponent, environment ())) &&
      (oOpponent != query_attack ()))
  {
    // The change of name here is because otherwise the opponent
    // would consider us as met and would never see our short
    // description.

    command ("say It might seem as if we have never met before, but " +
             "the contrary is true. We have known each other all our " +
             "lives. For I am " + sOpponentCap + ", same as you are.");

    remove_name (query_names ());
    set_name (sOpponent);
    add_name ("avatar");

    command ("emote explains: I am whom you need to know to advance " +
             "in your search of the Way of the Dragon.");
  }
}


void cc_react_welcome ()
{
  iReaction = ALARM_NONE;

  if ((present (oOpponent, environment ())) &&
      (oOpponent != query_attack ()))
  {
    command ("emote studies you with a long stare.");
    command ("say Welcome, " + sOpponentCap + " !");

    if (m_is_monk (oOpponent))
    {
      if (m_is_guru (oOpponent))
      {
        // The change of name here is because otherwise the opponent
        // would consider us as met and would never see our short
        // description.

        remove_name (query_names ());
        set_name (sOpponent);
        add_name ("avatar");

        command ("mk bless " + OB_NAME (oOpponent));
        command ("say It is a pleasure to see you again.");
      }
      else
      {
        iReaction = set_alarm (CC_TALK_DELAY, 0.0, &cc_react_intro ());
      }
    }
  }
}

//-------------------------------------------------------------------

string cc_long ()
{
  return (
    "Assuming the form of " + LANG_ADDART (query_nonmet_name ()) +
    ", the avatar is everything you became, physically and mentally. " +
    "As a friend, the avatar is a unique mentor, for " +
    XPNOUN (this_object ()) + " carries your flaws for " +
    "you to learn from. As a foe, the avatar is a unique adversary, " +
    "for you have to win over yourself to win over " +
    XOBJ (this_object ()) + ". Few ever achieve the level " +
    "of mastery to do either, let alone both.\n");
}

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("avatar");
  set_gender (G_NEUTER);
  set_race_name ("being");
  set_adj ("formless");
  set_long (&cc_long ());

  m_init (100);
  m_equip (({ 0, 0 }));
  m_stature (180, 70);

  // Avatar has all skills maxed

  set_skill (SS_DEFENCE, 100);
  set_skill (SS_AWARENESS, 100);
  set_skill (SS_BLIND_COMBAT, 100);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (M_SKILL_STRIKE, 100);
  set_skill (M_SKILL_PLEXUS, 100);

  // Add the asks we react to

  add_ask (({ "way", "way of dragon", "way of the dragon",
              "path", "path of dragon", "path of the dragon",
              "unity", "advance", "search" }),
           VBFC_ME ("cc_ask_way"), ASK_COMMAND);

  add_ask (({ "mind" }), VBFC_ME ("cc_ask_mind"), ASK_COMMAND);
  add_ask (({ "body" }), VBFC_ME ("cc_ask_body"), ASK_COMMAND);
  add_ask (({ "test" }), VBFC_ME ("cc_ask_test"), ASK_COMMAND);
}

//-------------------------------------------------------------------

void init_living ()
{
  object oHim = this_player ();

  // Do not react to monsters and wizards, as well as already accepted opponents.

  if (interactive (oHim) && !dg_is_wizard (oHim) && (oHim != oOpponent))
  {
    oOpponent = oHim;
    sOpponent = dg_get_name (oOpponent);
    sOpponentCap = capitalize (sOpponent);

    // Let us assume the appearance of our visitor.

    // The change of name is done twice because otherwise the
    // opponent would consider us as met and would never see
    // our short description.

    remove_name (query_names ());
    set_name ("Avatar of " + sOpponentCap);
    add_name ("avatar");

    set_gender (oOpponent->query_gender ());
    set_race_name (oOpponent->query_race_name ());
    set_adj (oOpponent->query_adj (TRUE));

    set_stats (({ oOpponent->query_base_stat (SS_STR),
                  oOpponent->query_base_stat (SS_DEX),
                  oOpponent->query_base_stat (SS_CON),
                  oOpponent->query_base_stat (SS_INT),
                  oOpponent->query_base_stat (SS_WIS),
                  oOpponent->query_base_stat (SS_DIS) }));

    add_prop (CONT_I_HEIGHT, oOpponent->query_prop (CONT_I_HEIGHT));
    add_prop (CONT_I_WEIGHT, oOpponent->query_prop (CONT_I_WEIGHT));

    set_hp (query_max_hp ());
    set_mana (query_max_mana ());
    set_fatigue (query_max_fatigue ());

    s_log (M_LOG_WIZARD, sOpponentCap + " arrived at the avatar.");

    if (iReaction != ALARM_NONE) remove_alarm (iReaction);
    iReaction = set_alarm (CC_TALK_DELAY, 0.0, &cc_react_welcome ());
  }
}

//-------------------------------------------------------------------

void do_die (object oKiller)
{
  object oMe = this_object ();
  object oRoom = environment ();

  if ((oKiller == oOpponent) &&
      (m_is_monk (oKiller)))
  {
    tell_room (oRoom, QCTNAME (oMe) + " shouts: Enough !\n");

    stop_fight (oOpponent);
    oOpponent->stop_fight (oMe);

    oKiller->catch_tell (
      "Suddenly, a silvery glow envelops " + XTNAME (oKiller, oMe) + ", " +
      "who bows solemnly in a gesture conceding your victory,\n");
    tell_room (
      oRoom,
      "Suddenly, a silvery glow envelops " + QTNAME (oMe) + ".\n",
      oKiller);

    set_hp (query_max_hp ());

    if (m_is_guru (oKiller))
    {
      oKiller->catch_tell (
        "You hear a whisper in your mind: Congratulations. " +
        "Once again, you have demonstrated that you " +
        "possess the unity of mind and body vital to " +
        "following the Way of the Dragon.\n");
    }
    else
    {
      oKiller->catch_tell (
        "You hear a whisper in your mind: Congratulations. " +
        "You have demonstrated that you possess the unity " +
        "of mind and body vital to following the Way of " +
        "the Dragon.\n");

      oKiller->catch_tell (
        "The silvery glow extends from the avatar to envelop " +
        "you. In mute astonishment, you feel a rush of " +
        "enlightenment course through you.\n");
      tell_room (
        oRoom,
        "The silvery glow extends from the avatar to " +
        "envelop " + QTNAME (oKiller) + ".\n",
        oKiller);

      oKiller->set_hp (oKiller->query_max_hp ());

      QUEST_SET (oKiller, Q_MONK_GURU);
      QUEST_LOG (oKiller, "defeated the monk avatar.");
      oKiller->add_exp_quest (M_GURU_EXP);
      oKiller->catch_tell ("You feel more experienced.\n");

      s_log (M_LOG_WIZARD, sOpponentCap + " solved the guru quest.");
    }
  }
  else
  {
    ::do_die (oKiller);
  }
}

//-------------------------------------------------------------------

