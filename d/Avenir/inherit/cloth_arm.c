/*
 * Just some redefinitions to make cloth armours look a little
 * better. Ie, they will be 'ripped' instead of 'broken'.
 *    Cirion, August 1996
 *
 * * Lucius May 2009: Fixed the rip part to work with a mudlib change.
 *   Lilith June 2022: Fixed bug with remove. It was being called twice when
 *      items were broken, which normally isn't a problem unless you're doing
 *      things like adding and removing skills and such. 
 *   Zizuph July 2022: Removed query_likely_cond override which was broken.
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: is_cloth_armour
 * Description	: A function to allow for segregating these cloth
 * 		  based armours from other types via calls and filters.
 * Arguments	: none
 * Returns	: 1 - always.
 */
public nomask int
is_cloth_armour(void)	{ return 1; }

/*
 * Function name: arm_condition_desc
 * Description:   Returns the description of this armour
 */
public string
arm_condition_desc(void)
{
    string str;

    if (query_prop(OBJ_I_BROKEN))
        return "It is torn to shreads.\n";

    switch(condition - repair)
    {
        case 0:
            str = "is intact and without any rips";
            break;
        case 1:
        case 2:
            str = "has a few tears in it";
            break;
        case 3:
        case 4:
            str = "has a number of rips and tears";
            break;
        case 5:
        case 6:
        case 7:
            str = "has many rips and tears in it";
            break;
        default:
            str = "is likely to fall apart any second";
            break;
    }

    return "It " + str + ".\n";
}

public varargs void
remove_broken(int silent)
{
    /* If the wizard so chooses, this message may be omitted. */
    if (!silent && wearer && worn)
    {
        tell_object(wearer, "The " + short(wearer) + " is torn "
          + "to shreds!\n");
        tell_room(environment(wearer), "The " + QSHORT(this_object()) +
            " worn by " + QTNAME(wearer) + " is torn to shreds!\n", wearer);
    }

    ::remove_broken(1);
}

/* Because the lovely administration has broken certain bits
 * of functionality, I've had to replicate these sections
 * from /std/object.c with the slight modification since the
 * aforementioned lovely administration also refuses to fix
 * or otherwise correct what they did.  Par for the course.
 */
public varargs string 
short(object for_obj)
{
    if (!obj_short)
    {
        if (sizeof(obj_adjs) && sizeof(obj_names))
            obj_short = implode(obj_adjs," ") + " " + obj_names[0];
        else if (sizeof(obj_names))
            obj_short = obj_names[0];
        else
            return 0;
    }

    string result = (query_prop(OBJ_I_BROKEN) ? "ripped ": "");
    return result + check_call(obj_short, for_obj);
}

public varargs string
plural_short(object for_obj)
{
    if (!obj_pshort)
        return 0;

    if (!check_seen((objectp(for_obj) ? for_obj : this_player())))
        return 0;

    string result = (query_prop(OBJ_I_BROKEN) ? "ripped ": "");
    return result + check_call(obj_pshort, for_obj);
}
