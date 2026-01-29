/*******************************************************************\
| MEETING.C                                                         |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 98/07/15 Cirion	Added voting
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up
 * 03/11/07 Arandir     Added a common board exit
 * 03/12/11 Arandir     Added the tree to dance around
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <time.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;
inherit M_VOTING_LIBS;

//-------------------------------------------------------------------

/*
 * Function name : m_tile_touch
 * Function name : m_tile_push
 * Function name : m_tile_kick
 * Description   : A set of actions to make the common board room
 *                 exit a tad less boring than it usually is.
 *
 */

int m_tile_touch (string sArgs)
{
  object oHim = this_player ();

  if ((sArgs != "spot") && (sArgs != "tile") && (sArgs != "wall") && (sArgs != "stone")) return (FALSE);

  write ("You gently touch the smooth stone in the northern wall. " +
         "As your fingertips brush its surface, you feel as if " +
         "you were touching silk rather than stone.\n");
  say (QCTNAME (oHim) + " runs " + QPOS (oHim) + " fingertips " +
       "across a stone in the northern wall.\n");

  return (TRUE);
}


int m_tile_push (string sArgs)
{
  object oHim = this_player ();

  if ((sArgs != "spot") && (sArgs != "tile") && (sArgs != "wall") && (sArgs != "stone")) return (FALSE);

  write ("You push the smooth stone in the northern wall, " +
         "but try as you might, it just refuses to budge. " +
         "Just as you give up and remove your hands from " +
         "the stone, you think you feel a slight looseness. " +
         "As if it could indeed budge and only a stronger " +
         "impulse was needed.\n");
  say (QCTNAME (oHim) + " tries in vain to push a stone in the northern wall.\n");

  return (TRUE);
}


int m_tile_kick (string sArgs)
{
  object oHim = this_player ();

  if ((sArgs != "spot") && (sArgs != "tile") && (sArgs != "wall") && (sArgs != "stone")) return (FALSE);

  write ("You make a step back and aim a hefty kick at the " +
         "smooth stone in the northern wall. Just when your " +
         "foot is about to make contact and you brace yourself " +
         "for the impact, an entire portion of the wall gives way " +
         "in a flash !\n");
  say (QCTNAME (oHim) + " aims a kick at the northern wall but " +
       "before it lands, a portion of the wall gives way in a " +
       "flash and " + QPNOUN (oHim) + " disappears behind it.\n");
  oHim->move_living ("M", "/d/Genesis/start/human/town/common", TRUE, FALSE);
  say (QCTNAME (oHim) + " stumbles into the room as if in a middle " +
       "of a wild kick, with a bewildered expression on " +
       QPOS (oHim) + " face.\n");

  return (TRUE);
}

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("meeting room");
  set_long ("A long, smooth table of polished mahogany extends " +
            "along the length of this warm, sparsely adorned room. " +
            "Running up the stone walls are carved wooden beams painted " +
            "in dull, earth-tone reds. A small round window looks down " +
            "on a garden in the south wall. To the west is the southern " +
            "end of a large hall. A red cloth curtain blocks a doorway " +
            "to the east. An alcove lies to the north.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("council", "east");
  add_exit ("hall_upper_south", "west");
  add_exit ("discuss_recode", "north");
  
  add_item (({ "window", "glass", "glass window", "garden window" }),
            "The window is perfectly round, and about the size " +
            "of a human head. It is made from paper-thin, rose " +
            "tinted glass. It looks out over the peaceful " +
            "gardens below. Framing the window are thin panes " +
            "of wood, and running horizontal across the centre " +
            "is a single oak slat of wood.\n");
  add_item (({ "slat", "oak", "single slat", "oak slat" }),
            "It runs horizontal through the center of the " +
            "circular window.\n");
  add_item (({ "pane", "panes" }),
            "They are panes of rose-tinted glass framed by " +
            "thin panes of wood.\n");

  add_item (({ "wall", "walls", "stone wall", "stone walls" }),
            "The stone walls of this room are rough to the touch, except " +
            "for one slightly smoother spot just opposite the window. " +
            "Parts of the wall are partially obscured by thick " +
            "wooden beams.\n");
  add_item (({ "tile", "smooth tile", "stone", "smooth stone", "spot", "smooth spot" }),
            "One of the stones that make up the northern wall of this " +
            "room appears smoother than the rest. It reminds you of " +
            "the worn down stone tiles of the monastery hall.\n");
  add_item (({ "beam" ,"beams", "wood", "wooden beam", "wooden beams" }),
            "The beams supporting this room are very very " +
            "thick. They are made from strong wood, and are " +
            "painted a dull red-brown colour.\n");

  add_item (({ "curtain", "cloth curtain", "red curtain", "red cloth curtain" }),
            "Beyond the curtain, the elders meditate upon their " +
            "duties.\n");

  add_item (({ "table", "long table", "mahogany table", "polished table" }),
            "This table would be the envy of any lord. " +
            "Centuries old, it has countless layers of beeswax " +
            "rubbed into the surface. The wax traps available " +
            "light and sets the deep reddish hints of the " +
            "mahogany aglow.\n");

  if (TIME2FORMAT (time (), "mmm") == "Dec")
  {
    dg_clone_here (M_PATH_OBJ + "/tree");
  }

  dg_clone_here (M_OBJ_BOARD_MEMBER);
}

//-------------------------------------------------------------------

/*
 * Function name : init
 * Description   : Called whenever somebody comes our way.
 *
 */

void init ()
{
  ::init ();

  m_voting_hook_init ();

  add_action (&m_tile_touch (), "touch", FALSE);
  add_action (&m_tile_push (), "push", FALSE);
  add_action (&m_tile_kick (), "kick", FALSE);
}


void enter_inv (object oWho, object oFrom)
{
  ::enter_inv (oWho, oFrom);
  m_voting_hook_enter_inv (oWho, oFrom);
}

//-------------------------------------------------------------------

