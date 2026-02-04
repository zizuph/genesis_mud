// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, added connection to the toolshed.

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"

int shovel_gone;

void
reset_room()
{
    shovel_gone = 0;
}

void
init()
{
     ::init();
     add_action("do_search", "search");
}

void
create_room()
{
    set_short("cottage vegetable garden");
    set_long(
	"There is a sloppy garden here in the back of the cottage. " +
	"Bushy weeds dominate the garden but in among the " +
	"weeds can be seen droopy turnip tops, shriveled carrots and " +
	"pathetic beans. The tattered remains of a door hangs on broken " +
	"hinges in a doorway that leads into the kitchen of a small " +
	"cottage. A small path leads up a hill to the east. " +
	"There is a small toolshed north of here and to the west is " +
	"a snow-covered flower garden.\n"
    );

    add_item(({"weeds"}), "The weeds are dry and strawlike now "+
        "that winter is here.\n");
	
	add_item(({"turnips", "turnip tops", "vegetables", "carrots", 
	    "beans", "garden"}), "Their season is past. Winter has dessicated "+
        "everything in this garden.\n"); 
		
	add_item(({"door", "doorway", "cottage", "hinge", "hinges"}),  
        "The tattered remains of a door hang on broken " +
        "hinges in a doorway that leads into the kitchen "+
		"of the small cottage built into the hill.\n");

    add_item(({"toolshed", "shed", "north"}), "A small, "+
        "windowless building made of stone sits north of here. "+
        "It looks like a shed for storing tools.\n");	
		
	add_item(({ "path", "hill", "east"}), "A path leads east "+
        "up to a windswept hill.\n");

    add_item(({ "west", "flowers", "flower garden"}),
        "West lies the remains of a flower garden, covered in "+
        "a layer of snow.\n");
	
    add_item(({"snow", "layer of snow"}), "A thin layer of snow covers "+
        "the ground.\n");	
	
	
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(OBJ_I_SEARCH_TIME, 5);
    
    add_exit("cottage_kitchen", "south", 0);
    add_exit("cottage_graveyard", "east", 0);
    add_exit("toolshed", "north", 0);
    add_exit("cottage_flowers", "west", 0);  
    reset_room();	
}

int do_search(string str)
{
     object shovel;

     if (str == "here") {
	  if (!shovel_gone) {
	       shovel_gone = 1;
	       shovel = clone_object(OBJDIR+"shovel");
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
