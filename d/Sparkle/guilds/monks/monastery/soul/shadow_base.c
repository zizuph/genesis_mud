/*******************************************************************\
| SHADOW_BASE.C                                                     |
\*******************************************************************/

/*
 * 07/12/09 Arandir     Mercade thinks this has to be renamed from H to C
 *          Mercade     Fixed a bug in wrapping the attacked_by function
 * 04/08/26 Arandir     Removed the familiar because Mercade said
 *                      it is bad, luckily he also made the normal
 *                      emote hooks work on players :-) ...
 * 04/08/25 Arandir     Mild changes for relationship support
 * 04/08/18 Arandir     Mild changes for familiar support
 * 04/06/13 Arandir     Disabled the suspect exp hooks
 * 04/06/12 Arandir     Shadow is not saved for monsters
 * 04/05/22 Arandir     Added centralized hooks
 * 03/12/12 Arandir     Added the delayed save support
 * 03/12/03 Arandir     Added the character measurement support
 * 03/08/10 Arandir     Split into the general and combat parts
 * 03/07/23 Arandir     Removed support for fasting as it will not
 *                      be needed for the guru quest after all.
 * 03/07/08 Arandir     Moved the armour damaging effect of plexus
 *                      from the message display code to the
 *                      plexus code itself
 * 03/07/07 Arandir     Bugfixed the fatigue drain of the specials and
 *                      removed several pages of unused attack code
 * 03/07/05 Arandir     Moved special attack checks from the soul to here
 *                      and cleaned up the ton of duplicit attack checks
 * 03/06/24 Arandir     Changed the mwarn mechanism to be more efficient
 * 03/06/23 Arandir     Minor changes to compile in the new area
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 01/05/13 Manat	Does not check discipline in fight
 * 98/05/02 Cirion	Miscelaneous additions
 * ??/??/?? Shiva	Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

#include <math.h>
#include <tasks.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <state_desc.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include </std/combat/combat.h>

#include "../defs.h"

// Note that calling functions in inherited libraries from a shadow is
// tricky as the function can not call the shadow back directly !!!

inherit DG_MISC_LIBS;
inherit DG_TEXT_LIBS;
inherit DG_PLAYER_LIBS;
inherit M_TEXT_LIBS;
inherit M_EMOTE_LIBS;
inherit M_PLAYER_LIBS;
inherit M_LOGGING_LIBS;

//-------------------------------------------------------------------

void m_save_object ();
void m_restore_object ();

//-------------------------------------------------------------------

#include "shadow_base_general.c"
#include "shadow_base_combat.c"
#include "shadow_base_character.c"

//-------------------------------------------------------------------

/*******************************************************************\
| Saving                                                            |
\*******************************************************************/

// Local data

#define M_SAVE_MIN_DELAY        30.0
#define M_SAVE_MAX_AGE          300

private static int iSaveAlarm = ALARM_NONE;
private static int iSaveTime;


/*
 * Function name : m_filename
 * Function name : m_save_immediate
 * Function name : m_save_object
 * Function name : m_restore_object
 * Description   : Functions to save and restore the object.
 *
 */

string m_filename ()
{
  return (M_PATH_VAR_SOUL + "/" + dg_get_name (shadow_who));
}


void m_save_immediate ()
{
  iSaveAlarm = ALARM_NONE;

  if (interactive (shadow_who))
  {
    m_export_state_monk_kinship ();
    m_export_state_monk_character ();
    m_export_state_monk_relationship ();
    DG_FIXUID;
    save_object (m_filename ());
  }
}


void m_save_object ()
{
  // To prevent extreme load, we merge saves that are more
  // frequent than a given delay. A save is enforced when
  // removing the object as well.

  if (iSaveAlarm != ALARM_NONE)
  {
    if ((time () - iSaveTime) < M_SAVE_MAX_AGE)
    {
      remove_alarm (iSaveAlarm);
      iSaveAlarm = set_alarm (M_SAVE_MIN_DELAY, 0.0, m_save_immediate);
    }
  }
  else
  {
    iSaveAlarm = set_alarm (M_SAVE_MIN_DELAY, 0.0, m_save_immediate);
    iSaveTime = time ();
  }
}


void m_restore_object ()
{
  DG_FIXUID;
  restore_object (m_filename ());
  m_import_state_monk_kinship ();
  m_import_state_monk_character ();
  m_import_state_monk_relationship ();
}


void m_hook_save_remove_object ()
{
  if (iSaveAlarm != ALARM_NONE)
  {
    remove_alarm (iSaveAlarm);
    m_save_immediate ();
  }
}

//-------------------------------------------------------------------

/*******************************************************************\
| Hooks                                                             |
\*******************************************************************/

// Watch out with the hooks. Admin warns that some hooks spam
// the logs, and therefore should be avoided altogether.


void m_shadow_init ()
{
  mixed xResult;

  // Restore the state of the shadow as necessary ...

  m_restore_object ();

  // Initialize the rest with general init first ...

  xResult = m_shadow_general_init ();
  if (stringp (xResult))
  {
    s_log (M_LOG_DEBUG, xResult);
    remove_shadow ();
  }
  else
  {
    m_shadow_combat_init ();
    m_shadow_character_init ();

    m_collect_statistics (shadow_who);
  }
}


void remove_object ()
{
  // Note the order here. The save hook must be called last of
  // all hooks so that all the changes made by the hooks get
  // saved correctly. Of course the original function must
  // come last, being a destructor and all.

  m_hook_character_remove_object ();
  m_hook_save_remove_object ();
  shadow_who->remove_object ();
}


// Other hooks


void emote_hook (string sEmote, object oActor, string sAdverb, object *aoTargets, int iAttributes, int iTarget)
{
  shadow_who->emote_hook (sEmote, oActor, sAdverb, aoTargets, iAttributes, iTarget);
  m_hook_character_emote_seen (sEmote, sAdverb, oActor, aoTargets, iAttributes);
}


void emote_hook_onlooker (string sEmote, object oActor, string sAdverb, object *aoTargets, int iAttributes)
{
  shadow_who->emote_hook_onlooker (sEmote, oActor, sAdverb, aoTargets, iAttributes);
  m_hook_character_emote_seen (sEmote, sAdverb, oActor, aoTargets, iAttributes);
}


void emote_hook_actor (string sEmote, object *aoTargets)
{
  shadow_who->emote_hook_actor (sEmote, aoTargets);
  m_hook_character_emote_done (sEmote, aoTargets);
}


void attack_object (object oHim)
{
  shadow_who->attack_object (oHim);
  m_hook_character_attacking (oHim);
}


void attacked_by (object oHim)
{
  shadow_who->attacked_by (oHim);
  m_hook_character_attacked (oHim);
}


void notify_you_killed_me (object oHim)
{
  shadow_who->notify_you_killed_me (oHim);
  m_hook_combat_notify_you_killed_me (oHim);
}

//-------------------------------------------------------------------

