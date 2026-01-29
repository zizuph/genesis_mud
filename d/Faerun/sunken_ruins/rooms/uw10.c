/* /d/Faerun/sunken_ruins/rooms/uw10.c
 *
 * Nerull 2019
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SUNKEN_WATER;


/*public string
hook_no_swim(string str)
{
    if ((str == "east") || (str == "south"))
    {
        return "You decide that isn't a good idea, since the currents "+
            "seem dangerous in that direction.\n";
    }
    else if (str == "north")
    {
        return "The cliff blocks your way.\n";
    }

    return "";
}*/


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_room(void)
{
    underwater_room();
    
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 0);

    set_short("Somewhere under the surface of the ocean");
    
    set_long("You are below the surface of the ocean.\n");

    add_exit(SUNKEN_ROOM_DIR + "uw9.c", "up");
    
    reset_room();
}


void
do_add_slow(object playah)
{   

    seteuid(getuid());

    object slow_obj = 0;

    if (present("_slowme_swim_obj", playah))
    {
        return;
    }
    
    slow_obj = clone_object(DEFAULT_DIR + "obj/sea_slow_obj");
    slow_obj->move(playah, 1);
    slow_obj->setup_spell_effect();

    return;
}


/*
 * Function to cleanup props if a player leaves before standing
 */
/*void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    object token;
    
    if(!objectp(to) || !objectp(ob))
      return;
  
    if (objectp(token = present("_slowme_swim_obj", ob)))
    {   
        ob->remove_slow_shadow();
        token->remove_object();
    }
    
    return;
}*/


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            
        } 
		
		if (present("_slowme_swim_obj", ob))
		{
			return;
		}
        
        set_alarm(0.0, 0.0, &do_add_slow(ob));
    }
}


void
reset_room()
{
    ::reset_room();
}
