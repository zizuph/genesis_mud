/*
 * Hobbit burrow in Frogmorton
 * By Finwe, September 1998
 *
 * Additions made for the /d/Shire/eastroad/western/foam_mug_up quest
 * Raymundo, Feb 2020
 */
 
#pragma strict_types
 
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "defs.h"
#include "/d/Shire/waymeet/defs.h"
 
inherit "/d/Shire/eastroad/smial";
 
void reset_room();
 
object hobbit;
int is_nozzle = 1;

void
create_room()
{
   
    areaname  = "Frogmorton";  /*Name of village*/
    land      = "the Shire";   /*Name of land   */
    roomtype  = 4;             /*Type of room in the smial*/
    areatype  = "village";     /*Type of village*/
    smialsize = "medium size"; /*Size of the house*/
   
    extraline = "Since it is the largest room in the smial, it " +
        "is also the most popular room. " +
        "The family gathers here often for their substantial " +
        "meals and good talk. A large table sits at one end of " +
        "the room, and a sink sits against the north wall.";
 
    add_item(({"ceiling", "up"}),
        "The ceiling is plain.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood and swept clean. There's a " +
		"small drain near the north wall.\n");
	add_item("drain", "The drain is about the size of a hobbit's " +
		"fist, and covered in a wire mesh. It seems to lead outside, " +
		"which only makes sense. Where else would you drain water to?\n");
	add_item("north wall", "On the north wall of the smial is the "
		+ "sink. It looks like a good place to do dishes.\n");
	add_item("sink", "@@exa_sink@@");
	add_item("nozzle", "@@exa_nozzle@@");
    add_item(({"table", "large table"}),
        "The table is circular in shape and made from oak. A " +
        "white linen tablecloth covers the surface with some " +
        "flowers in the center. Six hefty chairs surround the " +
        "table.\n");
    add_item(({"tablecloth", "linen table cloth"}),
        "The table cloth is white and covers the top of the " +
        "table. Some flowers sit in the center of the table.\n");
    add_item(({"centerpiece", "flowers"}),
        "They are some wildflowers, arranged beautifuly in a " +
        "earthen vase.\n");
    add_item(({"vase", "earthen vase"}),
        "It is bowl shaped and dark brown colored. The lip fans " +
        "out slightly. The vase sits on the center of the table "+
        " with some flowers arranged in it.\n");
    add_item(({"chairs", "hefty chairs"}),
        "The chairs are sturdy and carved of oak. They are " +
        "stained a golden color and surround the table.\n");
 
 
    add_exit(FROG_DIR + "smial01b", "south");
   
    make_the_room();
    reset_room();
}
 
void
reset_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(MAIDEN);
        hobbit->set_power(100);
        hobbit->move(TO);
    }
}

void
init()
{
	::init();
	is_nozzle = 1;
	add_action("do_unscrew", "unscrew");
}

string
exa_sink()
{
	if(is_nozzle == 1)
	{
		return("The sink is nice and deep. You could do quite a lot "
			+ "of dishes in it. It looks to be made of stone. Underneath "
			+ "the sink, a pipe runs down to the drain on the floor. "
			+ "On the end of the pipe is a copper nozzle, presumably used "
			+ "to keep water from running out when the cook wants the "
			+ "sink full.\n");
	}
	else
	{
		return("The sink is nice and deep. You could do quite a lot "
			+ "of dishes in it. It looks to be made of stone. Underneath "
			+ "the sink, a pipe runs down to the drain on the floor.\n");
	}
}

string
exa_nozzle()
{
	if(is_nozzle == 1)
	{
		return("This looks like a nozzle you'd use on a pot still "
			+ "in order to keep the liquor from running out onto the "
			+ "floor before you were ready to catch it in a barrel. "
			+ "It looks like you could unscrew it.\n");
	}
	else
	{
		return("You find no nozzle.\n");
	}
}

int
do_unscrew(string str)
{
	if(str == "nozzle" | str == "pipe")
	{
		if(is_nozzle == 1)
		{
			write("You unscrew the nozzle from the pipe! The nozzle falls "
				+ "onto the floor.\n");
			say(QCTNAME(TP) + " unscrews the nozzle from the pipe! The "
				+ "nozzle falls onto the floor.\n");
			
			is_nozzle = 0;
			object nozzle;
			nozzle = clone_object(WAYM_OBJ_DIR + "still_nozzle");
			nozzle->move(environment(TP));
			return 1;
		}
		else
		{
			notify_fail("What nozzle? You don't see one.\n");
			return 0;
		}
	}
	else
	{
		if(is_nozzle == 1)
		{
			notify_fail("Unscrew what? The nozzle?\n");
			return 0;
		}
		else
		{
			return 0;
		}
	}
}