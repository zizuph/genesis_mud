/*
 * Knapsack sold in the Union shops
 *   Cir. 032696
 *  
 * Revisions:
 *   Lilith,  Jun 2001:  Removed the rem_old_name func so
 *                       Union members can use the "fill pack" command
 *   Mercade, May 2004:  Removed decay functions.
 *   Lucius,  Jul 2011:  Added plural_short masking.
 *   Lucius,  Jun 2016:  Added table mode display.
 */
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

static private int ktable;
static private string klabel = "none";

public void 
create_wearable_pack(void)
{
    set_name("knapsack");
    set_pname("knapsacks");
    set_adj(({"light","grey"}));
    add_adj("union");
    add_adj("unworn");
    set_short("grey knapsack");
    set_pshort("grey knapsacks");
    set_long("This is a small and very light knapsack, "
      +"made from a thin-weave grey cloth that is soft, almost "
      +"like silk, but very sturdy. You can 'ksort knapsack' to "
      +"separate items that will last from those that will not."
      +"@@check_label@@ ");

    set_cf(this_object());
    set_mass_storage(1); 
    set_slots(A_BACK);
    set_looseness(15);
    set_layers(2);
    set_keep(1); 

    set_alarm(0.0, 0.0, &remove_prop(CONT_I_CLOSED));

    add_prop(OBJ_I_VALUE, 100 + random(50));
    add_prop(CONT_I_HOLDS_COMPONENTS,    1);
    add_prop(CONT_I_CLOSED,              1);
    add_prop(CONT_I_WEIGHT,            500);
    add_prop(CONT_I_VOLUME,            500);
    add_prop(CONT_I_MAX_WEIGHT,     100000);
    add_prop(CONT_I_MAX_VOLUME,     100000);
    add_prop(CONT_I_REDUCE_VOLUME,     150);
    add_prop(CONT_I_REDUCE_WEIGHT,     150);
}

public varargs string
short(object for_obj)
{
    if (query_prop(CONT_I_CLOSED))
	return "closed " + ::real_short(for_obj);
    else
	return ::real_short(for_obj);
}

public varargs string
plural_short(object for_obj)
{
    string pshort = container::plural_short(for_obj);

    if (!strlen(pshort))
	return 0;

    if (query_prop(CONT_I_CLOSED))
	return "closed " + pshort;
    else
	return pshort;
}

/*
 * Function name: reject_me
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
public int
reject_me(object ob, object env)
{
    if (ob->move(env) == 0) 
    {  
	write("You remove "+ LANG_THESHORT(ob) +" from " +
	  LANG_THESHORT(this_object()) + ".\n"); 
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
    object *ob;

    if (!stringp(arg))
    {
	notify_fail("Sort what?\n");
	return 0;
    }

    ob = FIND_STR_IN_OBJECT(arg, this_player());   
    if (sizeof(ob))
    {
	do_sort();       
	return 1;
    }

    notify_fail("You can't seem to sort "+ arg +".\n");
    return 0;
}

public string
check_label(void)
{
    string res = " You can 'klabel <label>' this knapsack. "+
    " Use 'none' to unset the label. Currently it is: ";

    if (klabel == "none")
	res += "unset";
    else
	res += klabel;

    return res + ". You may also 'ktable <on|off>' to change "+
	"the inventory display mode.";
}

public int
f_klabel(string str)
{
    object env;

    if (!strlen(str))
    {
	return NF("What label would you like to "+
	  "assign this "+ short() +"?\n");
    }

    remove_adj(klabel);
    remove_name(klabel);

    klabel = lower_case(str);
    env = environment();

    if (str != "none")
    {
	add_adj(klabel);
	add_name(klabel, 1);

	if (env && (env == this_player()))
	    write("You label your "+ short() +" \""+ klabel +"\".\n");
    }
    else if (env && (env == this_player()))
	write("You remove the labeling from your "+ short() +".\n");

    return 1;
}

public int
f_ktable(string str)
{
    if (!strlen(str))
	return NF("Turn table mode on or off for this "+ short() +"?\n");

    switch(lower_case(str))
    {
    case "on":
	if (ktable)
	{
	    write("Table mode is already enabled.\n");
	}
	else
	{
	    ktable = 1;
	    write("Enabled table display mode for the "+ short() +".\n");
	}
	break;
    case "off":
	if (!ktable)
	{
	    write("Table mode is already disabled.\n");
	}
	else
	{
	    ktable = 0;
	    write("Disabled table display mode for the "+ short() +".\n");
	}
	break;
    default:
	return NF("Turn table mode on or off for this "+ short() +"?\n");
    }

    return 1;
}

public void
init(void)
{
    ::init();

    if (!interactive(environment()))
	return;

    add_action(start_sort, "ksort");
    add_action(f_klabel, "klabel");
    add_action(f_ktable, "ktable");
}

public string
query_recover(void)
{
    return MASTER + ":" + query_keep_recover() +
	query_container_recover() +
	"##KLABEL#"+ klabel +
	"##KTABLE#"+ ktable +"##";
}

public void
init_recover(string arg)
{
    string dummy;

    init_keep_recover(arg);
    init_container_recover(arg);

    sscanf(arg, "%s##KLABEL#%s##KTABLE#%d##%s",
	dummy, klabel, ktable, dummy);

    f_klabel(klabel);
}

/*
 * The below bits are taken from the inventory code of /cmd/live/things.c
 */
