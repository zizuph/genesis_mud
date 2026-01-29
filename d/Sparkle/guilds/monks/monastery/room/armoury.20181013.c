/*******************************************************************\
| ARMOURY.C                                                         |
\*******************************************************************/

/*
 * 98/??/?? Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/03/30 Arandir     Polished up
 * 03/09/07 Arandir     Fixed a bug with too many guardians
 * 03/09/13 Arandir     Added shelves for dropped items
 * 03/09/14 Arandir     Rewrote the logging mechanism
 * 03/09/16 Arandir     Fixed a bug in the logging
 * 04/08/16 Arandir     Support for sorting at armageddon
 * 10/09/17 Lavellan    Added fourth shelf 
 *
 */

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;
inherit DG_PLAYER_LIBS;

//-------------------------------------------------------------------

private static object oShelfArmours = 0;
private static object oShelfWeapons = 0;
private static object oShelfGeneral = 0;
private static object oShelfGlowarm = 0;


private static object oTrashcan = 0;

private static object oGuardian = 0;

private static mapping mRoomTake = ([ ]);
private static mapping mRoomDrop = ([ ]);

void reset_room ();

//-------------------------------------------------------------------

object m_get_shelf_armours () { return (oShelfArmours); }
object m_get_shelf_weapons () { return (oShelfWeapons); }
object m_get_shelf_general () { return (oShelfGeneral); }
object m_get_shelf_glowarm () { return (oShelfGlowarm); }
object m_get_trashcan () { return (oTrashcan); }

//-------------------------------------------------------------------

void create_room ()
{
  // The order of cloning here is made so that the top
  // shelf is also the first, the middle shelf is
  // second and the bottom shelf is third.

  oShelfGlowarm = dg_clone_here (M_PATH_OBJ + "/armoury_shelf_glw");
  oShelfGlowarm->m_configure_shelf (({ "new", "east", "eastern", 
        "glowing", "glow", "glowing", "lasting", "armour", "armours" }),
                                    "shelf for lasting armours", "on the eastern wall is the shelf for armours which could last a while");
  oShelfGeneral = dg_clone_here (M_PATH_OBJ + "/armoury_shelf_etc");
  oShelfGeneral->m_configure_shelf (({ "bottom", "general" }),
                                    "shelf for general items", "At the bottom is the shelf for general items");
  oShelfWeapons = dg_clone_here (M_PATH_OBJ + "/armoury_shelf_wep");
  oShelfWeapons->m_configure_shelf (({ "middle", "weapon", "weapons" }),
                                    "shelf for weapons", "In the middle is the shelf for weapons");
  oShelfArmours = dg_clone_here (M_PATH_OBJ + "/armoury_shelf_arm");
  oShelfArmours->m_configure_shelf (({ "top", "topmost", "armour", "armours",
        "non-glowing", "non-lasting armours" }),
                                    "shelf for armours", "Topmost is the shelf for armours");

  oTrashcan = dg_clone_here (M_PATH_OBJ + "/trashcan");

  set_short ("armoury");
  set_long  ("The walls of this stark, clean room are made of " +
             "rough white stone. Set in the south wall are " +
             "three massive shelves. " +
             VBFC ("dg_get_description:" + file_name (oShelfArmours)) + " " +
             VBFC ("dg_get_description:" + file_name (oShelfWeapons)) + " " +
             VBFC ("dg_get_description:" + file_name (oShelfGeneral)) + " " +
             "A new shelf has recently been constructed; " +
             VBFC ("dg_get_description:" + file_name (oShelfGlowarm)) + " " +
             "In the corner of the room is a trashcan.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("dormitory", "north");

  dg_add_entrance ("north", "You enter the cool, dark armoury.");

  reset_room ();
}
    
//-------------------------------------------------------------------

void m_log_transfer (object oWho, object *aoItems, string sDirection)
{
  string sName, sMessage;

  if (present (oGuardian) &&
      (sizeof (aoItems) > 0))
  {
    if (!dg_is_junior (oWho) &&
        !dg_is_wizard (oWho) &&
        CAN_SEE (oGuardian, oWho) &&
        CAN_SEE_IN_ROOM (oGuardian))
    {
      if (m_is_monk (oWho)) sName = dg_get_name (oWho);
                       else sName = LANG_ADDART (dg_get_nonmet_name (oWho));
    }
    else sName = "someone";

    sMessage = capitalize (sName) + " " +
               sDirection + " " +
               COMPOSITE_DEAD (aoItems) + ".";

    oGuardian->m_note_message (sMessage);
  }
}


void m_log_player (object oWho)
{
  string sWho = dg_get_name (oWho);
  object *aoTake = filter (mRoomTake [sWho], objectp);
  object *aoDrop = filter (mRoomDrop [sWho], objectp);

  m_log_transfer (oWho, aoTake, "took");
  m_log_transfer (oWho, aoDrop, "left");

  mRoomTake = m_delete (mRoomTake, sWho);
  mRoomDrop = m_delete (mRoomDrop, sWho);
}


void m_observe_take (object oWho, object oWhat)
{
  string sWho;

  if (living (oWho))
  {
    sWho = dg_get_name (oWho);
    if (member_array (sWho, m_indexes (mRoomTake)) < 0)
      mRoomTake += ([ sWho : ({ }) ]);
    if (member_array (sWho, m_indexes (mRoomDrop)) < 0)
      mRoomDrop += ([ sWho : ({ }) ]);
    if (member_array (oWhat, mRoomDrop [sWho]) < 0)
    {
      mRoomTake [sWho] += ({ oWhat });
    }
    else
    {
      mRoomDrop [sWho] -= ({ oWhat });
    }
  }
}


void m_observe_drop (object oWho, object oWhat)
{
  string sWho;

  if (living (oWho))
  {
    sWho = dg_get_name (oWho);
    if (member_array (sWho, m_indexes (mRoomTake)) < 0)
      mRoomTake += ([ sWho : ({ }) ]);
    if (member_array (sWho, m_indexes (mRoomDrop)) < 0)
      mRoomDrop += ([ sWho : ({ }) ]);
    if (member_array (oWhat, mRoomTake [sWho]) < 0)
    {
      mRoomDrop [sWho] += ({ oWhat });
    }
    else
    {
      mRoomTake [sWho] -= ({ oWhat });
    }

    oGuardian->m_notify_drop ();
  }
  else
  {
    oGuardian->m_notify_enter ();
  }
}

//-------------------------------------------------------------------

void enter_inv (object oWhat, object oFrom)
{
  ::enter_inv (oWhat, oFrom);
  m_observe_drop (oFrom, oWhat);
}


void leave_inv (object oWhat, object oWhere)
{
  ::leave_inv (oWhat, oWhere);
  if (living (oWhat)) m_log_player (oWhat);
                 else m_observe_take (oWhere, oWhat);
}


void reset_room ()
{
  if (oGuardian == 0) oGuardian = dg_clone_here (M_PATH_NPC + "/shisa");
  if (!present (oGuardian)) oGuardian->move_living ("away", this_object ());
}

//-------------------------------------------------------------------

