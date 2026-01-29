/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <macros.h>

#define NUM_APPLES 50

static int apples = NUM_APPLES;

public void
create_earthsea_room()
{
    set_short("Village path");
    set_long("The village is situated on " +
        "a somewhat more level area of the mountainside. " +
        "Beyond the village to the north the " +
        "forest continues up to the mountain's peak, which is crowned " +
        "with snow and clouds. Very far away down the mountain " +
        "to the south and east you can see beyond the evergreen forest " +
        "to the vast dark-blue north sea, " +
        "where sunlight sparkles on the waves. " +
        "The high elevation makes for thin air, which is " +
        "scented with pine and herbal smoke coming from chimneys " +
        "of some of the inhabited huts. There is a dark hut " +
        "a bit further southwest, and to the north you see a hut " +
        "with a cheerfully smoking chimney. To the east " +
        "there is a hut covered in living vines. Just by the path here " +
        "an apple tree stands, its branches laden with fruit.\n");
    add_item("north hut", "Just to the north is a hut with a smoking " +
        "chimney and good smells emanating from it. You see a sign over " +
        "the door.\n");
    add_item("southwest hut", "There is a hut to the southwest, where " +
        "you hear the sound of metal striking metal.\n");
    add_item("east hut", "A bit further to the east is " +
        "a hut covered in vines.\n");
    add_item((({"sea", "north sea"})),
        "At this elevation you can see all the way to the horizons " +
        "toward the south and east.\n");
    add_item((({"peak", "mountain's peak"})),
        "The snow-covered peak of Gont Mountain is visible through " +
        "a wreath of clouds that surrounds it.\n");
    add_item((({"forest", "evergreen forest"})),
        "The mountain of Gont is flanked with an ancient evergreen " +
        "forest that climbs almost to the peak.\n");
    add_item("mountainside", "The mountainside climbs steeply up " +
        "above the village.\n");
    add_item("village", "This is but a poor peasant village, but " +
        "who knows what mysteries lie beneath its simplicity?\n");
    add_item((({"path", "gravel path"})),
        "A narrow path paved with bits of gravel wanders in between " +
        "the huts.\n");
    add_item((({"huts", "thatch huts"})),
        "With their curved thatched, low roofs, the huts are shaped " +
        "like large mushrooms growing on the mountainside. " +
        "You can examine individual ones that are close to you.\n");
    add_item((({"tree", "small apple tree", "apple tree", "apples"})),
        "This is a small tree, but it is heavily laden with bright red " +
        "perfect, juicy-looking apples ... and a few not quite so " +
        "perfect ones.\n");
    add_item((({"huts", "thatch-covered huts"})),
        "This is a small village, with only a few huts clinging " +
        "to the steep mountainside. There is a hut to the north, and " +
        "several others to the south and east from here.\n");
    add_exit("village_path_2", "northeast");
    add_exit("village_path_4", "southwest");

    apples = 50;
}

public int
pick_apple(string str)
{
    object tp = this_player(), apple;
    if(str == "apple")
    {
        setuid();
        seteuid(getuid(this_object()));

        if (apples > 0)
        {
            if(random(4) == 0)
            {
                apple = clone_object(
                    "/d/Earthsea/gont/tenalders/obj/items/bad_apple"
                 );
            } else {
                apple = clone_object(
                    "/d/Earthsea/gont/tenalders/obj/items/jon_apple"
                );
            }

            apples--;

            if(apple->move(tp))
            {
                apple->move(this_object());
                write("You try to pick an apple, but your arms are "+
                    "full and it falls to the ground.\n");
                return 1;
            }

            write("You pick a "+ apple->query_short() + " from "+
                "the tree.\n");
            tell_room(environment(tp), QCTNAME(tp) + " picks a " +
                apple->query_short() + " from the tree.\n", ({ tp }));
        }
        else
        {
            write("You do not see any more apples within your reach!\n");
        }
        return 1;
    }

    return notify_fail("Pick what?\n");
}

public void
init()
{
    ::init();
    add_action(pick_apple, "pick");
}

void reset_room()
{
    ::reset_room();
    apples = NUM_APPLES;
}
