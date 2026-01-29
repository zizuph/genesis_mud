inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <tasks.h>
#include <stdproperties.h>
#include "../ctower.h";
 
int found;

void
ctower_reset()
{
    found = 0;
}

void
create_ctower_room()
{
    object door;
    object knight;
  
    set_short("Knight's Cell");
   
    set_long("This cell is more like an apartment "+
       "than a cell.  It is well furnished with a bed, desk and three "+
       "walls full of books.  The room is well lit and rather cozy.\n");
   
    add_item(({"bed"}),  "The bed looks comfy and well "+
       "used.  It is currently unmade.\n" );
   
    add_item(({"desk"}), "@@exa_desc");
   
    add_item(({ "book", "books", "shelves" }),  "There are "+
	"hundreds of books.  All are either novels or religious " +
	"tomes dedicated to Paladine.  You have no time for novels " +
	"and think it would be unwise to tamper with the religious " +
	"tomes.\n");
   
    add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
       "milky crystal that is cold to the touch.\n");
   
    add_item(({"door","crystal_door"}),  "The door is made "+
       "of an opaque crystal that looks fragile but isn't.\n" );
   
    set_noshow_obvious(1);
   
    door = clone_object(CTOWER_OBJ + "door2_b");
    door->move(this_object(), 1);
   
    setuid();
    seteuid(getuid());
  
    knight = clone_object(CTOWER_NPC + "knight");
    knight->move(this_object(), 1);
  
    add_prop(OBJ_S_SEARCH_FUN, "search_it");
  
    ctower_reset();
}
 
string
search_it(object player, string what)
{
    int success;
    object cube;
   
    if (what != "desk")
    {
        return 0;
    }
  
    success = player->resolve_task(TASK_ROUTINE, 
		    ({ TS_INT, SS_AWARENESS }) );
  
    if (!found && success > 0) 
    {
    	if (cube = clone_object(CTOWER_OBJ + "cube"))
    	{
	    found = 1;
	    cube->move(this_object(), 1);
    	}
    
    	return "Your search reveals a crystal cube in the desk.\n";
    }
  
    return 0;
}
 
string
exa_desc()
{
    if (!found)
    {
        return "A cluttered, oak desk.  You can't really tell if there " +
            "is anything of interest without looking more carefully.\n";
    }

    return  "A cluttered, oak desk.\n" ;
}
 



