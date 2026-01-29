/*
 * Front porch of Bag End
 * By Finwe, April 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit BASE_OUTSIDE;
inherit "/d/Gondor/open/room_chairs/room_chairs"; /* after the base room */

#define	CHAIR_NAME	"wooden bench"

public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */

void
create_outside_room()
{
    set_areadesc("front porch");
    set_area("outside");
    set_areaname("a large smial");
    set_land("Hobbiton");
    set_areatype(0);

    set_extraline("This is a large area outside a green door with " +
        "flagstones set in the ground. Two round windows are set " +
        "on either side of the round door, and a bell pull hangs on " +
        "the right side of the door next to a bench. Gardens surround " +
        "the porch, and worn steps lead down to a path.");

    room_add_object(BE_OBJ + "porch_door");

    add_chair(CHAIR_NAME,
	"[down] [in] / [on] [the] [wooden] 'bench' / 'bench'",
	3, "in");


    add_item(({"bench", "wooden bench"}),
        "It is a long seat made of wood. It has a high back and allows " +
        "several people to sit on it.\n");
    add_item( ({ "wooden bench", "bench",}), &look_at(CHAIR_NAME) );

    add_item(({"smial"}),
        "It is a tunnel dug into the hill and used as a home by hobbits.\n");
    add_item(({"flagstones", "flagstone"}),
        "They are irregular shaped flat stones set into the ground. " +
        "They are smooth and form a semi-circle in front of the door. " +
        "Grass grows between the flagstones.\n");
    add_item(({"bell pull", "bellpull"}),
        "It is a leather cord next to the right window. It is pulled " +
        "by visitors to announce their arrival.\n");
    add_item(({"windows", "round windows", "round window", "window"}),
        "There are two of them and each is set on either side of " +
        "the door. They are round and made of glass.\n");
    add_item(({"steps", "worn steps", "worn step", "step"}),
        "They are long blocks of stone set into the hill. they are " +
        "worn and lead down to a path.\n");
    add_item(({"stone blocks", "stone block", "blocks", "block"}),
        "They are rectangular, worn, and set into the hill.\n");
    add_item(({"grass"}),
        "It is green and short, and grows between the flagstones.\n");
    add_item(({"porch"}),
        "It is a large semi-circular area before the green door. " +
        "Flagstones and gardens surround the porch.\n");
    add_item(({"gardens", "garden"}),
        "They are full of colorful flowers and plants. They " +
        "surround the porch and are well cared for.\n");
    add_item(({"plants"}),
        "They are all sizes and surround the porch. They consist of " +
        "flowers and bushes.\n");
    add_item(({"flowers", "flower"}),
        "You see tall, cup-shaped, and star-shaped flowers growing " +
        "around the porch.\n");
    add_item(({"tall flower", "tall flowers"}),
        "They are tall clusters of lavender tubular shaped blooms. " +
        "The flowers grow around the porch.\n");
    add_item(({"cup-shaped flowers", "cup shaped flower", 
            "cup shaped flowers", "cup-shaped flower"}),
        "These flowers are medium in height. They are deep red with " +
        "a black center. Each flower has four overlapping petals.\n");
    add_item(({"star-shaped flower", "star-shaped flowers", 
            "star shaped flowers", "star shaped flower"}),
        "They are white and grow low to the ground.\n");    
    add_item(({"bushes"}),
        "They are thick and woody. The bushes have been cared for and " +
        "carefully surround the porch. They grow among the flowers.\n");
    add_item(({"path"}),
        "It is well worn and wanders south through Hobbiton.\n");

    add_exit(BE_ROOMS + "lawn07", "south", check_sitting, 1);
    add_exit(BE_ROOMS + "path12", "west", check_sitting, 1);
    add_exit(BE_ROOMS + "path21", "southeast", check_sitting, 1);

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);
}


public void init()
{
    ::init();
    add_action("ring_bell", "pull");
    add_action("ring_bell", "ring");
    init_room_chairs();	/* add chair verbs */
}

int ring_bell(string str)
{
    switch(str)
    {
        case "cord":
        case "bellpull":
        case "bell pull":
        case "leather cord":
        case "bell":
        {
            write("You pull the leather cord and a bell rings inside " +
            "the smail.\n");
            say(QCTNAME(TP) + " pulls the leather cord and a bell " +
            "rings inside the smial.\n");
            return 1;
        }
        default:
        {
            write("Pull what, the bellpull?");
            return 1;
        }
    }
}



/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from chair/sofa occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} 


/*
 * Function name:	look_at
 * Description	:	VBFC to describe chair/sofa + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    /* ok, the descs are a little lame, but you get the idea ... */
    switch ( arg )
    {
    case CHAIR_NAME:
        return "It is a long seat made of wood. It has a high back and allows " +
            "some people to sit on it.\n" +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }
} /* look_at */
