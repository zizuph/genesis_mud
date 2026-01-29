inherit "/d/Gondor/pelargir/sewers/sewer.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  thief;

void
reset_room()
{
    if (objectp(thief))
        return;

    thief = clone_object(PELAR_DIR + "npc/yngthief");
    thief->arm_me();
    thief->move_living("down", TO);
}

void
create_sewer()
{
    set_short("the sewer spillway");
    set_extra_long("Where the sewer empties out into the wide river a "
      + "gate is blocking the tunnel. The sewer smell is horrible, but it "
      + "is not so bad here where it mixes a little with the thick river "
      + "air. The bilge of the sewer running past your ankles makes "
      + "a nice slapping, splashing sound as it runs out the end of the "
      + "tunnel and hits the river water thirty feet below.");
    add_item(({"floor","mud","muck"}),BSN("This muck seems to ooze in the "
      + "slow current of the sewer. Hopefully it is only the current that "
      + "makes it move, though you have your doubts."));
    add_item(({"river", "anduin", }), BSN("In the distance you can make "
      + "out a few ships among the waves. If it were not for the smell "
      + "from the sewer you would be content to stand here and gaze at the "
      + "peaceful river all day."));
    add_item(({"grate","grating", "gate", }), BSN("The old grating "
      + "is covered with rust, but it is still sturdy. Touching it would "
      + "be perilous for sure, as upon closer inspection, one can see "
      + "that the rust has made the bars sharp, and the ooze from the "
      + "sewer coats the edges."));

    add_exit(PELAR_DIR + "sewers/grate", "west", 0, 1);
    add_prop(ROOM_I_LIGHT,1);

    reset_room();
}

