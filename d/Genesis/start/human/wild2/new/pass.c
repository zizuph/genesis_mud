/* 
 *	pass.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

void
create_wild_room()
{
    set_items_sparkle();
    set_items_darkroad();

    set_short("Renegade Cut");
    set_long("You are on the southern end of the mountain pass known as " +
        "Renegade Cut. The pass slices through rugged cliffs in the Grey " +
        "Mountains, allowing the Dark Road to connect the human cities " +
        "of Sparkle and Larton. Or, at least, it used to! Now it seems " +
        "that bandits have taken over the pass, ambushing unwary " +
        "travellers who attempt to follow the highway. A wide valley " +
        "sprawls out to the south, filled with tall grasses that " +
        "hide the colourful wildflowers that peek out as they sway " +
        "in the cool mountain breeze. On either side of the pass, two " +
        "massive cliffs rise high above your head, ensuring that " +
        "anyone walking into a potential ambush will have nowhere to " +
        "go, except to follow the Dark Road to either the north or south.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field9","south");
    add_exit(THIS_DIR + "pass", "north", "@@pass@@");
    add_exit(THIS_DIR + "pass", "northeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "pass", "northwest","@@mount@@",1,1);
    add_exit(THIS_DIR + "pass", "east","@@mount@@",1,1);
    add_exit(THIS_DIR + "pass", "west","@@mount@@",1,1);
    add_exit(THIS_DIR + "pass", "southeast","@@mount@@",1,1);
    add_exit(THIS_DIR + "pass", "southwest","@@mount@@",1,1);

    add_item(({"ambush","bandit","bandits"}),
        "Faint noises echo through the pass, and shadows shift unnaturally " +
        "ahead in the middle of the cut. All telltale signs that there " +
        "are bandits waiting to ambush the next person to pass through.\n");
    add_item(({"cliff","cliffs","sheer cliff","sheer cliffs","massive cliff",
            "massive cliffs","rocky cliff","rocky cliffs","face","faces",
            "cliff face","cliff faces","wall","walls"}),
        "Rising high and intimidating on either side of the Dark Road, are " +
        "two massive cliffs. The face of the cliff is rocky, yet too sheer " +
        "to climb safely. Staring at them for any length of time is an " +
        "uncomfortable reminder of how they have you trapped here.\n");
    add_item(({"breeze","cool breeze","mountain breeze",
            "cool mountain breese"}),
        "Well, you cannot see the breeze itself, only the effect it has " +
        "as it ripples through the tall grasses and wildflowers in the " +
        "fields of the valley south of here.\n");
    add_item(({"mountain pass","pass","cut","renegade cut"}),
        "Renegade Cut is the local name of this mountain pass, which " +
        "slices right through the Grey Mountains between two sheer " +
        "cliff walls. It has also become a favourite haunt for the " +
        "local bandits who wish to ambush unwary travellers and " +
        "merchants.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name:        pass
 * Description  :        Provides an explanation why a mortal cannot move
 *                       through Renegade Cut
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
pass()
{
    write("You are postive there are some bandits in the pass ahead, " +
        "waiting to ambush unwary travellers. You feel that this is " +
        "not the right time to try and follow the Dark Road north " +
        "from here.\n");
    return 1;
}
/* pass */

/*
 * Function name:        mount
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the mountains in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
mount()
{
    write("These cliffs are too difficult to climb! You will have to " +
        "follow the road to the north or the south to get away from " +
        "here!\n");
    return 1;
}
/* mount */
