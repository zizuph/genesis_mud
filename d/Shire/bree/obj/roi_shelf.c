/*
* RoI shelf in ranger treetop to hold items
* Finwe, November 2004
*
* 04 October 2008, ?: last update?
* 30 October 2010, Lavellan: Changed for new saving rack system
*/

inherit "/std/container";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

#define EXP_BROKEN_PAID     "_shire_can_exp_broken_pd_"
#define EXP_NB_PAID         "_shire_can_nb_exp_pd_"
#define MAX_SORT  750 

public void show_list(object for_obj, object *obarr);


public void
create_container()
{   
    set_short("large green shelf");
    set_name("shelf");
    set_adj(({"large", "green"}));
    set_long("It is a large, green shelf, designed to hold supplies donated " +
        "to the Rangers of Ithilien and for those who patrol the area. It " +
        "is hidden in a large branch on the treetrop. You can <sort green " + 
        "shelf> to remove saving items.\n");

    add_prop(OBJ_M_NO_GET, "The shelf cannot be taken.\n");
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,  50000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_ATTACH,    1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
    set_no_show_composite(1);

    if (!IS_CLONE)
    {
        return;
    }

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database());
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

    /*
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
    else */
    if (sizeof(obarr) > 0)
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
    if (arg != "green shelf") 
        return notify_fail("Sort what, the green shelf?\n"); 

    if (sizeof(all_inventory(TO)) < MAX_SORT) 
    { 
        do_sort();        
        write("You sort the green shelf. Everything that saves falls out onto the floor.\n"); 
        say(QCTNAME(this_player()) +" sorts the green shelf.\n"); 
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

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

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

    if (to == this_object() || !objectp(to))
    {
        return;
    }

    remove_rack_entry(ob);
}
