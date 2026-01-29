/*
 * Drop room container.
 *   Cirion 033096
 *
 * Revisions:
 *	Lilith, Feb 2004: Added sort ability
 *	Lilith, Apr 2004: Updated sort ability
 *	Lucius, Mar 2005: Updated to use different list code
 *	Lucius, Jun 2011: Updated prop code to accept recovered items
 *	Lucius, Aug 2011: Updated to use modified list code
 *	Lilith, Jul 2014: Reversed sort so non-saving items fall out
 *	Lucius, Jun 2016: Fixed above change to work, added Text Bock Support.
 *			  Added some interactive checks and block drinks.
 *  Lilith, Aug 2021: Capacity of case increased.
 *
 */
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

inherit "/std/receptacle";
inherit "/d/Avenir/inherit/logrotate";
inherit "/d/Avenir/inherit/shop_list";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

#include <files.h>
#include "../defs.h"

#define MAX_SORT  500

//#define LOGGING
#define CASE_LOG_GET  (GUILDLOG + "case_get")
#define CASE_LOG_PUT  (GUILDLOG + "case_put")

private static int alarm;
private static object *sorted;

public int
special_sort(object a, object b)
{
    int v1, v2;

    v1 = a->query_prop(OBJ_I_VOLUME);
    v2 = b->query_prop(OBJ_I_VOLUME);

    if (v1 == v2)
	return 0;
    if (v1 < v2)
	return 1;
    if (v1 > v2)
	return -1;
}

public string
external_within(void)
{
    object *obs = all_inventory();
    int size = sizeof(obs);

    if (!size)
	return "nothing";

    if (size <= 10)
	return COMPOSITE_DEAD(obs);

    obs = sort_array(obs, special_sort)[0..min(4, sizeof(obs) - 1)];
    return "many objects, most notably " + COMPOSITE_DEAD(obs);
}

public void
describe_contents(object for_obj, object *obarr)
{
    do_list("all");
}

/*
 * Function name: within
 * Description:   Give a description of items in this container
 */
public string
within(void)
{
    object *stuff;

    if (!query_prop(CONT_I_CLOSED))
	return "";

    if (!sizeof(all_inventory(TO)))
	return " The case is bare.";

    do_list("all");
    return "";
}

public string
show_help(void)
{
    if (!IS_MEMBER(TP))
	return "";

    return " Your Jazur blessed eyes make out the words "+
	"'help arsenal' etched into the leaded glass.";
}

public void
create_receptacle(void)
{
    if (!IS_CLONE)
	return;

    set_name(({"case", "_union_case"}));
	set_adj(({"union", "adamantine", "metal", "weapon"}));
    set_short("long metal case");
    set_long("It is a long dark case of a dark metal, similiar "+
      "to adamantine. The front panel is leaded glass lined "+
      "with strips of weaving decorations. This is where the "+
      "Shadow Union stores weapons and other items of the "+
	  "guild's armamentarium."+
      "@@show_help@@@@within@@ ");
    add_item("lock", "What seems to be the lock is a tiny, "+
      "perfectly half spherical indentation on the "+
      "western end of the case.\n");

    remove_prop(CONT_I_TRANSP);

    add_prop(CONT_I_LOCK, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_MAX_WEIGHT, 10000000);
    add_prop(CONT_I_MAX_VOLUME, 10000000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 8549);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It is attached to the wall by thick "+
	"metal and stone brackets.\n");

    set_no_pick();
    set_key(TOKEN_ID);
    set_cf(TO);

    set_no_show_composite(1);

    set_maxlist(100);
    set_show_price(0);
    config_default_trade();
    set_store_room(file_name(TO));

    // object gets cloned, so don't need recovery for it.
    object bandeleria = clone_object(OBJ + "band_s");
    bandeleria->add_prop("_obj_i_do_not_restore", 1);
    bandeleria->move(TO, 1);

    // Set options and initialize auto-save functionality
    set_enable_logging(0);
    set_enable_recovery(1);
    init_database();
    set_alarm(0.0, 0.0, recover_objects_from_database);
}

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    force_new_list();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from == TO)
	return;

    // set keep on all objects by default
    ob->set_keep(1);

    // store the item for auto-save
    add_rack_entry(ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to == TO || !objectp(to))
	return;

    // remove the item from auto-save list
    remove_rack_entry(ob);
}

