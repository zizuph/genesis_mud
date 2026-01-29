/*    this is the inside of the man-eating clam
 
   coder(s):   Amelia 
 
 
    objects:    none
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define WADE "/d/Calia/sea/level0/"
#define OYSTER "/d/Calia/sea/level0/wade_99_99"


void
reset_room()
{

   object clam;

   clam = present("clam", TO);


    if(!objectp(clam))
      {
         clam = clone_object(CLAM);
         clam->move_living("X",TO);
      }
}
void
create_room()
{
	set_short("Further from shore...");
	set_long("You are standing waist deep in the sea, further from "+
		"shore.  The blue-green sea is all around "+
		"you, and feels warm and refreshing.  There are seabirds "+
           "fishing here.  The sea extends west all the way to "+
        "where it merges with the horizon.  Far away in the "+
        "northwest you can see a ship that heads away from the "+
        "busy dock of Gelan.  In the south the landscape is "+
        "dominate by Mt. Kyrus.  To the southwest you can see "+
        "through the clear water what appears to be an oyster "+
        "bed.  Blocking the way, however, is a giant clam.  "+
        "You can wade back to the north from here.  "+
        "\n");

	add_item((({"sea", "blue-green sea", "water"})),
		("The water is clear and a perfect temperature. "+
		"You can look down all the way to the bottom.\n"));
	add_item((({"seabirds", "pelicans", "pelican", "sea gulls"})),
		("There are pelicans and sea gulls flying around, "+
		"apparently hunting for fish.\n"));
		
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
   reset_room();
    
	
}

void
init()
{
	::init();
	add_action("dive", "swim");
    add_action("dive","wade");
}
int
dive(string where)
{
    if ((where=="southwest")||(where=="sw"))
	{
    object clam = present("clam", TO);
    if (clam->query_bound())
    {
        tell_room(environment(TP), QCTNAME(TP)+" swims off to the "+
            "southwest.\n",TP);
        write("You swim off to the southwest.\n");
        TP->move_living("M",OYSTER,1);
        tell_room(OYSTER,QCTNAME(TP)+" swims in from the northeast.\n",TP);
	    return 1;
    }
    else
    {
        write("The giant clam emits a large stream of water, "+
            "blocking your path.  You will have to find some "+
            "way to bind this clam before trying to swim by.\n");
        say(QCTNAME(TP)+" tries to swim away but the giant clam "+
            "emits a large stream of water, blocking the path.\n",TP);
        return 1;
    }
	}
    if ((where=="north")||(where=="n"))
    {
        tell_room(E(TP),QCTNAME(TP)+" wades off to the north.\n",TP);
        write("You wade off to the north.\n");
        TP->move_living("M",WADE+"wade_1_1",1);
        tell_room(WADE+"wade_1_1",QCTNAME(TP)+" wades in from the south.\n",TP);
        return 1;
    }
	notify_fail("Swim where?\n");
	return 0;
}

