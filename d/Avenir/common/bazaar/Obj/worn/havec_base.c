// file name:	/d/Avenir/common/bazaar/Obj/worn/havec_base.c
// creator(s):	Lucius Mar 2009
// purpose:	Base object for packs and sacks created by Havec.
/*
 * Revisions:
 *   Lucius    May 2009: Added 'discrete' option.
 *   Lucius    Jul 2011: Added plural_short masking.
 *   Lucius    Jun 2016: Added table mode display.
 *   Cotillion Jan 2018: Add a suffix to the added label name to 
 *                       prevent exploits.
 */
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include "havec.h"
#include <files.h>

public static int table;
public static string desc = "", style = "", fabric = "";
public static string label = "", discrete = "no";

public static mapping m_descs = ([
	"plain"       :  1,
	"rugged"      :  5,
	"light"       :  4,
	"heavy"       :  1,
	"embroidered" :  5,
	"sturdy"      :  6,
	"large"       :  7,
	"small"       :  2,
	"tooled"      :  9,
	"faded"       : 10,
	"travel-worn" : 10,
	"well-worn"   : 10,
	"dirty"       : 15,
	"tattered"    : 15,
	"practical"   :  5,
	"simple"      :  1,
]);
public static mapping m_fabrics = ([       
        "canvas"   :  5,
        "felt"     : 12,
        "homespun" :  6,
        "leather"  : 10,
        "suede"    :  9,
        "webcloth" : 15,
]);

public string * query_m_descs(void)	{ return m_indexes(m_descs);	}
public string * query_m_fabrics(void)	{ return m_indexes(m_fabrics);	}

public void set_desc(string str)	{ desc = str;		}
public void set_style(string str)	{ style = str;		}
public void set_fabric(string str)	{ fabric = str;		}

public string query_desc(void)		{ return desc;		}
public string query_style(void)		{ return style;		}
public string query_fabric(void)	{ return fabric;	}


public varargs string
short(object viewer)
{
    if (discrete == "yes")
	return ::real_short(viewer);

    return ::short(viewer);
}

public varargs string
plural_short(object viewer)
{
    string pshort;

    if (discrete == "yes")
	return container::plural_short(viewer);
    else
	return ::plural_short(viewer);
}


public string
label_name(string str)
{
    string suffix = query_name();
    if (!suffix) {
        suffix = "pack";
    }
    return str + "_" + suffix;
}

public string
extra_long(void)
{
    return "Avenir packs support additional syntaxes "+
	"through the 'avp' command.\nCurrent label is: "+
	(strlen(label) ? label_name(label) : "(none)") + ".  "+
	"Discrete: "+ discrete +".  Table mode: "+
	(table ? "on" : "off") +". ";
}

public void
set_long(mixed long)
{
    if (stringp(long))
	long += "@@extra_long@@";

    ::set_long(long);
}

public void
create_tailored(void)
{
    int value = BASE_VALUE;

    if (m_descs[desc]) {
	value += m_descs[desc] * 10;
    }
    if (m_fabrics[fabric]) {
	value += m_fabrics[fabric] * 10;
    }

    add_prop(OBJ_I_VALUE, value);
    set_adj(({ desc, fabric }));
}
  
public void
create_wearable_pack(void)
{
    set_keep(1);
    set_mass_storage(1); 

    add_adj("sybarun");

    add_prop(OBJ_I_WEIGHT, 200 + random(200));
    add_prop(OBJ_I_VOLUME, 400 + random(100));
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    add_item("tag", "A golden trefoil, the symbol of Sybarus, is "+
        "represented on the tag, as are the words:  \"Havec "+
        "Sackmaker\".  Use 'fill pack' to put items not worn or "+
        "kept in this pack.  Use 'empty pack' to remove all non-kept "+
        "and non-sellable items from your pack.  This pack can "+
        "be used to safely store herbs and magical components.\n");
}

