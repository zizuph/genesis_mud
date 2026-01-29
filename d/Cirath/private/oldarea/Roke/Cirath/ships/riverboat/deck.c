inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>
#include <ss_types.h>
#define BOATS "/d/Roke/Cirath/ships/"

void
create_deck()
{
  set_short("On the puny river boat");
  set_name("water");
  set_long(BS(
    "You are standing on the deck of the puny riverboat. The boat is "+
    "made of wood and doesn't look very safe. But then, what could go "+
    "wrong on this little journey across the river?\n",60));

  add_exit(BOATS+"riverboat/cabin", "aft", 0);

  add_prop("_room_i_no_dig",1);
}

