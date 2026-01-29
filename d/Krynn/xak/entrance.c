/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit XAKOUTROOM
#include "/sys/ss_types.h"
#include <macros.h>

void
create_xak_room() 
{
    set_short("The main entrance");
    set_long("This is the entrance, or at least whats left of the"
	     + " entrance to the ruined city of Xak Tsaroth."
	     + " To your north lies the only passable street left as"
	     + " far as you can see. That street leads into the cities"
	     + " main square. To the south the street breaks up as it"
	     + " enters the cursed marshlands across a ruined obelisk.\n");
    
    add_exit(TDIR + "square.c", "north", 0);
    add_exit(TDIR + "obelisk.c", "south", "@@cross_over", 5);
    OUTSIDE;
    LIGHT;
    add_item(({"street", "streets", "houses", "city", "ruins"}),
	     "@@ruins");
    add_item("obelisk", "@@obelisk");
}

string
obelisk()
{
    write("The obelisk seems to have once been a part of this now"
	  + " ruined city, which you guess to be Xak Tsaroth. It has long"
	  + " since been claimed by the marshlands and now just represents"
	  + " the lost magnificence this city must once have had, before the"
	  + " cataclysm.\n");
    return "";
}

int
cross_over()
{
    write("You cross tenaciously over the ruined obelisk wondering"
	  + ", as it lurches dangerously under you, how on earth"
	  + " you got into this mess.\n");
    return 0;
}

string
ruins()
{
    write("The ruins of this city are pitiful indeed. Wrought by the"
	  + " massive forces of the cataclysm that took place in Krynn many"
	  + " years earlier the streets of this city are all either totally"
	  + " blocked by rubble or they have been dragged underground. Only"
	  + " one street looks even half passable and that lies to your north.\n");
    return "";
}
