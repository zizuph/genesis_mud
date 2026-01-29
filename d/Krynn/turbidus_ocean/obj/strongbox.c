/* 
 * Strongbox on Ergothian galleon.
 *
 * Arman, January 2021.
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

object coins;

#define CHEST_KEY 7007

void
create_container()
{
    set_name("strongbox");
    add_name("box");
    set_adj("iron");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(CHEST_KEY);
    set_pick(90);

    add_prop(OBJ_I_VALUE,120);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    add_item("lock", "The lock looks so sturdy and thick that " +
         "all you might do it watch and admire.\n");
}

/* Added to make the key break when the chest is unlocked.
 */
public int
do_default_unlock(string str)
{
    object* items;

    if(::do_default_unlock(str)==1)
    {
        items = all_inventory(this_player());

        for(int i = 0; i<sizeof(items); i++)
        {
            if(items[i]->id("_ergothian_captain_key"))
            {
                this_player()->catch_tell("As you try to remove " +
                    "the key from the lock, the key breaks!\n");
                tell_room(environment(this_object()), "As "+
                    QTNAME(this_player())+ " tries to remove the " +
                    "key from the lock, the key breaks!\n", 
                    this_player());
                items[i]->remove_object();
                break;
            }
        }
        return 1;
    }
    return 0;
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the chest.\n");
	return;
    }
    ::enter_inv(obj,from);
}

void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}

string
short_descr()
{
    return "iron strongbox";
}

string
long_descr()
{
    return "This is a heavy strongbox made of iron to " +
        "protect the most valuable of items this Ergothian " +
        "galleon may carry.\n";
}
