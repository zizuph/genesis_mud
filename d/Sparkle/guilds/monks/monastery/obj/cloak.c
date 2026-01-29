/*******************************************************************\
| CLOAK.C                                                           |
\*******************************************************************/

/*
 * 08/01/29 Arandir     More robust when querying incomplete character
 * 06/09/06 Arandir     Added setting up of combat experiments
 *                      Made sure recovery is turned off
 * 06/02/09 Arandir     Made autowearable
 * 05/10/16 Arandir     Made autoloadable
 * 05/05/10 Arandir     Extended output of mfinger
 * 05/05/09 Arandir     Removed decay
 * 05/05/08 Arandir     Created off monk robe
 *
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/armour";

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

int m_action_finger (string sArgs)
{
  string sWho;
  object oWho;

  string sGuildOcc, sTitleOcc;
  string sGuildLay, sTitleLay;
  string sGuildRace, sTitleRace;

  mixed *amCharacter;
  int   *aiNormalized;
  int   iRank;

  // Some help for forgetful wizzies :-)

  notify_fail ("Syntax: " + query_verb () + " <player>\n");

  if (!strlen (sArgs)) return (FALSE);
  sWho = dg_remove_whitespace (sArgs);

  oWho = find_player (sWho);
  if (!objectp (oWho)) return (FALSE);

  // Headers and general information

  write (dg_repeated_string ("=", 3) +
         "[ " + capitalize (sWho) + " ]" +
         dg_repeated_string ("=", DG_LINELEN - strlen (sWho) - 8) + "\n");

  sGuildOcc = oWho->query_guild_name_occ ();
  if (strlen (sGuildOcc))
  {
    write (". Occ " +
           oWho->query_guild_tax_occ () + "% " +
           oWho->query_guild_style_occ () + ": " +
           dg_capitalize_words (sGuildOcc) + "\n");
    sTitleOcc = oWho->query_guild_title_occ ();
    if (strlen (sTitleOcc))
    {
      write ("  " + sTitleOcc + "\n");
    }
  }

  sGuildLay = oWho->query_guild_name_lay ();
  if (strlen (sGuildLay))
  {
    write (". Lay " +
           oWho->query_guild_tax_lay () + "% " +
           oWho->query_guild_style_lay () + ": " +
           dg_capitalize_words (sGuildLay) + "\n");
    sTitleLay = oWho->query_guild_title_lay ();
    if (strlen (sTitleLay))
    {
      write ("  " + sTitleLay + "\n");
    }
  }

  sGuildRace = oWho->query_guild_name_race ();
  if (strlen (sGuildRace))
  {
    write (". Race " +
           oWho->query_guild_tax_race () + "% " +
           oWho->query_guild_style_race () + ": " +
           dg_capitalize_words (sGuildRace) + "\n");
    sTitleRace = oWho->query_guild_title_race ();
    if (strlen (sTitleRace))
    {
      write ("  " + sTitleRace + "\n");
    }
  }

  // Monk guild specific information

  if (m_is_monk (oWho))
  {
    write (dg_repeated_string ("-", 3) +
           "[ Monk Guild ]" +
           dg_repeated_string ("-", DG_LINELEN - 18) + "\n");

    iRank = m_get_normalized_rank (oWho);

    write (". ");
    if (m_is_monk (oWho, SS_OCCUP)) write ("Occupational member");
    if (m_is_monk (oWho, SS_LAYMAN)) write ("Layman member");
    if (m_is_council_member (oWho)) write (", councillor");
    if (m_is_elder_member (oWho)) write (", elder");
    write (", rank " + iRank + "\n");

    write (dg_repeated_string ("-", DG_LINELEN - 1) + "\n");

    amCharacter = M_SHADOW_SRVR->m_get_character (oWho);
    aiNormalized = m_get_normalized_character (oWho);

    if (pointerp (amCharacter) && pointerp (aiNormalized))
    {
      write (sprintf (". Traits %7i PER %7i HON %7i EFF %7i RES %7i PAX\n",
                      aiNormalized [M_TRAIT_PERFECTION],
                      aiNormalized [M_TRAIT_HONESTY],
                      aiNormalized [M_TRAIT_EFFORT],
                      aiNormalized [M_TRAIT_RESPECT],
                      aiNormalized [M_TRAIT_PEACEFULNESS]));
      write (sprintf (". Events   %5i-%-5i %5i-%-5i %5i-%-5i %5i-%-5i %5i-%-5i\n",
                      amCharacter [M_CHARACTER_POSITIVE][M_TRAIT_PERFECTION], amCharacter [M_CHARACTER_NEGATIVE][M_TRAIT_PERFECTION],
                      amCharacter [M_CHARACTER_POSITIVE][M_TRAIT_HONESTY], amCharacter [M_CHARACTER_NEGATIVE][M_TRAIT_HONESTY],
                      amCharacter [M_CHARACTER_POSITIVE][M_TRAIT_EFFORT], amCharacter [M_CHARACTER_NEGATIVE][M_TRAIT_EFFORT],
                      amCharacter [M_CHARACTER_POSITIVE][M_TRAIT_RESPECT], amCharacter [M_CHARACTER_NEGATIVE][M_TRAIT_RESPECT],
                      amCharacter [M_CHARACTER_POSITIVE][M_TRAIT_PEACEFULNESS], amCharacter [M_CHARACTER_NEGATIVE][M_TRAIT_PEACEFULNESS]));
    }
  }

  // Footer

  write (dg_repeated_string ("-", DG_LINELEN - 1) + "\n");

  return (TRUE);
}

//-------------------------------------------------------------------

#define M_SCENARIO_ARMED        BIT(0)
#define M_SCENARIO_PLEXUS       BIT(1)
#define M_SCENARIO_STRIKE       BIT(2)

int m_action_tester (string sArgs)
{
  string *asScenarios;
  string sScenarios;
  int    iFlags;
  int    iMonkStats;
  int    iAlienStats;

  object oItem;

  object oMonk;
  object oAlien;

  // Some help for forgetful wizzies :-)

  notify_fail ("Syntax: " + query_verb () + " <scenario>, <monk stats>, <alien stats>\n" +
               "  <scenario>         - the combat scenario flags to use\n" +
               "    armed                arm the alien\n" +
               "    plexus               have the monk use plexus\n" +
               "    strike               have the monk use strike\n" +
               "  <monk stats>       - the statavg of the monk\n" +
               "  <alien stats>      - the statavg of the alien\n");

  if (stringp (sArgs))
  {
    if (sscanf (sArgs, "%s,%i,%i", sScenarios, iMonkStats, iAlienStats) != 3)
    {
      return (FALSE);
    }
  }
  else return (FALSE);

  asScenarios = explode (sScenarios, " ");
  iFlags = 0;
  foreach (string sScenario : asScenarios)
  {
    switch (sScenario)
    {
      case "armed":   iFlags |= M_SCENARIO_ARMED; break;
      case "plexus":  iFlags |= M_SCENARIO_PLEXUS; break;
      case "strike":  iFlags |= M_SCENARIO_STRIKE; break;
      case "":        break;
      default:        return (FALSE);
    }
  }

  // We will be cloning ...

  DG_FIXUID;

  // Create and equip the monk ...

  oMonk = clone_object (M_PATH_NPC + "/tester");
  oMonk->move (environment (environment ()), MOVE_SUBLOC_ALWAYS);
  oMonk->set_stats (({ iMonkStats, iMonkStats, iMonkStats,
                       iMonkStats, iMonkStats, iMonkStats,
                       iMonkStats, iMonkStats, iMonkStats }));

  oItem = clone_object (M_PATH_OBJ + "/tester-armour");
  oItem->move (oMonk, MOVE_SUBLOC_ALWAYS);
  oMonk->command ("wear all");

  if (iFlags & M_SCENARIO_PLEXUS) oMonk->catch_question ("plexus");
  if (iFlags & M_SCENARIO_STRIKE) oMonk->catch_question ("strike");

  // Create and equip the alien ...

  oAlien = clone_object (M_PATH_NPC + "/tester");
  oAlien->move (environment (environment ()), MOVE_SUBLOC_ALWAYS);
  oAlien->set_stats (({ iAlienStats, iAlienStats, iAlienStats,
                        iAlienStats, iAlienStats, iAlienStats,
                        iAlienStats, iAlienStats, iAlienStats }));

  oItem = clone_object (M_PATH_OBJ + "/tester-armour");
  oItem->move (oAlien, MOVE_SUBLOC_ALWAYS);
  oAlien->command ("wear all");

  if (iFlags & M_SCENARIO_ARMED)
  {
    oItem = clone_object (M_PATH_OBJ + "/tester-weapon");
    oItem->move (oAlien, MOVE_SUBLOC_ALWAYS);
    oAlien->command ("wield all");
    oMonk->m_acquire_weapon (oAlien);
  }

  // Fire away !

  oMonk->command ("kill " + OB_NAME (oAlien));

  return (TRUE);
}

//-------------------------------------------------------------------

void create_armour ()
{
  ::create_armour ();

  set_name (({ "robe", "cloak" }));
  set_adj (({ "rough", "light", "silvery", "grey" }));

  set_short ("silvery grey robe");
  set_long  ("A silvery grey robe made of rough but light fabric.\n");

  set_ac (1);
  set_af (this_object ());
  set_at (A_ROBE);

  add_prop (OBJ_I_VALUE, 250);
  add_prop (OBJ_I_WEIGHT, 1000);
  add_prop (OBJ_I_VOLUME, 500);
}


void init ()
{
  ::init ();

  add_action (m_action_finger, "mfinger");
  add_action (m_action_tester, "mtester");
}

//-------------------------------------------------------------------

void enter_env (object oTo, object oFrom)
{
  ::enter_env (oTo, oFrom);

  if (!m_is_authorized_wizard (oTo)) set_alarm (0.0, 0.0, &remove_object ());
}

//-------------------------------------------------------------------

void init_arg (string sArgs)
{
  int iWorn = FALSE;
  sscanf (sArgs, "worn=%d", iWorn);

  if (iWorn) set_alarm (0.0, 0.0, &command_wear ());
}


string query_auto_load ()
{
  return (MASTER + ":" + "worn=" + objectp (query_worn ()));
}


/*
 * Function name : query_recover
 * Description   : Turns recovery off by returning FALSE.
 *
 */

string query_recover ()
{
  return (FALSE);
}

//-------------------------------------------------------------------

