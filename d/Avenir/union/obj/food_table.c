/* Table for food.
 *   Cirion 011398
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
#include <filter_funs.h>

#include "../defs.h"

object tablet, pen, vase, waters, *breads = ({});

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

public object *
largest_ten(object *obs)
{
    return sort_array(obs, special_sort)[0 .. min(2, sizeof(obs) - 1)];
}

public string
external_within(void)
{
    object *stuff;
    string str = " In the center of the room stands a kesoit table";

    stuff = FILTER_DEAD(all_inventory(TO));
    if (!sizeof(stuff))
	return str + ".";
    else if (sizeof(stuff) <= 5)
	return str + ", upon which lies " + COMPOSITE_DEAD(stuff) + ".";
    else
	return str + ", upon which many things are arranged, including "+
	    COMPOSITE_DEAD(largest_ten(stuff)) + ".";
}

/*
public string
within(void)
{
    object *stuff;

    if (!query_prop(CONT_I_CLOSED))
	return "";

    stuff = FILTER_DEAD(all_inventory(TO));
    if (!sizeof(stuff))
	return " The tabletop is bare.";
    else
	return " Lying atop the table is " + COMPOSITE_DEAD(stuff) + ".";
}
*/

public void
set_the_table(void)
{
    int size;

    if (!objectp(tablet))
    {
	tablet = clone_object(OBJ + "pad");
	tablet->move(TO, 1);
    }

    if (!objectp(pen))
    {
	pen = clone_object(BAZAAR + "Obj/misc/poet_pen");
	pen->randomize();
	pen->move(TO, 1);
    }

    // make a vase, fill it with flowers
    if (!objectp(vase))
    {
	object obj;

	vase = clone_object(OBJ + "vase");
	vase->move(TO, 1);

	size = random(2) + 1;
	while(size--)
	{
	    if (!catch(obj = clone_object(BAZAAR + "Obj/flower/single")))
	    {
		obj->set_colour(
		  one_of_list(({"black","blue","red","white"})));
		obj->set_type(one_of_list(
		    ({"aster","dragonflower","freesia","iris","orchid"})));
		obj->create_flower();
		obj->move(vase, 1);
	    }
	}
    }

    // provide some glasses of water
    if (!objectp(waters = present("_crucible_component")))
    {
	waters = clone_object(OBJ + "glass_of_water");
	waters->move(TO, 1);
    }

    waters->set_heap_size(random(2) + 2);

    // provide some loaves of bread
    breads->remove_object();
    size = random(4) + 2;
    breads = allocate(size);

    while(size--)
	breads[size] = clone_object(OBJ + "loaf");
    breads->move(TO, 1);
}

public void
describe_contents(object for_obj, object *obarr)
{
    do_list("all");
}


public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    force_new_list();
}


public void
create_container(void)
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name(({"table", "_union_table"}));
    set_adj(({"simple","kesoit","wood",}));
    set_short("simple kesoit table");
    set_long("A sturdy table, made of kesoit wood. In its "+
	"simplicity it is crafted with such precision that it looks "+
	"like it was made of a solid piece of wood.\n");
	//@@within@@ ");

    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 1934);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It does not move.\n");
    add_prop(CONT_I_ATTACH, 1);

    set_no_show_composite(1);
	
	set_maxlist(100);
    set_show_price(0);
    config_default_trade();
    set_store_room(file_name(TO));

    set_the_table();
	
	// Set options and initialize auto-save functionality
    set_enable_logging(0);
    set_enable_recovery(1);
    init_database();
    set_alarm(0.0, 0.0, recover_objects_from_database);
	

}

public int
prevent_enter(object ob)
{
    string dirty;

    if (!present(TP, ENV(TO)))
	return 0;

    if (living(ob))
    {
	TP->catch_msg(QCTNAME(ob) + " doesn't seem to want to be "+
	    "turned into a meal quite yet.\n");
	return 1;
    }

    if (ob->adjectiv_id("dirty"))
	dirty = "unclean";
    else if (ob->adjectiv_id("filthy"))
	dirty = "filthy";
    else if (ob->adjectiv_id("rotten"))
	dirty = "rotten";
    else if (ob->adjectiv_id("rancid"))
	dirty = "rancid";

    if (strlen(dirty))
    {
	write(CAP(dirty) + " things may not be placed upon the table.\n");
	return 1;
    }

    return 0;
}


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

#ifdef SHADOW
	ob->remove_union_shelf_shadow();
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
	return 1;
    }
	
    return 0;
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


public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP))
    {
	/* from /lib/shop.c */
	add_action(do_list,  "list");
	add_action(do_show,  "show");
	add_action(do_value, "value");
    }
}


