/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "southern"
#define DIR2 "north"

create_room()
{
#include "cloissidedesc.h"
    add_exit(MANSION + "crt/clois41", "west", 0);
    add_exit(MANSION + "crt/clois43", "east", 0);
    add_exit(MANSION + "crt/gard32", "north", 0);
  }
