/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>

inherit INSIDE_BASE;

int amulet;

void
create_solace_room()
{
    set_short("Crypt room");
    set_long("This very large well lit room has earthen walls and floor"
	     + ", water drips in many places from the ceiling forming many puddles"
	     + " all over the room. The centre of the room contains one particularly"
	     + " large puddle where most of the water has come to settle.\n"
	     + "A ladder leads up.\n");
    
    add_exit(TDIR + "crypt3", "up", 0);
    add_exit(TDIR + "crypt8", "north", 0);
    
    add_item(({"floor", "ground"}), "@@floor");
    add_item(({"puddle", "puddles"}), "@@puddle");
    add_item(({"large puddle", "big puddle"}), "@@bpuddle");
    add_search(({"large puddle", "big puddle"}), 8, "searchpuddle", 1);
    add_item("water", "The water in all the puddles is murky " +
	     "except the central one\nwhich strangely has clear water.\n");
    add_item(({"wall", "walls", "earthen wall", "earthen walls",
		   "ceiling", "roof"}), "@@wall");
    
    INSIDE;
    LIGHT;
}

void
reset_solace_room()
{
    amulet = 0;
}

void
init()
{
    ::init();
    ADA("dig");
}

mixed
searchpuddle(object searcher, string str)
{
    if (amulet == 0)
	{
	    clone_object(OBJ + "amulet")->move(TO);
	    amulet = 1;
	    return "You uncover an amulet!\n";
	}
    return 0;
}

int
dig(string str)
{
    NF("Dig where?\n");
    if ((str == "ground") || (str == "here") || (str == "the ground")
	|| (str == "floor") || (str == "the floor"))
	{
	    write("You dig where you are standing but find nothing useful.\n");
	    say(QCTNAME(TP) + " digs in the ground at his feet.\n");
	    return 1;
	}
    if ((str == "in puddle") || (str == "puddle") || (str == "the puddle"))
	{
	    write("Which puddle do you want to dig in?\n");
	    return 1;
	}
    if ((str == "in large puddle") || (str == "large puddle") || (str == "the large puddle"))
	{
	    write("You dig in the clear water.\n");
	    if (amulet == 0)
		{
		    write("You uncover an amulet!\n");
		    clone_object(OBJ + "amulet")->move(TO);
		    amulet = 1;
		}
	    say(QCTNAME(TP) + " digs in the centre puddle.\n");
	    return 1;
	}
    return 0;
}

string
puddle()
{	
    write("The room has many small scattered pools of water"
	     + " formed from the water dripping from the ceiling. The"
	     + " centre of the room contains one particularly large"
	     + " puddle.\n");
    say(QCTNAME(TP) + " studies the puddles carefully.\n");
    return "";
}

string
bpuddle()
{
    write("The large puddle is full of clear water. The bottom"
	  + " of the puddle contains loose sandy mud.\n");
    say(QCTNAME(TP) + " studies the large puddle carefully.\n");
    return "";
}

string
floor()
{
    write("The floor is just normal earth, it is a bit muddy.\n");
    say(QCTNAME(TP) + " studies the floor carefully.\n");
    return "";
}

string
wall()
{
    write("The walls and the ceiling of the room are earthen though"
	  + " they appear to be sturdy enough. Water drips slowly from the ceiling.\n");
    say(QCTNAME(TP) + " studies the room carefully.\n");
    return "";
}

