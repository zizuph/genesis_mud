/*******************************************************************\
| DISC.C                                                            |
\*******************************************************************/

/*
 * 15/12/22 Petros      Removed ability to contact non-guildmaster wizards
 * 04/11/14 Arandir     Guild masters as targets of telioys
 * 04/08/27 Arandir     Added fixing of UID and EUID in constructor
 * 04/03/06 Arandir     The disc was both recovering and autoloading
 * 03/09/10 Arandir     Added support for recalling telioys
 * 03/06/25 Arandir	Ported to new area
 * 01/05/14 Manat       Checks for linkdead, busy and idle
 * 01/05/13 Manat       Made the dics heapable
 * 01/05/13 Manat       Reports when the target is out of discs
 * 00/12/26 Manat       Fixed a typo
 * 98/08/16 Cirion	Created
 *
 */

#include <math.h>
#include <flags.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/heap";

inherit "/lib/keep";
inherit "/d/Genesis/magic/spellcasting";
inherit "/d/Genesis/magic/spells/tell";

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

#define M_TELL_OBJECT   "_monk_tell_object"

//-------------------------------------------------------------------

void create_heap ()
{
  // Fixing the UID and EUID is needed when this happens
  // to be the very first monk object loaded, because then
  // it needs to load the guild server as it queries various
  // guild functions.

  DG_FIXUID;

  set_name ("disc");
  add_name (M_TELL_OBJECT, TRUE);

  set_short ("small iron disc");
  set_long ("It is a small disc made from dull, beaten " +
            "iron. In the center of the disc is a tiny square hole. " +
            "The hole seems to shimmer and refract the light passing " +
            "through it.\n");

  add_prop (HEAP_I_UNIT_WEIGHT, 2);
  add_prop (HEAP_I_UNIT_VOLUME, 2);
  add_prop (HEAP_I_UNIT_VALUE, 188);
  add_prop (HEAP_S_UNIQUE_ID, M_TELL_OBJECT);

  set_heap_size (1);

  set_keep ();

  add_prop (OBJ_S_WIZINFO,
            "This spell object is used to send a tell message to " +
            "other monks. The ingredient is the object itself, " +
            "which is prayed for in monk chapel.\n" +
            "Form: SS_FORM_DIVINATION (1)\n" +
            "Elem: SS_ELEMENT_AIR (1)\n" +
            "Time: 4\n" +
            "Mana: 10\n");

  add_spell ("telioy", "Speak to distant Monks", create_spell_tell, target_tell);
}

//-------------------------------------------------------------------

void tell (object oCaster, object *aoTargets, int *piResist, int iResult)
{
  object oTarget = aoTargets [0];
  string sName = oTarget->query_met_name ();

  oCaster->catch_tell ("You hold the small iron disc to your lips and whisper " +
                       "to " + sName + ": " + query_tell_message () + "\n" +
                       "The disc turns to dust in your fingers.\n");

  if (!present (M_TELL_OBJECT, oTarget))
  {
    oCaster->catch_tell ("You sense that " + sName + " might not be able " +
                         "to respond promptly.\n");
  }
  else if (query_idle (oTarget) > 300)
  {
    oCaster->catch_tell ("You sense that " + sName + " might not be attentive " +
                         "to respond promptly.\n");
  }

  tell_room (environment (oCaster),
             QCTNAME (oCaster) + " holds a small iron disc to " +
             QPOS (oCaster) + " lips and whispers softly to it.\n" +
             "The disc turns to dust in " + QPOS (oCaster) + " fingers.\n",
             oCaster);
  oTarget->catch_msg ("A vision of " + XNAME (oTarget, oCaster) + " appears " +
                      "before you and whispers: " + query_tell_message () + "\n");
  tell_room (environment (oTarget),
             "A brief vision appears in the air before " +
             QNAME (oTarget) + " and whispers something.\n",
             oTarget);

  oTarget->m_remember_telioy (XNAME (oTarget, oCaster), query_tell_message ());
}


int create_spell_tell (object oCaster, object *aoTargets, string sArgs)
{
  // Most things are left default for the tell spell

  ::create_spell_tell (oCaster, aoTargets, sArgs);

  set_spell_element (SS_ELEMENT_AIR, 1);
  set_spell_form (SS_FORM_DIVINATION, 1);
  set_spell_ingredients (({ M_TELL_OBJECT }));
  set_spell_effect (tell);
  set_spell_stationary (FALSE);
  set_spell_visual (FALSE);

  return (FALSE);
}


object *find_tell_targets (object oCaster, string sArgs)
{
  object oTarget;
  mixed  xBusy;

  if (!strlen (sArgs))
  {
    oCaster->catch_tell ("Contact whom ?\n");
    return (({ }));
  }

  oTarget = find_living (sArgs);

  // 2015-12-22 by Petros
  // Monks should not be able to send to wizards other than guild wizards.
  if (!objectp (oTarget) ||
      !m_is_monk (oTarget) ||
      (dg_is_wizard (oTarget)
       && (dg_is_invisible (oTarget) || !m_is_guild_wizard (oTarget))))
  {
    oCaster->catch_tell ("That person is not present right now.\n");
    return (({ }));
  }

  if (!query_interactive (oTarget))
  {
      oCaster->catch_tell ("That person is not interactive right now.\n");
      return (({ }));
  }

  if (oTarget->query_prop (WIZARD_I_BUSY_LEVEL) & BUSY_F)
  {
    oCaster->catch_tell ("That person does not want to be disturbed.\n");
    return (({ }));
  }

  xBusy = oTarget->query_prop (M_PROP_TMP_I_BUSY);
  if (intp (xBusy) && xBusy)
  {
    oCaster->catch_tell ("That person does not want to be disturbed.\n");
    return (({ }));
  }
  if (stringp (xBusy))
  {
    oCaster->catch_tell ("That person does not want to be disturbed and left a message: " + xBusy + "\n");
    return (({ }));
  }

  return (({ oTarget }));
}

//-------------------------------------------------------------------

void enter_env (object oTo, object oFrom)
{
  ::enter_env (oTo, oFrom);

  if (m_is_monk (oTo)) add_spell_object (oTo);
}


void leave_env (object oFrom, object oTo)
{
  ::leave_env (oFrom, oTo);

  // Remove the telioy spell when the disc is gone. This
  // does not cover the situation when somebody leaves
  // monks but I suppose that is very rare ...

  if (m_is_monk (oFrom)) remove_spell_object (oFrom);
}

//-------------------------------------------------------------------

/*
 * Function name : query_recover
 * Description   : Check to see if the object will auto load. Two
 *                 thirds of the discs will recover.
 * Returns       : The recover string
 *
 */

string query_recover ()
{
  return (FALSE);
}


/*
 * Function name : query_auto_load
 * Description   : Check to see if the object will auto load. Two
 *                 thirds of the discs will auto load.
 * Returns       : The auto load string
 *
 */

string query_auto_load ()
{
  return (MASTER + ":" + (num_heap () * 2)/3);
}


/*
 * Function name : init_arg
 * Desctiption   : Initializes to the previously saved state
 *
 */

void init_arg (string sArgs)
{
  if (!sArgs) return;

  set_heap_size (MAX (1, atoi (sArgs)));
}

//-------------------------------------------------------------------

