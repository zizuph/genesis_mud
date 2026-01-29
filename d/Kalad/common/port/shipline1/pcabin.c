#include "../default.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/room";

void
create_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Captain's Private Cabin");
    set_long("This is the private chamber's belonging to the "+
      "captain of this vessel. It is small and not too surprising "+
      "without elaborate displays. There is a lantern hanging from "+
      "the ceiling and a small cozy looking bed in the corner.\n");
    add_item(({"bed", "small bed", "cozy bed"}),
      "It is a small cozy bed. Not too soft but not too firm either.\n");
    add_item(({"bedding", "sheets", "sheet"}),
      "The bedding is a cream colour, which has seen better days.\n");
    add_item(({"pillow", "pillows"}),
      "There is just one pillow that has been fluffed up nicely.\n");
    add_item(({"iron lantern","lantern"}),"It fills the cabin with a soft "+
      "glowing light.\n");
    add_item(({"ceiling", "floor", "flooring", "wall", "walls"}),
      "It is plain hardwood.\n");
    add_exit(PORT + "shipline1/cabin", "out");
}

int
do_emote(string str)
{
  notify_fail("Emote what?\n");
  if(!str)
    return 0;

  say( QCTNAME(this_player()) + " " +str+ "\n" );
  write("You emote: " +METNAME+ " " +str+ "\n");
  return 1;
}

public void
init()
{
    ::init();

    /* Any init code you might have. */
    add_action(do_emote, "emote");
}
