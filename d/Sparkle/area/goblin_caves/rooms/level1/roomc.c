/*
 * Stairs to level 2
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();
    set_short("Stairs");
    set_long("You are standing on the top of the stairs leading down. " +
             "There are two granite gargoyles with red glowing eyes. " +
             "You can see a web in the southeast corner." +
             "\n\n");
    add_item(({"stairs", "stair"}),
             "Stairs lead down to lower levels of the caves.\n");
    add_item(({"gargoyles", "gargoyle", "statue", "statues"}),
			  "The gargoyle statues seem made of lifeless granite, " +
			  "but a strange glow in their eyes makes you feel " +
			  "uncomfortable.\n");
	add_item(({"eyes", "glow"}),
	         "The red glow from the eyes of the statues fills you with a " +
                 "desire to leave.\n");
	add_item(({"web", "spider web"}),
	         "There is a spider web covering southeast corner.\n");
	add_item(({"corner", "southeast corner"}),
	         "You can see a spider web in the corner.\n");
	add_item("spiders", "You cannot see any spiders. They must be hiding.\n");
    add_cmd_item( ({ "web", "spider web"}),
                  ({ "clear", "remove"}),
                  "Spider web seems so sticky that you reconsider your " +
                  "action.\n");

    add_exit ("roomb", "west");
    add_exit ("../level2/roomi2", "down");
    //add_exit ("..\l2\roomi2", "down", "@@check_next_level", 0);

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());
} /* create_room */

/*
 * Function name:		check_next_level
 * Description  :		checks if entrance to next level is allowed
 */
int
check_next_level()
{
	write("The granite of the statues suddenly starts to move and one of " +
	      "the gargoyles steps between you and the stairs blocking your " +
	      "advancement.\n");
	return 1;
} /* check_next_level */