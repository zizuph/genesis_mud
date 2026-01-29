/*
 *   The storage room of the Solamnian armoury, made by Percy
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "../../local.h"

#define MAX_ITEMS 15
#define MAX_IDENTICAL 3

static int max_items;
static int max_identical;
static object *remove_list;
object rack;

int remove_alarm = 0;

void
create_room()
{
    set_short("The high armoury's store room");
    set_long("This is the store room for the high armoury.\n");
    
    AE(VROOM + "high_armoury", "south", 0);
    
    INSIDE;
    add_prop(ROOM_I_NO_CLEANUP,1);
    set_alarm(1.0,0.0,reset_room);
}

/*Loads in the rack*/
void
reset_room()
{
    if (!rack)
    {
        rack = clone_object(VOBJ + "rack");
        rack->move(TO);
    }
}

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
    {
        items = MAX_ITEMS;
    }

    if (identical < 1 || identical > MAX_IDENTICAL)
    {
        identical = MAX_IDENTICAL;
    }
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
    object *all_inv, *inv_all;
    int     sz, index, count, i;
    
    if (living(ob))
    {
        return;
    }

    if (!remove_list)
    {
        remove_list = ({ });
    }

    if (!max_items)
    {
        max_items = MAX_ITEMS;
        max_identical = MAX_IDENTICAL;
    }

    inv_all = FILTER_DEAD(all_inventory(this_object()));

    for (i=0; i<sizeof(inv_all) ; i++)
    {
        inv_all[i]->move(rack);
    }
    
    all_inv = FILTER_DEAD(all_inventory(rack));
    sz = sizeof(all_inv);

    tell_room(this_object(), sz + " items in rack.\n");
    tell_room(this_object(), max_identical + " max possible identical.\n");

    if (max_identical && sz > max_identical)
    {
        count = 1;
        tell_room(this_object(), "In Identical loop.\n");

        for (index = sz - 1 ; index >= 0 ; index--)
        {
            if (ob != all_inv[index] &&
		MASTER_OB(all_inv[index]) == MASTER_OB(ob) &&
                all_inv[index]->short() == ob->short() &&
                all_inv[index]->long() == ob->long())
            {
	        count++;
            }
        }

        if (count > max_identical)
	{
            if (member_array(ob, remove_list) < 0)
            {
	        remove_list += ({ ob });
            }

            if (!remove_alarm)
            {
	        remove_alarm = set_alarm(1.0,0.0,"remove_items");
            }
            return;
        }
    }
    sz -= sizeof(remove_list);

    if (sz > max_items)
    {
        remove_list += ({ all_inv[sz - 1] });
    }

    if (sizeof(remove_list))
    {
        if (!remove_alarm)
        {
            remove_alarm = set_alarm(1.0,0.0,"remove_items");
        }
    }
}

void
remove_items()
{
    int i;
    
    for (i=0 ; i<sizeof(remove_list) ; i++)
    {
          if (remove_list[i] && present(remove_list[i], rack))
          {
               remove_list[i]->remove_object();
          }
    }
    remove_list = ({ });
    
    remove_alarm = 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

