/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "northern"
#define DIR2 "south"

create_room()
{
#include "cloissidedesc.h"
    add_exit(MANSION + "crt/clois11", "west", 0);
    add_exit(MANSION + "crt/clois13", "east", 0);
    add_exit(MANSION + "crt/gard22", "south", 0);
  }
