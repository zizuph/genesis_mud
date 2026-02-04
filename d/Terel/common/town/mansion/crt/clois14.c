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
#include "cloiscornerdesc.h"
    add_exit(MANSION + "crt/clois13", "west", 0);
    add_exit(MANSION + "crt/clois24", "south", 0);
  }
