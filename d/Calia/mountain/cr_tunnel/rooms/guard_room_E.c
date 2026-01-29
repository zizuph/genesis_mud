/*	room guarding east entrance/exit of tunnel

	coder(s):	Amelia
	history :     
                        18/9/95 global variable for npc        Maniac
			15/9/95 corrected alarm to tell to player only
				if player is in room           Amelia
                       16/5/95  init for enter_inv  Maniac
			5/3/95	updated by Amelia
                  	5/2/95	created by Amelia
			16/7/95   changed from guard.c to guard
	purpose:	guards east end of calian tunnel
	exits:		down to tunnel11, out to /croad3
	objects:	none
	npcs:		../monsters/guard.c
	quests:		none
	specials:	can ask guard to look outside or open door
			via guard's add_ask functions
	to do:
	bugs:		no known
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "tunnels.h"
#include <filter_funs.h>


object npc;

void
reset_room()
{
    if(!objectp(npc))
    {
        npc = clone_object(TUNNELS_NPCS+"guard3.c");
        npc->arm_me();
        npc->move_living("into the room", TO);
    }
}

void
create_room()
{
	object obj;
	set_short("A guardroom");
	set_long("You are standing inside a room that looks like "+
		"the inside of a hollow tree.  The walls are grained "+
		"like wood, but are coated with a multicolored resinous "+
		"crystal which sparkles.  There is a strange door "+
		"here, built right into the tree wall.  It is "+
		"camouflaged and contains a small opening that "+
		"looks like it might be a peephole, with a flap of "+
		"bark covering it.\n");

	add_item((({"door", "strange door"})),
		("Upon close examination you see the outlines of a "+
		"door, built right into the tree wall.  You can "+
		"ask the guard to open it.\n"));
	add_item((({"peephole", "opening", "hole"})),
		("There is a peephole in the door, and the "+
		"guard looks through it every now and then.  It is covered "+
		"by a small flap of bark and is well camouflaged.\n"));
	add_item((({"crystal", "resinous crystal"})),
		("The tree seems to have soaked up liquid crystal "+
		"into its very fibers, so that it has become part "+
		"of the tree.\n"));
	add_item((({"tree", "tree wall"})),
		("This room appears to be inside a large hollow "+
		"tree that is imbued with crystal.\n"));
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE,1);

	reset_room();

	add_exit(TUNNELS_ROOMS+"tunnel11", "down", 0,0);
}

void
init()
{
   int id;
   ::init();
   add_action("cant_open", "open");
   id = set_alarm(2.0, 0.0, "guard_hail", TP);
}

void
guard_hail(object tp)
{
   if (objectp(npc) && present(npc, TO) && present(tp, TO))
      tp->catch_msg(QCTNAME(npc)+" bows to you and says, Hail in the "+
         "name of Caliana!\n");
}

/* only way through door, is to ask guard */
int
cant_open(string str)
{
	if((str=="door")||(str=="the door"))
	{
		write("You can't open the door, because the guard "+
			"blocks the way.\n");
		return 1;
	}
	/* else */
	return 0;
}
