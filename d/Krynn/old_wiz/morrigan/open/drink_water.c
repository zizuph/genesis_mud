/* Pax Tharkas, outside the entrance to Sla-Mori.
 *
 * 941107 by Rastlin 
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXOUTROOM;			/* A room object */

object niche, hole;
int open, found;

void
create_pax_room()
{

        seteuid(getuid());

	niche = clone_object(POBJ + "niche");
	niche->move(TO);

	set_short("Granite cliff");
	set_long("@@hole_open");

	OUTSIDE;

	add_item("cliff", "@@found_niche");

        add_item(({"stream", "ditch"}), "A small stream trickling " +
            "through the " +
            "canyon. Through the clear water you can see the granite " +
            "of the mountains forming an irregular, but solid, ditch.\n");

        add_item("crevasse", "A small narrow crevasse in the " +
                 "mountainside. Fresh clear water trickles from the " +
                 "crack, and runs downwards, out of the canyon.\n");

        set_alarm(15.0, 45.0, "do_trickle");

        add_exit(VALLEY + "forest7", "north", 0);
}


init()
{
   ::init();
   add_action("drink_water", "drink");
}


string
found_niche()
{
	found = 1;

	return BS("As you are running your hands all over " +
	"the rock wall you suddenly find a small niche in the granite.",70);
}

string
hole_open()
{
	string niche;

	niche = "";

	if(found)
		niche = "Well hidden in the cliff is a small niche. ";

	if(!open)
                return "You are standing in a small canyon. The " +
                "mountainsides bordering the canyon rises steep " +
                "upwards making any movement, except out of the " +
                "canyon, north, impossible. The canyon ends at the " +
                "base of a gigantic granite cliff. " + niche + " At the " +
                "top of the cliff, and the mountainsides, low trees and " +
                "bushes grow, their roots visible, grasping for a hold " +
                "in the sparse soil. Water trickles from a small " +
                "crevasse in the mountainside and runs downwards, north, " +
                "out of the small canyon. On the canyon floor, all " +
                "around you, trees and bushes are growing. There is " +
                "a small almost invisible path going north, into the " +
                "brush.\n";

        return "You are standing in a small canyon. The " +
                "mountainsides bordering the canyon rises steep " +
                "upwards making any movement, except out of the " +
                "canyon, north, impossible. The canyon ends at the " +
                "base of a gigantic granite cliff. There is a gaping " +
                "hole in the rock, the entrance to Sla-Mori." + niche +  
                " At the top of the cliff, and the mountainsides, low " +
                "trees and bushes grow, their roots visible, grasping " +
                "for a hold in the sparse soil. Water trickles from a " +
                "small crevasse in the mountainside and runs downwards, " +
                "north, out of the small canyon. On the canyon floor, " +
                "all around you, trees and bushes are growing. There is " +
                "a small almost invisible path going north, into the " +
                "brush.\n";
}


void
handle_wall()
{
	if(!open)
	{
		tell_room(TO, BS("Silently, a huge block of stone " +
		"separates from the cliff face and begins moving " +
		"slowly to one side. A blast of chill, dank air " +
		"flowes from the gaping hole in the rock.  This " +
		"is supposed to be the entrance into Sla-Mori, " +
		"the burial chamber of Kith-Kanan.", 70));
		if (hole)
			hole->remove_object();
		hole = clone_object(POBJ + "d_o_entrance");
		hole->move(TO);
		open = 1;
		hole->query_other_room()->open_wall();
	}
	else
	{
		tell_room(TO, BS("The stone begins to slide " +
		"silently back into place. There is a light sound " +
		"when the stone becomes one with the rock again.", 70));
		if (hole)
		{
			hole->query_other_room()->open_wall();
			hole->remove_object();
		}
		open = 0;
	}
}

void
do_trickle()
{
   tell_room(TO, "Water trickles from the crevasse and gently down " +
             "the small stream.\n"); 
}


int
drink_water(string what)
{
    NF("Drink what ?\n");

    if ((what == "water") || (what == "from stream") ||
       (what == "from ditch") || (what == "water from stream") ||
       (what == "water from ditch"))
    {
       if (TP->drink_soft(TP->drink_max() / 16,0))
       {
          write("You drink some water from the small stream, and " +
                "feel refreshed.\n");
          say(QCTNAME(TP) + " drinks some water from the small stream.\n");
       }
       else
          write("Hmm, you don't feel thirsty at all at the moment.\n");
       return 1;
    }
    return 0;
}
