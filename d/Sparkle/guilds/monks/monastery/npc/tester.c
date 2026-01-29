/*******************************************************************\
| TESTER.C                                                          |
\*******************************************************************/

/*
 * 06/09/03 Arandir     Simulate unarmed option off
 * 06/09/02 Arandir     Created
 *
 */

#include <const.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_NPC_BASE;

//-------------------------------------------------------------------

#define M_DISPLAY(msg) tell_room (environment (), (msg) + "\n")

int iDoPlexus = FALSE;
int iDoStrike = FALSE;

int iKillCount = 0;
int iDeathCount = 0;

int iDamage = 0;
int iDamageTotal = 0;
int iDamagePerDeathMin = 999999999;
int iDamagePerDeathMax = 0;

int iTime = 0;
int iTimeTotal = 0;
int iTimePerDeathMin = 999999999;
int iTimePerDeathMax = 0;

//-------------------------------------------------------------------

string m_safe_ratio (int iNumerator, int iDenominator)
{
  if (iDenominator) return (ftoa (itof (iNumerator) / itof (iDenominator)));
               else return ("N/A");
}


void m_display_statistics ()
{
  M_DISPLAY ("===[ TESTER COMBAT STATS ]=====================================================");
  M_DISPLAY (". Kills " + iKillCount + ", deaths " + iDeathCount + ", ratio " + m_safe_ratio (iKillCount, iDeathCount));
  M_DISPLAY (". Damage " + iDamageTotal);
  M_DISPLAY (". Per death minimum " + iDamagePerDeathMin + ", average " + m_safe_ratio (iDamageTotal, iDeathCount) + ", maximum " + iDamagePerDeathMax);
  M_DISPLAY (". Time " + iTimeTotal);
  M_DISPLAY (". Per death minimum " + iTimePerDeathMin + ", average " + m_safe_ratio (iTimeTotal, iDeathCount) + ", maximum " + iTimePerDeathMax);
  M_DISPLAY ("-------------------------------------------------------------------------------");
}

//-------------------------------------------------------------------

void create_monster ()
{
  object oShadow;

  ::create_monster ();

  set_name ("tester" + "-" + random (1000));
  set_gender (one_of_list (G_MALE, G_FEMALE));
  set_race_name ("human");
  set_adj (({ "brave", "courageous", "masochistic" }));
  set_long ("This is a combat tester monster. It can fight with any " +
            "weapon and special and keeps statistics on combat. " +
            "Ask for help if required.\n");

  set_stats (({ 100, 100, 100, 100, 100, 100, 100, 100, 100 }));

  // We only set those skills that can affect combat.

  set_skill (SS_DEFENCE,      100);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (SS_BLIND_COMBAT, 100);
  set_skill (M_SKILL_STRIKE,  100);
  set_skill (M_SKILL_PLEXUS,  100);

  set_skill (SS_2H_COMBAT,    100);
  set_skill (SS_PARRY,        100);
  set_skill (SS_WEP_SWORD,    100);
  set_skill (SS_WEP_POLEARM,  100);
  set_skill (SS_WEP_AXE,      100);
  set_skill (SS_WEP_KNIFE,    100);
  set_skill (SS_WEP_CLUB,     100);
  set_skill (SS_WEP_MISSILE,  100);
  set_skill (SS_WEP_JAVELIN,  100);

  set_skill (M_SKILL_FORMING_CLUB,  M_SKILL_MAX_FORMING);
  set_skill (M_SKILL_FORMING_BLADE, M_SKILL_MAX_FORMING);
  set_skill (M_SKILL_FORMING_STICK, M_SKILL_MAX_FORMING);

  add_prop (CONT_I_HEIGHT, 175);
  add_prop (CONT_I_WEIGHT, 80000);

  // We are an occupational monk by occupation :-)

  DG_FIXUID;

  oShadow = clone_object (M_SHADOW_OCC);
  oShadow->shadow_me (this_object (), M_TYPE_OCC, M_STYLE_OCC, M_NAME_LONG);
}

//-------------------------------------------------------------------

int query_option (int iOption)
{
  switch (iOption)
  {
    case OPT_UNARMED_OFF: return (TRUE);
  }

  return (FALSE);
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

  if (iDoPlexus) command ("mk plexus");
  if (iDoStrike) command ("mk strike");

  return (0);
}


void m_notify_plexus_landed ()
{
  if (iDoPlexus) command ("mk plexus");
}


void m_notify_strike_landed ()
{
  if (iDoStrike) command ("mk strike");
}

//-------------------------------------------------------------------

varargs mixed hit_me (int iPen, int iType, object oAttacker, int iAttack, int iHitloc = -1)
{
  mixed *axResult = ::hit_me (iPen, iType, oAttacker, iAttack, iHitloc);
  iDamage += axResult [HITRES_DAMAGE];

  // Start timing the combat in case this is the first hit.

  if (!iTime) iTime = time ();

  // Keep our panic level low to avoid running all over the place.

  add_panic (-query_panic ());

  return (axResult);
}


void do_die (object oKiller)
{
  int iNow = time ();
  int iLifetime = iNow - iTime;

  iDamageTotal += iDamage;
  iDamagePerDeathMin = min (iDamagePerDeathMin, iDamage);
  iDamagePerDeathMax = max (iDamagePerDeathMax, iDamage);
  iDamage = 0;

  iTimeTotal += iLifetime;
  iTimePerDeathMin = min (iTimePerDeathMin, iLifetime);
  iTimePerDeathMax = max (iTimePerDeathMax, iLifetime);
  iTime = iNow;

  iDeathCount ++;

  // Do a kill notification.

  oKiller->notify_you_killed_me (this_object ());

  // Heal instantly to prime shape.

  set_hp (query_max_hp ());
  set_fatigue (query_max_fatigue ());

  // Display notice so that kills do not go unnoticed.

  M_DISPLAY (query_name () + " would have been killed now.");
}


void notify_you_killed_me (object oVictim)
{
  iKillCount ++;
}

//-------------------------------------------------------------------

void catch_question (string sQuestion)
{
  switch (sQuestion)
  {
    case "help":
      M_DISPLAY ("Ask tester <plexus> or <strike> to toggle special attacks.");
      M_DISPLAY ("Ask tester <stats> to display statistics.");
      break;

    case "plexus":
      iDoPlexus = !iDoPlexus;
      M_DISPLAY ("Plexus is " + (iDoPlexus ? "enabled" : "disabled") + ".");
      command ("mk plexus");
      break;

    case "strike":
      iDoStrike = !iDoStrike;
      M_DISPLAY ("Strike is " + (iDoStrike ? "enabled" : "disabled") + ".");
      command ("mk strike");
      break;

    case "stats":
      m_display_statistics ();
      break;
  }
}

//-------------------------------------------------------------------

