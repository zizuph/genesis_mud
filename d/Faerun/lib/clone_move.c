#pragma no_clone
#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"

/*
 * Function name: clone_move
 * Description	: Clone and move an object to a destination, insuring
 *                the object actually moves, and removing it if not.
 * Arguments	: string path - The file_name() of the object to clone.
 *                mixed dest  - The location where the object should be
 *                  moved to, (the default is this_object()).
 *                int num - number of copies to clone (default: 1).
 *                string how - Argument passed straight to move_living.
 * Returns	: If num > 1, an array of clone obs will be returned.
 * 		  Otherwise an objectp if successfull, else 0.
 *
 * Notes	: If the object is living, move_living will be used.
 * 	  	  Also, before being moved, it will have arm_me()
 * 	  	  called in it as well, to allow for cloning and wielding
 * 	  	  of eqipment before moving into the destination.
 * 	  	  If it's not living, a simply move() is called.
 * 	  	  If the object cannot be moved by its preferred
 * 	  	  method, it will be destructed.
 */

public varargs mixed
clone_move(string path, mixed dest = previous_object(), int num = 1,
    string how = "M")
{
    int size;
    string euid;
    object *obs, ob;

    if (!strlen(path))
    {
	return 0;
    }
    else
    {
	if (dest == 0)
	    dest = previous_object();

	if (num < 1)
	    num = 1;

	obs = allocate(size = num);
    }

    while(size--)
    {
	if (ob = clone_object(path))
	{
	    if(living(ob))
	    {
		ob->arm_me();

		if(ob->move_living(how, dest, 1, 1) != 0)
		    ob->remove_object();
		else
		    obs[size] = ob;
	    }
	    else
	    {
		if(ob->move(dest) != 0)
		    ob->remove_object();
		else
		    obs[size] = ob;
	    }
	}
    }

    if ((num > 1) && sizeof(obs))
	return obs - ({ 0 });
    else
	return ob;
}
