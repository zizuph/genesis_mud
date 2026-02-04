/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "western"
#define DIR2 "east"

create_room()
{
#include "cloissidedesc.h"
    add_exit(MANSION + "crt/clois11", "north", 0);
    add_exit(MANSION + "crt/clois31", "south", 0);
    add_exit(MANSION + "crt/gard22", "east", 0);
  }
