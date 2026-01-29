#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

void reset_room();

static object stuff;

public void
create_gondor()
{
    set_short("west graves");
    set_long(BSN("You are right beside a big gravemound, it is " +
        "covered with white flowers. You also notice a tombstone " +
        "at your feet. East of here the road continues north " +
        "and south."));
    add_exit(ROH_DIR + "road/graves", "east", 0);
    add_item(({"flower", "flowers", "white flower", "white flowers"}),
        BSN("When you examine the flower, you become aware of that " +
        "you were taught, in your youth, by an old teacher, that " +
        "this flower is called 'Evermind'. The " +
        "flower was called 'Simbelmyne' by the Elves. They say that " +
        "the flower blossoms all year around because of the strong " +
        "spirits of the men that have ruled Rohan."));
    add_item("tombstone", BSN(
        "This is an very old tombstone, you can hardly distinguish " +
        "between it and the gravemound. But when you look at it " +
        "very closely you discover that there is a picture carved " +
        "into the tombstone. You also discover a small sign at the " +
        "bottom of the stone."));
    add_item("picture", BSN(
        "You can vagely make out that the picture shows a great " +
        "battle at the plains. It might show a battle between " +
        "humans, but you just do not know."));
    add_item("sign", BSN(
       "You look at the sign, and you can see that there is some " +
       "writing on it. Why not try to read it?"));
    add_cmd_item("sign", "read", BSN(
        "This is the tombstone of King Eorl the Young of Rohan. The " +
        "King died bravely in a fight with the Easterlings in the " +
        "plains. This occured in the Year 2545 of the Third Age. Eorl " +
        "the Young is herein buried with his horse Felarof, the first " +
        "tamed Meara-horse."));

    set_up_herbs( ({ HERB_DIR + "simbelmyne",
                     ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                  ({ "flowers", "ground", }), 3);
    reset_room();
}

void
reset_room()
{
    if (!objectp(stuff))
    {
        stuff = clone_object(WEP_DIR + "knife");
        stuff->move(TO);
    }
    set_searched(-2);
}

