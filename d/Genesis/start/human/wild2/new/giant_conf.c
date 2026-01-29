/*
 * 	giant_conf.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit THIS_DIR + "base";

void
reset_room();

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

    set_short("Giant conference");
    set_long("You are standing atop a small plateau, at the west end of a " +
        "valley high in the Grey Mountains. The valley all around you is " +
        "covered in tall grasses and colourful wildflowers, framing a " +
        "dirt trail that winds down to the east. In the middle of the " +
        "plateau, there are several massive tree stumps arranged in a " +
        "circle around a large fire pit. It seems like this is the place " +
        "where the mountain giants arrange their annual elf bashing "+
        "conference! But since elves are sparse in these regions it is " +
        "rumoured that humans, dwarves, hobbits, goblins and gnomes are " +
        "seen as acceptable replacements.\n");

    add_trees(0);

    add_exit(THIS_DIR + "giant_path","east");
    add_exit(THIS_DIR + "giant_conf", "west","@@mount@@",1,1);
    add_exit(THIS_DIR + "giant_conf", "northeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "giant_conf", "north","@@mount@@",1,1);
    add_exit(THIS_DIR + "giant_conf", "northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "giant_conf", "southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "giant_conf", "south","@@mount@@",1,1);
    add_exit(THIS_DIR + "giant_conf", "southwest","@@mount@@",1,1);

    add_item(({"foothill","foothills","rugged foothills","rugged foothill",
            "hill","hills"}),
        "You are in the foothills of the Grey Mountains, atop a small " +
        "plateau overlooking a small valley that spreads out to the east. " +
        "The rugged foothills slope steadily upwards all around, rising " +
        "up into rocky cliffs.\n");
    add_item(({"mountain","mountains","grey mountains","mountainside",
            "mountainsides"}),
        "The Grey Mountains rise up all around you here, surrounding " +
        "the small valley before you. The rocky mountainside is " +
        "filled with steep cliffs and rugged foothills that make " +
        "travel away from the trail almost impossible.\n");
    add_item(({"vale","valley","small valley"}),
        "Stretching out to the east, a small valley full of " +
        "tall grasses and colourful wildflowers spreads out before " +
        "you.\n");
    add_item(({"path","dirt path","small path","small dirt path","trail",
                "small trail","dirt trail","small dirt trail"}),
        "The trail is almost unrecognizable as it ends in a mass of " +
        "big footprints that seem to circle around a large meeting " +
        "place that sits in the middle of the plateau.\n");
    add_item(({"footprints","giant footprints","big footprints",
            "footprint","giant footprint","big footprint"}),
        "These footprints are very, VERY big! Clearly, you have entered " +
        "mountain giant territory.\n");
    add_item(({"plateau","small plateau"}),
        "This is a small plateau in the mountains, and you are standing " +
        "on top of it!\n");
    add_item(({"meeting","meeting place"}),
        "This is a small plateau in the mountains, and you are standing " +
        "on top of it!\n");
    add_item(({"stump","stumps","chair","chairs","seat","seats"}),
        "These stumps are massive, but are just the right height to " +
        "provide a comfortable seat for a giant.\n");
    add_item(({"pit","fire pit","fire"}),
        "This fire pit is well equipped with a spit for roasting any " +
        "elves (or anyone else!) that the mountain giants might catch!\n");
    add_item(({"spit","roasting spit","wooden spit","wooden roasting spit"}),
        "This is a wooden roasting spit, apparently used for cooking " +
        "any elves that the mountain giants can catch.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    reset_room();
}

/*
 * Function name:        mount
 * Description  :        Gives an explanation for why the mortal cannot travel
                         across the mountains in this direction
 * Returns      :        int 1 - denies moving along the exit path
 */
int
mount()
{
    write("The rocky cliffs that make up the steep mountainsides here " +
        "prevent you from going in that direction. You will have to find " +
        "another way around.\n");
    return 1;
}
/* mount */

/*
 * Function name:        reset_room
 * Description  :        Clones the NPCs
 */
void
reset_room()
{
    object giant;
    int i;
    
    if (!present("giant")) {
        for (i = 0; i < 3; i++) {
            giant = clone_object(OBJ_DIR + "giant");
            giant->arm_me();
            giant->move(TO);
        }
    }
}
/* reset_room */