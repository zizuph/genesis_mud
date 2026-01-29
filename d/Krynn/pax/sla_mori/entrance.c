/* Pax Tharkas, outside the entrance to Sla-Mori.
 *
 * 950331 by Rastlin 
 *
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;			/* A room object */

#define CORRIDORS \
   ({   \
      LOW_LEVEL + "corridor1", \
      LOW_LEVEL + "corridor2", \
      LOW_LEVEL + "corridor3", \
      LOW_LEVEL + "corridor4", \
      LOW_LEVEL + "corridor5", \
      LOW_LEVEL + "corridor6", \
   })

#define GALLERY \
   ({   \
     WALL_LEVEL + "gallery1", \
     WALL_LEVEL + "gallery2", \
     WALL_LEVEL + "gallery3", \
     WALL_LEVEL + "gallery4", \
     WALL_LEVEL + "gallery5", \
     WALL_LEVEL + "gallery6", \
   })

#define ROOMS_TO_LOAD \
   ({   \
     GROUND_LEVEL + "guard_room1", \
     GROUND_LEVEL + "guard_room2", \
   })


object gdwarf, gghost;
object niche, hole;
int open;


void
load_other_rooms()
{
    int i;
    object *roomfiles;

    roomfiles = ROOMS_TO_LOAD;

    for (i = 0; i < sizeof(roomfiles); i++)
	roomfiles[i]->load_me();
}


void
reset_pax_room()
{
    object *roomfiles;

    if(objectp(gdwarf))
	return;

    roomfiles = CORRIDORS;

    gdwarf = clone_object(PMONSTER + "barphu");
    gdwarf->move_living("arrives", roomfiles[random(6)]);

    if(objectp(gghost))
	return;

    roomfiles = GALLERY;

    gghost = clone_object(PMONSTER + "gully_ghost");
    gghost->move_living("arrives", roomfiles[random(6)]);
}


void
create_pax_room()
{
    load_other_rooms();
    reset_pax_room();

    open = 0;

    set_short("Entrance to Sla-Mori");
    set_long("@@hole_open");

    add_item("dust", BS("The dust seems to be very, very old. " +
	"It must have been here for quite some time.", 70));

    add_item("floor", "There is a lot of dust on the cavefloor.\n");

    add_exit(PSLA + "tunnel01", "south");

    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(ROOM_I_LIGHT, 0);

    seteuid(getuid(TO));
}

string
hole_open()
{
    if(!open)
	return BS("You are standing in a small cave inside " +
	  "of Sla-Mori, the old burial chamber of the great " +
	  "elven king Kith-Kanan. You can sense that this is " +
	  "a place of evil. The floor is coverd with a great " +
	  "deal of dust. On the south wall is a tunnel, leading " +
	  "deeper into Sla-Mori.", 70);

    return BS("You are standing in a small cave inside of Sla-Mori, " +
      "the old burial chamber of the great elven king " +
      "Kith-Kanan. You can sense that this is a place of " +
      "evil. The gaping hole in the rock provides enough " +
      "light to show all the dust on the floor and the tunnel " +
      "on the south side of the cave, that is leading deeper " +
      "into Sla-Mori.", 70);
}

void
open_wall()
{
    if(!open)
    {
	tell_room(TO, BS("Silently, a huge block of stone " +
	    "separates from the cliff face and begins moving " +
	    "slowly to one side.", 70));

	if (hole) hole->remove_object();

	hole = clone_object(POBJ + "d_entrance");
	hole->move(TO);
	open = 1;
	change_prop(ROOM_I_LIGHT, 1);
    }
    else
    {
	tell_room(TO, BS("The stone begins to slide " +
	    "silently back into place. There is a light sound " +
	    "when the stone becomes one with the rock again.", 70));

	if (hole) hole->remove_object();

	open = 0;
	change_prop(ROOM_I_LIGHT, 0);
    }
}











