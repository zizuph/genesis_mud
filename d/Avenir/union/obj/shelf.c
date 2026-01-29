/*
 * shelf
 *   Cirion 011398
 *
 * Revisions:
 *   Lucius Mar 2005: Updated to use different list code
 *   Lucius May 2005: Added Friends tracking and shadowing
 * 		      of containers to stop a mudlib bug.
 *   Lucius Nov 2007: Changed logging code, also disabled it until needed.
 *   Petros Oct 2010: Added auto-save functionality for shelf items
 *   Lucius Jul 2011: Possible fix to 'strack' for auto-save recovery.
 *   Lucius Aug 2011: Updated to use modified list code
 *   Lucius Jun 2016: Modifed sorting to dump non-saving. Updated to
 *                    use configurable text blocks. Changed recovery
 *                    to auto-shuttle food/drinks to Salon table.
 *   Lucius Aug 2017: Give all Named Warriors access to 'strack'.
 *   Lilith Aug 2021: Increased capacity of rack.
 *
 */
#pragma strict_types

inherit "/std/container";
inherit "/d/Avenir/inherit/logrotate";
inherit "/d/Avenir/inherit/shop_list";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; // auto-save library

#include <files.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

#define MAX_SORT  500

#define LOGGING
#define SHELF_LOG_GET  (GUILDLOG + "shelf_get")
#define SHELF_LOG_PUT  (GUILDLOG + "shelf_put")

#define DONATE	"donate"
#define BORROW	"borrow"

/* mapping donate = ([
 *   (string)name: ([ (string)how: ({ ({ (string)what, (int)time, }), }), ]),
 * ]);
 */
private static mapping donate = ([]);
private static object *sorted, *foods = ({});
private static int alarm, food_alarm;


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
    object *obs = all_inventory(TO);
    int size = sizeof(obs);
    string str = " Along the east wall is a wide, sturdy shelf";

    if (!size)
	return str + ".";
    else if (size <= 5)
	return str + ", upon which lies " + COMPOSITE_DEAD(obs) + ".";
    else
    {
	obs = sort_array(obs, special_sort)[0..min(4, sizeof(obs) - 1)];
	return str + ", upon which many items have been stacked, "+
	"including "+ COMPOSITE_DEAD((obs)) + ".";
    }
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
	return " The shelf is bare.";

    do_list("all");
    return "";
}

public string
show_help(void)
{ 
    if (!IS_MEMBER(TP))
	return "";

    return " Your skilled eyes make out the "+
	"words 'help shelf' carved into the sturdy wood.";
}

public void
create_container(void)
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name(({"shelf", "_union_shelf"}));
    set_adj(({"east","wide","wood","sturdy"}));
    set_short("sturdy shelf");
    set_long("A wide shelf made of wood. It is quite deep and looks "+
      "like it is capable of carrying a good deal of weight without "+
      "bowing.@@show_help@@@@within@@\n");

    remove_prop(CONT_I_TRANSP);

    add_prop(CONT_I_MAX_WEIGHT, 6000000);
    add_prop(CONT_I_MAX_VOLUME, 6000000);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(OBJ_I_VALUE, 1934);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "It does not move.\n");

    set_maxlist(100);
    set_show_price(0);
    config_default_trade();
    set_store_room(file_name(TO));

    set_no_show_composite(1);

    // Set the options for auto-save and start the recovery
    set_enable_logging(0);
    set_enable_recovery(1);    
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());    
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

    if (from == this_object())
	return;

    if (!IS_CLONE)
	return;

    // auto-set keep flag
    ob->set_keep(1);
    // store the item for auto-save
    add_rack_entry(ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to == this_object() || !objectp(to))
	return;

    if (!IS_CLONE)
	return;

    // remove the item from auto-save list
    remove_rack_entry(ob);
}

public void
dump_donate(void)
{
    dump_mapping(donate);
}

