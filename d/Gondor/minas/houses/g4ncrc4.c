inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define CLIMB_SKILL	20

void
create_room()
{
    set_short("in a rowan tree in a garden in Minas Tirith");
    set_long(BSN("You are in the lower branches of a big rowan tree "
      + "standing in the southern part of a garden in the Fourth "
      + "Circle of Minas Tirith. The tree rises higher into the air "
      + "above you, but it is impossible to climb any higher."));

    add_item(({"tree", "big tree", "rowan", "rowan tree", "big rowan tree", }),
        BSN("This rowan is the only tree in the garden. Its topmost "
      + "branches almost reach up to the battlements on top of the "
      + "Fourth Wall that borders the garden on the east, but it "
      + "is impossible to climb that high in this tree."));

    add_item(({"wall", "fourth wall", }), BSN(
        "The Fourth Wall of the city borders the garden on the east. It "
      + "rises many yards into the sky, made from huge boulders hewn "
      + "from the same white rock onto which the city has built. The "
      + "top of the wall is even higher than the highest branches of "
      + "this tree."));

    add_item(({"garden", }), BSN(
        "This is a private garden in the Fourth Circle of Minas Tirith. "
      + "It is situated between a mansion to the west and the south and "
      + "the Fourth Wall of the City to the east. It extends further "
      + "to the north until it reaches the city wall there, too."));

    add_exit(MINAS_DIR+"houses/g2ncrc4","down",0,1);

    set_up_herbs(({ SHIRE_HERB_DIR + "treemushroom" }), 
                 ({"tree","rowan","big tree",}), 3);
}

int
do_climb(string str)
{
    object  tp = TP;
    string  vb = query_verb();

    NFN(CAP(vb) + " where?");
    if (!strlen(str))
        return 0;

    if (str == "down")
    {
        tp->move_living("down", MINAS_DIR + "houses/g2ncrc4");
        write("You climb down again.\n");
    }
    else if (str == "up")
        write("You cannot climb any further up in this tree!\n");
    else
        return 0;

    return 1;
}

void
init()
{
    ::init();

    add_action(do_climb, "climb");
}

