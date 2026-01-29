/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("valley");
    set_long("You are in the valley which goes east straight towards the " +
             "Misty Mountains. Its green vegetation is a big contrast to "+
             "the dark grey colours of the peaks. To the west, the valley "+
             "goes towards the Great East "+
             "Road.\n");

    add_item("valley", "This is a fair green valley. It is mostly filled with "+
                       "green bushes. It is nice and peaceful here although "+
                       "the nearby mountains reminds you that there may be " +
                       "danger close.\n");
    add_item("vegetation", "The valley is mostly filled with the green bushes.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
                          "danger brooding there.\n");
    add_item(({"bushes", "bush"}), "You see ordinary green bushes all "+
                    "around. They all seem to grow well except maybe one "+
                    "to the south that looks a bit damaged. Perhaps just "+
                    "some animals?\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit("/d/Rhovanion/common/shirelink", "west",    0,    2);
    add_exit(MISTY_DIR+"p2", "east",    0,    3);

}

void
init()
{
  ::init();
  add_action("enter_bushes", "enter");
}

int
enter_bushes(string str)
{
  NF("Enter what?\n");
  if((str != "bushes") && (str != "bush")) return 0;
  tell_room(MISTY_DIR+"g1", QCTNAME(TP)+" jumps in from the bushes.\n");
  TP->catch_msg("You wade your way through the bushes to the other side.\n");
  TP->move_living("M", MISTY_DIR+"g1", 1);
  tell_room(TO, QCTNAME(TP)+" wades "+HIS(TP)+" way through the bushes.\n");
  return 1;
}
