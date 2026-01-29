/*******************************************************************\
| BELT.C                                                            |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Fixed use of XOBJ style macros
 *                      Removed the focus skill
 * 04/11/14 Arandir     Guild masters on member list
 * 05/08/16 Arandir     Reduced the obscene mana drain
 * 03/09/14 Arandir     Monsters can wear the belt
 * 03/09/09 Arandir     Changed the aging mechanism
 * 03/04/13 Arandir     Largely bugfixed
 * 03/04/04 Arandir	Ported to new area
 * 02/02/?? Mercade     Added the setuid and seteuid calls
 *                      because this object may need to
 *                      create the master monk object
 * 01/02/?? Manat       Changed the description
 * 01/01/?? Manat       Fixed the aging support and typos
 * 00/12/?? Manat       Added the aging support
 * 00/06/?? Cirion      Added the slis spell
 * 99/02/?? Lilith	Created
 *
 */

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>

#include "../defs.h"

inherit M_OBJ_CLOTHES_WEARABLE_BASE;

inherit "/d/Genesis/magic/spellcasting";
inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

inherit DG_PLAYER_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

private string sBeltColor = "";
private string sBeltDesc = "\n";
private int    iBeltAgingOn = FALSE;
private int    iBeltAgingStart = 0;
private int    iBeltAgingTotal = 0;

object *m_slis_target (object oCaster, string sArgs);
int m_slis_create (object oCaster, object *aoTargets, string sArgument);

//-------------------------------------------------------------------

string m_belt_short ()
{
  object oHolder = environment ();
  object oLooker = vbfc_caller ();
  string sShort;

  if (sBeltColor == "") sShort = "thick belt";
                   else sShort = "thick " + sBeltColor + " belt";

  // This only seems to work for commands that write the
  // description to a single person, but so what ...

  if ((objectp (oHolder)) &&
      (objectp (oLooker)) &&
      (query_worn () == oHolder))
  {
    sShort += " tied around ";
    if (oHolder == oLooker) sShort += "your";
                       else sShort += XPOS (oHolder);
    sShort += " waist";
  }

  return (sShort);
}


string m_belt_long ()
{
  object oHolder = environment ();
  object oLooker = vbfc_caller ();
  string sLong;

  sLong = "This flexible belt is made of densely woven flax " +
          "fiber. It is three fingers wide and nearly as long ";

  // This was here before I decided to polish the code. Meseems
  // it is a simple hack to check whether we are called from
  // examine, which is in /cmd/live/things, or from show,
  // which is somewhere else ...

  if (previous_object (-2) == find_object ("/cmd/live/things"))
  {
    sLong += "as you are tall. " + sBeltDesc;
  }
  else
  {
    sLong += "as " + XPNOUN (oHolder) + " is tall. " +
             "The " + sBeltColor + " color corresponds to the " +
             "depth of " + XPOS (oHolder) + " mastery " +
             "of the dragon discipline.\n";
  }

  return (sLong);
}

//-------------------------------------------------------------------

void m_belt_aging_start ()
{
  iBeltAgingStart = time ();
}


void m_belt_aging_update ()
{
  int iDelta;

  if (iBeltAgingOn && query_worn ())
  {
    iDelta = time () - iBeltAgingStart;
    iBeltAgingStart += iDelta;
    iBeltAgingTotal += iDelta;
  }
}

//-------------------------------------------------------------------

void m_configure_belt ()
{
  object oMe = this_player ();
  string sNewColor = "";
  string sNewFeat = "";
  int    iSkill;

  iBeltAgingOn = FALSE;

  iSkill = (oMe->query_skill (SS_DEFENCE) +
            oMe->query_skill (SS_ACROBAT) +
            oMe->query_skill (SS_UNARM_COMBAT));

  switch (iSkill)
  {
    case 0 .. 150:
      sNewColor = "white";
      sNewFeat  = "Presently, you are at the first step to mastery, " +
                  "common to apprentices and laymen.";
      break;
    case 151 .. 210:
      sNewColor = "yellow";
      sNewFeat  = "You have passed from the white belt into the " +
                  "second level of mastery expected of those who " +
                  "have begun to study the dragon discipline in the " +
                  "earnest.";
      break;
    case 211 .. 240:
      sNewColor = "green";
      sNewFeat  = "You have attained the third level, that degree " +
                  "of knowledge of the dragon discipline which " +
                  "will swiftly propel you into the brown and " +
                  "black, if you maintain focus.";
      break;
    case 241 .. 260:
      sNewColor = "brown";
      sNewFeat  = "Presently, you have all but mastered the teachings " +
                  "of the Dragon Order. You are at that stage when all " +
                  "will soon become as clear to you as the sound of a " +
                  "gong in the crisp mountain air.";
      break;
    case 261 .. 999:
      iBeltAgingOn = TRUE;
      if (iBeltAgingTotal < 45 * DG_SEC2DAY)
      {
        switch (iBeltAgingTotal / DG_SEC2DAY)
        {
          case 0 .. 4:
            sNewColor = "black"; break;
          case 5 .. 10:
            sNewColor = "slightly worn black"; break;
          case 11 .. 17:
            sNewColor = "somewhat worn black"; break;
          case 18 .. 25:
            sNewColor = "worn grey"; break;
          case 26 .. 34:
            sNewColor = "frayed grey"; break;
          case 35 .. 44:
            sNewColor = "frayed light grey"; break;
        }
        sNewFeat = "You have achieved a commendable feat. You wear " +
                   "the belt as a sign that you have mastered the " +
                   "physical and mental rigors of the Order of " +
                   "the Dragon.";
      }
      else
      {
        sNewColor = "frayed white";
        sNewFeat  = "Misleading to the unenlightened, the white color " +
                    "of your belt is a token of a rare insight into " +
                    "the teachings of the Dragon Order. For a true " +
                    "follower of the path knows that it is one's " +
                    "actions rather than colored trinklets that " +
                    "distinguish a master from a layman.";
      }
      break;
  }

  if (sBeltColor != sNewColor)
  {
    remove_adj (sBeltColor);
    add_adj (sNewColor);

    sBeltColor = sNewColor;
    sBeltDesc  = "The " + sNewColor + " color corresponds " +
                 "to the depth of your mastery of the dragon " +
                 "discipline. " + sNewFeat + "\n";
  }
}

