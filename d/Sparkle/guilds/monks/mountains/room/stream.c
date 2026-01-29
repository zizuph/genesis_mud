/*******************************************************************\
| STREAM.C                                                          |
\*******************************************************************/

/*
 * 02/07/21 Arandir	Created
 *
 */

#include <macros.h>

#include "../defs.h"

inherit DG_ROOM_BASE;

//-------------------------------------------------------------------

#define MT_SHORE_ROOM   DG_PATH + "/meadows/room/meadows_3"

void mt_wash_downstream (object oItem);

//-------------------------------------------------------------------

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("a stream");
  set_long  ("A stream.\n");
}

//-------------------------------------------------------------------

/*
 * Function name : enter_inv
 * Description   : Anything that enters this room will be evicted
 *                 in the meadows later on, as if the stream
 *                 washed it there.
 *
 */

void enter_inv (object oItem, object oFrom)
{
  oItem->set_no_merge (TRUE);
  ::enter_inv (oItem, oFrom);
  set_alarm (20.0 + itof (random (10)), 0.0, &mt_wash_downstream (oItem, oFrom));
}

/*
 * Function name : mt_wash_downstream
 * Description   : Used to send small items dropped on the bridge
 *                 through the planks and downstream to the meadows.
 *
 */

void mt_wash_downstream (object oItem)
{
  tell_room (MT_SHORE_ROOM,
    "The stream washes " + LANG_ASHORT (oItem) + " ashore.\n");

  oItem->set_no_merge (FALSE);
  oItem->move (MT_SHORE_ROOM, MOVE_SUBLOC_ALWAYS);
}

//-------------------------------------------------------------------
