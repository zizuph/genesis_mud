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
    
    add_adj("polearm");
    add_name("rack_polearm");
    set_short("polearm rack");
    set_long("This is a large rack, made from a blackwood pine native to this "
    + "area. It has been specialy designed to hold polearms.\n");
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
    /* Only accept polearms */
    if (!obj->check_weapon() || obj->query_wt() != W_POLEARM)
    {
        write("The " + short() + " is no place for " + obj->short() + ".\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */
