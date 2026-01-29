/*******************************************************************\
| STUN.C                                                            |
+-------------------------------------------------------------------+
| Paralyzes the victim of plexus.                                   |
\*******************************************************************/

/*
 * 08/03/12 Arandir     Somehow a premature removal crept in
 * 08/03/08 Arandir     Better logging of stun effect timing
 * 08/03/02 Arandir     Logging of stun effect timing
 * 08/02/16 Mercade     Use CMDPARSE_PARALYZE_CMD_IS_ALLOWED
 * 07/06/14 Arandir     Logs victims whose quickness changes
 * 07/05/28 Arandir     Enabled block on movement after AoB approval
 * 06/09/26 Arandir     Better logging of certain plexus anomalies
 * 06/09/16 Arandir     Changed the way victim is identified
 * 06/08/16 Arandir     Added more sanity checks and logging on stuns
 * 06/03/26 Arandir     Rewritten to accommodate new combat system
 * 03/06/25 Arandir     Ported to the new area and cleaned up
 * 02/10/17 Arandir     Disabled the probabilistic block on
 *                      movement to comply with AoB requirements
 * 98/08/05 Cirion      Recoded and commented
 * 94/07/?? Glindor     Created
 *
 */

#include <macros.h>
#include <cmdparse.h>

#include "../defs.h"

inherit "/std/object";

inherit DG_PLAYER_LIBS;
inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

#define M_DEBUG_LOCAL_STUN      FALSE

//-------------------------------------------------------------------

#define PHASE_NONE      0
#define PHASE_STUN      BIT(0)
#define PHASE_SLOW      BIT(1)

int     iPhase = PHASE_NONE;

int     iStunningAlarm = ALARM_NONE;
int     iSlowingAlarm  = ALARM_NONE;

// fSlowingDuration             The total duration of the slowing phase.
// fSlowingRemaining            The remaining duration of the slowing phase.

// The actual slowdown is determined by the proportion
// of fSlowingRemaining to fSlowingDuration ...

float   fSlowingDuration = 0.0;
float   fSlowingRemaining = 0.0;

// M_SLOWING_PERIOD             The period with which LIVE_I_QUICKNESS is adjusted

#define M_SLOWING_PERIOD        1.0

// iSlowingPropertyCurrent      The current value of LIVE_I_QUICKNESS of victim
// iSlowingPropertyOriginal     The original value of LIVE_I_QUICKNESS of victim

// The current and original values are tracked in order to detect
// external changes to LIVE_I_QUICKNESS that can disrupt the
// slowing phase ... note that there is no protocol on
// modifying LIVE_I_QUICKNESS from multiple items.

#define QUICKNESS_MINIMUM       -100
#define QUICKNESS_DEFAULT       0

int     iSlowingPropertyCurrent;
int     iSlowingPropertyOriginal;

object  oVictim = NULL;

// The commands that are allowed during stun ...

private static string *asStunCommands = ({
  "examine", "glance", "look", "exa", "x" });

private static string *asStunMessages = ({
  "The blow to your abdomen rendered you unable to do that.",
  "Sharp pain in your abdomen prevents you doing that.",
  "You feel like throwing up rather than doing that.",
  "Your limbs refuse to follow your orders." });


// We might want to debug the timings ...

#if M_DEBUG_LOCAL_STUN
float fCreationTime;
float fLastStunTime;
float fLastSlowTime;
float fAccumulatedStunTime = 0.0;
float fAccumulatedSlowTime = 0.0;
#endif


void m_stun_alarm ();
void m_slow_alarm ();

//-------------------------------------------------------------------

/*******************************************************************\
| Debugging functions.                                              |
\*******************************************************************/

/*
 * Function name : remove_object
 * Description   : Independent debugging of timing
 *
 */

#if M_DEBUG_LOCAL_STUN
void remove_object ()
{
  // Log the timing ...
  s_log (M_LOG_DEBUG, "Victim " + ftoa (gettimeofday () - fCreationTime) +
                      " stun " + ftoa (fAccumulatedStunTime) +
                      " slow " + ftoa (fAccumulatedSlowTime) +
                      ".");
  // Remove self ...
  ::remove_object ();
}
#endif


/*
 * Function name : m_conditional_remove_object
 * Description   : Removes the stun object if either
 *                 the stun or the victim are gone
 *
 */

void m_conditional_remove_object ()
{
// When debugging timing, the stun object gets
// removed only when the victim is gone, to
// get totals over entire fight ...
#if M_DEBUG_LOCAL_STUN

  if (!objectp (oVictim)) remove_object ();

// When not debugging timing, the stun object also
// gets removed when neither stunning nor slowing ...
#else

  if ((!objectp (oVictim)) || (iPhase == PHASE_NONE)) remove_object ();

#endif
}

//-------------------------------------------------------------------

/*******************************************************************\
| Functions that actually manipulate the victim.                    |
\*******************************************************************/

/*
 * Function name : m_victim_start_stun
 * Description   : Sets whatever is needed in the victim to start stunning.
 *
 */

void m_victim_start_stun (float fTime)
{
  if (!(iPhase & PHASE_STUN))
  {
    iPhase |= PHASE_STUN;
    oVictim->add_stun ();

    iStunningAlarm = set_alarm (fTime, 0.0, m_stun_alarm);
  }
  else s_log (M_LOG_DEBUG, "Starting stun that has already been started.");

// Independent debugging of timing
#if M_DEBUG_LOCAL_STUN
fLastStunTime = gettimeofday ();
#endif
}


/*
 * Function name : m_victim_stop_stun
 * Description   : Reverses the effects of m_victim_start_stun.
 *
 */

void m_victim_stop_stun ()
{
  if (iPhase & PHASE_STUN)
  {
    iPhase &= ~PHASE_STUN;
    oVictim->remove_stun ();

    DG_REMOVE_ALARM (iStunningAlarm);
  }
  else s_log (M_LOG_DEBUG, "Stopping stun that has not been started.");

// Independent debugging of timing
#if M_DEBUG_LOCAL_STUN
fAccumulatedStunTime += gettimeofday () - fLastStunTime;
#endif
}


/*
 * Function name : m_victim_adjust_slow
 * Description   : Sets whatever is needed in the victim to adjust slowing.
 *
 */

void m_victim_adjust_slow ()
{
  if (iPhase & PHASE_SLOW)
  {
    int iSlowingPropertyReal = oVictim->query_prop (LIVE_I_QUICKNESS);

    // The difference between the expected and the real value
    // of LIVE_I_QUICKNESS means another item is messing with
    // the value, in which case, we revert to a conservative
    // mode that ends up with LIVE_I_QUICKNESS of zero ...

    // This is logged so that cases where LIVE_I_QUICKNESS is
    // modified from multiple items can be investigated in
    // detail and, ideally, some protocol aranged.

    if (iSlowingPropertyReal != iSlowingPropertyCurrent)
    {
      s_log (M_LOG_DEBUG, "External change of LIVE_I_QUICKNESS from " +
                          iSlowingPropertyCurrent +
                          " to " +
                          iSlowingPropertyReal +
                          ".",
                          oVictim);

      iSlowingPropertyOriginal = QUICKNESS_DEFAULT;
    }

    // LIVE_I_QUICKNESS is set so that the setting of quickness in the range
    // between minimum quickness and original quickness is proportional to
    // the position of fSlowingRemaining between fSlowingDuration and zero.

    iSlowingPropertyCurrent = iSlowingPropertyOriginal;
    if (fSlowingDuration > fSlowingRemaining)
    {
      iSlowingPropertyCurrent += ftoi (itof (QUICKNESS_MINIMUM - iSlowingPropertyOriginal)
                                          * (fSlowingRemaining / fSlowingDuration));
    }
    oVictim->add_prop (LIVE_I_QUICKNESS, iSlowingPropertyCurrent);
  }
  else s_log (M_LOG_DEBUG, "Adjusting slow that has not been started.");
}


/*
 * Function name : m_victim_start_slow
 * Description   : Sets whatever is needed in the victim to start slowing.
 *
 */

void m_victim_start_slow (float fTime)
{
  if (!(iPhase & PHASE_SLOW))
  {
    iPhase |= PHASE_SLOW;
    fSlowingDuration = fSlowingRemaining = fTime;
    iSlowingPropertyOriginal = iSlowingPropertyCurrent = oVictim->query_prop (LIVE_I_QUICKNESS);

    m_victim_adjust_slow ();

    iSlowingAlarm = set_alarm (M_SLOWING_PERIOD, M_SLOWING_PERIOD, m_slow_alarm);
  }
  else s_log (M_LOG_DEBUG, "Starting slow that has already been started.");

// Independent debugging of timing
#if M_DEBUG_LOCAL_STUN
fLastSlowTime = gettimeofday ();
#endif
}


/*
 * Function name : m_victim_stop_slow
 * Description   : Reverses the effects of m_victim_start_slow.
 *
 */

void m_victim_stop_slow ()
{
  if (iPhase & PHASE_SLOW)
  {
    iPhase &= ~PHASE_SLOW;
    oVictim->add_prop (LIVE_I_QUICKNESS, iSlowingPropertyOriginal);

    DG_REMOVE_ALARM (iSlowingAlarm);
  }
  else s_log (M_LOG_DEBUG, "Stopping slow that has not been started.");

// Independent debugging of timing
#if M_DEBUG_LOCAL_STUN
fAccumulatedSlowTime += gettimeofday () - fLastSlowTime;
#endif
}

//-------------------------------------------------------------------

/*
 * Function name : m_command_stop
 * Description   : Stop player from performing commands.
 *
 */

