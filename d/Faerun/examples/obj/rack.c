/*
 * Sample rack system for guild
 * Based on Rangers rack
 * Finwe, October 2007
 */

inherit "/std/container";
inherit "/d/Faerun/lib/box_list";
inherit "/lib/shop";
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

#define MAX_SORT  500 

public void show_list(object for_obj, object *obarr);


public void
create_container()
{   
    set_short("large wooden rack");
    set_name("rack");
    set_adj(({"large", "wooden"}));
    set_long("It is a large wooden rack to hold stuff for a guild. You can <sort rack> to remove saving items.\n");

    add_prop(OBJ_M_NO_GET, "The rack cannot be taken.\n");
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,  50000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
    set_no_show_composite(1);


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
                (sizeof(obarr) > 1 ? " are" : " is") + " in the " +
                this_object()->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing in the " + 
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

    obarr = FILTER_DEAD(obarr);
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
        reject_me(ob, env); 

    if (ob->query_auto_load()) 
        reject_me(ob, env); 
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
        write("You sort the large wooden. Everything that saves falls out onto the floor.\n"); 
        say(QCTNAME(this_player()) +" sorts the large wooden rack.\n"); 
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
