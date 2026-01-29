/*
 * Herb Sack
 * Originally coded by Palmer, 2004
 * 
 * Fixed message so when sorted herbs removed, it says short() 
 * Instead of pouch
 * -- Finwe, June 2004
 *
 * Cleaned up sack and changed it to a large rabbit-skin sack
 * --  Finwe June 2007
 */

inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/common/obj/herb_list";
inherit "/lib/wearable_item";
inherit "/lib/shop";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>


#define NO_SELL_PROP "You do not want to sell the " + query_short() + ". Do " + \
    "<keep herb sack> to remove the protection."
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
// #define BACKPACK_SUBLOC  BELT_O_SUBLOC
#include <wa_types.h>

int ttl_moved = 0; // Number of non-glowing herbs moved with ssort

public void show_list(object for_obj, object *obarr);

void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_VOLUME, 2200);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_CLOSED,     0);


    remove_adj("camouflaged");
    remove_adj("green-coloured");
    remove_adj("pack");
    remove_name("pack");
    remove_name("backpack");
    remove_adj("backpack");
    remove_adj("large");
    add_adj(({"large", "rabbit-skin"}));

    set_short("large rabbit-skin sack");
    set_pshort("large rabbit-skin sacks");
    set_long("@@long_description");
    set_name("herb sack");
    set_name("sack");
    set_slots(A_TORSO);
    set_looseness(15);
    set_layers(0);    
    set_fill_verb("fillsack");
    set_empty_verb("emptysack");
    config_default_trade();
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    set_layers(0);
    set_looseness(0);

}


    
/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
 
int
item_filter(object ob)
{
    return IS_HERB_OBJECT(ob);
}

 
public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the " + query_short() + ".\n");
        return 1;
    }

    return 0;
}

    
    
string
long_description()
{
    string long_desc = "This " + query_short() + " is made from tanned rabbit skins and designed to hold herbs. It is soft supple, and can be worn over the shoulder. The inside is lined with canvas to make it durable. <fillsack> will put all your herbs in it, and <emptysack> will retrieve them herbs from the " + query_short() + ".\n";

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_VBFC)
    {
        long_desc += "The " + query_short() + " is not protected from being sold. <keep herb sack> to protect it. ";
    }
    else
    {
        long_desc += "The " + query_short() + " is protected from being sold. <unkeep herb sack> will remove this protection. ";
    }

    return long_desc;
}



int
do_keep(string str)
{
    if (!parse_command(str, TP, " [the] [large] [rabbit-skin] [rabbit skin] [rabbit] 'herb sack' / " +
        "'herb sack' / 'sack' "))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    if (ENV(TO) != TP)
    {
        NFN0("You do not have the " + TO->query_short() + " with you.");
    }

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
        write("You may now sell the " + query_short() + ".\n");
    }
    else
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        write("You will now keep the herb sack when you are selling " +
            "supplies. To be able to sell it again, just type <keep " +
            "sack> again.");
    }
    return 1;
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
//for_obj->catch_tell ("[describe contents]\n");

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
            for_obj->catch_tell("There is nothing in the " + 
                this_object()->query_short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + this_object()->query_short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
//for_obj->catch_tell ("[show list]\n");

    int i, price;

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());
    for_obj->catch_tell(print_shop_list(obarr));
}


public void
query_id_herb(object *ob)
{

    ;

}

/*
 * Function name: reject_me
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
int
reject_me(object ob, object env)
{
    if (ob->move(env) == 0) 
    {  
        //write("You remove "+ LANG_THESHORT(ob) +" from " + 
        //    LANG_THESHORT(this_object()) + ".\n");
	ttl_moved += 1; 
        return 1; 
    } 
    return 0; 
}

/*
 * Function name: check_lasting
 * Description  : check to see if item is recoverable or autoloading
 */
void
check_lasting(object ob, object env)
{
    if (ob->check_recoverable()) 
        return;
    if (ob->query_auto_load())
        return;
    else
        reject_me(ob, env);
}

/*
 * Function name: do_sort
 * Description  : runs inventory through check_lasting.
 */
void
do_sort()
{
    map(all_inventory(this_object()), 
         &check_lasting(,environment(this_object()))); 
}



/*******************************************************************************
*******************************************************************************/
