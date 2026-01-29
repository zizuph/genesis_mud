/* Cabinet in Kurinost elven tower ruins
 * Arman June 2018
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_container()
{
    set_name("cabinet");
    set_adj("elven");
    add_adj("crystal");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(1241241);

    set_no_pick();

    add_prop(OBJ_I_VALUE,120);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    set_no_show_composite(1);

    add_item("lock", "The lock looks very sophisticated.\n");
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the elven crystal cabinet.\n");
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
    return "elven crystal cabinet";
}

string
long_descr()
{
    return "This is a delicate elven cabinet made of a transparent " +
        "crystal. It is approximately four feet " +
        "in height and very narrow, designed to hold books or scrolls.\n";
}


/* Added to make the key break when the cabinet is unlocked.
 */
public int
do_default_unlock(string str)
{
    object* items;

    if(::do_default_unlock(str) == 1)
    {
        items = all_inventory(this_player());
        for(int i = 0; i < sizeof(items); i++)
        {
            if(items[i]->id("_kurinost_elven_cabinet_key"))
            {
                this_player()->catch_tell("The delicate crystal key " +
                    "vanishes as you unlock the cabinet!\n"); 
                tell_room(environment(this_object()), "As "+
                    QTNAME(this_player())+ " unlocks the elven crystal "+
                    "cabinet, the delicate key suddenly vanishes!\n",   
                    this_player());
                items[i]->remove_object();
                break;
            }
        }
        return 1;
    }
    return 0;
}
