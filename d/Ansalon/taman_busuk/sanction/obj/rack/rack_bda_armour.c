#include "../../local.h"
#include <wa_types.h>

inherit SOBJ + "rack/new_rack";

/*
 * Function name:   create_rack
 * Description:     Basic rack constructor.
 */
void
create_rack()
{
    ::create_rack();
    
    add_adj("armour");
    add_name("rack_armour");
    set_short("armour rack");
    set_long("This is a large rack, made from a blackwood pine native to this "
    + "area. It has been specially designed to hold armours.\n");
} /* create_rack */

/*
 * Function:    valid_item_for_rack
 * Description: Mask this to indicate what type of items can actually
 *              enter the racks.
 * Arguments:   (object) - obj to verify if it can enter
 * Returns:     (int) 1 - Success, 0 - Failure
 */
public int
valid_item_for_rack(object obj)
{
    /* Only accept armours */
    if (!obj->check_armour())
    {
        write("The " + short() + " is no place for " + obj->short() + ".\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */
