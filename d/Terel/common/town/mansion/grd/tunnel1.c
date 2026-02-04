/* tunnel1 */
/* janus 921029 */

inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include </sys/money.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

create_room()
{
    set_short("tunnel");
    set_long(BS("You are in a dark, dank tunnel dug under the mansion. "+
        "Cold water drops slowly from the ceiling. "+
       "The ceiling is supported by half rotted "+
       "wooden beams, pray that they support the tons of earth and stone "+
       "above your head. \n"));
    add_exit(MANSION + "grd/cellar", "north",0,0);
    add_exit(MANSION + "grd/tunnel","south",0,0);
    add_item(({"area","ground","floor","cellar"}),
               BS("There is a lot of debris and "+
               "pieces of this and that lying around.\n"));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,0);
  }
