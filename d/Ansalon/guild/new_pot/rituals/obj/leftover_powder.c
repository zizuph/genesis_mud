/*
 * Genesis Magic System Leftover Power
 *
 * Leftover power is what happens when someone takes an existing
 * leftover and grinds it into powder. This allows a single leftover 
 * to be used for multiple spells.
 *
 * Created by Petros, December 2011
 *
 * Revisions:
 *   
 *   Lucius, Aug 2016: Remove "food" attributes.
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

inherit "/std/leftover";

/*
 * Function:    query_leftover_powder
 * Description: Convenience function to indicate that this is a
 *              powder object, not just a leftover.
 */
public int
query_leftover_powder(void)
{
    return 1;
}

public string
long_description(void)
{
    string my_verb = "consist";

    if (num_heap() == 1)
        my_verb += "s";
    
    return capitalize(LANG_THESHORT(this_object())) + " " + my_verb 
        + " of the powdered remains "
        + "of " + LANG_ADDART(query_organ()) + " from " 
        + LANG_ADDART(query_race()) + ".\n";
}

/*
 * Function:    leftover_init
 * Description: This configures this powder object to be based on an actual
 *              leftover file.
 * Returns      0/1 - failure/success
 */
public int
leftover_init(string organ, string race)
{
    ::leftover_init(organ, race);

    // weight, volume set to 1/5 of standard leftovers
    set_amount(2);
    add_adj(organ);

    // don't want this to be used for spells that require the whole leftover
    remove_name("_leftover_" + organ);
    add_name("_leftover_" + organ + "_powder");

    // Strip out these names, shouldn't apply to powders.
    remove_name(({ "leftover", "food", "bone", "organ" }));
    remove_pname(({ "leftovers", "foods", "bones", "organs" }));

    add_name("powder");
    add_name("pinch");

    set_short("pinch of " + race + " " + organ + " powder");
    set_pshort("pinches of " + race + " " + organ + " powder");

    add_prop(HEAP_S_UNIQUE_ID, "_leftover_powder_" + race + "_" + organ);
    
    return 1;
}

/*
 * Function name: query_recover
 * Description  : Get the recover string, so that the race and organ are
 *                preserved.
 * Returns      : string - the recover string.
 */
public string
query_recover(void)
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;

    return (MASTER + ":" + num_heap() + "," + query_organ() + "," + query_race());
}

/*
 * Function name: init_recover
 * Description  : Re-initialise the race and organ.
 * Arguments    : string - the recover arguments.
 */
public void
init_recover(string arg)
{
    int size;
    string organ, race;

    if (sscanf(arg, "%d,%s,%s", size, organ, race) == 3)
    {
        leftover_init(organ, race);
        set_heap_size(size);
    }
}

/*
 * Do not eat the powders!
 */
public int
command_eat(void)	{ return 0; }

