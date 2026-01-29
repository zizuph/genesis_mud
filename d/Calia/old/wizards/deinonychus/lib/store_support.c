/* This file is to be inherited into all storerooms for shops. It makes sure
   that there are just a few items in stock in the shop. Too many items
   occupy too much memory, and removing many items at once is bad for game 
   speed.

   To make this work you have to include the following function in your
   store-room code:
   
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

*/

#include <macros.h>
#include <filter_funs.h>

#define	MAX_ITEMS	30
#define	MAX_IDENTICAL	5

static int	max_items;
static int	max_identical;
static object	*remove_list;

/*
 * Function name: set_max_values
 * Description  : Set maximum number of items in a store room
 * Arguments    : items     - max number of items in store room
 *                identical - max number of identical items in store room
 */
void
set_max_values(int items, int identical)
{
    if (items < 1 || items>MAX_ITEMS)
	items = MAX_ITEMS;
    if (identical < 1 || identical > MAX_IDENTICAL)
	identical = MAX_IDENTICAL;
    max_items = items;
    max_identical = identical;
}

/*
 * Function name: store_update
 * Description:   Update the contents of the storeroom, remove excess items
 * Arguments:     ob: the object that is added to the room. Currently unused,
 *                but will be used in the future
 */
void 
store_update(object ob)
{
    object *all_inv;
    int     sz, index, count;

    if (living(ob))
	return;
    if (!remove_list)
	remove_list = ({ });
    if (!max_items)
    {
	max_items = MAX_ITEMS;
	max_identical = 0;
    }
    all_inv = FILTER_DEAD(all_inventory(this_object()));
    sz = sizeof(all_inv);
    if (max_identical && sz > max_identical)
    {
	count = 1;
	for (index = sz - 1 ; index >= 0 ; index--)
  	{
	    if (ob != all_inv[index] &&
		MASTER_OB(all_inv[index]) == MASTER_OB(ob) &&
		all_inv[index]->short() == ob->short() &&
		all_inv[index]->long() == ob->long())
		count++;
	}
	if (count > max_identical)
	{
	    if (member_array(ob, remove_list) < 0)
		remove_list += ({ ob });
	    if (find_call_out("remove_items") < 0)
		call_out("remove_items", 1);
	    return;
	}
    }
    sz -= sizeof(remove_list);
    if (sz > max_items)
	for (index = sz - 1; index > 0; index--)
	    if (member_array(all_inv[index], remove_list) < 0)
		remove_list += ({ all_inv[index] });
    if (sizeof(remove_list))
	if (find_call_out("remove_items") < 0)
	    call_out("remove_items", 1);
}

void
remove_items()
{
    int i;

    for (i=0 ; i<sizeof(remove_list) ; i++)
	if (remove_list[i] && present(remove_list[i]))
	    remove_list[i]->remove_object();
    remove_list = ({ });
}
