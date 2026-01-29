/*
 * /d/Genesis/sys/equip.c
 *
 * The code in this definition file may help wizards to control the number
 * of clones of their equipment. For more information, see equip.h.
 * 
 * Written by Mercade on March 19 1997.
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

#include <macros.h>

/*
 * Global variable.
 *
 * equipment: ([ string file: object *registered_clones ])
 */
private mapping equipment = ([ ]);

/*
 * Function name: equip_count
 * Description  : Count and return the number of clones of a particular piece
 *                of equipment.
 * Arguments    : string/object file - the object to count the clones of.
 * Returns      : int - the number of registered clones.
 */
public int
equip_count(mixed file)
{
    /* If an objectpointer, make it to a filename. */
    if (objectp(file))
    {
	file = MASTER_OB(file);
    }

    /* Not a string, bad argument. */
    if (!stringp(file))
    {
	return 0;
    }

    /* Not registered. */
    if (!pointerp(equipment[file]))
    {
	return 0;
    }

    /* Check the validity of the object. */
    equipment[file] = filter(equipment[file], objectp);

    /* Return the number of registered clones. */
    return sizeof(equipment[file]);
}

/*
 * Function name: equip_register
 * Description  : Register 'obj' as clone of the particular piece of
 *                equipment.
 * Arguments    : object obj - the clone to register.
 */
public void
equip_register(object obj)
{
    string file = MASTER_OB(obj);

    /* Register the object. */
    if (pointerp(equipment[file]))
    {
	/* Though first see whether it has been registered before. */
	if (member_array(obj, equipment[file]))
	{
	    /* Already registered. */
	    return;
	}

	equipment[file] += ({ obj });
    }
    else
    {
	equipment[file] = ({ obj });
    }
}

/*
 * Function name: equip_unregister
 * Description  : Unregister 'obj' as clone of a particular piece of
 *                equipment.
 * Arguments    : object obj - the clone to unregister.
 */
public void
equip_unregister(object obj)
{
    string file = MASTER_OB(obj);

    /* Was not registered. */
    if (!pointerp(equipment[file]))
    {
	return;
    }

    /* Unregister the object. */
    equipment[file] -= ({ obj });

    /* Unregistered the last clone. */
    if (!sizeof(equipment[file]))
    {
	/* Remove the empty array from the mapping. */
	equipment = m_delete(equipment, file);
    }
}

/*
 * Function name: equip_clone
 * Description  : Clone 'file' when there are less than 'number' clones
 *                registered so far.
 * Arguments    : string file - the file to clone.
 *                int number  - the maximum number of items allowed.
 * Returns      : object - the cloned object or 0 when there were too many
 *                         already.
 */
public object
equip_clone(string file, int number)
{
    object obj;

    /* Skip the possible ".c". */
    sscanf(file, "%s.c", file);

    /* Too many objects registered already. */
    if (equip_count(file) >= number)
    {
	return 0;
    }

    /* Clone the object. */
    obj = clone_object(file);

    /* Register the object. */
    equip_register(obj);

    return obj;
}

/*
 * Function name: equip_alternative
 * Description  : Clone 'file' when there are less than 'number' clones
 *                registered so far. If this fails, clone 'alternative'.
 * Arguments    : string file        - the file to clone.
 *                int number         - the maximum number of items allowed.
 *                string alternative - the alternative to clone.
 * Returns      : object - the cloned object, either 'file' or 'alternative'.
 */
public object
equip_alternative(string file, int number, string alternative)
{
    /* Try to make the clone. */
    object obj = equip_clone(file, number);

    /* Not cloned. There were too many already. */
    if (!objectp(obj))
    {
	/* So, clone the alternative. */
	obj = clone_object(alternative);
    }

    return obj;
}

/*
 * Function name: equip_dump
 * Description  : Will dump information about the number of registered
 *                clones to this_player().
 * Returns      : int 1 - always.
 */
public int
equip_dump()
{
    string *files = sort_array(m_indices(equipment));
    int index = -1;
    int size = sizeof(files);

    while(++index < size)
    {
	write(sprintf("%-50s : %2d\n", files[index],
	    equip_count(files[index])));
    }

    return 1;
}
