/*
 * coded by Amelia 9/7/97
 * base of cliff northwest in High Fall
 * npcs:  Sparrowhawk
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include <macros.h>
#include "/d/Earthsea/herbs/herb_sets/meadow_herbs.h";

private object boy;
private int alarm1 = 0;

public void
create_herb_room()
{
    set_short("Mountain meadow");
    set_long("The forest opens out onto a meadow at the " +
        "base of a tall limestone cliff. The meadow is clear of " +
        "trees and covered in a carpet of thick grass and " +
        "flowers. The cliff towers above, seeming to reach to the " +
        "top of the mountain. The meadow extends south and east, " +
        "where you can see a grazing area.\n");
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
      "The cliff towers over the meadow to the north. Only the "+
      "very skilled may climb it, unless you are a mountain goat.\n");
    add_item((({"meadow", "carpet", "grass", "flowers"})),
      "This is a beautiful meadow, with a thick carpet of "+
      "dark green grass and flowers. It is ideal for grazing.\n");
    add_item((({"forest", "trees"})),
      "The forest stands to the southwest, but the meadow is "+
      "clear of trees.\n");
    add_item((({"top", "mountain top"})),
      "It seems that the cliff might reach all the way to the "+
      "top of the mountain, however, you cannot see the top "+
      "from here.\n");
    reset_room();
    set_tell_time(110);
    add_tell("Far above a hawk soars gracefully in a widening " +
        "gyre.\n");
    add_tell("A large golden bee buzzes past you to land " +
        "on a clover flower.\n");
    add_exit("n9", "east");
    add_exit("n6", "southwest");
    add_exit("n8", "south");
    set_up_herbs(select_herb_files(MEADOW_HERBS), MEADOW_LOCATIONS, 3);

    if(random(5) > 3)
    {
        add_herb_file("/d/Earthsea/herbs/herb_files/clover4");
    }
}

public void
reset_room()
{
    alarm1 = 0;

    if(!objectp(boy))
    {
        boy = clone_object("/d/Earthsea/gont/tenalders/npc/goatherd");
        boy->move(this_object());
        boy->command("emote strides in.");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        if((!alarm1) && (present("boy", this_object())))
        {
            boy->hawk_script();
            alarm1 = 1;
        }
    }
}

public int
climb_cliff(string str)
{
    object tp = this_player();

    if(str == "cliff" || str == "limestone cliff")
    {
        write("You try to climb the cliff but fall in a heap.\n");
        tell_room(this_object(), QCTNAME(tp) + " tries to climb the cliff, " +
            "but falls into a heap.\n", ({ tp }));
        write("So, you think you are a mountain goat?\n");
        return 1;
    }

    return notify_fail("Climb what?\n");;
}

public void
init()
{
    ::init();
    add_action(climb_cliff, "climb");
}
