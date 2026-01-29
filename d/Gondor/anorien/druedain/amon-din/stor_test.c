inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/din/din_defs.h"

#define FIREWOOD	(RANGER_DIR + "obj/firewood")

//	Global variables
static object  stack;

void
reset_room()
{
    if (objectp(stack))
    {
        stack->set_burn_time(600);
        return;
    }

    stack = clone_object(FIREWOOD);
    stack->add_name(({"log","logs"}));
    stack->set_is_stack();
    stack->set_burn_time(600);
    stack->add_prop(OBJ_M_NO_GET, "The stack of firewood is too heavy to take it.\n");
    stack->add_prop(DIN_I_FIREWOOD, 1);
    stack->move(TO);
}

void
create_room()
{
    set_short("in a long narrow storage building atop Amon Din");
    set_long(BSN("The shadows are quite thick here at the northern"
      + " end of this building. The walls remain bare, and the"
      + " debris upon the floor are even thicker than to the south."
      + " Piles of lumber are stacked in one corner of the room. It"
      + " appears as if the woodstores have run quite low."));
    add_item(({"shadow","shadows"}), BSN(
        "The lack of any natural light source in this building and"
      + " the absence of windows makes for a very dark chamber."));
    add_item(({"building","chamber"}), BSN(
        "This narrow building seems dedicated to the storage of fuel"
      + " for the beacon tower outside. If this place has ever been"
      + " cared for, you would not be able to tell from its current"
      + " state."));
    add_item(({"walls","wall"}), BSN(
        "These brick walls are quite unremarkable, aside from being"
      + " a bit dusty."));
    add_item(("floor"), BSN(
        "In many places the scraps of wood and bark have piled into"
      + " mounds here at the back of this building."));
    add_item(({"debris","scraps","scraps of wood","bark","mounds","mound"}), BSN(
        "It seems that quite a lot of wood comes through this place,"
      + " and the bits that are rotten or dead tend to end up like"
      + " this, in a pile on the floor."));
    add_item(({"pile","piles","pile of lumber","piles of lumber",
               "lumber"}), BSN(
                "Most of the logs have been placed in a single large"
              + " stack of firewood in the corner of the room."));

    add_exit(AMON_DIR + "storage1", "south");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, "A dark, narrow building.\n");

    reset_room();
}

int
do_get(string str)
{
    if (!strlen(str))
        return 0;

    if (str == "log" || str == "logs")
    {
        TP->catch_msg("Where do you want to get a log from?\n");
        return 1;
    }

    else
        return 0;
}

void
init()
{
    ::init();
    add_action(do_get, "get");
    add_action(do_get, "pick");
    add_action(do_get, "take");
}