public int
do_label(string arg)
{
    object env;

    if (!strlen(arg))
    {
        notify_fail("Label it what?\n");
        return 0;
    }

    if (sizeof(explode(arg, " ")) > 1)
    {
	write("Limit your label to a single word.\n");
	return 1;
    }

    remove_name(label_name(label));
    label = lower_case(arg);
    env = environment();

    if (label != "none")
    {
	add_name(label_name(label), 1);
	if (env && (env == this_player()))
	    write("You label your "+ short(TP) +" \""+ label_name(label) +"\".\n");
    }
    else
    {
	label = "";
	if (env && (env == this_player()))
	    write("You remove the labeling from your "+ short(TP) +".\n");
    }

    return 1;
}

public int
do_desc(string arg)
{
    if (strlen(arg))
	write("This is a toggled option, argument ignored.\n");

    if (discrete == "no")
    {
	discrete = "yes";
	write("The outwards appearance of the "+ short() +
	    " will now be MORE discrete.\n");
    }
    else
    {
	discrete = "no";
	write("The outwards appearance of the "+ short() +
	    " will now be LESS discrete.\n");
    }

    return 1;
}

public int
do_table(string str)
{
    if (!strlen(str))
	return NF("Turn table mode on or off for this "+ short() +"?\n");

    switch(lower_case(str))
    {
    case "on":
	if (table)
	{
	    write("Table mode is already enabled.\n");
	}
	else
	{
	    table = 1;
	    write("Enabled table display mode for the "+ short() +".\n");
	}
	break;
    case "off":
	if (!table)
	{
	    write("Table mode is already disabled.\n");
	}
	else
	{
	    table = 0;
	    write("Disabled table display mode for the "+ short() +".\n");
	}
	break;
    default:
	return NF("Turn table mode on or off for this "+ short() +"?\n");
    }

    return 1;
}


public nomask int
avenir_pack(void)	{ return 1; }

#define FAIL	"Valid command(s) are: label, discrete, table\n"

public int
bridge(string str)
{
    if (!strlen(str)) {
	return notify_fail(FAIL);
    }

    object obj;
    string cmd, what;

    /* Determine which pack. */
    if (sscanf(str, "%s for %s", str, what) == 2)
    {
	if (!parse_command(what, filter(all_inventory(TP),
		    &->avenir_pack()), "%o", obj))
	{
	    notify_fail("Do \""+ str +"\" for which avenir pack?\n");
	    return 0;
	}
    }

    if (!objectp(obj))
	obj = TO;

    function func;
    string *arr = explode(str, " ");
    str = (sizeof(arr) > 1 ? implode(arr[1..], " ") : "");

    switch(arr[0])
    {
    case "label":	func = obj->do_label;	break;
    case "discrete":	func = obj->do_desc;	break;
    case "table":	func = obj->do_table;	break;
    default:
	/* Shouldn't be reached normally. */
	return notify_fail(FAIL);
    }

    return func(str);
}

public void
init(void)
{
    ::init();
    add_action( bridge, "avp" );
}

public void
init_recover(string arg)
{
    sscanf(arg, "%s{D:%s}{S:%s}{F:%s}{L:%s}{I:%s}{T:%d}%s",
	arg, desc, style, fabric, label, discrete, table, arg);

    if (!strlen(fabric))
    { /* This should not happen... */
	remove_object();
	return;
    }

    init_container_recover(arg);
    create_tailored();

    if (strlen(label))
	do_label(label);
}

public string
query_recover(void)
{
    return MASTER + ":{D:" + desc	+ "}" +
		     "{S:" + style	+ "}" +
		     "{F:" + fabric	+ "}" +
		     "{L:" + label	+ "}" +
		     "{I:" + discrete	+ "}" +
		     "{T:" + table	+ "}" +
		     query_container_recover();
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
    if (!table && sizeof(selection))
        obarr -= selection;

    if (table)
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
    else if (table)
    {
        for_obj->catch_tell(HANGING_INDENT("Other   : " + comp + ".", 10, 0));
    }
}
