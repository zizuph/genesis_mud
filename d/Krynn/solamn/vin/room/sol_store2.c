/* General store for Vingaard Keep by Morrigan, Jan 97       */
/* Taken from the Calia General store by Maniac and Mercade. */
/*
Raven tells you: ahh , in remove_object of store room you add if (SECURITY-
>armageddon_active()) (or something like that) and saving_objects =
map(all_inventory(),  query_recovery()).. then save_object().. in create
restore_object() and slowly clone the items.. I need to check function names
dont remember them exactly thoguht
*
* Runtime fix by cotillion 2002-11-17
*/


#pragma save_binary

inherit "/lib/store_support";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit IN_BASE;

void recover_stock(string *recstr);

#define RECOVERY ("/d/Krynn/solamn/vin/room/store_recover_data")

string *recovery;



#ifdef DISABLE_COMMERCE

int arm = random(2) + 1;


/*
 * This define defines the standard inventory that should be cloned every
 * reset if the shop is not in full stock. The first entry is the function
 * that is used to create the object, the second its filename and the third
 * is the number of objects that should be in stock.
 */
#define MINIMUM_INVENTORY  \
({  ({ "create_object", VARM + "s_gauntlets",3}), \
        ({ "create_object", VARM + "s_helm",3}), \
        ({ "create_object", VARM + "s_shield", 2}), \
        ({ "create_object", VARM + "s_armour", 3}), \
        ({ "create_object", VARM + "s_boots", 3}), \
        ({ "create_object", VARM + "full_armour", arm}), \
        ({ "create_object", VWEP + "two_handed_sword", 2}), \
        ({ "create_object", VWEP + "s_sword", 3}), \
        ({ "create_object", VWEP + "s_shortsword", 2}), \
        ({ "create_object", VWEP + "s_mace", 2}), \
        ({ "create_object", VWEP + "s_halberd", 1}) })

/*
* Global variable
*/
mixed to_check = MINIMUM_INVENTORY;

/*
* extra = ({ function_name, filename }) ... given from reset_room()
*/
int
object_filter(string extra1, string extra2, object obj)
{

    return (function_exists(extra1, obj) == extra2);

}
#endif
void
reset_vin_room()
{
#ifdef DISABLE_COMMERCE
    object *all_inv = all_inventory(this_object());
    object ob;
    int    i, j, k;
    int    num_found;

    for (i = 0; i < sizeof(to_check); i++)
    if ((num_found = sizeof(filter(all_inv,
                        &object_filter(to_check[i][0], to_check[i][1]) )))
        < to_check[i][2])
    {
        for (j = num_found; j < to_check[i][2]; j++)
	{
	    ob = clone_object(to_check[i][1]);
	    ob->move(this_object());
	}
    }
#endif
}

void
recover_stock(string *recstr)
{
    string filenm, *next;
    object result;
    
    if (!sizeof(recstr))
    {
        return;
    }
    
    if (stringp(recstr[0]) && 
	wildmatch("*:*", recstr[0]))
    {
        filenm = explode(recstr[0], ":")[0];
        result = clone_object(filenm);
        result->init_recover(recstr[0]);
        result->move(this_object());
    }
    
    set_alarm(0.5, 0.0, &recover_stock( recstr[1..] ) );
}

void
create_vin_room()
{
    set_short("Storeroom of Solamnic Armoury");
    set_long("This is the storeroom of the Solamnic Armoury in Vingaard "+
        "Keep, used to store items that are sold there.\n");
    add_prop(ROOM_I_INSIDE, 1);
    AE(VROOM + "sol_store","east",0);

    restore_object(RECOVERY);

    if (pointerp(recovery) && sizeof(recovery))
    {
        set_alarm(0.5, 0.0, &recover_stock(recovery));
    }
}


void
remove_object()
{
    object *obs;

    obs = all_inventory();
    obs -= filter(obs, &->may_not_recover());
    recovery = map(obs, &->query_recover()) - ({ 0 });

    save_object(RECOVERY);    
    ::remove_object();
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

