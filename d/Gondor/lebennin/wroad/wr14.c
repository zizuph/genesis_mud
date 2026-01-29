/*
 *      /d/Gondor/lebennin/wroad/wr14.c
 *
 *      Road leading from Pelargir to Dol Amroth
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"

inherit LEBENNIN_STD_DIR + "base";

static object door;

void
create_lebennin_room()
{
    door = clone_object(AREA_DIR + "wroad/obj/cabin_door_out");
    door->move(this_object());

    set_up_herbs(({(HERB_DIR+"carrot"), (HERB_DIR+"sage"), (HERB_DIR+"basil"),
                   (HERB_DIR+"garlic"), (HERB_DIR+"thyme"), (HERB_DIR+"mint"),
                   (HERB_DIR+"rosemary")}));
    // Set herbs in this room only to be found in the garden
    places = ({"garden", "herb garden"});

    set_short("Road in Lebennin");
    set_long("You stand in the wide plains just southeast of the " +
        "cobblestone road. Myriads of colourful flowers dot the plains " +
        "around you. Various trees break the monotomy of the grass " +
        "plains. A grove of oak trees stand out in the landscape.\n");

    set_items_plains();
    add_item(({"trees", "grove", "tree"}), "A grove of oaks is situated " +
        "at the base of a hill here. A small hunting cabin is situated next " +
        "to one of the oak trees.\n");
    add_item(({"hunting cabin", "cabin", "log cabin", "pine cabin", "roof"}), 
        "Nestled beside a tree in the grove of oaks stands a small " +
        "hunting cabin. The cabin is built by sturdy pine logs, and has " +
        "a grass thatched roof. On the west side of the cabin is a sturdy " +
        "door, and next to the door stands a small herb garden. " +
        "On the south side of the cabin you can see a window.\n");
    add_item(({"window", "cabin window"}), "The window shows the interior of " +
        "hunting cabin, revealing an an old human standing by a butcher's " +
        "block.");
    add_item(({"road", "stone road", "old road", "cobblestones", 
        "cobblestone road"}), "To the nort an old cobblestone road runs " +
        "from the east to the west across the plains.\n");
    add_item(({"garden", "herb garden"}), "A well tended herb garden stands " +
        "next to the entrance of the cabin.\n");

    add_tell("A slight breeze makes the leaves of the oak trees glimmer in " +
        "the " + daylight() + ".\n");
    add_tell(&set_day_night_tells("Faint snoring can be heard from the " +
        "hunting cabin.\n", "Chopping sounds can be heard emanating from the " +
        "hunting cabin.\n"));
    add_tell(&set_day_night_tells("A thin trail of smoke can be seen " +
        "trailing up from the chimney of the hunting cabin.\n", "A " +
        "black-legged seagull settles on the roof of the hunting cabin, " +
        "shrilling: kittee-wa-aaake, kitte-wa-aaake.\n"));
    add_tell(&set_day_night_tells("Small animals can be heard foraging for " +
        "food nearby.\n", "Suddenly the shape of someone moving can be seen " +
        "through the window of the hunting cabin.\n"));

    add_exit(AREA_DIR + "wroad/wr13", "northwest", 0, 1);
    set_no_exit_msg(get_all_no_exits(({"nw"})), "You decide to stay on " +
        "the road.\n");
}
