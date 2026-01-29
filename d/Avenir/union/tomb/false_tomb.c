/*
 * False tomb of Akram
 *   Cirion, May 1, a997
 */
#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/quest";

#include "defs.h"
#include <tasks.h>
#include <composite.h>

#define URN_ID		"_Avenir_tomb_urn_id"
#define MAX_URNS	25


public void
reset_room()
{
    int size = NUM_ITEMS(URN_ID);
    while(size < MAX_URNS)
    {
	object urn = clone_object(TOBJ + "urn");
	urn->add_name(URN_ID);
	urn->move(TO);
	size++;
    }
}

public string
desc_urns(void)
{
    object *urns = filter(all_inventory(TO), &->id(URN_ID));

    if (!sizeof(urns))
	return "";

    if (sizeof(urns) == 1)
    {
	return " Standing in the northwestern corner near the "+
	    "doorway is " + COMPOSITE_DEAD(urns) + ".";
    }
    return " Scattered in the northwestern corner next "+
	"to the doorway are "+ COMPOSITE_DEAD(urns) + ".";
}

public void
create_room(void)
{
    set_short("solemn tomb");
    set_long("Pale walls of stark white marble rise up to a vaulted "+
	"ceiling high above. In the very center of the room rises, "+
	"as if born of the very stone upon which it rests, a massive "+
	"massive sarcophagus.@@desc_urns@@ A passage framed by a solid "+
	"lintel leads along a passage to the west, and a long and "+
	"narrow opening stands in the eastern wall.\n");

    add_item(({"floor","ground"}),
	"It is made from the same marble as the walls.\n");
    add_item(({"coffin","sarcophagus"}),
	"It is a massive structure, a perfect rectangle made from the "+
	"same marble as the floor. The lid of the sarcophagus is "+
	"decorated with images of spheres and flowers, faces and "+
	"strange, weaving patterns.\n");
    add_item(({"lid","top"}),
	"It is massive, far too heavy to ever be moved by mortal hands.\n");
    add_item(({"wall","walls"}),
	"The walls are perfectly smooth and white marble.\n");
    add_item(({"door","doorway","west","passage"}),
	"The doorway, framed by a wooden lintel, leads out into a dim "+
	"passage to the west.\n");
    add_item(({"lintel","frame"}),
	"The lintel surrounding the doorway to the west is made from "+
	"solid ashwood, ages old.\nInscribed along the top of the "+
	"lintel are words.\n");
    add_item(({"crack","east","east passage","opening"}),
	"The opening to the east is narrow, just wide enough to be able "+
	"to squeeze through. It runs from the floor to the ceiling, "+
	"making it seem as if a great force moved the earth, placing a "+
	"crack deep into the heart of the world.\n");
    add_item(({"words","word"}),
	"We pass through this world watching the flickering shadows of "+
	"reality. The weight of the things of the world will open the way, "+
	"a shadow shall guide your eyes, the words shall follow you and "+
	"open the door to Grace.\n");

    add_cmd_item(({"lintel","words","word"}), "read",
	"We pass through this world watching the flickering shadows of "+
	"reality. The weight of the things of the world will open the "+
	"way, a shadow shall guide your eyes, the words shall follow "+
	"you and open the door to Grace.\n");
    add_cmd_item(({"sarcophagus","coffin","lid","top"}), "open",
	"It will not move.\n");
    add_cmd_item(({"sarcophagus","coffin","lid","top"}), "lift",
	"You hands cannot find a good hold on the surface of the lid.\n");
    add_cmd_item(({"sarcophagus","coffin","lid","top"}),
	({ "move", "push", "pull" }),
	"The massive stone does not budge.\n");
    add_cmd_item(({"sarcophagus","coffin","lid","top"}), "break",
	"The stone is solid and impenitrable.\n");
    add_cmd_item(({"sarcophagus","coffin","lid","top"}), "kick",
	"Frustrated?\n");
    add_cmd_item(({"crack","slit"}), ({"enter","squeeze"}),
	"@@check_east@@");

    add_exit(THALLW, "east", "@@check_east@@", 0, 1);
    add_exit("entry_passage2", "west");
    reset_room();
}

public int
check_east(void)
{
    int move_him;

    if (query_verb() == "enter" || query_verb() == "squeeze")
        move_him = 1;

    if (TP->query_encumberance_volume() > 40)
    {
        write("You are carrying too much to fit through the narrow passage.\n");
        return 1;
    }

    write("You squeeze through the narrow slit to the east.\n");

    if (move_him)
        TP->move_living("through the narrow slit.\n", THALLW, 1, 0);

    return move_him;
}
