inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("thicket");
    set_long(
        "You are standing in a dark hillside thicket surrounded by " +
	"grotesquely gnarled oak trees.  Animal footprints are visible " +
	"in the frost hardened ground.  In front of the oak tree is an " +
	"enormous clump of savage briars.\n"
    );

    add_item(({"briars", "clumps"}), 
        "The briars are rather thick and are covered with large sharp " +
	"looking barbs.\n"
    );

    add_item(({"footprints", "animal footprints"}),
        "You don't recogize the footprints as belonging to any animal you " +
        "know of.  Whatever left them had big feet with very large claws " +
	"though.\n"
    );    

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "The oak trees are ancient and gnarled so grotesquely you wonder " +
        "if perhaps they were once diseased or cursed by some evil being.\n"
    );

    add_item("thicket", "It's an ordinary thicket.\n");

    add_item("ground", 
	"The ground has strange animal footprints pressed into the hardened " +
	"frost.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "forest01", "east"); 
}



public int enter(string str)
{
    notify_fail("What?\n");
    
    if (!strlen(str))
    {
        return 0;
    }
    if (parse_command(str,({}),"[into] [the] 'thicket' / 'briars' [of] [thorns]"))
    {
        write("You push your way carefully into the thicket, "+
            "braving its thorns.\nOuch ouch ouch!\n\n");
        TP->heal_hp(-50);
        TP->move_living("into the thicket of thorns. You hear cursing",
            "/d/Terel/sorgum/tomb/forest02");
        return 1;
    }

    
    return 0;
}



public void init()
{
    ::init();
    
    add_action(enter,"enter");
    add_action(enter,"walk");
    add_action(enter,"push");
}
