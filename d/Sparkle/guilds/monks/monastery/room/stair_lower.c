/*******************************************************************\
| STAIR_LOWER.C                                                     |
\*******************************************************************/

/*
 * 2018118 Ckrik Prevent people from taking food left for Mzenska
 *         if he's around.
 * 98/06/14 Cirion	Created
 * 02/04/26 Arandir	Ported to new area
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

private object oMzenska;

void reset_room ();

//-------------------------------------------------------------------

/*
 * Function name : m_exit_up
 * Description   : Prevent the player from entering the monastery
 *                 when they are not a monk or a wizard.
 *
 */

int m_exit_up ()
{
  object oMe = this_player ();

  if (!present (oMzenska)) return (FALSE);

  if (dg_is_wizard (oMe))
  {
    oMe->catch_msg (
      XCTNAME (oMe, oMzenska) + " slides respectfully out of your way.\n" +
      "You hear a whisper in your mind: Welcome, immortal.\n");
    return (FALSE);
  };

  if (m_is_monk (oMe))
  {
    oMe->catch_msg (
      XCTNAME (oMe, oMzenska) + " slides out of your way.\n");
    return (FALSE);
  };

  oMe->catch_msg (
    XCTNAME (oMe, oMzenska) + " slithers across your path.\n");
  say (
    QCTNAME (oMzenska) + " slithers across the path of " +
    QTNAME (oMe) + ", blocking " +
    QPOS (oMe) + " path.\n");

  oMzenska->command ("emote hisses threateningly.");

  return (TRUE);
}

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("stairwell");
  set_long  ("Aged blocks of rough stone make up the walls " +
             "of this circular stairwell. Smooth, worn stone steps " +
             "ascend into the darkness above. " +
             dg_embed_composite () +
             "To the west is the northern end of a great hall.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_lower_north", "west");
  add_exit ("stair_upper", "up", &m_exit_up ());

  dg_add_entrance ("up", "You descend the circular stairwell.");

  m_item_stair_worn ();

  reset_room ();
}

//-------------------------------------------------------------------

void reset_room ()
{
  if (!oMzenska)
  {
    oMzenska = dg_clone_here (M_PATH_NPC + "/mzenska", "arm_me",
      "Lying at the base of the stair is a long, sinuous fire " +
      "lizard, casually observing his surroundings with ruby-red eyes. ");
  };

  if (!present (oMzenska))
  {
    oMzenska->move_living ("away", this_object ());
  };
}

int m_is_food (object oItem)
{
  return ((function_exists ("create_food", oItem)) &&
          (oItem->query_amount () > 0));
}

mixed m_prevent_food()
{
  if (!present (oMzenska)) return (FALSE);

  return oMzenska->query_the_name() + " stares at you and growls unhappily.\n" +
    "You decide you better leave " + oMzenska->query_the_possessive_name() +
    " food alone.\n";
}

void enter_inv(object oItem, object oFrom)
{
  if (!m_is_food(oItem)) return;

  oItem->add_prop(OBJ_M_NO_GET, &m_prevent_food());
}

void leave_inv(object oItem, object oTo)
{
  if (!m_is_food(oItem)) return;

  if (!present (oMzenska))
  {
    oItem->remove_prop(OBJ_M_NO_GET);
  }    
}

//-------------------------------------------------------------------

