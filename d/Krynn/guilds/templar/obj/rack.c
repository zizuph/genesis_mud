inherit "/d/Genesis/specials/guilds/objs/describable_rack";

/*
 * Function:    hook_prepend_describe_contents
 * Description: Allows one to customize the text that goes above the
 *              listing of the contents in the rack object.
 */
public void
hook_prepend_describe_contents(object for_obj, object * obarr)
{
} /* hook_prepend_describe_contents */

/*
 * Function:    hook_append_describe_contents
 * Description: Allows one to customize the text that goes after the
 *              listing of the contents in the rack object.
 */
public void
hook_append_describe_contents(object for_obj, object * obarr)
{
} /* hook_append_describe_contents */

/*
 * Function name:   create_rack
 * Description:     Basic rack construct
 * Arguments:       None
 * Returns:         Nothing
 */
void
create_rack()
{
    set_name("rack");
    set_adj("large");
    add_adj("wooden");
    set_long("This is a large rack for holding various items.\n");
} /* create_rack */

/*
 * Function name:   valid_item_for_rack
 * Description:     Mask this to indicate what type of items can actually
 *                  enter the racks.
 * Arguments:       (object) obj - object to put into rack
 * Returns:         (int) 1 - Can enter, 0 - Fail to enter
 */
public int
valid_item_for_rack(object obj)
{
    if (living(obj))
        return 0;
    
    return 1;
} /* valid_item_for_rack */