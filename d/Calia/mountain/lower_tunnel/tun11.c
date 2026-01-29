/* Lower tunnel room

   coder(s):     Amelia
                 Digit
   history:
                 5/3/96     some amendments, s exit added    Maniac
                25/5/95      northwest exit changed    Maniac
                23/2/95     added elevator/ice chute - Digit
                5/2/95     created - Amelia
   purpose:      Quick transportation from tunnel to Palace
   objects:      none
   npcs:         elevgnome.c
   quests:       none
   special:      Currently the bottom of the ice chute as well as
                 the bottom of the elevator shaft.
   to do:        Add the gnome (elevator operator) and the mule sounds
   bugs:         none known
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "tun.h"

object gnome;

void
reset_room()
{
    if (!gnome) {
        gnome = clone_object(TUN+"elevgnome");
        gnome->move_living("", this_object());
    }
}


void
create_room()
{
	set_short("An underground tunnel");
	set_long("The tunnel opens into a large cave.  Piled against "+
		"the rock wall to the west, you see a heap of broken tools " +
                "and other junk. Judging by the fact there is also " +
                "a large curious opening in the east wall and the lower " +
                "end of an ice chute a few metres away, it would " + 
                "seem that the engineers have been hard at work here.\n");

   add_item("tunnel", "A long tunnel runs off to the northwest from here, " +
                      "while there is a somewhat shorter one to the south.\n");
   add_item((({"torch", "torches", "blue torches"})),
		("The torch does not glow with ordinary fire, but "+
		"instead has a ball of glowing blue crystal at the end.\n"));
   add_item("east wall", "Judging by the fact there is " +
                "a large curious opening in the east wall and the lower " +
                "end of an ice chute a few metres away, it would " +
                "seem that the engineers have been hard at work here.\n");
   add_item((({"opening","curious opening", "large opening", 
              "large curious opening"})),
		("@@closed_open"));
   add_item((({"chute","ice chute", "lower end", "end"})),
           ("The chute leads upwards into the mountain and is made "+
           "from ice.  It is lit by some sort of sparkling substance "+
           "which coats its walls.\n"));
   add_item((({"substance","sparkling substance"})),
           ("It sparkles like a crystalline resin and coats the "+
           "walls of the chute.\n"));
   add_item(({"heap", "broken tools", "junk", "tools", "west wall" }), 
		("Piled against the west wall of the cave is a heap of " +
                 "obviously useless junk.\n"));

    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_I_INSIDE, 1);

   add_exit(TUN+"tun4", "northwest", "@@travel_tunnel", 2);
   add_exit(TUN+"elevator","opening", 0, 0);
   add_exit(TUN+"tun12", "south", 0, 0); 
   reset_room();
}


int
travel_tunnel()
{
    write("You walk for about a mile down the tunnel.\n");
    return 0;
}

string
closed_open()
{
	string *list;
	
	list = query_exit();
	if(list && (member_array("opening",list)!= -1))
	    return("The opening leads to a small wooden room.\n");
	
	return("The opening looks very dark! Better not go in there.\n");
}
