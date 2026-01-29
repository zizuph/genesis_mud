/*
 *  Date:                      What is done:                           By whom:
 *  ---------------------------------------------------------------------------
 *  06/05-2017                Started making it.                       Znagsnuf
 *  08/05-2017                Implementing new code
 *
*/

inherit "/d/Faerun/obj/racks/base_rack";

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>
#include <language.h>

// Update this path to the same path the rack is cloned from
#define RACK_LOG   ("/d/Faerun/obj/racks/rack_log")

int rack_type;

string date = "";
string current_date = "";

/*
* Function name: enter_inv
* Description:   Called when objects enter this container or when an
*                object has just changed its weight/volume/light status.
* Arguments:     ob: The object that just entered this inventory
*                from: The object from which it came.
*/
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    string print, name, weapon;
//    date = ("/d/Gondor/common/obj/clock")->query_date_s();
    date = ctime(time());

    if (from == this_object())
    {
        return;
    }

    print = "";
// Only magical and imbued items logged
    if(ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR)
       || ob->query_prop(OBJ_I_IS_MAGIC_WEAPON)
       || ob->query_prop(MAGIC_AM_MAGIC)
       || ob->query_prop("_obj_s_imbue_short"))
    {
        if((current_date) != date)
        {
            print +=  sprintf(
    "%-22s\n"+
    "------------------------\n",
            date + " - Donated");

            current_date = date;

        }

        name = this_player()->query_name();
        weapon = ob->query_short();

        if (from && this_player())
        {
            print += sprintf("%-11s            %-49s\n", name, weapon);
            write_file(RACK_LOG, print);
        }
    }
}

/*
* Function name: leave_inv
* Description:   Called when objects leave this container or when an
*                object is about to change its weight/volume/light status.
* Arguments:     ob: The object that just left this inventory.
*                to: Where it went.
*/
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    string print, name, weapon;
// we dont use the middle-earth clock for our racks
//    date = ("/d/Gondor/common/obj/clock")->query_date_s();

    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }

    print = "";
// Only magical and imbued items logged
    if(ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR)
       || ob->query_prop(OBJ_I_IS_MAGIC_WEAPON)
       || ob->query_prop(MAGIC_AM_MAGIC)
       || ob->query_prop("_obj_s_imbue_short"))
    {
        if((current_date) != date)
        {
            print +=  sprintf(
    "%-22\n"+
    "------------------------\n",
            date + " - Taken");

            current_date = date;

        }

        name = this_player()->query_name();
        weapon = ob->query_short();

        if (to && this_player())
        {
            print += sprintf("%-11s            %-49s\n", name, weapon);
            write_file(RACK_LOG, print);
        }
    }
}

public void
create_rack()
{
    set_short("equipment rack");
    set_name("rack");
    set_adj("equipment");
    set_long("This massive equipment rack is set deeply into the north wall. " +
        "It stretches nearly the entire length of the chamber and from the " +
        "floor to the ceiling. Countless hooks, chains and straps line its " +
        "interior for effective ordering and storage of various equipment " +
        "types.\n");

    set_no_show_composite(0);

    remove_prop(CONT_I_TRANSP);

    add_prop(CONT_I_MAX_WEIGHT, 6000000);
    add_prop(CONT_I_MAX_VOLUME, 6000000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 1934);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "The rack is too hevy to take.\n");


    rack_type = 0;
}

/*
 * Function name: set_rack_type
 * Description  : Set the type of rack
 * Arguments    : type - the type of the rack (0 - saving items, 1 - non
 *              :   saving items without mark, 2 - non saving with mark)
 */
void set_rack_type(int type)
{
    rack_type = type;
}

/*
 * Function name: is_recoverable
 * Description  : See if we can recover this item
 * Arguments    : ob - the item to check
 * Returns      : 0 when unrecoverable, 1 when it is
 */
int is_recoverable(object ob)
{
    if(ob->query_recover() && !ob->may_not_recover())
        return 1;

    return 0;
}


object *filter_rackable_objects(object *obs) 
{
    object *rack_obs = ::filter_rackable_objects(obs);

    switch(rack_type)
    {
        // Saving items
        case 0:
        {
            rack_obs = filter(rack_obs, is_recoverable);
            break;
        }
    }

    return rack_obs;
}