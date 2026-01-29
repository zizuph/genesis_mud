#include "../../local.h"

#include <wa_types.h>
#include <files.h>

inherit SOBJ + "rack/new_rack";

/*
 * Function name:   create_rack
 * Description:     Basic rack constructor.
 */
void
create_rack()
{
    ::create_rack();
    
    set_name("rack");
    add_name(({"box", "rack_herb"}));
    set_adj(({"massive", "carved"}));
    set_short("massive carved rack");
    set_long("Rather vast and massive, the rack is shaped after some sort of "
    + "flower. Wooden petals are crudely carved from single piece of wood. In "
    + "the middle there is sort of a lid to seal the rack from air and "
    + "humidity.\n");
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
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the " + short() + ".\n");
        return 0;
    }
    
    return 1;
} /* valid_item_for_rack */