/*
 * File Name        : pirate_cove.c
 * By               : Arman.
 * Inspiration from : -
 * Date             : March 2005.
 * Description      : The room pirates can sail their boats to.
 *                    Pretty ugly code, but then if it works...
 *
 */
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <macros.h>
#include "/d/Calia/sys/water.h"

#include <stdproperties.h>

inherit "/d/Ansalon/kalaman/std/dock_room_base";

object ship, ship2, pirate;


void
reset_kalaman_room()
{
    object boat_in, boat_in2;

    if (!objectp(ship)) 
    {
	ship = clone_object(BOBJ +"pirate_ship2");
	ship->move(this_object());
    }

    if (!objectp(boat_in = ship->query_boat_in())) 
    {
	ship->config_boat_inside();
	boat_in = ship->query_boat_in();
    }

    if (!objectp(ship2)) 
    {
	ship2 = clone_object(BOBJ +"pirate_ship2");
	ship2->move(this_object());
    }

    if (!objectp(boat_in2 = ship2->query_boat_in())) 
    {
	ship2->config_boat_inside();
	boat_in2 = ship2->query_boat_in();
    }

    if (!objectp(pirate))
    {
	pirate = clone_object("/d/Ansalon/guild/pirates/npc/boat_seller");
	pirate->arm_me();
	pirate->move(TO, 1);
    }

}


void
create_kalaman_room()
{
    set_short("Secluded cove on the edge of Horned Bay");
    set_long("@@long_descr");

    add_item(({"mithas","isle","cliffs","high cliffs","cliff", "mainland"}),
      "All around you rise great cliffs, enclosing this cove except " +
      "for a small passage to your west into Horn Bay. You could " +
      "probably sail out that direction.\n"); 
    add_item(({"bay","horned bay","bloodsea","blood sea"}), 
      "Beyond the cove to your west opens up Horned Bay, which "+
      "stretches further out to the northwest where it meets the Bloodsea.\n");
    add_item(({"water", "waters", "sea"}), "The water within the Bloodsea has "+
      "a strange and reddish colour. Rumour has it that the colour "+
      "is the result of the blood of many victims who lost their "+
      "lives during Krynn's most terrible hour, though it "+
      "could be the clay stirred up from the sea bottom by the "+
      "maelstrom.\n");
    add_item(({"white sands","sands","cove","secluded cove","shore"}),
      "You stand on the white sands of a secluded cove, used by some " +
      "pirates of the Bloodsea as a dock for their ships.\n");
    add_item(({"small passage","passage"}),
      "A small passage leads out of the cove to your west. You could " +
      "only sail out of it though...\n");
    add_item(({"dark cave","cave"}),
      "To your northwest opens up a dark cave, returning you to the " +
      "warren of passages that makes up the hideout of the local " +
      "pirates.\n");
    add_item(({"village", "nethosak","city"}), "You cannot see the city from " +
      "here as the cliffs are too high.\n");


    add_exit("underground_cave","northwest",0,0);
    add_row_exit("/d/Ansalon/goodlund/bloodsea/room/2a", "west", 0, 1);


    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    reset_kalaman_room();

}

string
long_descr()
{ 
    return "You are standing on the white sands of a secluded cove, the waters " +
    "of Horned Bay lapping lightly on the shore. High cliffs enclose " +
    "the cove in all directions except to the west where a small passage " +
    "allows ships to enter and exit. A dark cave opens up in the cliff " +
    "to your northwest.\n";
}


