/*******************************************************************\
| DORMITORY.C                                                       |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 00/12/26 Manat	Fixed a typo
 * 01/04/22 Manat	Added a mirror
 * 01/05/11 Manat	Fixed mirror description
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/04 Arandir     Polished up and bugfixed
 * 03/07/24 Arandir     Simplified the sleep and wake up tests
 * 03/10/08 Arandir     Fixed the check for taking multiple items
 * 03/12/25 Arandir     Fixed parsing of return with no arguments
 * 04/03/06 Arandir     A minor typo when returning items
 * 19/07/03 Ckrik Added guardian to prevent exiled monks from
 *                accessing armoury
 *
 */

#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;
inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

// This is a list of objects that monks can take from the racks

private string *asEquipment = ({ M_PATH_OBJ + "/belt",
                                 M_PATH_OBJ + "/pants",
                                 M_PATH_OBJ + "/robe",
                                 M_PATH_OBJ + "/sandals",
                                 M_PATH_OBJ + "/shirt" });

// This mapping keeps the list of people who took something from
// the racks. The key is the person name plus the object name,
// the value is the time when the item was taken.

private mapping mEquipmentTaken = ([ ]);

// Kunlao, the armoury guardian
private object oKunlao;

//-------------------------------------------------------------------

string m_equipment_names ()
{
  return (COMPOSITE_WORDS (asEquipment->query_pname ()));
}

//-------------------------------------------------------------------

int m_action_return (string sWhat)
{
  object oMe = this_player ();
  object oItem;
  int    iResult, iItem, iItems;

  notify_fail (capitalize (query_verb()) + " what ?\n");

  if (!strlen (sWhat)) return (FALSE);
  if (!parse_command (sWhat, oMe, "%o", oItem)) return (FALSE);
  if (!oItem) return (FALSE);

  iItems = sizeof (asEquipment);
  for (iItem = 0 ; iItem < iItems ; iItem ++)
    if (oItem->id (asEquipment [iItem]))
      break;

  if (iItem < iItems)
  {
    oItem->remove_me ();
    write ("You return the " + oItem->short () + " to the racks.\n");
    say (QCTNAME (oMe) + " returns " + LANG_ADDART (oItem->short ()) + " to the shelves.\n");
    oItem->remove_object ();

    mEquipmentTaken = m_delete (mEquipmentTaken, dg_get_name (oMe) + ":" + asEquipment [iItem]);
  }
  else
  {
    write ("There is no place for the " + oItem->short () + " in the racks.\n");
  }

  return (TRUE);
}


int m_action_get (string sWhat)
{
  object oMe = this_player ();
  object oItem;
  string *asItems;
  string *asAdjectives;
  string sItem, sAdjective;
  int    iResult, iItem;

  notify_fail (capitalize(query_verb()) + " what ?\n");

  if (!strlen (sWhat)) return (FALSE);

  asItems = asEquipment->query_name ();
  if (parse_command (sWhat, ({ }), "%s %p", sAdjective, asItems))
  {
    sItem = asItems [0];
  }
  else
  {
    sItem = sWhat;
    sAdjective = "";
  }

  // See whether the item in question is one of those in the racks.

  for (iItem = 0 ; iItem < sizeof (asEquipment) ; iItem ++)
  {
    if (asEquipment [iItem]->id (sItem))
    {
      sItem = asEquipment [iItem];
      break;
    }
  }

  if (iItem >= sizeof (asEquipment)) return (FALSE);

  // Check that it is a monk who is taking the item ...

  if (!m_is_monk (oMe))
  {
    write ("These items are reserved for members of the Order.\n");
    return (TRUE);
  }

  // Check that the monk does not have the item yet ...

  if (oItem = present (sItem, oMe))
  {
    write ("You already have " + LANG_ADDART (oItem->short()) +
           ". Taking another one would be greedy. You could, " +
           "however, return the " + oItem->short () + " and " +
           "then get a new one.\n");
    return (TRUE);
  }

  // One can only take each item once every three hours.

  if (mEquipmentTaken [dg_get_name (oMe) + ":" + sItem] > (time () - 3*3600))
  {
    write ("You recently got the item from the rack. It " +
           "would be unlawful to take more.\n");
    return (TRUE);
  }

  // Create the item in question ...

  DG_FIXUID;
  oItem = clone_object (sItem);

  // If an adjective was specified, try to set it. A failure here
  // is not handled by write because it can well be that an item
  // in the room rather than in the racks was meant.

  if (sAdjective != "")
  {
    iResult = FALSE;
    iResult = oItem->m_set_adjective (sAdjective);
    if (!iResult)
    {
      asAdjectives = 0;
      asAdjectives = oItem->m_get_adjectives ();
      if (pointerp (asAdjectives))
      {
        notify_fail ("There is no such " + oItem->m_short () + ". " +
                     "You can select from " +
                     COMPOSITE_WORDS (asAdjectives) + " " +
                     oItem->m_short () + ".\n");
      }
      else
      {
        notify_fail ("There is no such " + oItem->m_short () + ".\n");
      }

      oItem->remove_object ();
      return (FALSE);
    }
  }
  else
  {
    oItem->m_random_adjective ();
  }

  write ("You pick " + LANG_ADDART (oItem->short ()) + " from the racks.\n");
  say (QCTNAME(oMe) + " picks " + LANG_ADDART (oItem->short ()) + " from the shelves.\n");

  if (oItem->move (oMe)) oItem->move (this_object ());

  mEquipmentTaken [dg_get_name (oMe) + ":" + sItem] = time ();

  return (TRUE);
}

