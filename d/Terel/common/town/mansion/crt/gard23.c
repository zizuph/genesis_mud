/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "northeast"
#define DIR2 "southwest"

create_room()
{
#include "gardendesc.h"
    add_exit(MANSION + "crt/gard22", "west", 0);
    add_exit(MANSION + "crt/clois24", "east", 0);
    add_exit(MANSION + "crt/clois13", "north", 0);
    add_exit(MANSION + "crt/gard33", "south", 0);
    add_exit(MANSION + "crt/well", "southwest", 0);
  }
