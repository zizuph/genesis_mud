#pragma strict_types
//  /bazaar/Obj/misc/qarraba.c
//  updated: Feb 29 2004, Lilith: added sort ability
//  updated: Dec 1, 2004, Lilith: per Serif, naming of herbs is a 
//                                possible balance issue, so removed.
//
//  * Lucius, Oct 2008: Almost entirely recoded to be more useful
//                      and beneficial to all.
//  * Lucius, Jan 2009: The REDUCE props shouldn't have been under 100.
//                      As leftovers are now heavier, increased value
//                      again to make them less cumbersome.
//  * Lucius, Mar 2009: Added options, 'for' syntax, weight estimate.
//  * Lucius, May 2009: Removed rigid prop to reduce volume problems.
//  			Reality will just have to take a back seat.
//  * Lucius, Aug 2011: Updated to use modified list code.
//  * Cotillion, Feb 2016: All added names will be followed by _qarraba
//  * Vyasa, Oct 2016: Fixed bug that didn't allow you to 'keep' it
//                     and players sold it by mistake when performing a 'sell all'.
//  * Lucius, Jul 2017: Re-coded display listing. Removed sort option.
//
//
inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>

#define TP  this_player()

#define QAUTO	0x01
#define QDARK	0x02
#define QOPT(Z) (Z & options)
#define QARRABA_SUFFIX "_qarraba"


private static int options;
private static string desc = "", label = "", last = "";
private static string *aold = ({}), *limit = ({}), *categories = ({
    "Food", "Drink", "Herb", "Corpse",
});
/* "name" : ({ binflag, "help text",
 * 	"optional prop", optional prop enable, optional prop disable
 */
private static mapping qopts = ([
	"autolist" : ({ QAUTO, "Auto list the contents of a qarraba "+
	    		"under examination as if 'qlist' were invoked.",
       			0, 0, 0,
	}),
	"blackout" : ({ QDARK, "Darken the qarraba -- or make it non-"+
		 	"transparent.",
			CONT_I_TRANSP, 0, 1,
       	}),
]);


public int
category(object ob)
{
    if (IS_HERB_OBJECT(ob))
	return 1;

#if 0
    // FALLS UNDER FOOD
    if (IS_LEFTOVER_OBJECT(ob))
	return 1;
#endif

    if (IS_FOOD_OBJECT(ob))
	return 1;

    if (IS_DRINK_OBJECT(ob))
	return 1;

    return 0;
}

public int
prevent_enter(object ob)
{
    if (category(ob))
	return 0;

    write("The "+ ob->short(TP) +
	" does not belong in the "+ real_short(TP) +".\n");

    return 1;
}

public void
create_container(void)
{
    if (!IS_CLONE)
	return;

    set_name("qarraba");
    add_name(({"_bazaar_component_jar_", "jar", "carboy"}));
    set_short("qarraba");
    set_adj(({"glass","wide-mouth","herb","herbal","sybarun"}));
    set_long("This qarraba, also known as a carboy, "+
       "is as lovely as it is functional. "+
       "It is a clear, wide-mouth glass vessel with a large glass and "+
       "cork stopper. The upper portion is hand-painted with vines "+
       "and blossoms interwoven with willow wands and serpents, "+
       "the symbols of Sachluph. The lower portion is cradled by a "+
       "basket made of thin strips of cured leather. Attached to it "+
       "is a strap so that the qarraba may be slung over one shoulder. "+
       "A stitched tag on the strap reads \"qhelp\". ");

    add_item(({"stopper", "cork", "cork stopper" }),
       "This stopper is roughly the size of your palm. It is "+
       "made of cork with a rounded glass handle. It fits "+
       "snugly in the mouth of the qarraba.\n");
    add_item(({"basket", "strips", "cured leather"}),
       "The basket of the qarraba is made of strips of "+
       "interwoven leather. It serves as a cradle that "+
       "both protects the qarraba and makes it easy to "+
       "carry as well.\n");
    add_item(({"strap"}),  "It is a simple loop of leather "+
       "that an arm can be slipped through so the qarraba "+
       "can be carried over the shoulder.\n");

    add_prop(CONT_I_IN,         1);
    add_prop(CONT_I_CLOSED,     1);
// Purposefully done, -Lucius
//    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     1);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    add_prop(CONT_I_WEIGHT,        500);
    add_prop(CONT_I_VOLUME,        500);
    add_prop(CONT_I_MAX_VOLUME,  50000);
    add_prop(CONT_I_MAX_WEIGHT,  50000);
    add_prop(CONT_I_REDUCE_VOLUME, 200);
    add_prop(CONT_I_REDUCE_WEIGHT, 200);
    add_prop(OBJ_I_VALUE, 50 + random(20));

    set_slots(A_ANY_SHOULDER);
    set_cf(this_object());
    set_looseness(10);
    set_layers(2);
    set_keep(1); 
}

