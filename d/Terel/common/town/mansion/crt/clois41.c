/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

create_room()
{
    object door;
#include "cloiscornerdesc.h"
    door = clone_object(MANSION + "crt/gard_door2");
    door->move(this_object());
    add_exit(MANSION + "crt/clois42", "east", 0);
    add_exit(MANSION + "crt/clois31", "north", 0);
  }
