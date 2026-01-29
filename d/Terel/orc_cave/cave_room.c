/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave_room.c
 *
 * A generic orc cave room.  All the orc caves rooms should inherit this
 * file.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells faintly like sulfur.\n";
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
	return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
	write(smell_desc());
	return 1;
    }
    return 0;
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Cave");
    set_long("You are in a large complex of tunnels and caves. " +
	     "Stalactites hang down from above and stalagmites protrude " +
	     "from the ground.  The walls are somewhat damp with moisture.  " +
	     "The air is cool and carries a strange scent.  ");

    add_item(({"stalagmites", "stalagmite"}),
	     "They vary in size and are a bit lighter in colour than the " +
	     "ground from which they come.\n");

    add_item(({"stalactites", "stalactite"}),
	     "Hanging down from the ceiling, they have a rough texture. " +
	     "Some of them drip water onto the cavern floor.\n");

    add_item(({"wall", "walls"}),
	     "The walls have the same rough texture as " +
	     "the stalagmites, but are darker in colour.  Lower down dried " +
	     "leaves and twigs are stuck on, indicating the water " +
	     "level must have been higher in here recently.\n");
    
    INSIDE;
}

