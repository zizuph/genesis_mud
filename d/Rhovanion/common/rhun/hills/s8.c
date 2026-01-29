
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"

init()
{
    ::init();
    add_action("dig", "dig");
}

create_room()
{
    set_short("Seaside");
    set_long("The sand of the beach is quite soft here, and "+
	"warm to the touch.  The gentle waves of the Sea of Rhun "+
	"lap up onto the beach as it continues from northeast "+
	"to southwest.\n");
	
    add_exit(RHUN_DIR+"hills/s4", "northeast");
    add_exit(RHUN_DIR+"hills/s9", "southwest");
    
    add_item(({"beach"}), 
        "The sandy beach leads away from here "+
	"to the northeast and south.\n");
    add_item("sand", "It looks like it would be quite easy to "+
	"dig down into the sand here, perhaps you could find "+
	"some buried treasure?!?\n");
    add_item(({"waves","wave", "water"}), "The waves roll gently up on the soft sand. The water seems cold.\n");

}

int
dig(string str)
{
    NF("Dig where?\n");
    if(!strlen(str))
	return 0;
	
    if((str=="sand")||(str=="in sand"))
    {
	/* Put the whistle for the Rhosgobel quest here */
	
	write("There's nothing down here in the sand, yet."
	    +"  Perhaps the treasure hasn't yet been buried.\n");
	return 1;
    }
    else 
	return 0;
}


