/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "southeast"
#define DIR2 "northwest"

create_room()
{
#include "gardendesc.h"
    add_exit(MANSION + "crt/gard32", "west", 0);
    add_exit(MANSION + "crt/clois34", "east", 0);
    add_exit(MANSION + "crt/gard23", "north", 0);
    add_exit(MANSION + "crt/clois43", "south", 0);
    add_exit(MANSION + "crt/well", "northwest", 0);
  }