//-------------------------------------------------------------------

void create_object ()
{
  ::create_object ();

  // Fixing the UID and EUID is needed when this happens
  // to be the very first monk object loaded, because then
  // it needs to load the guild server as it queries various
  // guild functions.

  DG_FIXUID;

  set_name ("belt");
  add_adj (({ "woven", "long", "thick", "monk", "flexible" }));

  set_short (&m_belt_short ());
  set_long (&m_belt_long ());

  config_wearable_item (A_WAIST, 1, 15, this_object());

  add_prop (OBJ_I_VALUE, 0);
  add_prop (OBJ_I_WEIGHT, 250);
  add_prop (OBJ_I_VOLUME, 150);
  add_prop (OBJ_M_NO_DROP, "You decide not to drop a symbol of your mastery of the dragon discipline.\n");
  add_prop (OBJ_M_NO_SELL, "You cannot sell a symbol of your mastery of the dragon discipline.\n");
  add_prop (OBJ_M_NO_STEAL, "The belt seems to resist your grasp.\n");

  add_spell ("slis", "Find brethren", m_slis_create, m_slis_target);
}

//-------------------------------------------------------------------

mixed wear (object oThis)
{
  object oPlayer = environment ();
  object oRoom = environment (this_player ());

  if (!query_interactive (oPlayer) || m_is_monk (oPlayer))
  {
    write ("You loop the " + short () +" around your "+
           "waist and draw it tight.\n");
    tell_room (oRoom, QCTNAME (oPlayer) + " loops the " +
               short () +" around " + QPOS (oPlayer) + " waist " +
               "and draws it tight.\n", oPlayer);

    m_belt_aging_start ();

    return (1);
  }
  else
  {
    return ("The belt, thick, heavy and unfamiliar, seems " +
            "to resist your attempts to tie it around your " +
            "waist.\n");
  }
}


mixed remove (object oThis)
{
  object oPlayer = environment ();

  if ((oPlayer != this_player ()) ||
      (oThis != this_object ())) return (-1);

  m_belt_aging_update ();

  return (0);
}

//-------------------------------------------------------------------

void enter_env (object oTo, object oFrom)
{
  ::enter_env (oTo, oFrom);

  // The belt assumes color based on the current owner.

  m_configure_belt ();

  // Monks get the slis spell together with the belt.

  if (m_is_monk (oTo)) add_spell_object (oTo);
}


void leave_env (object oFrom, object oTo)
{
  ::leave_env (oFrom, oTo);

  // Remove the slis spell when the belt is gone. This
  // does not cover the situation when somebody leaves
  // monks but I suppose that is very rare ...

  if (m_is_monk (oFrom)) remove_spell_object (oFrom);
}

//-------------------------------------------------------------------

void init_arg (string sArgs)
{
  if (sscanf (sArgs, "age=%d", iBeltAgingTotal) != 1)
  {
    iBeltAgingTotal = 0;
  }
}


string query_auto_load ()
{
  m_belt_aging_update ();

  return (MASTER + ":" + "age=" + iBeltAgingTotal);
}

//-------------------------------------------------------------------

int m_slis_filter (object oWho)
{
  return ((m_is_monk (oWho) || m_is_guild_wizard (oWho))
          && !dg_is_invisible (oWho)
          && !dg_is_junior (oWho));
}


void m_slis_effect (object oCaster, object *aoTargets, int *aiResist, int iResult)
{
  object *aoPeople = filter (users (), &m_slis_filter ()) - ({ oCaster });

  if (sizeof (aoPeople) > 0)
  {
    write ("You can see a vision of " +
           COMPOSITE_WORDS (aoPeople->query_name ()) +
           " all around you.\n");
  }
  else
  {
    write ("Your vision comes, but it is empty.\n");
  }
}


object *m_slis_target (object oCaster, string sArgs)
{
  // This is a bogus return value, since an empty array would
  // cause the spell to fail.

  return (({ oCaster }));
}


int m_slis_create (object oCaster, object *aoTargets, string sArgument)
{
  set_spell_time (3);
  set_spell_mana (10);
  set_spell_task (TASK_SIMPLE);
  set_spell_element (SS_ELEMENT_AIR, 1);
  set_spell_form (SS_FORM_DIVINATION, 1);
  set_spell_ingredients (({ }));
  set_spell_resist (0);
  set_spell_effect (&m_slis_effect ());
  set_spell_conc_message ("You place your fingers on your forehead and close your eyes.\n");

  return (0);
}

//-------------------------------------------------------------------