int m_command_stop (string sArgs)
{
  object oHim = this_player ();
  string sVerb;

  // Some sanity checks to make sure we do not paralyze wrong target.
  // This should never happen though, hence the logging ...

  if (oHim != oVictim)
  {
    s_log (M_LOG_DEBUG, "Paralysis actor is " +
                        capitalize (dg_get_name (oHim)) +
                        " instead of " +
                        capitalize (dg_get_name (oVictim)) +
                        ".");
    return (FALSE);
  }

  if (environment () != oVictim)
  {
    s_log (M_LOG_DEBUG, "Paralysis environment is " +
                        capitalize (dg_get_name (environment ())) +
                        " instead of " +
                        capitalize (dg_get_name (oVictim)) +
                        ".");
    return (FALSE);
  }

  // We do not paralyze wizards ...

  if (dg_is_wizard (oHim)) return (FALSE);

  // We paralyze only when stunning. Since it is not possible
  // to add and remove the command hook at need, we keep the
  // command hook and enable and disable the paralysis ...

  if (!(iPhase & PHASE_STUN)) return (FALSE);

  // Certain verbs are always allowed.

  // If the exception of allowing movement while stunned is
  // to be introduced again, the proper way is to check if
  // the verb is in query_exit_cmds of the environment.

  sVerb = query_verb ();

  if (CMDPARSE_PARALYZE_CMD_IS_ALLOWED (sVerb)) return (FALSE);
  if (member_array (sVerb, asStunCommands) >= 0) return (FALSE);

  // We now know that we block, tell the poor player so :-)

  write (one_of_list (asStunMessages) + "\n");

  return (TRUE);
}

//-------------------------------------------------------------------

/*
 * Function name : m_land_plexus
 * Description   : Announce a new plexus with a given duration.
 *
 */

void m_land_plexus (float fStunTime, float fSlowTime)
{
  // Start the new stun phase only if we are not currently stunning.

  if (!(iPhase & PHASE_STUN))
  {
    m_victim_start_stun (fStunTime);
  }

  // Start the new slow phase only if we are not currently slowing.

  if (!(iPhase & PHASE_SLOW))
  {
    m_victim_start_slow (fSlowTime);
  }
  else
  {
    // If we are currently slowing, increase the duration of the
    // slow phase and restart the slow phase by setting the
    // total duration to the remaining duration ...

    fSlowingRemaining += fSlowTime;
    fSlowingDuration = fSlowingRemaining;

    m_victim_adjust_slow ();
  }
}


/*
 * Function name : m_stun_alarm
 * Description   : Alarm to handle end of stun phase.
 *
 */

void m_stun_alarm ()
{
  iStunningAlarm = ALARM_NONE;

  if (objectp (oVictim))
  {
    m_victim_stop_stun ();

    oVictim->catch_msg ("You feel your breath returning, although you are still a bit windy.\n");
    tell_room (environment (oVictim), QCTNAME (oVictim) + " seems to regain " + QPOS (oVictim) + " breath.\n", oVictim, oVictim);
  }

  m_conditional_remove_object ();
}


/*
 * Function name : m_slow_alarm
 * Description   : Alarm to handle change of slow phase.
 *
 */

void m_slow_alarm ()
{
  if (objectp (oVictim))
  {
    fSlowingRemaining -= M_SLOWING_PERIOD;

    if (fSlowingRemaining > 0.0)
    {
      // Still some time left in the slow phase.
      m_victim_adjust_slow ();
    }
    else
    {
      // The slow phase is over.
      m_victim_stop_slow ();
    }
  }

  m_conditional_remove_object ();
}

//-------------------------------------------------------------------

void create_object ()
{
  ::create_object ();

  set_no_show ();
  set_name (M_PLEXUS_STUN_ID);

  add_prop (OBJ_M_NO_GET, TRUE);
  add_prop (OBJ_M_NO_DROP, TRUE);
  add_prop (OBJ_I_NO_GIVE, TRUE);
  add_prop (OBJ_M_NO_STEAL, TRUE);
  add_prop (OBJ_M_NO_TELEPORT, TRUE);

// Independent debugging of timing
#if M_DEBUG_LOCAL_STUN
fCreationTime = gettimeofday ();
#endif
}


void init ()
{
  ::init ();

  // The init function is called both for our owner
  // and for our neighbors in the inventory of the
  // owner. The following check prevents stunning
  // the neighbors, such as messengers ...

  if (environment () == oVictim)
  {
    add_action (m_command_stop, "", ACTION_PARTIAL);
  }
}


void enter_env (object oTo, object oFrom)
{
  ::enter_env (oTo, oFrom);

  if (living (oTo))
  {
    if (objectp (oVictim))
    {
      s_log (M_LOG_DEBUG, "Paralysis object entering secondary environment.", oTo);
    }
    else
    {
      oVictim = oTo;
    }
  }
  else
  {
    s_log (M_LOG_DEBUG, "Paralysis object entering inanimate environment.", oTo);
  }
}

//-------------------------------------------------------------------

