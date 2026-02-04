/* cloister corner */

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

#define DIR1 "eastern"
#define DIR2 "west"

create_room()
{
#include "cloissidedesc.h"
    add_exit(MANSION + "crt/clois14", "north", 0);
    add_exit(MANSION + "crt/clois34", "south", 0);
    add_exit(MANSION + "crt/gard23", "west", 0);
  }