public int
track_shelf(string str)
{
    string *arr;

    if (LEVEL(TP) < NORMAL)
	return 0;

    if (!strlen(str))
    {
	return NF("What exactly are you attemping to do?\n "+
	  "See 'help shelf' for proper usage.\n");
    }

    arr = explode(str, " ");
    if (sizeof(arr) == 1)
	arr += ({ (string)0 });

    switch(arr[0])
    {
    case "clear":
	if (!arr[1] || !donate[arr[1]])
	{
	    write("That individual doesn't appear to have used the shelf.\n");
	    return 1;
	}

	m_delkey(donate, arr[1]);
	write("Tracking information for \""+ CAP(arr[1]) +"\" cleared.\n");
	break;
    case "list":
	{
	    string *who = m_indices(donate);
	    int ix, size = sizeof(who);

	    if (!size)
	    {
		write("Nobody has made use of the shelf recently.\n");
		return 1;
	    }

	    write(CAP(LANG_NUM2WORD(size)) +
	      (size > 1 ? " people have" : " person has") +
	      " used the shelf:\n");

	    ix  = -1;
	    who = sort_array(who);

	    while(++ix < size)
	    {
		write(sprintf("%s (%s) has donated %d items while borrowing %d.\n",
		    CAP(who[ix]),
		    (FRIEND(who[ix]) ? "Friend" : "Outlander"),
		    sizeof(donate[who[ix]][DONATE]),
		    sizeof(donate[who[ix]][BORROW])));
	    }
	}
	break;
    default:
	{
	    string how;
	    mixed *items;
	    int ix, size, ln;

	    if (!donate[arr[0]])
	    {
		write(CAP(arr[0]) +" doesn't appear to have used the shelf.\n");
		return 1;
	    }

	    if (arr[1] == DONATE)
		how = "donated";
	    else if (arr[1] == BORROW)
		how = "borrowed";
	    else
	    {
		write("What information are you trying to query?\n"+
		  "See 'help shelf' for usage.\n");
		return 1;
	    }

	    ix = -1;
	    items = donate[arr[0]][arr[1]];
	    size = sizeof(items);
	    ln = strlen((size + 1) + "");

	    write(CAP(arr[0]) +" has "+ how +" the following items:\n");

	    while(++ix < size)
	    {
		write(sprintf("%*d) %s on %s\n",
		    ln, (ix + 1), items[ix][0], ctime(items[ix][1])));
	    }
	}
	break;
    }

    return 1;
}

private void
track_donate(object who, object what, string how)
{
    string name = who->query_real_name(), item = what->short();

    if (!donate[name])
	donate[name] = ([]);

    if (!donate[name][how])
	donate[name][how] = ({ });

    donate[name][how] += ({ ({ item, time() }) });
}

private void
food_recovery(void)
{
    food_alarm = 0;

    // Make sure we have some valid foods.
    if (!sizeof(foods = filter(foods, objectp)))
	return 0;

    // Load the Salon
    (ROOM + "lounge")->teleledningsanka();

    // Find the table in the Salon
    object table = present("salon:table", find_object(ROOM + "lounge"));

    // Error!
    if (!objectp(table))
	return;

    // Try to move nicely...
    foods = filter(foods, &->move(table));
    // But force if ncessary.
    foods->move(table, 1);
    // Empty array
    foods = ({ });
}

