/*
 * 	mansion.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian, Oct 2015
 */

#pragma strict_types

#include "/d/Sparkle/area/bandit/wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

int do_lift(string str);

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    set_herbs();

    set_short("On a white stone yard");
    set_long("Standing at the very top of a tall grassy hill, you have a " +
        "wonderful view of the land all around you for miles. A narrow lane, " +
        "bordered by two lines of small yellow flowers, winds down the east " +
        "face of the hill, joining up with the broad and straight length of " +
        "the Orc Road which runs east out of the Grey Mountains until it " +
        "meets a crossroads. Just past the crossroads, you see a dusty road " +
        "travelling to the port of Sparkle, sitting on the wide blue " +
        "expanse of the Pen Sea which covers the entire eastern horizon. " +
        "In almost every other direction, the jagged peaks of the Grey " +
        "Mountains seem to dominate the view. On the top of the hill itself, " +
        "dozens of white stone slabs have fallen on the foundation of an old " +
        "mansion. Just west of the foundation, an old garden path is still " +
        "visible leading down the western side of the hill.\n");

    add_trees(0);

    add_exit("/d/Genesis/start/human/wild2/new/lawn","west");
    add_exit("/d/Genesis/start/human/wild2/new/lane","east");
    add_exit(THIS_DIR + "mansion","north", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "mansion", "southwest", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "mansion", "southeast", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "mansion", "south", "@@mount@@", 1,1);
    add_exit(THIS_DIR + "mansion", "northwest", "@@hill@@", 1,1);
    add_exit(THIS_DIR + "mansion", "northeast", "@@hill@@", 1,1);

    add_item(({"here"}),
        "Standing at the very top of a tall grassy hill, you have a " +
        "wonderful view of the land all around you for miles. A narrow lane, " +
        "bordered by two lines of small yellow flowers, winds down the east " +
        "face of the hill, joining up with the broad and straight length of " +
        "the Orc Road which runs east out of the Grey Mountains until it " +
        "meets a crossroads. Just past the crossroads, you see a dusty road " +
        "travelling to the port of Sparkle, sitting on the wide blue " +
        "expanse of the Pen Sea which covers the entire eastern horizon. " +
        "In almost every other direction, the jagged peaks of the Grey " +
        "Mountains seem to dominate the view. On the top of the hill itself, " +
        "dozens of white stone slabs have fallen on the foundation of an old " +
        "mansion. Just west of the foundation, an old garden path is still " +
        "visible leading down the western side of the hill.\n");
    add_item(({"mountain", "mountains", "grey mountains", "peak", "peaks"}),
        "Stretching across most of the horizon, you see an endless " +
        "line of jagged, snow-capped mountain peaks as they pierce the " +
        "sky. These are the Grey Mountains, a legendary fixture in the " +
        "countryside surrounding Sparkle. It is said that the " +
        "traditional homeland of the dwarves, Dwarfheim is hidden " +
        "somewhere to the north, while somewhere in the south, goblins " +
        "have tunneled deep into the heart of the mountains, " +
        "establishing a realm of their own.\n");
    add_item(({"sea", "pen sea", "waters", "water"}),
        "Spreading out to the east, farther than the eye can see, is " +
        "the Pen Sea. Nearby, to the east, you can see the famous " +
        "port of Sparkle, a major hub of activity with a constant " +
        "stream of ships arriving and departing from even the most " +
        "remote corners of the world.\n");
    add_item(({"crossroads", "crossroad"}),
        "The Orc Road run east to intersect with a wide and busy road " +
        "which seems to run both north and south. However, it is " +
        "difficult to tell, as the roads seem to get lost behind the " +
        "Grey Mountains which dominate the horizon in almost every " +
        "direction.\n");
    add_item(({"sparkle", "town", "city", "village", "port"}),
        "To the east, you can just barely see the town of " +
        "Sparkle, the legendary port city which is the hub of the " +
        "Pen Sea. The town appears to be quite lively, as if it " +
        "never sleeps, a feeling which is only accented by the fact " +
        "that there appears to be an endless stream of ships which " +
        "are either arriving or departing from the great port.\n");
    add_item(({"flower", "flowers", "yellow flower", "yellow flowers",
            "row", "rows", "small flower", "small flowers"}),
        "Dozens of small yellow flowers are lined up in two rows, " +
        "escorting the lane as it winds its way down the grassy hill.\n");
    add_item(({"lane", "dirt", "dirt lane", "narrow lane", "slope"}),
        "This narrow dirt lane winds down the eastern face of the " +
        "hill you are currently standing on top of. On either " +
        "side of the lane, two long rows of small yellow flowers " +
        "follow the lane as it runs to the Orc Road.\n");
    add_item(({"road", "orc road"}),
        "Just north of the hill, you can see the narrow lane join " +
        "up with the wide dusty path of the Orc Road. Leading from " +
        "the town of Sparkle and digging passage through a high " +
        "pass, the Orc Road continues west towards the Orc Forest " +
        "before turning south as the road to Faerie.\n");
    add_item(({"hill", "grassy hill", "tall hill", "top", "hilltop", "land"}),
        "This tall hill is covered in a carpet of dark green grass, " +
        "and it seems like you can see for miles from up here. A narrow " +
        "lane winds down the easten side of the hill, while the " +
        "remnants of an old mansion rest here at the top. You also " +
        "notice what appears to have been a garden path wandering " +
        "away down the western side of the hill.\n");
    add_item(({"green oaks", "faerie", "greenoaks"}),
        "The village of Green Oaks, in the land of Faerie, sits " +
        "far beyond the Grey Mountains somewhere to the south.\n");
    add_item(({"grass", "green grass", "lawn", "garden", "soil"}),
        "Lush and deep, this grass covers the tall hill in a dark " +
        "green blanket. There appears to be an old garden in the " +
        "middle of the lawn on the western side of the hill, but you " +
        "cannot see much of it from here.\n");
    add_item(({"slab","slabs", "white slab", "yard", "stone", "white stone",
            "white slabs", "stones", "white stones"}),
        "The yard here is covered in large slabs of white stone, " +
        "apparently rubble left behind when the mansion here fell " +
        "into disrepair. The slabs are scattered all over the top of " +
        "the hill, including some which have fallen into the " +
        "foundation.\n");
    add_item(({"foundation","foundations" }),
        "The foundation is hollowed out deep into the soil at the " +
        "top of the hill, and it is mostly filled with the rubble " +
        "of large slabs of white stone, broken and crumbled as the " +
        "mansion they once graced fell into disrepair. This foundation " +
        "was once the basement, and is now all that remains of that " +
        "mansion.\n");
    add_item(({"basement","rubble","entrance" }),
	    "There are a lot of broken stone slabs in this basement, and " +
        "some of the rubble is blocking what appears to have been " +
        "an entrance into a lower level of the mansion.\n");
    add_item(({"mansion","house","ruins" }),
        "The mansion is not here anymore, just its ruins after it " +
        "fell into disrepair.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

/*
 * Function name:        init
 * Description  :        Sets up commands for the player
 */
void
init()
{
    ::init();
    add_action("do_lift","lift");
}
/* init */

/*
 * Function name:        do_lift
 * Description  :        Lifts a slab so they can enter the basement
 */
int
do_lift(string str)
{
    if(!str)
    {
        write("Lift what?\n");
        return 1;
    }

    if((str != "slab"))
    { 
        write("Lift what?\n");
        return 1;
    }

    write("You take a deep breath, grabbing the edge of the stone slab, and " +
        "lift the stone aside using all of your strength. The entrance into " +
        "the lower levels is still intact, and you decide to go down to " +
        "visit them. Just after you move into the tunnel, it sounds like " +
        "the stone slab has fallen back into place, once again covering " +
        "this basement entrance.\n");
    SAYBB(" lifts up the edge of a stone slab, and enters a tunnel leading " +
        "down into the basement. Shortly after they enter the tunnel, the " +
        "stone slab slips and falls back into place, once again covering " +
        "the basement entrance.");
    TP->move_living("M",THIS_DIR + "base1",1,0);
    SAYBB(" arrives in the tunnel after moving the stone slab.");
    return 1;
}
/* do_lift */

/*
 * Function name:        do_search
 * Description  :        Allows the player to search for a clue to entering
 *                       the basement
 */
public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "rubble", 
           "slab", 
           "stone",
           "stone slab",
           "white stone",
           "basement",
           "stone slabs",
           "stones",
           "white slab",
           "slabs",
           "white slabs",
        }) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "As you carefully inspect all of the slabs, especially the rubble " +
        "in the basement, you discover that one of the slabs is loose! It " +
        "seems to be covering an entrance into the basement of the mansion, " +
        "and you think you are strong enough to lift the slab if you wanted " +
        "to see what is down there.\n";

}
/* do_search */

/*
 * Function name:        hill
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the hill in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
hill()
{
    write("The hill looks a little bit steep in that direction, you " +
        "can follow the path east to get back to the Orc Road.\n");
    return 1;
}
/* hill */

/*
 * Function name:        mount
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
mount()
{
    write("It looks like it would be a little difficult doing off in that " +
        "direction from here, it might be better to stick to the path you " +
        "are on.\n");
    return 1;
}
/* mount */