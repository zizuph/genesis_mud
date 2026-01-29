/*
 * Inn at Sarn Ford
 * Varian - February 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Gondor/common/lib/time.c";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
void

create_room()

{
    set_short("Cozy sleeping chamber at the Sleepy Fisherman");
    set_long("This is a cozy little sleeping chamber which sprawls " +
        "across the top floor of the Sleepy Fisherman Inn. There are " +
        "several beds laid out across a wide common room, ready to " +
        "provide a comfortable rest for any weary traveller who has " +
        "purchased a stay for the evening. The sloped ceiling is made " +
        "from heavy beams of oak, while wide planks of maple weave " +
        "their way across the floor. A sturdy staircaise winds its " +
        "way down against the southern wall, leading to the main " +
        "room of the inn below. A small handful of windows allow you " +
        "to take a glimpse out of the other three walls. You can " +
        "still hear the occasional sound of laughter and voices " +
        "drifting up from below, but thankfully it is not so loud " +
        "as to be very disturbing.\n");
  
    add_item(({"chamber", "sleeping chamber", "room", "common room"}),
        "This is a cozy little sleeping chamber which sprawls " +
        "across the top floor of the Sleepy Fisherman Inn. There are " +
        "several beds laid out across a wide common room, ready to " +
        "provide a comfortable rest for any weary traveller who has " +
        "purchased a stay for the evening. The sloped ceiling is made " +
        "from heavy beams of oak, while wide planks of maple weave " +
        "their way across the floor. A sturdy staircaise winds its " +
        "way down against the southern wall, leading to the main " +
        "room of the inn below. A small handful of windows allow you " +
        "to take a glimpse out of the other three walls. You can " +
        "still hear the occasional sound of laughter and voices " +
        "drifting up from below, but thankfully it is not so loud " +
        "as to be very disturbing.\n");
    add_item(({"bed", "beds", "box", "boxes", "wooden box", "wooden boxes"}),
        "These beds are really just wooden boxes, filled with " +
        "fresh straw and covered with a couple of thick blankets. " +
        "It might not be the fanciest place to sleep, but it is " +
        "certainly more comfortable than braving the elements " +
        "outside.\n");
    add_item(({"straw", "fresh straw"}),
        "The beds seem to be stuffed with straw, fortunately the " +
        "innkeeper seems to have made sure it is nice and fresh.\n");
    add_item(({"blanket", "blankets", "thick blankets", "thick blanket"}),
        "Each of the beds in this chamber have been outfitted with a " +
        "couple of nice, thick, cozy blankets. It might not be very " +
        "sophisticated, but you have certainly seen worse.\n");
    add_item(({"ceiling", "sloped ceiling"}),
        "The ceiling is made of wood, sloping up to a peak in the " +
        "middle of the room. Wide beams of study oak support " +
        "long planks of wood, with several nails poking through. " +
        "The slate tiles you saw on the roof from outside have " +
        "obviously been nailed into place here.\n");
    add_item(({"beam", "beams", "oak beams"}),
        "These thick beams of oak frame the structure of the roof, " +
        "which has apparently been made from slate tiles nailed " +
        "into wooden planks.\n");
    add_item(({"nails", "nail"}),
        "You can see the pointy tips of nails poking through the " +
        "planks of wood in the ceiling. You would guess that they are " +
        "there to keep the slate tiles in place.\n");
    add_item(({"plank", "planks"}),
        "Do you want to look at the planks on the floor? or the " +
        "planks on the ceiling?\n");
    add_item(({"oak planks", "ceiling planks", "oak plank", "ceiling plank"}),
        "These oak planks stretch across the ceiling, supported by " +
        "several sturdy oak beams. You can see several nails " +
        "poking through them.\n");
    add_item(({"maple planks", "maple plank", "floor", "floor planks", "floor plank"}),
        "Narrow strips of maple planks have been laid across the floor of the " +
        "sleeping chamber. Although the wood is worn and scratched with frequent  " +
        "use, the floor still looks quite respectable.\n");
    add_item(({"staircase", "south wall", "southern wall"}),
        "The southern wall of this room is occupied by a sturdy, wooden " +
        "staircase which leads back down to the main room of the inn " +
        "below. Occasionally, you can hear the odd bark or laughter " +
        "or singing voices, but not so loud as to be very disturbing.\n");
    add_item(({"wall", "walls", "wooden wall", "wooden walls"}),
        "Which wall did you want to inspect? The southern wall? The " +
        "northern wall? The eastern wall? or the western wall?\n");
    add_item(({"window", "windows"}),
        "Which window did you want to look through? There are windows " +
        "in the west, north and east walls.\n");
    add_item(({"west wall", "western wall"}),
        "This is a wooden wall with a couple of windows that look " +
        "out over the Brandywine river.\n");
    add_item(({"north wall", "northern wall"}),
        "A couple of windows peek through the wood of the northern " +
        "wall, looking down on the dock that has been built on the " +
        "Brandywine river.\n");
    add_item(({"east wall", "eastern wall"}),
        "There are a couple of windows in this wooden wall, which " +
        "gaze down upon a small path which trails away to the " +
        "northeast.\n");
    add_item(({"west window", "western window"}),
        "Looking through the window, you get a wonderful view of the " +
        "majestic Brandywine river below.\n");
    add_item(({"north window", "northern window"}),
        "As your peer out the northern window, you can see a modest " +
        "dock, jutting out into the wide, swirling waters of the " +
        "Brandywine river.\n");
    add_item(({"east window", "eastern window"}),
        "Gazing through the eastern window, you have a clear view " +
        "of a path which winds its way up along the riverbank to " +
        "the northeast.\n");
    add_item(({"river", "brandywine", "riverbank"}),
        "You can see the Brandywine river through most of the windows " +
        "here. It looks quite impressive when seen from this height.\n");
    add_item(({"dock", "modest dock"}),
        "There is a modest dock which juts out into the river here, " +
        "occasionally you will see a boat pull up against it, letting " +
        "passengers on or off.\n");
    add_item(({"path", "small path"}),
        "This small path leads away from the dock and inn, following " +
        "the riverbank away to the northeast. Occasionally, you will " +
        "catch side of the odd traveller.\n");

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(SARNFORD_DIR + "inn.c", "down");
}

int
start_cmd(string args)
{
    if (!args || !strlen(args))
    {
        notify_fail("Start what?\n");
        return 0;
    }

    if (args != "here")
    {
        notify_fail("Start where? here?\n");
        return 0;
    }

    object key = present("_sarnford_inn_key", this_player());
    if (!objectp(key))
    {
        write("You need to purchase a key downstairs before you can "
            + "spend the night here.\n");
        return 1;
    }

    this_player()->set_temp_start_location(MASTER);
    key->remove_object();

    write("You find an empty bed and make yourself comfortable. Knowing "
        + "that you will awake here next time you enter these realms.\n");
    say(QCTNAME(this_player()) + " makes " + this_player()->query_objective()
        + "self comfortable upon one of the beds.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(start_cmd, "start");
}