public int
prevent_enter(object ob)
{
    string dirty;

    if (living(ob))
    {
	TP->catch_msg(QCTNAME(ob) + " really shouldn't go there.\n");
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
    else if (ob->adjectiv_id("broken"))
	dirty = "broken";
    else if (ob->adjectiv_id("rancid"))
	dirty = "rancid";
    //    else if (ob->adjectiv_id("bloody"))
    //        dirty = "bloody";
    else if (ob->adjectiv_id("stinky"))
	dirty = "stinking";
    else if (ob->adjectiv_id("stinking"))
	dirty = "stinking";

    if (strlen(dirty))
    {
	if (this_interactive())
	    write(CAP(dirty) + " things may not be placed upon the shelf.\n");
	return 1;
    }

    if (IS_FOOD_OBJECT(ob) || IS_DRINK_OBJECT(ob))
    {
	if (this_interactive())
	{
	    write("Placing food on the shelf would defile it.\n");
	    return 1;
	} else {
	    // Auto-move foods during recovery
	    foods += ({ ob });
	    if (!food_alarm)
		food_alarm = set_alarm(1.0, 0.0, food_recovery);
	    return 0;
	}
    }

#ifdef SHADOW
    // Mudlib bug fixed.
    if (IS_CONTAINER_OBJECT(ob))
    {
	if (!ob->query_prop(CONT_I_CLOSED))
	    clone_object(SHADOW)->shadow_me(ob);
    }
#endif

    // Handle auto-recovery.
    if (!this_interactive())
	return 0;

    if (FRIEND(TP))
    {
	track_donate(TP, ob, DONATE);
#ifdef LOGGING
	logrotate(SHELF_LOG_PUT, ctime(time()) +": " +
	  TP->query_real_name() +" (friend) put "+
	  ob->short() +" in the shelf.\n");
#endif
    }
    else if (!IS_MEMBER(TP))
    {
	track_donate(TP, ob, DONATE);
#ifdef LOGGING
	logrotate(SHELF_LOG_PUT, ctime(time()) +": " +
	  TP->query_real_name() +" (outlander) put "+
	  ob->short() +" in the shelf.\n");
#endif
    }
    else
    {
#ifdef LOGGING
	logrotate(SHELF_LOG_PUT, ctime(time()) +": " +
	  TP->query_real_name() +" (union) put "+
	  ob->short() +" in the shelf.\n");
#endif
    }

    return 0;
}

/*
 * Function name: prevent_leave
 * Description:   only friends and union members may get items.
 */
public int
prevent_leave(object ob)
{
    // Avoid issues during recovery.
    if (!this_interactive())
	return 0;

    if (FRIEND(TP))
    {
	write("A shadow slides across your hand, making your "+
	  "fingers tingle uncomfortably.\nA voice caresses "+
	  "your mind:  Since you are a Friend of the Union, "+
	  "you may take what you like.\n");

	track_donate(TP, ob, BORROW);
#ifdef SHADOW
	ob->remove_union_shelf_shadow();
#endif
#ifdef LOGGING
	logrotate(SHELF_LOG_GET, ctime(time()) +": " +
	  TP->query_real_name() +" (friend) got "+
	  ob->short() +" from the shelf.\n");
#endif
	return 0;
    }
    else if (!IS_MEMBER(TP))
    {
	write("A shadow slides across your hand. It wraps "+
	  "around your wrist and squeezes so tightly that "+
	  "your fingers cannot grasp anything.\n "+
	  "You jerk your hand away from the shelf and its "+
	  "contents.\n");
	say(QCTNAME(TP)+" starts to reach for something on "+
	  "the "+ short()+", then "+HE(TP)+" jerks back "+
	  HIS(TP)+" hand in apparent pain.\n");

#ifdef LOGGING
	logrotate(SHELF_LOG_GET, ctime(time()) +": " +
	  TP->query_real_name() +" (outlander) tried to get "+
	  ob->short() +" from the shelf.\n");
#endif
	return 1;
    }
    else if (U_IS_PUNISHED(TP, U_PUNISHED_NOSHELF))
    {
	write("A shadow slides across your hand. It wraps "+
	  "around your wrist and squeezes so tightly that "+
	  "your fingers cannot grasp anything.\n "+
	  "A voice whips through your mind:  You dare defy "+
	  "the Will of the Elders?!\n"+
	  "You jerk your hand away from the case and its "+
	  "contents.\n");
	say(QCTNAME(TP)+" starts to reach for something in "+
	  "the "+ short()+", then "+HE(TP)+" jerks back "+
	  HIS(TP)+" hand in apparent pain.\n");

#ifdef LOGGING
	logrotate(SHELF_LOG_GET, ctime(time()) +": " +
	  TP->query_real_name() +" (union) tried to get "+
	  ob->short() +" from the shelf.\n");
#endif
	return 1;
    }

#ifdef SHADOW
    ob->remove_union_shelf_shadow();
#endif
#ifdef LOGGING
    logrotate(SHELF_LOG_GET, ctime(time()) +": " +
      TP->query_real_name() +" took "+
      ob->short() +" from the shelf.\n");
#endif
    return 0;
}

/*
 * Function name: finish_sort
 * Description  : 
 */
private void
finish_sort(void)
{
    alarm = 0;

    if (query_prop(CONT_I_CLOSED))
	return;

    filter(sorted, &->move(environment()));
    sorted = 0;

    tell_room(environment(),
	"Everything that doesn't save falls off.\n");
}

public int
start_sort(string arg)
{
    if (arg != "shelf")
    {
	notify_fail("Sort what? The shelf?\n");
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

    write("You start sorting the shelf.\n");
    say(QCTNAME(this_player()) +" starts sorting the shelf.\n");

    sorted = filter(arr, &->check_recoverable()) +
    filter(arr, &->query_auto_load());
    sorted = arr - sorted;
    alarm = set_alarm(0.5, 0.0, &finish_sort(arr));

    return 1;
}

public int 
help_shelf(string str)
{
    if (str != "shelf" && str != "here")
	return notify_fail("Help what? Help shelf?\n");

    str = LIST->query_union_text("shelf_help");

    if (!strlen(str))
	write("There seems to be no help available.\n");
    else
	write(str);

    if (LEVEL(TP) >= NORMAL)
    {
	write("\nAdditional commands for Warriors:\n\n"+
	  "* strack list                     -=-  " +
	  "List who has used the shelf.\n"+
	  "* strack clear <who>              -=-  " +
	  "Clear current information on <who>.\n"+
	  "* strack <who> <donate | borrow>  -=-  " +
	  "List what <who> has placed or taken.\n");
    }

    return 1;
}

public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP))
    {
	add_action(help_shelf,  "help");
	add_action(start_sort,  "sort");
	add_action(track_shelf, "strack");

	/* from /lib/shop.c */
	add_action(do_list,  "slist");
	add_action(do_show,  "sshow");
	add_action(do_value, "svalue");
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
