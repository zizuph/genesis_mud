/*
 * New functions in /std/object.c
 *
 * Explanation of the rationale behind these functions.
 *
 *  1. It is possible to differ between resistance
 *     against the elements in _itself_, as well as
 *     _given_ to other objects.
 *  2. We do not need two properties for each element.
 *     [MAGIC_I_RES_XXX and OBJ_I_RES_XXX]
 *  3. We do not have to go through all items in the
 *     inventory to find the net resistance.
 *  4. Objects need not exist in the inventory to be
 *     able to protect something else.
 *  5. Other magical effects can be registered through
 *     add_magic_effect(), in a similar way.
 *
 * The effect is less CPU, easier routines (see for instance
 * example_ring.c in this dir), more flexibility and a whole
 * lot of new possibilities.
 *
 * Sir Rogon.
 */

#include <stdproperties.h>

mixed *magic_effects = ({});

//-- For now..

#define LCALL this_object()->

/*
 * Function name:  add_magic_effect
 * Description:    Notifies this object that it has been placed
 *                 a magical effect upon it.
 * Arguments:      The effect object, or the filename of
 *                 the code which handles the magical 
 *                 effect. (Filename for a shadow.)
 */
varargs void
add_magic_effect(mixed what)
{
    if (!what)
	what = previous_object();

    magic_effects += ({ what });
}

/*
 * Function name:  remove_magic_effect
 * Description:    Removes the magical effect from the
 *                 list of effects affecting this object.
 * Arguments:      What effect.
 * Returns:        If the effect was found.
 */
varargs int
remove_magic_effect(mixed what)
{
    int il;

    if (!what)
	what = previous_object();

    il = member_array(what, magic_effects);

    if (il == -1)
	return 0;

    magic_effects = magic_effects[0 .. (il-1)] + 
	            magic_effects[(il+1) .. (sizeof(magic_effects)-1)];
    return 1;
}

/*
 * Function name:  query_magical_effects
 * Description:    Returns the magical effects upon this
 *                 object.
 */
mixed *
query_magic_effects()
{
    return magic_effects;
}

/*
 * Function name: query_magic_res
 * Description:   Return the total resistance for this object
 * Arguments:     prop - The searched for property.
 */
int
query_magic_res(string prop)
{
    int no_objs, max, max_add, max_stat, i, *value;
    object *list;

    list = this_object()->query_magic_effects();

    if (!sizeof(list))
	return (int)this_object()->query_prop(PRE_OBJ_MAGIC_RES + prop);

    max_add = 100;

    for (i = 0; i < sizeof(list); i++)
    {
	value = (int *)list[i]->query_prop(prop);
	if (pointerp(value))
	{
	    if ((sizeof(value) > 0) && !value[1])
	    	max_stat = max_stat > value[0] ? max_stat : value[0];
	    else
	        max_add = max_add * (100 - value[0]) / 100;
	}
    }

    if (max_add > 0)
	max_add = 100 - max_add;

    max = max_stat > max_add ? max_stat : max_add;
    max += (int)this_object()->query_prop(PRE_OBJ_MAGIC_RES + prop);

    return max < 100 ? max : 100;
}
