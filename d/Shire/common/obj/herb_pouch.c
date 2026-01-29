/*
 * Made pouch recoverable and keepable
 * -- Finwe, April 2002
 *
 * Modification log:
 *   Lavellan (2011/07/11) - changed value (endless money bug otherwise)
 *                         - added wear location, fixed wear detection and typo
 */

inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/common/obj/herb_list";
inherit "/lib/keep";
inherit "/lib/shop";

#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_container()
{
    set_name("pouch");
    set_adj("leather");
    set_pshort("leather pouches");
    set_short("@@short_func@@");
    set_long("@@long_func@@");

    //add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(OBJ_I_VALUE, 60);
    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(CONT_I_CLOSED,     0);
    set_fill_verb("fillpouch");
    set_empty_verb("emptypouch");

    /* some herbs are spell components */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    set_keep();

    set_slots(A_ANY_SHOULDER);
}


/* Function name: short_func
 * Description  : Returns a string for the short description depending
 *                on whether or not there are herbs in the pouch.
 * Returns      : string description
 */
string
short_func()
{
    if (sizeof(all_inventory(TO)))
        return "leather pouch containing herbs";

    return "leather pouch";
}

/* Function name: long_func
 * Description  : Returns a string for the long description depending
 *                on whether or not the pouch is tied to your belt.
 * Returns      : string description
 */
public string
long_func()
{
    string long_desc = "This is a leather pouch to store herbs in. ";

    //if (query_prop(OBJ_M_NO_SELL))
    if (query_worn())
        long_desc += " At present, the pouch is worn over your shoulder.";
    else
        long_desc += " It is possible wear the pouch over your shoulder "
	    + "to prevent it from being stolen or inadvertently sold.";
    return (long_desc + "\n");
}

/* Function name: prevent_enter
 * Description  : Checks that it is an herb.
 * Arguments    : object obj - the object entering
 * Returns      : 1 if it is not an herb, 0 if it is
 */
public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the " + query_name() + ".\n");
        return 1;
    }

    return 0;
}