public int
prevent_enter(object ob)
{
    string dirty;

    if (living(ob))
    {
	TP->catch_msg(QCTNAME(ob) + " is repelled from being "+
	    "placed in the case.\n");
	return 1;
    }

    if (ob->adjectiv_id("dirty"))
	dirty = "unclean";
    else if (ob->adjectiv_id("filthy"))
	dirty = "filthy";
    else if (ob->adjectiv_id("rotten"))
	dirty = "rotten";
    else if (ob->adjectiv_id("dusty"))
	dirty = "dusty";
    else if (ob->adjectiv_id("rancid"))
	dirty = "rancid";
    else if (ob->adjectiv_id("bloody"))
	dirty = "bloody";
    else if (ob->adjectiv_id("stinky"))
	dirty = "stinking";
    else if (ob->adjectiv_id("stinking"))
	dirty = "stinking";

    if (strlen(dirty))
    {
	if (this_interactive())
	    write("Do not defile the purity of case with "+ 
        dirty + " items.\n");
	return 1;
    }

    if (IS_FOOD_OBJECT(ob) || IS_DRINK_OBJECT(ob))
    {
	if (this_interactive())
	    write("Placing food in the case would be unclean.\n");
	return 1;
    }

#ifdef SHADOW
    if (IS_CONTAINER_OBJECT(ob))
    {
	if (!ob->query_prop(CONT_I_CLOSED))
	    clone_object(SHADOW)->shadow_me(ob);
    }
#endif

#ifdef LOGGING
    if (this_interactive())
    {
	logrotate(CASE_LOG_PUT, ctime(time()) +": " +
	    this_player()->query_real_name() +
	    " put "+ ob->short() +" in the case.\n");
    }
#endif

    return 0;
}

/*
 * Function name: prevent_leave
 * Description:   only friends and union members may get items.
 */
public int
prevent_leave(object ob)
{
    if (U_IS_PUNISHED(TP, U_PUNISHED_NOCASE))
    {
	write("A shadow slides across your hand. It wraps "+
	  "around your wrist and squeezes so tightly that "+
	  "your fingers cannot grasp anything.\n "+
	  "A voice whips through your mind:  You dare defy "+
	  "the Will of the Elders?!\n"+
	  "You jerk your hand away from the case and its "+
	  "contents.\n");
	say(QTNAME(TP)+" starts to reach for something in "+
	  "the weapons case, then "+HE(TP)+" jerks back "+
	  HIS(TP)+" hand in apparent pain.\n");
#ifdef LOGGING
	logrotate(CASE_LOG_GET, ctime(time()) +": " +
	  this_player()->query_real_name() +" tried to get "+
	  ob->short() +" from the case.\n");
#endif
	return 1;
    }

    if (!IS_MEMBER(TP))
    {
	write("A shadow slides across your hand. It wraps "+
	  "around your wrist and squeezes so tightly that "+
	  "your fingers cannot grasp anything.\n "+
	  "You jerk your hand away from the shelf and its "+
	  "contents.\n");
	say(QTNAME(TP)+" starts to reach for something on "+
	  "the weapons case, then "+HE(TP)+" jerks back "+
	  HIS(TP)+" hand in apparent pain.\n");
#ifdef LOGGING
	logrotate(CASE_LOG_GET, ctime(time()) +": " +
	  this_player()->query_real_name() +" tried to get "+
	  ob->short() +" from the case.\n");
#endif
	return 1;
    }
    else
    {
#ifdef SHADOW
	ob->remove_union_case_shadow();
#endif
#ifdef LOGGING
	logrotate(CASE_LOG_GET, ctime(time()) +": " +
	  this_player()->query_real_name() +" took "+
	  ob->short() +" from the case.\n");
#endif
	return 0;
    }
}

