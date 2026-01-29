/*******************************************************************\
| ROOM.C                                                            |
+-------------------------------------------------------------------+
| Base room module for the domain.                                  |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Created
 *
 */

#include <language.h>
#include <stdproperties.h>

#include "defs.h"

inherit "/std/room";

inherit S_LIB_TEXT;
inherit S_LIB_CLOCK;
inherit S_LIB_PLAYER;
inherit S_LIB_LOGGING;

//-------------------------------------------------------------------

// The fragments are included rather than inherited
// because LPC cannot handle diamond inheritance

#include "room_item.h"
#include "room_clock.h"

//-------------------------------------------------------------------

/*
 * Function name : init
 * Description   : Called whenever somebody comes our way.
 *
 */

void init ()
{
  ::init ();

  // Item actions ...
  add_action (s_action_examine, "exa");
  add_action (s_action_examine, "examine");

  // Clock actions ...
  add_action (s_action_time, "time");
}

//-------------------------------------------------------------------