public string
short(object for_obj)
{
    string res = (query_prop(CONT_I_CLOSED) ? "closed" : "open");

    if (strlen(desc))
	res += " " + desc;

    return res +" "+ ::real_short(for_obj);
}

public varargs string
long(string str, object for_obj)
{
    string desc = container::long(str, for_obj);

    if (!strlen(str))
    {
	desc += "It is currently "+ 
	    (query_prop(CONT_I_CLOSED) ? "closed" : "open");
    }

    return desc + ".\n";
}

public int
do_help(string str)
{
    if (strlen(str) && !id(str))
    {
	notify_fail("Qhelp what? The jar or qarraba perhaps?\n");
	return 0;
    }

    write("You can do 'qlist <category | item>' to display specific "+
	"types of items. This will only apply to the most recent "+
	"qarraba if you carry more than one.\n\n"+
	"You can 'qdesc <desc> [for <qarraba>]' to personalize "+
	"its description.\n\n"+
	"You may also 'qlabel <label> [for <qarraba>]' to add a "+
	"uniquely identifable name. A suffix of "+ QARRABA_SUFFIX +
	" will be automatically added.\n\n"+
	"Use 'none' to unset either the label or the desc.\n\n"+
	"Further options may be toggled using the 'qoption' command.\n"+
	"Currently the label is: "+
		(strlen(label) ? label  + QARRABA_SUFFIX: "(UNSET)") +"\n"+
	" Currently the desc is: "+
		(strlen(desc)  ? desc  : "(UNSET)") +"\n"+
	"   Current options are: ");

    string *sarr = ({});

    foreach(string opt, mixed data : qopts)
    {
	if (QOPT(data[0]))
	    sarr += ({ opt });
    }

    if (sizeof(sarr))
	write(COMPOSITE_WORDS(sort_array(sarr)) + "\n");
    else
	write("(NONE)\n");

    return 1;
}

public int
do_desc(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Describe it as what? Use 'qdesc <what>'.\n");
        return 0;
    }

    string *sarr = explode(lower_case(arg), " ");

    if (sizeof(sarr) > 3)
    {
	write("Limit your description to three words or less.\n");
	return 1;
    }

    remove_adj(aold);
    aold = sarr;
    desc = arg;

    if (desc != "none")
    {
	if (environment() && TP == environment())
	{
	    write("You describe your "+ real_short(TP) +
		" \""+ desc +"\".\n");
	}
	set_adj(sarr);
    }
    else
    {
	write("You undescribe your "+ short(TP) +".\n");
	desc = "";
    }

    return 1;
}

public int
do_label(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Label it what? Use 'qlabel <word>'.\n");
        return 0;
    }

    if (sizeof(explode(arg, " ")) > 1)
    {
	write("Limit your label to a single word.\n");
	return 1;
    }

    remove_name(label + QARRABA_SUFFIX);
    label = lower_case(arg);

    if (label != "none")
    {
	if (environment() && TP == environment())
	{
	    write("You label your "+ short(TP) +
		" \""+ label + QARRABA_SUFFIX + "\".\n");
	}
	add_name(label + QARRABA_SUFFIX, 1);
    }
    else
    {
	write("You remove the labeling from your "+ short(TP) +".\n");
	label = "";
    }

    return 1;
}

public int
do_option(string arg)
{
    if (!strlen(arg))
    {
	arg = "Available options are:\n";

	foreach(string opt : sort_array(m_indexes(qopts)))
	{
	    arg += sprintf("%15s : %-=60.60s\n",
		opt, qopts[opt][1]);
	}

	return notify_fail(arg);
    }

    arg = lower_case(arg);

    if (!qopts[arg])
    {
	return notify_fail("The "+ short(TP) +" does not "+
	    "support option \""+ arg +"\".\n");
    }

    mixed opt = qopts[arg];
    string str = "the option \""+ arg + "\" on the "+ short(TP);

    if (QOPT(opt[0]))
    {
	options ^= opt[0];
	arg = "You disable ";

	if (strlen(opt[2]))
	    add_prop(opt[2], opt[4]);
    }
    else
    {
	options |= opt[0];
	arg = "You enable ";

	if (strlen(opt[2]))
	    add_prop(opt[2], opt[3]);
    }

    write(arg + str + "\n");
    return 1;
}

public int
do_list(string arg)
{
    if (strlen(arg))
    {
	if (member_array(capitalize(arg), categories) != -1)
	{
	    limit = ({ capitalize(arg) });
	}
	else
	{
	    object *obarr = FIND_STR_IN_OBJECT(arg, this_object());

	    if (sizeof(obarr))
	    {
		describe_contents(this_player(), filter(obarr, visible));
		return 1;
	    }

	    notify_fail("Choose one of these categories to list by:\n    "+
		COMPOSITE_WORDS_WITH(categories, "or") + "\n");
	    return 0;
	}
    }

    ::show_visible_contents(TP);
    return 1;
}

