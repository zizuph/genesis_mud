/* Basic pub landlord functions */

#pragma no_clone
#pragma strict_types

object pub;
string kitchen;

/*
 * Function name: set_pub
 * Description  : Sets landlord's pub object pointer, to make
 *                it easier to see if he's where he's supposed
 *                to be.
 * Arguments    : ob - Object pointer to set as his pub.
 * Returns      : n/a
 */
void
set_pub (object ob)
{
    if (!pub)
        pub = ob;
}
 
/* Function name: set_kitchen
 * Description  : Sets landlord's kitchen pointer, to make it easier
 *                dealing with him running and hiding from attackers.
 * Arguments    : str - String with the path name to the kitchen.
 * Returns      : n/a
 */
void
set_kitchen (string str)
{
    if (!kitchen)
        kitchen = str;
}

