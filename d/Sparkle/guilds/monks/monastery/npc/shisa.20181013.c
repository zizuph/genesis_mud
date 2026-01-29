/*******************************************************************\
| SHISA.C                                                           |
\*******************************************************************/

/*
 * 10/09/17 Lavellan    Sorts armours using new shelf for glowing
 * 10/02/09 (Gorboth)   Disabled armour sorting per player council request 
 * 06/09/02 Arandir     Removed the focus skill
 * 04/08/16 Arandir     Support for sorting at armageddon
 * 03/09/17 Arandir     Fixed a typo
 * 03/09/14 Arandir     Support for sorting items
 * 03/09/11 Arandir     Fixed a typo
 * 03/05/25 Arandir     Polished up
 * 02/05/02 Arandir	Ported to new area without rewrite
 * 98/10/22 Cirion	Created
 *
 */

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

private static string *asMessages = ({ });

private static int iAlarmSort = ALARM_NONE;

//-------------------------------------------------------------------

void m_note_message (string sMessage)
{
  command ("emote writes something down on his clipboard.");
  asMessages += ({ sMessage });

  if (sizeof (asMessages) > 400)
    asMessages -= ({ asMessages [0] });
}


string m_ask_clipboard ()
{
  object oMe = this_object ();
  object oHim = this_player ();

  if (m_is_elder_member (oHim) ||
      m_is_council_member (oHim))
  {
    if (sizeof (asMessages) > 0)
    {
      oHim->catch_msg (XCTNAME (oHim, oMe) + " shows you his clipboard:\n");
      oHim->more (implode (asMessages, "\n"));
      return ("sigh");
    }
    else
    {
      return ("say SorryIDon'tHaveAnythingWrittenDownNow!");
    }
  }
  else
  {
    command ("emote holds his clipboard close to his body.");
    return ("say I'mAfraidYouAreNotAuthorizedToHaveThatInformation.");
  }
}

//-------------------------------------------------------------------

/*
 * Function name : m_sort_container
 * Description   : Does a single move of items to sort the shelves.
 * Returns       : An indication whether a move was done.
 *
 */

int m_sort_container (object oContainer, string sDescription)
{
  object oMe = this_object ();
  object oRoom = environment ();
  object oShelfArmours = oRoom->m_get_shelf_armours ();
  object oShelfWeapons = oRoom->m_get_shelf_weapons ();
  object oShelfGeneral = oRoom->m_get_shelf_general ();
  object oShelfGlowarm = oRoom->m_get_shelf_glowarm ();
  object oTrashcan = oRoom->m_get_trashcan ();
  object *aoItems;
  object *aoGlowarm;
  object *aoArmours;
  object *aoWeapons;
  object *aoGeneral;
  object *aoTrashed;

  aoItems = FILTER_DEAD (all_inventory (oContainer));
  aoItems -= ({ oShelfArmours, oShelfWeapons, oShelfGeneral, oTrashcan,
    oShelfGlowarm });

  if ((ARMAGEDDON->shutdown_active ()) || (sDescription == "trash"))
  {
    aoTrashed = filter (aoItems, operator (!) @ &->check_recoverable ());
    aoTrashed = filter (aoTrashed, operator (!) @ &->check_armour ());
    if (sizeof (aoTrashed))
    {
      tell_room (oRoom,
                 QCTNAME (oMe) + " sighs in resignation, noticing " +
                 COMPOSITE_DEAD (aoTrashed) + " on the " +
                 sDescription + " that should be in the " +
                 "trashcan. He then moves " +
                 DG_AMOUNT_SWITCH (sizeof (aoTrashed), "it", "them") + " there.\n");
      aoTrashed->move (oTrashcan, MOVE_SUBLOC_ALWAYS);
      return (TRUE);
    }
  }

  aoGlowarm = filter (aoItems, &->check_armour ());
  aoGlowarm = filter (aoGlowarm, &->check_recoverable());
  if (sizeof (aoGlowarm) && (oContainer != oShelfGlowarm))
  {
    tell_room (oRoom,
               QCTNAME (oMe) + " gasps in dismay, noticing " +
               COMPOSITE_DEAD (aoGlowarm) + " on the " +
               sDescription + " that should be on the " +
               "shelf for lasting armours. He then moves " +
               DG_AMOUNT_SWITCH (sizeof (aoGlowarm), "it", "them") + " there.\n");
    aoGlowarm->move (oShelfGlowarm, MOVE_SUBLOC_ALWAYS);
    return (TRUE);
  }

  aoArmours = filter (aoItems, &->check_armour ());
  aoArmours = filter (aoArmours, operator (!) @ &->check_recoverable ());
  if (sizeof (aoArmours) && (oContainer != oShelfArmours))
  {
    tell_room (oRoom,
               QCTNAME (oMe) + " sighs in resignation, noticing " +
               COMPOSITE_DEAD (aoArmours) + " on the " +
               sDescription + " that should be on the " +
               "shelf for armours. He then moves " +
               DG_AMOUNT_SWITCH (sizeof (aoArmours), "it", "them") + " there.\n");
    aoArmours->move (oShelfArmours, MOVE_SUBLOC_ALWAYS);
    return (TRUE);
  }

  aoWeapons = filter (aoItems, &->check_weapon ());
  if (sizeof (aoWeapons) && (oContainer != oShelfWeapons))
  {
    tell_room (oRoom,
               QCTNAME (oMe) + " throws his arms up in despair, seeing " +
               COMPOSITE_DEAD (aoWeapons) + " on the " +
               sDescription + " that should be on the " +
               "shelf for weapons. He then moves " +
               DG_AMOUNT_SWITCH (sizeof (aoWeapons), "it", "them") + " there.\n");
    aoWeapons->move (oShelfWeapons, MOVE_SUBLOC_ALWAYS);
    return (TRUE);
  }

  aoItems -= aoGlowarm;
  aoItems -= aoArmours;
  aoItems -= aoWeapons;
  if (sizeof (aoItems) && (oContainer != oShelfGeneral))
  {
    tell_room (oRoom,
               QCTNAME (oMe) + " stomps his foot in anger, noticing " +
               COMPOSITE_DEAD (aoItems) + " on the " +
               sDescription + " that should be on the " +
               "shelf for general items. He then moves " +
               DG_AMOUNT_SWITCH (sizeof (aoItems), "it", "them") + " there.\n");
    aoItems->move (oShelfGeneral, MOVE_SUBLOC_ALWAYS);
    return (TRUE);
  }

  return (FALSE);
}