private static mapping cache = ([]);

public void
cache_items(object item, object for_obj)
{
    if (cache[item])
	return;

    cache[item] = ({
	item->singular_short(for_obj),
	item->can_id_herb(for_obj),
	item->query_herb_name(),
    });
}

private int
sort_category(object a, object b)
{
    string one = cache[a][0],
	   two = cache[b][0];

    if (one < two)
	return -1;
    if (one > two)
	return 1;

    if (last == "Herb")
    {
	one = cache[a][2];
	two = cache[b][2];

	if (one < two)
	    return -1;
	if (one > two)
	    return 1;
    }

    return 0;
}

private string
describe_item(object item)
{
    if (cache[item][1])
	return "[" + cache[item][2] + "] " + cache[item][0];
    else
	return cache[item][0];
}

private object *
display_category(object *oblist, string cat, object for_obj)
{
    string res = "";

    if (!sizeof(oblist))
    {
	if (sizeof(limit))
	{
	    for_obj->catch_tell(sprintf("|%|6s|%|59s|%|8s|\n", "----",
		    "No items of that type found!", "None"));
	}
	return ({ });
    }

    if (!strlen(last))
	last = cat;

    if (last != cat)
    {
	last = cat;
	res += sprintf("|%6s|%59s|%8s|\n", "", "", "");
    }

    map(oblist, &cache_items(, for_obj));
    foreach(object item: sort_array(oblist, sort_category))
    {
	res += sprintf("| %4.4d | %-57.57s | %|6.6s |\n",
	    item->num_heap(), describe_item(item), cat); 
    }

    for_obj->catch_tell(res);
    return oblist;
}

public void
describe_contents(object for_obj, object *obarr)
{
    object *corpse;
    int size = sizeof(obarr);
    string *arr = categories;

    if (!size)
    {
	for_obj->catch_tell("The " + real_short() + " is empty.\n");
	return;
    }

    for_obj->catch_tell(sprintf(
	    "+%'-'76s\n|%|6s|%|59s|%|8s|\n+%'-'76s\n",
	    "+", "####", "Item Name", "Type", "+"));

    if (sizeof(limit))
	arr &= limit;

    foreach(string cat: arr)
    {
	switch(cat)
	{
	case "Food":
	    corpse = FILTER_LEFTOVER_OBJECTS(obarr); obarr -= corpse;
	    obarr -= display_category(FILTER_FOOD_OBJECTS(obarr), cat, for_obj);
	    break;
	case "Drink":
	    obarr -= display_category(FILTER_DRINK_OBJECTS(obarr), cat, for_obj);
	    break;
	case "Herb":
	    obarr -= display_category(FILTER_HERB_OBJECTS(obarr), cat, for_obj);
	    break;
	case "Corpse":
	    if (sizeof(corpse))
		display_category(corpse, cat, for_obj);
	    else
		obarr -= display_category(FILTER_LEFTOVER_OBJECTS(obarr), cat, for_obj);
	    break;
	}
    }

    cache = ([]);
    limit = ({});
    for_obj->catch_tell(sprintf(sprintf("+%'-'76s\n", "+")));
}

public void
show_visible_contents(object for_obj)
{
    if (QOPT(QAUTO) || query_verb() == "glance")
	::show_visible_contents(for_obj);
}

public nomask int
avenir_qarraba(void)	{ return 1; }

public int
bridge(string str)
{
    object obj;
    string what, verb = query_verb();

    if (strlen(str))
    {
	if (sscanf(str, "%s for %s", str, what) != 2)
	{
	    if (sscanf(str, "for %s", what))
	    {
		str = "";
	    }
	    else if (verb == "qlist")
	    {   // Special semantics for 'qlist'
		if (member_array(capitalize(str), categories) == -1)
		{
		    what = str;
		    str = "";
		}
	    }
	}

	if (strlen(what))
	{
	    object *obs = filter(all_inventory(TP), &->avenir_qarraba());
	    obj = PARSE_COMMAND_ONE(what, obs, "%i");

	    if (!objectp(obj))
	    {
		if (verb != "qlist")
		{
		    notify_fail("Do \""+ verb +"\" for which qarraba?\n");
		    return 0;
		}

		str = what;
	    }
	}
    }

    if (!objectp(obj))
	obj = this_object();

    function func;

    switch(verb)
    {
    case "qdesc":	func = obj->do_desc;	break;
    case "qlabel":	func = obj->do_label;	break;
    case "qlist":	func = obj->do_list;	break;
    case "qoption":	func = obj->do_option;	break;
    default: /* Shouldn't be reached normally. */
	notify_fail("Invalid command.\n");
	return 0;
    }

    return func(str);
}

query_recover()
{
     return MASTER + ":" + my_recover_args + query_container_recover();
}

void
init_recover(string arg)
{
    my_init_recover_code();
    init_container_recover(arg);
}
