/*
 * Try Item Room Enhancement
 *
 * This library gives a room the ability to use "try_item" instead of
 * add_item. The main benefit of try_item over add_item is that it will
 * not replace existing objects.
 *
 * Created by Petros, April 2010
 */
#pragma strict_types

public int  try_item(mixed names, mixed desc);

/*
 * Function:    try_item
 * Description: checks to see if an item already exists within a given object, 
 *              and if it does not, it then adds it as add_item() would.                
 * Arguments:   mixed names - string or array of strings, the
 *                            item name(s).
 *              mixed desc  - string or function, the description.
 * Returns:     int - the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         items_added;
    string      *exists;

    items_added = 0;
    if (pointerp(names)) 
    { 
        exists = ({});
        foreach (string name : names)
        {
            if (this_object()->item_id(name)) 
            {
                exists += ({ name });
            }
        }
        names -= exists;
        if (sizeof(names))
        {
            this_object()->add_item(names, desc);
        }
        items_added = sizeof(names);
    } 
    else if (!this_object()->item_id(names))
    {
        this_object()->add_item(names, desc);
        items_added = 1;
    }
    return items_added;
}
