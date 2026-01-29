
/*	
        Room where guard lives who guards Calian entrance/exit from 
        mountain tunnels to the southern area of foothills of 
        Mount Kyrus. 

        Originally coded by Amelia, adapted by Maniac 7/3/96
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "tun.h"


private int id;
object npc;

void
reset_room()
{
	if(!objectp(npc))
	{
                npc = clone_object(NPCS+"guard_S.c");
		npc->move_living("into the room", TO);
		npc->arm_me();
	}
}


void
create_room()
{
	set_short("A guardroom");
	set_long("You enter a guardroom.  The ceiling, walls and floor "+
		"of this room are solid rock.  On the north side, you "+
		"can see a ladder that leads down to a tunnel, "+
		"which apparently leads underground.  On the south "+
		"side you see cracks in the rock wall that look "+
		"like the outline of a door.\n");

	add_item((({"door", "cracks"})),
		("Upon close examination you see the outlines of a "+
		"door, built right into the wall.  There is even "+
		"a peephole in the door, carefully camouflaged.\n"));
	add_item((({"floor", "ceiling", "walls", "wall", "rock"})),
            ("The floor, ceiling and walls are solid rock, except for an "+
             "opening with a ladder poking through on the north side.  On "+
             "the south side side, you see cracks in the wall.\n"));
        add_item("ladder","A ladder leads down to what looks like "+
		"an opening to an underground tunnel.\n");
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE,1);

	reset_room();

	add_exit(TUN+"tun14", "down", "@@down",0);
}

int
down()
{
	write("You climb down the ladder.\n");
	return 0;
}

void
init()
{
    ::init();
    add_action("cant_open", "open"); 
    id = set_alarm(2.0, 0.0, "guard_hail", TP);
}


void
guard_hail(object tp)
{
   if (objectp(npc) && present(npc, TO) && present(tp, TO))
      {
         tp->catch_msg(QCTNAME(npc) + " bows to you and says, Hail in "+
            "the name of Caliana!\n");
      }
}

int
cant_open(string str)
{
	if ((str=="door")||(str=="the door"))
		{
		write("You can't open the door, because "+
		      "the guard is blocking it.\n");
		return 1;
		}
	/* else */
	return 0;
}

