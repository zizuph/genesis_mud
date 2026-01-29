/*
 * A vine that gets tied to a tree.  You can also climb down it, but that
 * isn't really part of the rope code.
 *					Napture.
 */

#include "my.h"
inherit STD_ROPE;

#define DOWN_VINE (JUNGLE_ROOM + "on_vine3")

create_rope()
{
    set_name("vine");
    set_adj("long");
    set_long("This is a very long, thick vine. It hangs over the edge " +
	"of the platform, heading towards the ground.\n");
}

init()
{
    ::init();
    add_action("do_climb", "climb");
}

int
check_down_rope()
{
    object *inv, down;
    
  /* Down_vine defined in jung_defs.h */
    DOWN_VINE->load_me();
    if (!(down = find_object(DOWN_VINE)))
	return 0;
    inv = all_inventory(down);
    if (sizeof(inv))
	return 1;
    return 0;
}

do_climb(string str)
{
    string dummy;
    int dir, skill;
    object ob1;

#define DOWN 1
#define UP   2
 
    NF("Climb what?\n");
    if (!str)  
        return 0;
    
    dir = 0;
    if (sscanf("xxx " + str + " xxx", "%s down %s", dummy, dummy)==2)
	dir += DOWN;
    if (sscanf("xxx " + str + " xxx", "%s up %s",   dummy, dummy)==2)
	dir += UP;
    sscanf(str, "down %s", str);
    sscanf(str, "up %s", str);
    if (dir == 0)  {
	NF("But which way do you want to climb?\n");
	return 0;
    }
    if (dir == 3)  {
	NF("You can't climb both up and down at the same time!!!!!\n");
	return 0;
    }
	
    NF("Climb "+(dir == DOWN ? "down" : (dir == UP ? "up" : ""))+" what?\n");
    if (!parse_command(str, environment(TP), "%o", ob1))  
	return 0;
    if (ob1!=TO)  
	return 0;

    skill = TP->query_skill(SS_CLIMB);
    if (skill == 0)  {
	write("But you don't know how to climb!\n");
	return 1;
    }
    if (dir == UP)  {
	write("You try to climb up the vine...but as it's tied to the " +
	    "tree here, you don't get very far!\n");
	SAYNAME("", " climbs up the vine - head first into the tree trunk!\n");
	return 1;
    }
    
    if (dir == DOWN)  {
	if (check_down_rope())  {
	    write("You can't climb down the vine as there is someone " +
		  "there, in your way!\n");
	    return 1;
	}
	TP->move_living("climbing down the vine", DOWN_VINE, 1);
	return 1;
    }
    write("Something went wrong! Please 'bug' the last command you did.\n");
    return 1;
}