static object *
display_category(object for_obj, object *oblist, string category)
{
    if (sizeof(oblist))
    {
	for_obj->catch_tell(HANGING_INDENT(sprintf("%-8s: %s.",
	      extract(category, 0, 7), COMPOSITE_DEAD(oblist)), 10, 0));
    }

    return oblist;
}

public void
describe_contents(object for_obj, object *obarr)
{
    string comp, str;
    object *selection;
    int display, size = sizeof(obarr);

    for_obj->catch_tell(show_sublocs(for_obj));
    str = "The " + this_object()->short();

    if (!size)
    {
	for_obj->catch_tell(str + " is empty.\n");
	return;
    }

    /* Filter all coins and gems. */
    selection = filter(obarr, &->id("coin")) | filter(obarr, &->id("gem"));
    if (!ktable && sizeof(selection))
	obarr -= selection;

    if (ktable)
    {
	obarr -= display_category(for_obj, selection, "Value");
	//      obarr -= display_category(for_obj, FILTER_ARMOUR_OBJECTS(obarr), "Armours");
	obarr -= display_category(for_obj, FILTER_WEARABLE_OBJECTS(obarr), "Clothes");
	obarr -= display_category(for_obj, FILTER_WEAPON_OBJECTS(obarr), "Weapons");
	obarr -= display_category(for_obj, FILTER_HERB_OBJECTS(obarr), "Herbs");
	obarr -= display_category(for_obj, FILTER_POTION_OBJECTS(obarr), "Potions");
	obarr -= display_category(for_obj, FILTER_FOOD_OBJECTS(obarr), "Food");
	obarr -= display_category(for_obj, FILTER_DRINK_OBJECTS(obarr), "Drinks");
	obarr -= display_category(for_obj, FILTER_KEY_OBJECTS(obarr), "Keys");
	obarr -= display_category(for_obj, FILTER_TORCH_OBJECTS(obarr), "Torches");
    }
    else
    {
	comp = COMPOSITE_DEAD(selection + obarr);
	for_obj->catch_tell(HANGING_INDENT(str + " contains " +
	    comp + ".", 2, 0));
    }

    /* Nothing else (visible). */
    display = (sizeof(obarr) != size);
    if (!sizeof(obarr) || !(comp = SILENT_COMPOSITE_DEAD(obarr)))
    {
	if (!display)
	    for_obj->catch_tell(str + " is empty.\n");
    }
    else if (ktable)
    {
	for_obj->catch_tell(HANGING_INDENT("Other   : " + comp + ".", 10, 0));
    }
}
