
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/farlong.h"

init()
{
    ::init();
    add_action("searching_wall", "search");
    add_action("pushing_wall", "push");
}

create_room()
{
    set_short("Small room");
    set_long("This is a small room in the northeast corner of the "+
	"first level of this ruined stone castle.  The walls here "+
	"are especially crumbled, the stones loosened.  The only exit "+
	"is back to the southwest.\n");

    add_item(({"wall", "walls", "stone", "stones", "grey stone"}), 
	"The walls here are made of a light-grey stone.  They have "+
	"begun to crumble in places, due to natural entropy and the "+
	"passage of time.  The east wall is especially crumbled; "+
	"perhaps you should take a closer look at it.\n");
    add_item(({"hall", "hallway", "southeast"}), "A hallway "+
	"stands just southwest of this point.\n");
    add_item("east wall", "The east wall is especially crumbled.  "+
	"Perhaps you could find something if you searched along it.\n");	
	
    AE(RHUN+"castle/hall_e","southwest");

    IN;
}

int
searching_wall(string str)
{
    NF("Search what?\n");
    if(!strlen(str))
	return 0;
    if(!((str=="east wall")||(str=="wall")||(str=="along wall")))
	return 0;
    write("Searching the stones of the eastern wall of this chamber, "+
	"you find that they are quite loose.  You could probably "+
	"push right through the wall if you tried.\n");
    return 1;
}

int
pushing_wall(string str)
{
    NF("Push what?\n");
    if(!strlen(str))
	return 0;
    if(!((str=="east wall")||(str=="wall")))
	return 0;
    write("You push at the stones of the east wall.  They give way, "+
	"and you find yourself in another room!\n");
    say(QCTNAME(TP)+" pushes at the stones, and is suddenly gone!\n");
    TP->move_living("M", RHUN+"castle/stairs0");
    return 1;
}