//-------------------------------------------------------------------

int m_exit_armoury ()
{
  object oMe = this_player ();
  if (m_is_monk (oMe) || dg_is_wizard (oMe))
  {
    if (m_is_monk (oMe) && m_is_punished (oMe, M_PUNISH_EXILE))
    {
      if (!present(oKunlao))
      {
        return (FALSE);
      }
      else
      {
        oKunlao->command("sigh deeply");
        oKunlao->command("say I am sorry " +
          DG_GENDER_SWITCH(oMe, "brother", "sister") +
          " " + oMe->query_name() + " but the council has exiled you " +
          "from the monastery. I cannot allow you to pass until " +
          "you are once again in the council's good graces.");
        return (TRUE);
      }
    }
    return (FALSE);
  }
  else
  {
    write ("You may not enter there.\n");
    return (TRUE);
  }
}

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("dormitory by the mirror");
  set_long  ("Low wooden pallets are arranged evenly " +
             "all around the floor. This room is dark and " +
             "quiet, and has a very restful air to it. The basalt " +
             "blocks of the walls are lined with dry reeds to " +
             "keep out the cold air of the night, allowing those " +
             "who rest to wander down the peaceful venues of sleep. " +
             dg_embed_composite() +
             "On the west wall stands an ornamented mirror and the " +
             "racks along the east wall contain clothing worn by members " +
             "of the Order: " + m_equipment_names () + ". A small doorway " +
             "leads south into a cleanly-swept room.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_top", "north");
  add_exit ("armoury", "south", &m_exit_armoury ());

  add_item (({ "pallet", "pallets", "bed", "beds" }),
            "They are simple wood-slat pallets, covered in " +
            "soft, thin bedding. Though simple, they look " +
            "comfortable and warm.\n");
  add_item (({ "block", "blocks", "wall", "walls" }),
            "The walls consist of great basalt stone blocks. " +
            "The spaces between them are filled with dry " +
            "reeds, so there is little draft.\n");
  add_item (({ "reed", "reeds" }),
            "They are dry with age.\n");
  add_item (({ "rack", "racks", "clothes", "shelves" }),
            "The rack on the east wall hold the standard " +
            "garments of the Dragon Order. They are simple " +
            "and comfortable, and free to those members who " +
            "wish to use them.\n");
  add_item (({ "floor", "ground" }),
            "Evenly spaced on the wooden floor of this " +
            "long room are simple pallets. A thin silvery " +
            "thread inset in the floor boards winds along the " +
            "isle between the pallets, forming a writing.\n");
  add_item (({ "writing", "letters", "thread" }),
            "The dreams grow like slow ice ...\n");

  dg_clone_here (M_PATH_OBJ + "/mirror");
}

//-------------------------------------------------------------------

void m_check_start (object oWho)
{
  if (oWho->query_default_start_location () == MASTER_OB (this_object ()))
  {
    // One can only start here if they are a monk and not punished.

    if (!m_is_monk (oWho))
    {
      write ("You can no longer sleep in the monastery since " +
             "you are not a member of the Dragon Order.\n");
      oWho->set_default_start_location (oWho->query_def_start ());
    }
    else if (m_is_punished (oWho, M_PUNISH_EXILE))
    {
      write ("You may not sleep in the monastery as long " +
             "as you are exiled from the Dragon Order.\n");
      oWho->set_default_start_location (oWho->query_def_start ());
    }
  }
}


int m_action_start (string sWhere)
{
  object oMe = this_player ();

  if (sWhere == "here")
  {
    if (m_is_monk (oMe))
    {
      if (m_is_punished (oMe, M_PUNISH_EXILE))
      {
        write ("You may not sleep in the monastery as long " +
               "as you are exiled from the Dragon Order.\n");
      }
      else
      {
        write ("You pick a pallet where you will rest from now on.\n");
        say (QCTNAME (oMe) +" chooses a pallet for " + QOBJ (oMe) + "self.\n");
        oMe->set_default_start_location (MASTER);
      }
    }
    else
    {
      write ("Only a member of the Dragon Order can sleep here.\n");
    }

    return (TRUE);
  }

  notify_fail (capitalize(query_verb()) + " where ?\n");
  return (FALSE);
}

//-------------------------------------------------------------------

void enter_inv (object oWho, object oFrom)
{
  if ((interactive (oWho)) &&
      (!objectp (oFrom)))
  {
    say (QCNAME (oWho) + " awakens and gets up from " +
         QPOS (oWho) + " pallet.\n");
    set_alarm (1.0, 0.0, &m_check_start (oWho));
  }

  ::enter_inv (oWho, oFrom);
}


void leave_inv (object oWho, object oWhere)
{
  if ((interactive (oWho)) &&
      (!objectp (oWhere)) &&
      (m_is_monk (oWho)) &&
      (oWho->query_hp () > 0))
  {
    say (QCTNAME (oWho) + " lies down on " +
         QPOS (oWho) + " pallet and goes to sleep.\n");
  }

  ::leave_inv (oWho, oWhere);
}

void reset_room ()
{
  if (!oKunlao)
  {
    oKunlao = dg_clone_here (M_PATH_NPC + "/kunlao", "arm_me",
      "A tall musclebound monk is diligently cleaning the room. ");
  };

  if (!present (oKunlao))
  {
    oKunlao->move_living ("away", this_object ());
  };
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();

  add_action (m_action_start, "start");
  add_action (m_action_get, "get");
  add_action (m_action_get, "pick");
  add_action (m_action_get, "take");
  add_action (m_action_return, "return");
}

//-------------------------------------------------------------------

