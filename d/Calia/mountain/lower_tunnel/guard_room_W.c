/*	room where guard lives, who guards entrance/exit to Gelan

	coder(s):	Amelia
	history:	
            18/9/95  npc changed to global variable           Maniac
            15/9/95  leave_inv to remove alarm for guard hail (Amelia)
            16/5/95 init for enter_inv   Maniac
            5/3/95 updated by Amelia
            5/2/95 created Amelia


	purpose:	functions as western exit/entrance to tunnel
	exits:		to tun0.c, and also to road19.c
	objects:	none
    npcs:            guard_W3.c
	to do:
	bugs:		none known
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
                npc = clone_object(NPCS+"guard_W3.c");
		npc->move_living("into the room", TO);
		npc->arm_me();
	}
}

void
create_room()
{
	object obj;
	set_short("A guardroom");
	set_long("You enter a guardroom.  The ceiling, walls and floor "+
		"of this room are solid rock.  On the east side, you "+
		"can see a ladder that leads down to a tunnel, "+
		"which apparently leads underground.  On the west "+
		"side you see cracks in the rock wall that look "+
		"like the outline of a door.\n");

	add_item((({"door", "cracks"})),
		("Upon close examination you see the outlines of a "+
		"door, built right into the wall.  There is even "+
		"a peephole in the door, carefully camouflaged.\n"));
	add_item((({"floor", "ceiling", "walls", "wall"})),
		("The floor, ceiling and walls are solid rock, except for an "+
		"opening with a ladder poking through on the east side.  On "+
		"the west side, you see cracks in the wall.\n"));
	add_item("ladder","A ladder leads down to what looks like "+
		"an opening to an underground tunnel.\n");
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE,1);

	reset_room();

	add_exit(TUN+"tun0", "down", "@@down",0);
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