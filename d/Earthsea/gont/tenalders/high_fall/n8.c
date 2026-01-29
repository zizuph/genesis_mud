/*
 * coded by Amelia 9/7/97
 * base of cliff northwest in High Fall
 * Four-leaf clover grows here, for the lucky items quest
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/meadow_herbs.h"

private object *goats = allocate(5);

public void
create_herb_room()
{
    set_short("Mountain meadow");
    set_long("The meadow has a thick carpet of green grass " +
        "and flowers, making it an ideal grazing location. To the " +
        "north you see a tall limestone cliff, which reaches " +
        "straight up to the top of the mountain. The path ends " +
        "here due to the surrounding tangle of dense forest " +
        "undergrowth.\n");
    add_item((({"view", "spectacular view"})),
        "You turn and look back down the mountain. From here " +
        "you can see far away to the deep blue sea that " +
        "encircles Gont. The steep flank of the mountain " +
        "to the south is covered in an evergreen forest, " +
        "and at lower elevations you see small farms and " +
        "grazing areas. To your horror you realize that " +
        "some of the inhabited areas are in flames! " +
        "Just off the southeast coastline, there are " +
        "three large longships, with the black and red " +
        "sails of Karego-At!\n");
    add_item((({"cliff", "limestone cliff"})),
        "The cliff towers over the meadow to the north. Only the " +
        "very skilled may climb it, unless you are a mountain goat.\n");
    add_item((({"meadow", "carpet", "grass", "flowers"})),
        "This is a beautiful meadow, with a thick carpet of " +
        "dark green grass and flowers. It is ideal for grazing.\n");
    add_item((({"forest", "trees"})),
        "The forest stands to the southwest, but the meadow is " +
        "clear of trees.\n");
    add_item((({"top", "mountain top"})),
        "It seems that the cliff might reach all the way to the " +
        "top of the mountain, however, you cannot see the top " +
        "from here.\n");
    add_item((({"undergrowth", "tangle", "dense forest undergrowth",
        "forest undergrowth"})),
        "Dense bushes and briars prevent movement in that direction.\n");
    add_item((({"bushes", "briars", "dense bushes"})),
        "Some dense bushes covered in long thorns block the way " +
        "to the south.\n");
    reset_room();
    set_tell_time(110);
    add_tell("Far above a hawk soars gracefully in a widening " +
        "gyre.\n");
    add_tell("A large golden bee buzzes past you to land " +
        "on a clover flower.\n");
    add_exit("n7", "north");
    set_up_herbs(select_herb_files(MEADOW_HERBS), MEADOW_LOCATIONS, 3);

    if(random(5) > 3)
    {
        add_herb_file("/d/Earthsea/herbs/herb_files/clover4");
    }
}

public void
reset_room()
{
    int i = random(5);

    ::reset_room();

    while(i--)
    {
        if(!objectp(goats[i]))
        {
            goats[i] = clone_object("/d/Earthsea/gont/tenalders/npc/goat");
            goats[i]->move(this_object());
            goats[i]->command("emote bounces in");
        }
    }
}
