/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "southwest"
#define DIR2 "northeast"

create_room()
{
#include "gardendesc.h"
    add_exit(MANSION + "crt/clois31", "west", 0);
    add_exit(MANSION + "crt/gard33", "east", 0);
    add_exit(MANSION + "crt/gard22", "north", 0);
    add_exit(MANSION + "crt/clois42", "south", 0);
    add_exit(MANSION + "crt/well", "northeast", 0);
  }
