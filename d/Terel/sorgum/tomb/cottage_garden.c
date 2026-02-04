inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

int shovel_gone = 0;

init()
{
     ::init();
     add_action("do_search", "search");
}

create_room()
{
    set_short("cottage garden");
    set_long(
	"There is a sloppy garden here in the back of the cottage. " +
	"Bushy weeds dominate the garden but in among the " +
	"weeds can be seen droopy turnip tops, shriveled carrots and " +
	"pathetic beans.  The tattered remains of a door hang on broken " +
	"hinges in a doorway that leads into the kitchen of a small " +
	"cottage.  A small path leads up a hill to the east.  " +
	"There is a small toolshed north of here and to the west it " +
	"appears that someone has tried to plant flowers.\n"

    );

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(OBJ_I_SEARCH_TIME, 5);
    
    add_exit(TOMBDIR + "cottage_kitchen", "in", 0);
    add_exit(TOMBDIR + "cottage_graveyard", "east", 0);
    /*  
    add_exit(TOMBDIR + "toolshed", "north", "@@go_north");
    add_exit(TOMBDIR + "cottage_flowers", "west", "@@go_west");        
    */
}

int do_search(string str)
{
     object shovel;

     if (str == "here") {
	  if (!shovel_gone) {
	       shovel_gone = 1;
	       shovel = clone_object(TOMBDIR+"shovel");
	       shovel->move(TO);
	       write("You find a shovel under some weeds.\n");
	  }
	  else {
	          write("Your search reveals nothing special.\n");
	     }
	  return 1;
     }

     return 0;
}
      
go_north()
{
     write("Sorry, the toolshed is not open to the public yet.\n");
     return 1;
}


go_west()
{
     write("Sorry, the flower garden is not open to the public yet.\n");
     return 1;
}
