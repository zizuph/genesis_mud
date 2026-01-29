/*
 * Smial in Longbottom
 * Finwe, January 2020
 *
 * /s/Shire/eastroad/western/foam_mug_up quest additions
 * such as add_items and the pipe
 * Raymundo, Feb 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../../defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit BASE_SMIAL;
// inherit BASE_COMMON;

static object hob;
object door;
object pipe; //For the quest in /d/Shire/eastroad/western/foam_mug_up
int is_pipe = 1;
void
create_smial()
{
    object door, key;

   areaname     = "Longbottom"; /*Name of village*/
   land         = "Southfarthing"; /*Name of land   */
   roomtype     = 9; /*Type of room in the smial   */
   areatype     = "hamlet"; /*Type of village*/
   smialsize    = "large"; /*Size of the house*/

    extraline = "";

//    door = clone_object(LB_OBJ_DIR + "5_door_cellar");
//    door->move(this_object());

    room_add_object(LB_OBJ_DIR + "5_door_cellar");

	add_item( ({"pipe", "copper", "copper pipe", "small pipe", "small copper pipe"}), "@@exa_pipe@@");

    set_add_walls();
    set_add_ceiling();
    set_add_floor_plain();
    set_wood_panel();
    set_add_cellar();

   reset_shire_room();
}

void
reset_shire_room()
{
    object other;
/*
    if (!hob)
    {
   	    hob = clone_object(HOBBITMAKER);
   	    hob->set_type(MAIDEN);
	    hob->set_power(140);
   	    hob->move(TO);
    }
*/
    if (door->query_open())
    {
        door->do_close_door("A hobbit comes in and closes the door."); /* If you want a message written put it */
        other->do_close_door("A hobbit comes in and closes the door."); /* between the "" */
    }
	is_pipe = 1;
}

void
init()
{
	::init();
	add_action("do_retrieve", "retrieve");
}

string
exa_shelf()
{
	if(is_pipe == 1)
	{
		return("The shelves are full of jars of pickled vegetables and "
			+ "rags. You see a few pots and pans as well, and even the "
			+ "odd tool. A small copper pipe catches your eye.\n");
	}
	else
	{
		return("The shelves are full of jars of pickled vegetables and "
			+ "rags. You see a few pots and pans as well, and even the "
			+ "odd tool.\n");
	}
}

string
exa_pipe()
{
	if(is_pipe == 1)
	{
		return("This is a small copper pipe that looks like it'd be "
			+ "part of a pot still. Hmm... You could retrieve it if "
			+ "you wanted to.\n");
	}
	else
	{
		return("You find no pipe.\n");
	}
}

int
do_retrieve(string str)
{
	if(str == "pipe" | str == "copper pipe" | str == "small pipe" | str == "small copper pipe")
	{
		if(is_pipe == 1)
		{
			pipe = clone_object(WAYM_OBJ_DIR + "still_pipe_3");
			pipe->move(TP);
			write("You retrieve the " + pipe->query_short() 
				+ " from the shelf!\n");
			say(QCTNAME(TP) + " retrieves a " + pipe->query_short()
				+ " from the shelf!\n");
			is_pipe = 0;
			return 1;
			
		}
		else
		{
			write("There is no pipe to get!\n");
			return 1;
		}
	}
	else
	{
		if(is_pipe == 1)
		{
		notify_fail("Retrieve what? The pipe?\n");
		return 0;
		}
		else
		{
			return 0;
		}
	}
}