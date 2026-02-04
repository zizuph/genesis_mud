/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "northwest"
#define DIR2 "southeast"

create_room()
{
#include "gardendesc.h"
    add_exit(MANSION + "crt/clois21", "west", 0);
    add_exit(MANSION + "crt/gard23", "east", 0);
    add_exit(MANSION + "crt/clois12", "north", 0);
    add_exit(MANSION + "crt/gard32", "south", 0);
    add_exit(MANSION + "crt/well", "southeast", 0);
  }
