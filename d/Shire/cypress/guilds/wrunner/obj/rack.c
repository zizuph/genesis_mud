/*
 *  Rack for Wild Elves to hold equipment
 *  Based on the trashcan in Hobbiton.
 *  Finwe, May 2004
 *
 * 2007/09/08 Last update
 * 2011/07/21 Lavellan - Commented out (unfinished?) stuff that gave general XP
 *                       for putting broken items into the rack...
 *                     - Made rack saving. Changed "Mithral"->Mithril
 *                     - Made sort remove non-saving rather than saving items
 *                     - Fixed listing of heaps. Stopped it hiding livings.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";
//inherit "/w/finwe/rack_list";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

//#include "defs.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

//#define EXP_BROKEN_PAID     "_shire_can_exp_broken_pd_"
//#define EXP_NB_PAID         "_shire_can_nb_exp_pd_"
#define MAX_SORT  150 


public void show_list(object for_obj, object *obarr);

void
create_container()
{
    set_name(({"rack", "equipment rack"}));
//    set_adj(({"large", "mithral"}));
    set_adj(({"large", "mithril"}));
//    set_short("large mithral rack");
    set_short("large mithril rack");
//    set_long("This large rack is made of mithral. It is durable and sturdy, and set against a wall. It holds equipment donated by Wild Elves, and for other guildmembers to use. It looks like you can <sort rack> to remove saving items.\n");
    set_long("This large rack is made of mithril. It is durable and sturdy, " +
        "and set against a wall. It holds equipment donated by Wild Elves, " +
        "and for other guildmembers to use. It looks like you can <sort rack> " +
        "to remove non-saving items.\n");

    add_prop(OBJ_I_NO_GET, 1);          /* Not gettable       */
    add_prop(CONT_I_IN,1);              /* It's a container!  */
    add_prop(CONT_I_RIGID,1);           /* A rigid object     */
    add_prop(CONT_I_TRANSP,0);          /* Not transparant    */
    add_prop(CONT_I_MAX_VOLUME,1000000); /* Can contain 20 Ltr */
    add_prop(CONT_I_MAX_WEIGHT,1000000); /* Can contain 20 Kg */

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database());
}

mixed enter_inv(object ob, object from)
{
//    int item_val, item_exp, item_b_exp;
//    int brok_val = 10,
//        nb_val = 15;

    ::enter_inv(ob, from);

/*    if(living(ob)) return;

    if (ob->query_prop("_obj_i_broken"))
    {
        ob->remove_prop("_obj_i_broken");
        item_val=(ob->query_value());
        item_exp=(item_val/75);
        if(item_exp == 0) 
            item_b_exp = (50+random(50));
        else
            item_b_exp = item_exp;
        write(item_val + " " + item_exp + " " + item_b_exp + "\n");
        ob->add_prop("_obj_i_broken",1);
//        ob->remove_object();
        TP->add_exp_general(item_b_exp);

    }
*/

    if (from == this_object())
    {
        return;
    }

    add_rack_entry(ob);

}


public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to == this_object())
    {
        return;
    }

    remove_rack_entry(ob);
}


/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (this_object()->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                this_object()->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing on the " + 
                this_object()->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
    int i, price;

    //obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());

    for_obj->catch_tell(print_shop_list(obarr));
}
// sorting routines
/* 
 * Function name: reject_me 
 * Description  : Move item to environment 
 * Returns      : 1 = success  0 = fail 
 */ 
public int 
reject_me(object ob, object env) 
{ 
    if (!ob->move(env) == 0) 
    { 
//   tell_room(env, capitalize(LANG_THESHORT(ob)) + " drops out of " + 
//       LANG_THESHORT(this_object()) + ".\n"); 
   return 1; 
    } 

    return 0; 
} 

/* 
 * Function name: check_lasting 
 * Description  : check to see if item is recoverable or autoloading 
 */ 
public void 
check_lasting(object ob, object env) 
{ 
    if (ob->check_recoverable()) 
//        reject_me(ob, env); 
        return;

    if (ob->query_auto_load()) 
//        reject_me(ob, env); 
        return;
    reject_me(ob,env);
} 

/* 
 * Function name: do_sort 
 * Description  : runs inventory through check_lasting. 
 */ 
public void 
do_sort(void) 
{ 
    map(all_inventory(this_object()), 
         &check_lasting(,environment(this_object()))); 
} 

/* 
 * Function name: start sort 
 * Description  : 
 */ 
public int 
start_sort(string arg) 
{ 
    if (arg != "rack") 
        return notify_fail("Sort what, the rack?\n"); 

    if (sizeof(all_inventory(TO)) < MAX_SORT) 
    { 
        do_sort();        
//        write("You sort the equipment rack. Everything that saves falls out onto the floor.\n"); 
        write("You sort the equipment rack. Everything that won't save " +
        "falls out onto the floor.\n"); 
        say(QCTNAME(this_player()) +" sorts the equipment rack.\n"); 
        return 1; 
    } 

    notify_fail("Too many items. Remove some objects and try again.\n"); 
    return 0; 
} 

// end sort routines
public void 
init(void) 
{ 
    ::init(); 
    add_action(start_sort,  "sort"); 

} 
