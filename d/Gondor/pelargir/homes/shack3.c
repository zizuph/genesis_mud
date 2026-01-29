#pragma strict_types

inherit "/d/Gondor/std/room";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static int Found = random(2);

public void
create_gondor()
{
    set_short("in a run-down shack");
    set_long(BSN("You are in an old run-down shack. Although it does not "
      + "look like anyone takes care of it, there are a few signs of "
      + "recent use, like the bits of rat droppings scattered here and "
      + "there, and the scratchings on the walls."));

    add_prop(ROOM_I_INSIDE,1);

    add_item( ({"floor", "ground", }),  BSN("From the dust on this "
        + "floor you believe even the spiders would leave tracks. "
        + "Between the boards making up the floor, large cracks are "
        + "showing.")); 
    add_item( ({"boards", "cracks", }), BSN("Large cracks are opening "
        + "between the boards making up the floor, so large that it "
        + "is possible to see the earth beneath the boards."));
    add_item( ({ "earth", "dirt", }), "Just plain dirt showing "
        + "through the cracks in the floor.\n");
    add_item("scratchings", BSN("These scratchings seem to have been "
      + "made by a small child as they are poorly made pictures of fish, "
      + "cats, people, and rats. Nothing really interesting."));
    add_item( ({ "droppings", "rat droppings", }), "They are droppings " +
        "left behind by rats.\n");

    add_exit(PELAR_DIR + "streets/peddlers03", "southeast", 0);

    add_prop(OBJ_S_SEARCH_FUN, "search_here");

    enable_reset(200);
}

public string
search_here(object tp, string str)
{
    object  nail;

    if (!strlen(str))
        return 0;

    switch (LOW(str))
    {
    case "earth":
    case "dirt":
    case "floor":
    case "cracks":
        if ((tp->query_skill(SS_AWARENESS) < (10 + random(20))) ||
            Found)
            return "You look through the cracks in the floor, but you "
                + "do not find anything of interest.\n";
        nail = clone_object(OBJ_DIR + "nail");
        nail->set_heap_size(4 + random(5));
        nail->add_prop(OBJ_M_NO_BUY, 1);
        if (nail->move(tp))
            if (nail->move(TO))
                nail->move(TO, 1);
        Found = 1;
        return "Through one of the cracks, you notice a few nails "
            +  "lying beneath the floor boards.\n"
            +  "You decide to pick them up.\n";
        break;
    default:
        return 0;
        break;
    }
}

public void
reset_room()
{
    if (Found)
        Found = random(2);
}