void m_sort ()
{
  object oRoom = environment ();
  object oShelfArmours = oRoom->m_get_shelf_armours ();
  object oShelfWeapons = oRoom->m_get_shelf_weapons ();
  object oShelfGeneral = oRoom->m_get_shelf_general ();
  object oShelfGlowarm = oRoom->m_get_shelf_glowarm ();

  iAlarmSort = ALARM_NONE;

  // Do not mess up the branching unless you are sure you
  // understand what it does. It is a bit tricky.

  if (!m_sort_container (oRoom, "floor"))
  if (!m_sort_container (oShelfGlowarm, "shelf for lasting armours"))
  if (!m_sort_container (oShelfArmours, "shelf for armours"))
  if (!m_sort_container (oShelfWeapons, "shelf for weapons"))
  if (!m_sort_container (oShelfGeneral, "shelf for general items"))
  {
    return;
  }

  iAlarmSort = set_alarm (5.0 + itof (random (5)), 0.0, &m_sort ());
}


void m_notify_drop ()
{
  // We start sorting a little while after the last item is dropped.

  if (iAlarmSort != ALARM_NONE) remove_alarm (iAlarmSort);
  iAlarmSort = set_alarm (45.0 + itof (random (30)), 0.0, &m_sort ());
}


void m_notify_enter ()
{
  // Entering at armageddon prompts sorting to resort glowing items.

  if (ARMAGEDDON->shutdown_active ())
    if (iAlarmSort == ALARM_NONE)
      iAlarmSort = set_alarm (10.0 + itof (random (10)), 0.0, &m_sort ());
}

void m_ask_sort ()
{
  // Asked to sort
  set_alarm(0.5, 0.0, &command("emote peers around."));
  set_alarm(1.5, 0.0, &m_sort());

}

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("shisa");
  set_gender (G_MALE);
  set_race_name ("gnome");
  set_adj (({ "tiny", "concerned" }));
  set_long ("This gnome is holding a clipboard and is constantly " +
            "scanning the floor of the room.\n");

  m_init ();
  m_equip (({ 0, 20 + random (90) }));
  m_stature (75, 30);

  set_skill (SS_UNARM_COMBAT, 40);
  set_skill (SS_DEFENCE, 10);
  set_skill (M_SKILL_STRIKE, 25);
  set_skill (M_SKILL_PLEXUS, 25);
  set_skill (SS_AWARENESS, 90);
  set_skill (SS_BLIND_COMBAT, 90);

  set_act_time (10);
  add_act ("emote frowns.");
  add_act ("emote looks at the shelves.");
  add_act ("emote paces up and down the room.");
  add_act ("emote scratches his head with his pen.");
  add_act ("emote knits his brows and looks concerned.");
  add_act ("emote writes down something on his clipboard.");

  add_ask (({ "clipboard", "inventory", "stuff" }),
           VBFC_ME ("m_ask_clipboard"), ASK_COMMAND);

  add_ask (({ "sort", "shelves" }), VBFC_ME("m_ask_sort"));
}

//-------------------------------------------------------------------

