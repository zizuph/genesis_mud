inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

void reset_room();

void
create_gondor()
{
    set_short("east graves");
    set_long(BSN("You are right beside a big gravemound, it is covered with white "
      + "flowers. You also notice a tombstone at your feet. West of here "
      + "the road continues north and south."));
    add_exit(ROH_DIR + "road/graves", "west", 0);
    add_item(({"flower", "flowers", "white flower", "white flowers"}), BSN(
        "When you examine the flower, you remember that a teacher once "
      + "told you, that this flower is called 'Evermind'. "
      + "The flower was also called 'Simbelmyne' by the Elves. They say that "
      + "the flower blossoms all year around because of the strong spirits "
      + "of the men that have ruled Rohan."));
    add_item("tombstone", BSN(
        "This is an old tombstone. You can hardly distinguish it "
      + "from the gravemound. Looking at it closely you discover a picture "
      + "carved into the tombstone. You also find a small sign at the "
      + "foot of the stone."));
    add_item("picture", BSN(
        "You can vagely make out that the picture shows the great battle "
      + "at Meduseld. When you look more carefully at the picture you find "
      + "yourself looking at the winner of the battle. He has his sword "
      + "at his enemy's throat."));
    add_item("sign", BSN(
        "You look at the sign, and you can see that there is some writing "
      + "on it. Why not try to read it?"));
    add_cmd_item("sign", "read", BSN(
        "This is the tombstone of the tenth King of Rohan. His name was " +
        "Frealaf the Wulf killer. The King killed Wulf during the spring after " +
        "the Long winter, in the palace Meduseld. He hunted the last Dunlendings " +
        "down at Isengard. Frealaf died peacefully in the year 2798 of the Third Age."));

    set_up_herbs( ({ HERB_DIR + "simbelmyne",
                     ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                  ({ "flowers", "ground", }), 3);
    reset_room();

}

public void
reset_room()
{
    if (!present("shield", TO))
	clone_object(ARM_DIR + "fsshield")->move(TO);
    set_searched(-2);
}

