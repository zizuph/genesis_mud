inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

void
create_room()
{
    set_short("The well room of the House of Stewards");
    set_long(BSN(
        "In the middle of the room is a large well. At its sides, "
      + "one can still see the remains of a wooden frame that was "
      + "used to pull up buckets filled with water. A dark passage "
      + "is leading west, and some stairs are going up, back into "
      + "the kitchen."));

    add_item(({"stairs", "steps", }), BSN(
        "The stairs go up back into the kitchen."));

    add_item(({"remains", "frame", "wooden frame", }), BSN(
        "At the sides of the well there are the remains of a wooden "
      + "frame that was used to pull up buckets filled with water. "
      + "You can still see the lower ends of two wooden beams, but "
      + "they are charred and about a foot's length is what is left "
      + "of each of them."));

    add_item(({"well", }), BSN(
        "The well is a large hole in the ground, surrounded by a small "
      + "bricklayed wall about a two feet high. Looking into the well "
      + "you can see water rushing through a duct not far underground."));

    add_item(({"water", "river", "duct", }), BSN(
        "Inside the well you see water rushing through a duct. It is "
      + "out of reach, though."));

    CELLAR_ROOF
    CELLAR_FLOOR
    CELLAR_WALLS
    CELLAR_STONES

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);

    add_exit(ITH_DIR + "emyn-arnen/palace/cellar", "west", 0, 3);
    add_exit(ITH_DIR + "emyn-arnen/palace/kitchen", "up", 0, 3);
}

void
init()
{
    ::init();

    add_action("enter_well", "enter");
    add_action("enter_well", "jump");
}

int
enter_well(string str)
{
    string  vb = query_verb(),
            dummy;

    if (!str)
    {
        NF(CAP(vb)+(vb == "jump"?" into":"")+" what?\n");
        return 0;
    }

    if (vb == "jump")
    {
        if (sscanf(str, "into %s", dummy) != 1)
        {
            NF("Jump into what?\n");
            return 0;
        }
        str = dummy;
    } 

    if (str != "well")
    {
        NF(CAP(vb)+(vb == "jump"?" into":"")+" what?\n");
        return 0;
    }

    write("Forgetting all caution, you jump into the dark water "
      + "in the well.\n");
    TP->move_living("into the well", ITH_DIR + "emyn-arnen/palace/in_well");
    return 1;
}