/*
 * unlock() returns 1 if the container does *not* get unlocked.
 */
public int
unlock(object ob)
{
    if (ob != TO)
	return 0;

    /* The case will not open for those who are punished */
    if (U_IS_PUNISHED(TP, U_PUNISHED_NOCASE))
    {
	write("Your sphere seems to slide away from the lock.\n");
	return 1;
    }

    return 0;
}

public int
open(void)
{
    if (objectp(TP) && present(TOKEN_ID, TP))
    {
	write("You slide your sphere into the indentation on the "
	  +"case.\nThe case opens.\n");
	say(QCTNAME(TP)+" does something with the case.\nThe case "
	  +"slides open.\n");
	return 1;
    }

    return 0;
}

public int
close(void)
{
    write("You slide the case shut.\n");
    say(QCTNAME(TP)+" slides the case shut.\n");
    tell_room(ENV(TO),"It closes with a soft 'click'.\n");

    add_prop(CONT_I_LOCK, 1);
    return 1;
}

/*
 * Ugly, ugly, but the only way I can think to allow
 * the case to be 'unlocked' for those who are carrying a
 * key.
 */
public mixed
query_prop(string str)
{
    switch(str)
    {
    case CONT_I_LOCK:
	if (objectp(TP) && (query_verb() == "open"))
	{
	    if (present(TOKEN_ID, TP) && !unlock(TO))
		return 0;
	}
	break;
    case CONT_I_CLOSED:
	if (calling_function(-1) == "slow_recover_objects")
	    return 0;
	break;
    }
    return ::query_prop(str);
}

/*
 * Function name: finish_sort
 * Description  :
 */
private void
finish_sort(void)
{
    alarm = 0;

//  if (query_prop(CONT_I_CLOSED))
// 	return;

    filter(sorted, &->move(environment()));
    sorted = 0;

    tell_room(environment(),
	"Everything that does not save falls out.\n");
}

/*
 * Function name: start sort
 * Description  :
 */
public int
start_sort(string arg)
{
    if (U_IS_PUNISHED(TP, U_PUNISHED_NOCASE))
    {
	notify_fail("You are restricted from doing that.\n");
	return 0;
    }

    if (arg != "case")
    {
	notify_fail("Sort what? The case?\n");
	return 0;
    }

    if (alarm)
    {
	write("The case is already being sorted.\n");
	return 1;
    }

    object *arr = all_inventory(TO);

    if (sizeof(arr) > MAX_SORT)
    {
	write("Too many items. Remove some objects and try again.\n");
	return 1;
    }

    write("You start sorting the case.\n");
    say(QCTNAME(this_player()) +" starts sorting the case.\n");

    sorted = filter(arr, &->check_recoverable()) +
    filter(arr, &->query_auto_load());
    sorted = arr - sorted;
    alarm = set_alarm(0.5, 0.0, &finish_sort(arr));

    return 1;
}
/* This is invoked from the room now -- Lilith, Mar 2022
public int
help_case(string str)
{
    if (str != "case" && str != "here")
	return notify_fail("Help what? Help case?\n");

    str = LIST->query_union_text("case_help");

    if (!strlen(str))
	write("There seems to be no help available.\n");
    else
	write(str);

    return 1;
}
*/
public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP))
    {
	//add_action(help_case, "help");
	add_action(start_sort, "sort");

	/* from /lib/shop.c */
	add_action(do_list,  "list");
	add_action(do_show,  "show");
	add_action(do_value, "value");
    }
}

/*
 * Masked to not print a message.
 */
public void
shop_hook_appraise_object(object ob)
{
}

public void
shop_hook_value_asking(string str)
{
}
