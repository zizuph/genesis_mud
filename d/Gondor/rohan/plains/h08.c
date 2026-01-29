#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain.c";

#include "/d/Gondor/defs.h"

public void
create_plain()
{
    set_geo("flat");
    set_wet("wet");
    set_grass("thick dark green");
    set_land("the Westfold");
    set_where("south");
    set_special(5);
    set_river_name("Snowbourn");
    set_rhard(1);
    set_rwhere("south");
    set_extraline("On the far bank of the river you can see the town Edoras.");

    add_exit("i08","north", 0, 6);
    add_exit("h09","east",  0, 6);
    add_exit(ROH_DIR + "road/crossroad","south", crossing, 7);
    add_exit("h07","west",  0, 6);

    add_item(({"edoras","town"}), BSN(
        "Edoras, the capital of Rohan, lies on a hill south of the Snowbourn. "
      + "A mighty wall encircles it. Within there rise the roofs of houses; "
      + "and in the midst, set upon a green terrace, there stands aloft a "
      + "great hall of Men. It seems to be thatched with gold, golden, too, "
      + "are the posts to it's doors."));
    add_item(({"stream","river","snowbourn"}), BSN(
        "The Snowbourn runs down swiftly into the plain, and at the foot of "
      + "the hills turns across your path in a wide bend, flowing away to "
      + "the east to feed the Entwash far off in its reed-choked beds. Over "
      + "the stream there is a ford between banks much trampled by the "
      + "passage of horses."));
    add_item(({"ford"}), BSN(
        "Over the stream there is a ford between low banks much trampled by "
      + "the passage of horses. Across the ford, you can see a wide track "
      + "leading towards Edoras and a road running from the west to the east."));

    set_drink_from( ({"stream","river","snowbourn"}) );
}
